#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include "stb_truetype.h"
#include "CommonTypes.h"
#include <fstream>

class Texture {
    private:
    int width;
    int height;

    const int fileHeaderSize = 14;
    const int infoHeaderSize = 40;

    unsigned char* createBitmapFileHeader(int height, int width, int pitch, int paddingSize) {
        int fileSize = fileHeaderSize + infoHeaderSize + (pitch + paddingSize) * height;

        static unsigned char fileHeader[] = {
            0,0, /// signature
            0,0,0,0, /// image file size in bytes
            0,0,0,0, /// reserved
            0,0,0,0, /// start of pixel array
        };

        fileHeader[0] = (unsigned char)('B');
        fileHeader[1] = (unsigned char)('M');
        fileHeader[2] = (unsigned char)(fileSize);
        fileHeader[3] = (unsigned char)(fileSize >> 8);
        fileHeader[4] = (unsigned char)(fileSize >> 16);
        fileHeader[5] = (unsigned char)(fileSize >> 24);
        fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

        return fileHeader;
    }

    unsigned char* createBitmapInfoHeader(int height, int width) {
        static unsigned char infoHeader[] = {
            0,0,0,0, /// header size
            0,0,0,0, /// image width
            0,0,0,0, /// image height
            0,0, /// number of color planes
            0,0, /// bits per pixel
            0,0,0,0, /// compression
            0,0,0,0, /// image size
            0,0,0,0, /// horizontal resolution
            0,0,0,0, /// vertical resolution
            0,0,0,0, /// colors in color table
            0,0,0,0, /// important color count
        };

        infoHeader[0] = (unsigned char)(infoHeaderSize);
        infoHeader[4] = (unsigned char)(width);
        infoHeader[5] = (unsigned char)(width >> 8);
        infoHeader[6] = (unsigned char)(width >> 16);
        infoHeader[7] = (unsigned char)(width >> 24);
        infoHeader[8] = (unsigned char)(height);
        infoHeader[9] = (unsigned char)(height >> 8);
        infoHeader[10] = (unsigned char)(height >> 16);
        infoHeader[11] = (unsigned char)(height >> 24);
        infoHeader[12] = (unsigned char)(1);
        infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);

