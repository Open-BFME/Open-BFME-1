// ?bfmeSetMapImage@AptMapPreview@@QAEXPAVMapMetaData@@@Z
// partial score=0.42 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x00521390 (591 bytes).  The 0x005216B0 caller passes this
// object and MapMetaData through the same map-preview update family as the
// already named title, description, and picture setters.  The map filename
// is the AsciiString at MapMetaData + 0x50.
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	bool endsWithNoCase(const T *suffix) const;

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	const char *str(void) const { return m_data ? m_data->m_text : ""; }
};

class Image
{
public:
	AsciiString getFilename(void) const;
};

// Image::getFilename is an existing BFME body reached by its ILT.
#pragma comment(linker, "/alternatename:?getFilename@Image@@QBE?AVAsciiString@@XZ=?j_000336ae@@YAXXZ")

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

#pragma comment(linker, "/alternatename:?findImageByName@MappedImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z=?j_0001d606@@YAXXZ")

class GameWindow
{
public:
	int winSetEnabledImage(int index, const Image *image);
	void winSetUserData(void *userData);
	unsigned int winSetStatus(unsigned int status);
	unsigned int winClearStatus(unsigned int status);
};

#pragma comment(linker, "/alternatename:?winSetEnabledImage@GameWindow@@QAEHHPBVImage@@@Z=?j_00035e09@@YAXXZ")
#pragma comment(linker, "/alternatename:?winSetUserData@GameWindow@@QAEXPAX@Z=?j_00002e69@@YAXXZ")
#pragma comment(linker, "/alternatename:?winSetStatus@GameWindow@@QAEII@Z=?j_00033523@@YAXXZ")
#pragma comment(linker, "/alternatename:?winClearStatus@GameWindow@@QAEII@Z=?j_00027b24@@YAXXZ")

class MapMetaData
{
private:
	char m_unmodelled[0x50];

public:
	AsciiString m_mapName;
};

extern Image *getMapPreviewImage(AsciiString mapName);

// The map-preview lookup is an existing body whose caller uses its ILT.
#pragma comment(linker, "/alternatename:?getMapPreviewImage@@YAPAVImage@@VAsciiString@@@Z=?j_0001fc8f@@YAXXZ")

class AptMapPreview
{
public:
	void bfmeSetMapImage(MapMetaData *map);
	void bfmeSetMapPlayerSlots(MapMetaData *map);

private:
	char m_unmodelled[4];
	GameWindow *m_mapImage;
};

// The adjacent map-preview player-slot updater is an existing retail body.
#pragma comment(linker, "/alternatename:?bfmeSetMapPlayerSlots@AptMapPreview@@QAEXPAVMapMetaData@@@Z=?j_00016239@@YAXXZ")

#define BFME_MAP_PREVIEW_FLAGS (*(unsigned int *)0x012F49CC)
#define BFME_MAP_PREVIEW_NULL_IMAGE (*(Image **)0x012F49C8)
#define BFME_MAP_PREVIEW_MISSING_IMAGE (*(Image **)0x012F49C4)

void AptMapPreview::bfmeSetMapImage(MapMetaData *map)
{
	if (m_mapImage)
	{
		m_mapImage->winSetEnabledImage(1, 0);

		if (!map)
		{
			m_mapImage->winSetUserData(0);

			if ((BFME_MAP_PREVIEW_FLAGS & 1) == 0)
			{
				BFME_MAP_PREVIEW_FLAGS |= 1;
				AsciiString missingMap("MissingMap");
				BFME_MAP_PREVIEW_NULL_IMAGE =
					(Image *)TheMappedImageCollection->findImageByName(missingMap);
			}

			if (BFME_MAP_PREVIEW_NULL_IMAGE)
				m_mapImage->winSetStatus(0x80);
			else
				m_mapImage->winClearStatus(0x80);

			m_mapImage->winSetEnabledImage(0, BFME_MAP_PREVIEW_NULL_IMAGE);
		}
		else
		{
			Image *image = getMapPreviewImage(map->m_mapName);
			bool showScrollShroud = false;

			if (image)
			{
				AsciiString filename = image->getFilename();
				showScrollShroud =
					reinterpret_cast<const StringBase<char> *>(&filename)
						->endsWithNoCase("_art.tga");
			}

			if (showScrollShroud)
			{
				AsciiString scrollShroud("ScrollShroud");
				m_mapImage->winSetEnabledImage(
					1, TheMappedImageCollection->findImageByName(scrollShroud));
			}

			m_mapImage->winSetUserData(map);

			if (image)
			{
				m_mapImage->winSetStatus(0x80);
				m_mapImage->winSetEnabledImage(0, image);
			}
			else
			{
				if ((BFME_MAP_PREVIEW_FLAGS & 2) == 0)
				{
					BFME_MAP_PREVIEW_FLAGS |= 2;
					AsciiString missingMap("MissingMap");
					BFME_MAP_PREVIEW_MISSING_IMAGE =
						(Image *)TheMappedImageCollection->findImageByName(missingMap);
				}

				if (BFME_MAP_PREVIEW_MISSING_IMAGE)
					m_mapImage->winSetStatus(0x80);
				else
					m_mapImage->winClearStatus(0x80);

				m_mapImage->winSetEnabledImage(0,
					BFME_MAP_PREVIEW_MISSING_IMAGE);
			}
		}
	}

	bfmeSetMapPlayerSlots(map);
}
