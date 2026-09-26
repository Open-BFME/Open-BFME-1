// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include
// AptMapPreview callbacks and teardown share this observed 0x40-byte layout.
// Constructor 0x00520670 writes through +0x3C; the enclosing setup constructor
// places its next member at preview+0x40. Unknown fields remain raw storage.

#include "ascii_string.h"
#include "basetype.h"

extern "C" int strcmp(const char *left, const char *right);
#pragma intrinsic(strcmp)
extern "C" void *memset(void *destination, int value, unsigned int size);
extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(
	const void *address, unsigned long size);

class GameWindow;
class BfmeObjENK;

// Observed map metadata view: the filename string is at +0x50.
class MapMetaData
{
public:
	char m_unmodelled00[0x50];
	AsciiString m_mapName;
};
void _bfme_closeAptScreen(const AsciiString &screenName);

// Image constructor 0x005D2260 installs 0x0110FFEC; slot zero routes to the
// scalar-deleting destructor at 0x005D2BD0.
class Image
{
public:
	virtual ~Image();
};

class GameWindow
{
public:
	GameWindow *winGetChild( void );
	GameWindow *winGetNext( void );
	int winHide( Bool hide );
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

// The gadget callback witnesses windows at +04/+08/+0C/+10 and children at
// +14..+30. AptMapPreviewImages.cpp witnesses the Image at +34 and owned flag
// at +38. The first four bytes and the unused tail stay explicitly opaque.
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

// Retail 0x005207C0, 214 bytes. Named MpGameSetup initialization and shutdown
// pass the same receiver+0x28 to this embedded preview.
// ?bfmeReset@AptMapPreview@@QAEXXZ
void AptMapPreview::bfmeReset(void)
{
	{
		AsciiString name("AptMapPreview::Picture");
		(reinterpret_cast<S4Holder0046DBB0 **>(0x012f19e8))[0]->take0046DEF0(name);
	}
	{
		AsciiString name("AptMapPreview::MapGadgetInit");
		_bfme_closeAptScreen(name);
	}

	m_currentMap = 0;
	m_mapPicture = 0;
	m_mapInfo = 0;
	m_mapDescription = 0;
	if (m_pictureOwned)
	{
		if (m_picture)
		{
			delete m_picture;
			m_picture = 0;
			m_pictureOwned = false;
		}
	}
	memset(m_children, 0, sizeof(m_children));
}

// Retail 0x00521990, 261 bytes. initGadgets at 0x00521AE0 registers ILT
// 0x00036DF9 under "AptMapPreview::MapGadgetInit" (literal push 0x00521AFD).
// Its common tail preserves the original preview receiver and passes the
// offset-zero string to the address-qualified method at 0x005217A0.
void AptMapPreview::mapGadgetInit( const char *name, void *userData,
	GameWindow *window )
{
	(void)userData;
	if ( window == 0 )
		return;

	if ( strcmp( name, "MapInfo" ) == 0 )
	{
		m_mapInfo = window;
		bfmeGoENK( (BfmeObjENK *)window, 1 );
		BfmeGadgetListBoxSetAudioFeedback( m_mapInfo, true );
	}
	else if ( strcmp( name, "MapDescription" ) == 0 )
	{
		m_mapDescription = window;
		bfmeGoENK( (BfmeObjENK *)window, 1 );
		BfmeGadgetListBoxSetAudioFeedback( m_mapDescription, true );
	}
	else if ( strcmp( name, "MapPicture" ) == 0 )
	{
		m_mapPicture = window;
	}
	else if ( strcmp( name, "CurrentMap" ) == 0 )
	{
		m_currentMap = window;
		int count = 0;
		GameWindow *child = window->winGetChild();
		if ( child != 0 )
		{
			GameWindow **slot = m_children;
			do
			{
				if ( count >= 8 )
					break;
				*slot = child;
				++count;
				++slot;
				child->winHide( true );
				child = child->winGetNext();
			}
			while ( child != 0 );
		}
	}

	rva005217A0( *(const AsciiString *)this );
}

// Retail 0x005204F0, 156 bytes. initGadgets registers ILT 0x0000AFAB under
// "AptMapPreview::Picture" (literal push 0x00521B6C). Display slots 44 and 55
// open/close the batch; slot 53 draws the image, as the existing display view
// in BfmeOverlay1293_bfmeDraw1293.cpp also witnesses.
void AptMapPreview::picture( const Coord2D *origin, const Coord2D *extent,
	void *unusedA, void *unusedB )
{
	(void)unusedA;
	(void)unusedB;

	if ( m_picture == 0 )
		return;
	if ( IsBadReadPtr( m_picture, 0x34 ) )
	{
		m_picture = 0;
		return;
	}

	float bottom = extent->y + origin->y;
	float right = origin->x + extent->x;
	float top = origin->y;
	float left = origin->x;
	const Image *image = m_picture;
	Display *device = TheDisplay;
	TheDisplay->bfmeBeginBatch();
	device->drawImage( image, left, top, right, bottom, -1, 2 );
	device->bfmeEndBatch();
}

// Retail 0x005217A0 forwards its unchanged preview receiver here twice.
// The leading storage is accessed through the canonical string API without
// adding constructor or destructor obligations to this observed layout.
void AptMapPreview::rva005216B0(MapMetaData *metadata)
{
	StringBase<char> *mapName = reinterpret_cast<StringBase<char> *>(m_unmodelled00);
	if (metadata != 0)
		mapName->set(*reinterpret_cast<const StringBase<char> *>(&metadata->m_mapName));
	else
		mapName->set("", 0);
	bfmeSetMapTitle(metadata);
	rva00521390(metadata);
	rva00521000(metadata);
	bfmeSetMapDescription(metadata);
	bfmeSetMapPicture(metadata);
}