        return infoHeader;
    }

    public:
    unsigned char* data;

    Texture(int width, int height) {
        this->width = width;
        this->height = height;
        data = new unsigned char[width * height * BYTES_PER_PIXEL];
    }
    
    ~Texture() {
        delete data;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    static void flipYAxis(Texture* texture) {
        unsigned char* newData = new unsigned char[texture->width * texture->height * BYTES_PER_PIXEL];
        for (int y = 0; y != texture->height; y++) {
            for (int x = 0; x != texture->width; x++) {
                int numberOfCharacterInWidth = texture->width * BYTES_PER_PIXEL;
                int pixelPosition = y * numberOfCharacterInWidth + x * BYTES_PER_PIXEL;
                
                int oppositelPosition = (texture->height - y-1) * numberOfCharacterInWidth  + x * BYTES_PER_PIXEL;

                newData[pixelPosition + 0] = texture->data[oppositelPosition + 0];
                newData[pixelPosition + 1] = texture->data[oppositelPosition + 1];
                newData[pixelPosition + 2] = texture->data[oppositelPosition + 2];
                newData[pixelPosition + 3] = texture->data[oppositelPosition + 3];

            }
        }
        texture->data = newData;
    }

    static Texture* createSquareTexture(const int width, const int height, const Colour colour) {
        Texture* texture = new Texture(width, height);
        for (int y = 0; y != height; y++) {
            for (int x = 0; x != width; x++) {
                int numberOfCharacterInWidth = width * BYTES_PER_PIXEL;
                int pixelPosition = y * numberOfCharacterInWidth + x * BYTES_PER_PIXEL;
                texture->data[pixelPosition + 0] = colour.getRedChar();
                texture->data[pixelPosition + 1] = colour.getGreenChar();
                texture->data[pixelPosition + 2] = colour.getBlueChar();
                texture->data[pixelPosition + 3] = colour.getAlphaChar();
            }
        }
        return texture;
    }

    // FIXME, think about this location
    static void drawText(Texture* newTexture, const stbtt_fontinfo font, int fontSize, std::string text) {
        unsigned char* bitmap = newTexture->data;

        int height = newTexture->height;
        int width = newTexture->width;
        float scale = stbtt_ScaleForPixelHeight(&font, fontSize);
        int ascent = 0;
        int decent = 0;
        int lineGap = 0;

        stbtt_GetFontVMetrics(&font, &ascent, &decent, &lineGap);
        int totalHeight = ascent + decent + lineGap; // ascent hight of character above 'baseline' decent hieght of character below. lineGap = space between lines. 

        int fullLength; 
        int baseline = ascent*scale;

        int xCursor = 0;
        for (uint i = 0; i != text.size(); i++) {
            int advance; // width of character including font padding. Yup font are pretentious. 
            int leftSideBearing; // left margin essentially.
            int x0, y0; // top left corner? 
            int x1, y1; // bottom right corner?

            stbtt_GetCodepointHMetrics(&font, text[i], &advance, &leftSideBearing);
            stbtt_GetCodepointBitmapBox(&font, text[i], scale, scale, &x0, &y0, &x1, &y1);

            int y = ascent + y1;
            int byteOffset = xCursor + x0 + (y * width);

            stbtt_MakeCodepointBitmap(&font,
                                        bitmap + byteOffset,
                                        BYTES_PER_PIXEL*(x1-x0),
                                        BYTES_PER_PIXEL*(y1-y0),
                                        width*BYTES_PER_PIXEL,
                                        2*scale, 
                                        scale,
                                        text[i]);

            xCursor += (advance * scale) + x1;
        }

        // newTexture->data
        // FIXME, weird hacky stuff is happening because of this.
        Texture::flipYAxis(newTexture);
    }

    void setColourToColour(const Colour from, const Colour to) {
        for (int y = 0; y != this->height; y++) {
            for (int x = 0; x != this->width; x++) {
                int numberOfCharacterInWidth = this->width * BYTES_PER_PIXEL;
                int pixelPosition = y * numberOfCharacterInWidth + x * BYTES_PER_PIXEL;
                
                if (from.red == this->data[pixelPosition + 0] && 
                    from.green == this->data[pixelPosition + 1] && 
                    from.blue == this->data[pixelPosition + 2] && 
                    from.alpha == this->data[pixelPosition + 3]) 
                {
                    this->data[pixelPosition + 0] = to.red;
                    this->data[pixelPosition + 1] = to.green;
                    this->data[pixelPosition + 2] = to.blue;
                    this->data[pixelPosition + 3] = to.alpha;
                }
            }
        }
    }

    void saveAsBitmapImage(const char* imageFileName) {
        unsigned char padding[3] = { 0, 0, 0 };
        int pitch = width * BYTES_PER_PIXEL;
        int paddingSize = (4 - pitch % 4) % 4;

        unsigned char* fileHeader = createBitmapFileHeader(height, width, pitch, paddingSize);
        unsigned char* infoHeader = createBitmapInfoHeader(height, width);
         std::cout << "test\n";

        FILE* imageFile = fopen(imageFileName, "wb");

        fwrite(fileHeader, 1, fileHeaderSize, imageFile);
        fwrite(infoHeader, 1, infoHeaderSize, imageFile);

        for (int y = 0; y < height; y++) {
            fwrite(data + (y*width*BYTES_PER_PIXEL), BYTES_PER_PIXEL, width, imageFile);
            fwrite(padding, 1, paddingSize, imageFile);
        }

        fclose(imageFile);
    }

    friend std::ostream& operator<<(std::ostream& os, const Texture& texture) {
        os << "Texture COLOUR{r: " << (int)texture.data[0] << ", g:" << (int)texture.data[1] << ", b:" << (int)texture.data[2] << "alpha:" << (int)texture.data[3] << "}";
        return os;
    }
};

#endif