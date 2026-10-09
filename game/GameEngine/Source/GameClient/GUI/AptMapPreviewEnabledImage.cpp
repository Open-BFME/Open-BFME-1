// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include
// CurrentMap image selection uses the layout witnessed in AptMapPreview.cpp.
// Evidence: targets/game/reverse/identity_evidence/00521390-map-image.md
#include "ascii_string.h"
#include "basetype.h"

extern "C" int strcmp(const char *left, const char *right);
#pragma intrinsic(strcmp)
extern "C" void *memset(void *destination, int value, unsigned int size);
extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(
	const void *address, unsigned long size);

class GameWindow;
extern void j_000336ae();
extern void j_00016239();
class BfmeObjENK;
class MapMetaData
{
public:
	char m_unmodelled00[0x50];
	AsciiString m_mapName;
};
void _bfme_closeAptScreen(const AsciiString &screenName);
class Image
{
public:
	virtual ~Image();
	AsciiString bfmeGetFilename( void ) const;
};

class GameWindow
{
public:
	GameWindow *winGetChild( void );
	GameWindow *winGetNext( void );
	int winHide( Bool hide );

	int winSetEnabledImage(int index, const Image *image);
	void winSetUserData(void *userData);
	unsigned int winSetStatus(unsigned int status);
	unsigned int winClearStatus(unsigned int status);
	int bfmeSetEnabledImage( int index, const Image *image );
	void bfmeSetUserData( void *userData );
	unsigned int bfmeSetStatus( unsigned int status );
	unsigned int bfmeClearStatus( unsigned int status );
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class MappedImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};

extern ImageCollection *TheMappedImageCollection;

extern Image *getMapPreviewImage( AsciiString mapName );

class Rva00521160Unnamed
{
public:
	void call( MapMetaData *map );
};

void bfmeGoENK( BfmeObjENK *window, char enable );
void BfmeGadgetListBoxSetAudioFeedback( GameWindow *listbox, Bool enable );

class Display
{
public:
	virtual void reserved00(); virtual void reserved01();
	virtual void reserved02(); virtual void reserved03();
	virtual void reserved04(); virtual void reserved05();
	virtual void reserved06(); virtual void reserved07();
	virtual void reserved08(); virtual void reserved09();
	virtual void reserved10(); virtual void reserved11();
	virtual void reserved12(); virtual void reserved13();
	virtual void reserved14(); virtual void reserved15();
	virtual void reserved16(); virtual void reserved17();
	virtual void reserved18(); virtual void reserved19();
	virtual void reserved20(); virtual void reserved21();
	virtual void reserved22(); virtual void reserved23();
	virtual void reserved24(); virtual void reserved25();
	virtual void reserved26(); virtual void reserved27();
	virtual void reserved28(); virtual void reserved29();
	virtual void reserved30(); virtual void reserved31();
	virtual void reserved32(); virtual void reserved33();
	virtual void reserved34(); virtual void reserved35();
	virtual void reserved36(); virtual void reserved37();
	virtual void reserved38(); virtual void reserved39();
	virtual void reserved40(); virtual void reserved41();
	virtual void reserved42(); virtual void reserved43();
	virtual void bfmeBeginBatch();
	virtual void reserved45(); virtual void reserved46();
	virtual void reserved47(); virtual void reserved48();
	virtual void reserved49(); virtual void reserved50();
	virtual void reserved51(); virtual void reserved52();
	virtual void drawImage( const Image *image, float startX, float startY,
		float endX, float endY, int color, int mode );
	virtual void reserved54();
	virtual void bfmeEndBatch();
};

extern Display * const TheDisplay;

class S4Holder0046DBB0
{
public:
	void take0046DEF0(const AsciiString &name);
};
class AptMapPreview
{
public:
	void bfmeReset(void);
	void rva005216B0(MapMetaData *metadata);
	void rva00521390(MapMetaData *metadata);
	void rva00521000(MapMetaData *metadata);
	void bfmeSetMapTitle(MapMetaData *metadata);
	void bfmeSetMapDescription(MapMetaData *metadata);
	void bfmeSetMapPicture(MapMetaData *metadata);
	void mapGadgetInit(const char *name, void *userData, GameWindow *window);
	void rva005217A0(const AsciiString &value);
	void picture(const Coord2D *origin, const Coord2D *extent,
		void *unusedA, void *unusedB);

private:
	char m_unmodelled00[4];
	GameWindow *m_currentMap;
	GameWindow *m_mapPicture;
	GameWindow *m_mapInfo;
	GameWindow *m_mapDescription;
	GameWindow *m_children[8];
	const Image *m_picture;
	bool m_pictureOwned;
	unsigned char m_unmodelled39[7];
};

// ?rva00521390@AptMapPreview@@QAEXPAVMapMetaData@@@Z
void AptMapPreview::rva00521390(MapMetaData *metadata)
{
	if (m_currentMap == 0)
		return;

	m_currentMap->winSetEnabledImage(1, 0);

	if (metadata == 0)
	{
		m_currentMap->winSetUserData(0);
		// Native static initialization restores its guard if the lookup throws.
		static const Image *BFME_MAP_PREVIEW_NULL_IMAGE =
			TheMappedImageCollection->findImageByName(AsciiString("MissingMap"));
		if (BFME_MAP_PREVIEW_NULL_IMAGE)
		{
			m_currentMap->winSetStatus(0x80);
			m_currentMap->winSetEnabledImage(0, BFME_MAP_PREVIEW_NULL_IMAGE);
		}
		else
			m_currentMap->winClearStatus(0x80);
	}
	else
	{
		const Image *image = getMapPreviewImage(metadata->m_mapName);
		// The accessor copies Image+8 into caller-owned return storage.
		typedef AsciiString (Image::*FilenameFn)() const;
		union { void (*fn)(); FilenameFn call; } bfmeGetFilename = { j_000336ae };
		bool showScrollShroud = image && (image->*bfmeGetFilename.call)().endsWithNoCase("_art.tga");
		if (showScrollShroud)
		{
			AsciiString scrollShroud("ScrollShroud");
			m_currentMap->winSetEnabledImage(1, TheMappedImageCollection->findImageByName(scrollShroud));
		}
		m_currentMap->winSetUserData(metadata);
		if (image)
		{
			m_currentMap->winSetStatus(0x80);
			m_currentMap->winSetEnabledImage(0, image);
		}
		else
		{
			static const Image *BFME_MAP_PREVIEW_MISSING_IMAGE =
				TheMappedImageCollection->findImageByName(AsciiString("MissingMap"));
			if (BFME_MAP_PREVIEW_MISSING_IMAGE)
			{
				m_currentMap->winSetStatus(0x80);
				m_currentMap->winSetEnabledImage(0, BFME_MAP_PREVIEW_MISSING_IMAGE);
			}
			else
				m_currentMap->winClearStatus(0x80);
		}
	}
	Rva00521160Unnamed *tail = (Rva00521160Unnamed *)this;
	// Preserve the receiver and metadata without assigning a sibling identity.
	typedef void (Rva00521160Unnamed::*CallFn)(MapMetaData *);
	union { void (*fn)(); CallFn call; } target = { j_00016239 };
	(tail->*target.call)(metadata);
}
