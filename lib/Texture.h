#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include "stb_truetype.h"
#include "CommonTypes.h"

class Texture {
    public:
    unsigned char* data;
    int width;
    int height;

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
        Texture* texture = new Texture();
        unsigned char* bitmap = new unsigned char[width * height * BYTES_PER_PIXEL];
        for (int y = 0; y != height; y++) {
            for (int x = 0; x != width; x++) {
                int numberOfCharacterInWidth = width * BYTES_PER_PIXEL;
                int pixelPosition = y * numberOfCharacterInWidth + x * BYTES_PER_PIXEL;
                bitmap[pixelPosition + 0] = colour.getRedChar();
                bitmap[pixelPosition + 1] = colour.getGreenChar();
                bitmap[pixelPosition + 2] = colour.getBlueChar();
                bitmap[pixelPosition + 3] = colour.getAlphaChar();
            }
        }
        texture->data = bitmap;
        texture->width = width;
        texture->height = height;
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
        // FIXME, weird hacky stuff is happening because of this.
        Texture::flipYAxis(newTexture);
    }

    friend std::ostream& operator<<(std::ostream& os, const Texture& texture) {
        os << "Texture COLOUR{r: " << (int)texture.data[0] << ", g:" << (int)texture.data[1] << ", b:" << (int)texture.data[2] << "alpha:" << (int)texture.data[3] << "}";
        return os;
    }
};

#endif