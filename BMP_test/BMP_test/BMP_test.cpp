#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

#pragma pack(push, 1) // сохраняет текущие настройки выравнивания и устанавливает выравнивание в 1 байт
struct BITMAPFILEHEADER 
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
struct BITMAPINFOHEADER 
{
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop) // восстанавливает предыдущие настройки выравнивания после определения структур

int main(int argc, char* argv[]) 
{
    const char* input_file = argv[1];
    const char* output_file = argv[2];

    ifstream in(input_file, ios::binary);
    if (!in) 
    {
        cout << "Cannot open input file";
        return 1;
    }

    ofstream out(output_file, ios::binary);

    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;

    in.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    if (!in) 
    {
        cout << "Error reading BMP file header";
        return 1;
    }

    if (file_header.bfType != 0x4D42) 
    {
        cout << "Not a BMP file";
        return 1;
    }

    in.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    if (!in) 
    {
        cout << "Error reading BMP info header";
        return 1;
    }

    if (info_header.biBitCount != 24) 
    {
        cout << "Only 24-bit BMP files are supported";
        return 1;
    }

    int width = info_header.biWidth;
    int height = info_header.biHeight;
    bool top_down = false;
    if (height < 0) 
    {
        height = -height;
        top_down = true;
    }

    const int row_padded = (width * 3 + 3) & ~3;
    vector<uint8_t> pixels(row_padded * height);

    in.seekg(file_header.bfOffBits, ios::beg);
    in.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
    if (!in) 
    {
        cout << "Error reading pixel data";
        return 1;
    }

    for (int i = 3; i < argc; i += 6) 
    {
        int x1 = atoi(argv[i]);
        int y1 = atoi(argv[i + 1]);
        int x2 = atoi(argv[i + 2]);
        int y2 = atoi(argv[i + 3]);
        char channel = toupper(argv[i + 4][0]);
        float intensity = atof(argv[i + 5]);

        if (channel != 'R' && channel != 'G' && channel != 'B') 
        {
            cout << "Invalid channel: " << channel;
            continue;
        }

        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        x1 = max(0, min(x1, width - 1));
        x2 = max(0, min(x2, width - 1));
        y1 = max(0, min(y1, height - 1));
        y2 = max(0, min(y2, height - 1));

        for (int y = y1; y <= y2; ++y) 
        {
            int data_y = top_down ? y : (height - 1 - y);
            for (int x = x1; x <= x2; ++x) 
            {
                int pos = data_y * row_padded + x * 3;

                switch (channel) {
                case 'B':
                    pixels[pos] = static_cast<uint8_t>(min(255.0f, max(0.0f, pixels[pos] * intensity)));
                    break;
                case 'G':
                    pixels[pos + 1] = static_cast<uint8_t>(min(255.0f, max(0.0f, pixels[pos + 1] * intensity)));
                    break;
                case 'R':
                    pixels[pos + 2] = static_cast<uint8_t>(min(255.0f, max(0.0f, pixels[pos + 2] * intensity)));
                    break;
                }
            }
        }
    }

    out.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    out.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    out.seekp(file_header.bfOffBits, ios::beg);
    out.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());

    if (!out) 
    {
        cout << "Error writing output file";
        return 1;
    }

    return 0;
}