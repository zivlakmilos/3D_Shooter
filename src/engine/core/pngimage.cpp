#include "engine/core/pngimage.h"

#include <png.h>
#include "engine/errors/errors.h"
#include "engine/core/memory/memory.h"

/*
 * TODO:
 *  Can (must) be inheritence from BaseCResourceHandler
 */
class PngStructHandler
{
public:
    PngStructHandler(void)
        : m_pStruct(NULL),
          m_pInfo1(NULL),
          m_pInfo2(NULL) {};
    virtual ~PngStructHandler(void)
    {
        png_destroy_read_struct(m_pStruct,
                                m_pInfo1,
                                m_pInfo2);
    };
    
    void inline setStruct(png_structpp pStruct) { m_pStruct = pStruct; };
    void inline setInfo1(png_infopp pInfo) { m_pInfo1 = pInfo; };
    void inline setInfo2(png_infopp pInfo) { m_pInfo2 = pInfo; };
    
private:
    png_structpp m_pStruct;
    png_infopp m_pInfo1;
    png_infopp m_pInfo2;
};

zi::PngImage::PngImage(void)
{
}

zi::PngImage::PngImage(std::string filePath)
{
    try {
        load(filePath);
    } catch(zi::ZException ex) {
        throw ex;
    }
}

zi::PngImage::PngImage(std::vector<png_byte> imageData, int width, int height)
{
    m_imageData = imageData;
    m_width = width;
    m_height = height;
}

zi::PngImage::~PngImage(void)
{
}

void zi::PngImage::load(std::string filePath)
{
    char header[8];
    PngStructHandler pngHandler;
    
    FILE *fd = fopen(filePath.c_str(), "rb");
    if(!fd)
        throw zi::ZException("Can't open PNG file \"" + filePath + "\"");
    zi::CFileHandler fileHandler(fd);
    
    fread(header, 1, 8, fd);
    
    if(png_sig_cmp((png_bytep) header, 0, 8))
        throw zi::ZException("File is not a PNG image");
    
    png_structp pPng = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!pPng)
        throw zi::ZException("Can't create PNG struct");
    pngHandler.setStruct(&pPng);
    
    png_infop pInfo = png_create_info_struct(pPng);
    if(!pInfo)
        throw zi::ZException("Can't create PNG info struct");
    pngHandler.setInfo1(&pInfo);
    
    png_infop pEndInfo = png_create_info_struct(pPng);
    if(!pInfo)
        throw zi::ZException("Can't create PNG info struct");
    pngHandler.setInfo1(&pEndInfo);
    
    if(setjmp(png_jmpbuf(pPng)))
        throw zi::ZException("Error while loading PNG");
    
    png_init_io(pPng, fd);
    png_set_sig_bytes(pPng, 8);
    png_read_info(pPng, pInfo);
    
    int bitDepth, colorType;
    png_uint_32 width, height;
    
    png_get_IHDR(pPng, pInfo, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);
    m_width = width;
    m_height = height;
    
    png_read_update_info(pPng, pInfo);
    int rowBytes = png_get_rowbytes(pPng, pInfo);
    
    m_imageData.resize(rowBytes * height);
    
    std::vector<png_bytep> rowPointers(m_height);
    
    int i;
    for(i = 0; i < height; i++)
        rowPointers[height - 1 - i] = &m_imageData[0] + i * rowBytes;
    
    png_read_image(pPng, &rowPointers[0]);
}

void zi::PngImage::crop(int x, int y, int width, int height)
{
    try {
        m_imageData = cropData(x, y, width, height);
        m_width = width;
        m_height = height;
    } catch(zi::ZException ex) {
        throw ex;
    }
}

zi::PngImage zi::PngImage::cropCopy(int x, int y, int width, int height)
{
    std::vector<png_byte> dstData;
    
    try {
        dstData = cropData(x, y, width, height);
    } catch(zi::ZException ex) {
        throw ex;
    }
    
    return zi::PngImage(dstData, width, height);
}

std::vector<png_byte> zi::PngImage::cropData(int x, int y, int width, int height)
{
    if(x + width > m_width ||
       y + height > m_height ||
       x < 0 ||
       y < 0)
        throw zi::ZException("Can't crop, rectangle not in image");
    
    std::vector<png_byte> dstData;
    
    for(int i = y * 4; i < y + height * 4; i += 4)
    {
        for(int j = x * 4; j < x + width * 4; j += 4)
        {
            int pos = i * m_width + j;
            for(int k = 0; k < 4; k++)
                dstData.push_back(m_imageData[pos + k]);
        }
    }
    
    return dstData;
}
