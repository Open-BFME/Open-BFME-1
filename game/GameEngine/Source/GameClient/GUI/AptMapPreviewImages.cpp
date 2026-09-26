// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include

// AptMapPreview image loading (0x00520BB0, 431 bytes) and selection
// (0x00520E70, 185 bytes) share the same Image model and compile settings.
// The descriptive _bfme_ name does not claim an original source spelling.
// AptMapPreview's image selection caller at 0x00520E70 passes a map-name
// string at MapMetaData+0x50, owns the returned Image at preview+0x34, and
// falls back to the mapped image "MissingMap" when no picture is available.
//
// The Image layout and UV/size operations follow GameClient/Image.h; the
// filename is the map path with its four-character extension replaced by
// "_pic.tga". String and coordinate types use their canonical headers.
// The address-derived Rva0044F4D0 is an existing one-pointer texture-owner
// ABI shim. Its int argument carries a filename pointer on this 32-bit target.
//
#include "ascii_string.h"
#include "basetype.h"

// Existing canonical implementation from string_base.cpp, kept visible for
// the retail inlined accessor; the class itself comes from string_base.h.
template <typename T>
inline const T *StringBase<T>::str() const
{
    return m_data ? &m_data->data[0] : (const T *)"";
}

typedef unsigned int size_t;
void *__cdecl operator new(size_t);
void __cdecl operator delete(void *);

class GlobalData;
extern GlobalData *TheWritableGlobalData;

class FileSystem
{
public:
    bool doesFileExist(const char *) const;
};
extern FileSystem *TheFileSystem;

class TextureClass
{
public:
    void Release_Ref();
};

class Rva0044F4D0
{
public:
    Rva0044F4D0(int name);
    ~Rva0044F4D0() { if (m_texture) m_texture->Release_Ref(); }
private:
    TextureClass *m_texture;
};

class Image
{
public:
    Image();
    virtual ~Image();
    void setName(AsciiString name);
    void setFilename(AsciiString name);
    void _bfme_setTexture(const Rva0044F4D0 &texture);
    unsigned int setStatus(unsigned int bit);
    void setUV(Region2D *uv) { if (uv) m_uv = *uv; }
    void setTextureHeight(int height) { m_textureHeight = height; }
    void setTextureWidth(int width) { m_textureWidth = width; }
private:
    AsciiString m_name;
    AsciiString m_filename;
    int m_textureWidth;
    int m_textureHeight;
    Region2D m_uv;
    int m_imageWidth;
    int m_imageHeight;
    Rva0044F4D0 *m_texture;
    unsigned int m_status;
};


Image *_bfme_createMapPictureImage(const AsciiString &mapName)
{
    if (!TheWritableGlobalData)
        return 0;

    AsciiString pictureName = mapName;
    pictureName.removeLastChar();
    pictureName.removeLastChar();
    pictureName.removeLastChar();
    pictureName.removeLastChar();
    reinterpret_cast<StringBase<char> *>(&pictureName)->concat("_pic.tga", 8);

    Image *image = 0;
    if (TheFileSystem->doesFileExist(pictureName.str()))
    {
        image = new Image;
        image->setName(pictureName);
        image->setFilename(pictureName);
        image->_bfme_setTexture(Rva0044F4D0((int)pictureName.str()));
        image->setStatus(2);
        Region2D uv;
        uv.lo.x = 0.0f;
        uv.lo.y = 0.0f;
        uv.hi.x = 1.0f;
        uv.hi.y = 1.0f;
        image->setUV(&uv);
        image->setTextureHeight(128);
        image->setTextureWidth(128);
    }
    return image;
}

// Selection owns a freshly created map image and borrows the fallback.
class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;
extern Image *createMapPictureImage(const AsciiString &mapName);

#pragma comment(linker, "/alternatename:?createMapPictureImage@@YAPAVImage@@ABVAsciiString@@@Z=?j_0004032c@@YAXXZ")
#pragma comment(linker, "/alternatename:?findImageByName@MappedImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z=?j_0001d606@@YAXXZ")

class MapMetaData
{
private:
	char m_unmodelled[0x50];

public:
	AsciiString m_mapName;
};

class AptMapPreview
{
public:
	void bfmeSetMapPicture(MapMetaData *map);

private:
	char m_unmodelled[0x34];
	const Image *m_picture;
	bool m_pictureOwned; // created map image is owned; MissingMap fallback is borrowed
};

void AptMapPreview::bfmeSetMapPicture(MapMetaData *map)
{
	if (m_pictureOwned)
	{
		if (m_picture)
		{
			delete m_picture;
			m_picture = 0;
		}
	}

	Image *picture = reinterpret_cast<Image *>(map);
	if (map)
	{
		picture = createMapPictureImage(map->m_mapName);
		m_pictureOwned = true;
	}
	if (!picture)
	{
		{
			AsciiString missingMap("MissingMap");
			picture = (Image *)TheMappedImageCollection->findImageByName(missingMap);
		}
		m_pictureOwned = false;
	}
	m_picture = picture;
}
