// cl: /DNDEBUG /MD /EHsc

#include "../../../../../reference/shims/stringinline/StringInline.h"

// Image vtable 0x0110FFEC slot zero is the scalar-deleting destructor
// at 0x005D2BD0; retail passes deletion flag 1, not a release count.
class Image
{
public:
	virtual ~Image();
};

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
