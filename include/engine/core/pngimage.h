#ifndef _ENGINE_PNG_IMAGE_H_
#define _ENGINE_PNG_IMAGE_H_

#include <string>
#include <vector>
#include <png.h>

namespace zi
{
    class PngImage
    {
    public:
        PngImage(void);
        PngImage(std::string filePath);
        virtual ~PngImage(void);
        
        void load(std::string filePath);
        void crop(int x, int y, int width, int height);
        std::vector<png_byte> cropCopy(int x, int y, int width, int height);
        
        std::vector<png_byte> inline getData(void) { return m_imageData; };
        int inline getWidth(void) { return m_width; };
        int inline getHeight(void) { return m_height; };
        
    private:
        std::vector<png_byte> m_imageData;
        int m_width;
        int m_height;
    };
}

#endif // _ENGINE_PNG_IMAGE_H_
