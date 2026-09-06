// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME: GondorGandalf portrait chooser, retail 0x000FA610, 392 bytes.
//
// this is a named image-key: AsciiString at +0, cached Image* at +4, flag at
// +0x38. In multiplayer/skirmish, a GondorGandalf key whose player lacks
// SCIENCE_GandalftheWhite returns HIGandalTheGrey. Else ThingFactory
// findTemplate(name) + getSelectedPortraitImage. Address-derived owner;
// image names do not identify the class.

#include <string.h>

void j_00016fae();
#pragma comment(linker, "/alternatename:?initialize@Rva00016FAE@@QAEXXZ=?j_00016fae@@YAXXZ")

// Buffer internals are owned by the existing StringBase implementation.
template <typename T> struct StringInlineData;

template <typename T> class StringBase
{
	friend class AsciiString;
private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	int compare( const AsciiString &other ) const;
};

class Image;
class Player;

enum ScienceType { SCIENCE_INVALID = -1 };

class GameLogicPortraitShim
{
public:
	bool isInMultiplayerOrSkirmishGame();
};

class ScienceStore
{
public:
	ScienceType getScienceFromInternalName(const AsciiString &name);
};

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class ThingTemplatePortraitShim
{
public:
	const Image *getSelectedPortraitImage() const;
};

class ThingTemplate;

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

class Rva00016FAE
{
public:
	__declspec(noinline) void initialize();
};

__declspec(noinline) void Rva00016FAE::initialize()
{
	j_00016fae();
}

class ZeroPrefix
{
public:
	ZeroPrefix() : image(0), value08(0) {}
	const Image *image;
	int value08;
};

class OneBlock
{
public:
	OneBlock() : value0c(1), value10(1) {}
	int value0c;
	int value10;
};

class ZeroBlock
{
public:
	int values[6];
};

#define TheGameLogic (*(GameLogicPortraitShim **)0x012F0898)
#define TheScienceStore (*(ScienceStore **)0x012ED7AC)
#define TheMappedImageCollection (*(MappedImageCollection **)0x012F6924)
#define TheThingFactory (*(ThingFactory **)0x012EF1D8)

class Rva000FA610
{
public:
	Rva000FA610();
	const Image *getPortrait(Player *player);

	AsciiString m_name;
	ZeroPrefix m_prefix;
	OneBlock m_one;
	ZeroBlock m_zero;
	int m_value2c;
	int m_value30;
	int m_value34;
	unsigned char m_flag;
	int m_value3c;
	int m_value40;
	Rva00016FAE m_value44;
};

class Player
{
public:
	bool hasScience(ScienceType science) const;
};

// ??0Rva000FA610@@QAE@XZ
Rva000FA610::Rva000FA610()
	: m_name(), m_prefix(), m_one()
{
	memset(&m_zero, 0, sizeof(m_zero));
	m_value30 = -1;
	m_value2c = 0;
	m_value34 = 0;
	m_flag = 0;
	m_value3c = 0;
	m_value40 = -1;
	m_value44.initialize();
}

// ?getPortrait@Rva000FA610@@QAEPBVImage@@PAVPlayer@@@Z
const Image *Rva000FA610::getPortrait(Player *player)
{
	if (m_flag)
		return m_prefix.image;

	if (TheGameLogic->isInMultiplayerOrSkirmishGame())
	{
		static AsciiString gondor("GondorGandalf");
		if (m_name.compare(gondor) == 0)
		{
			static AsciiString scienceName("SCIENCE_GandalftheWhite");
			ScienceType st = TheScienceStore->getScienceFromInternalName(scienceName);
			if (st != SCIENCE_INVALID)
			{
				if (!player->hasScience(st))
				{
					static const Image *cached = 0;
					if (cached)
						return cached;
					cached = TheMappedImageCollection->findImageByName(
						AsciiString("HIGandalTheGrey"));
					if (cached)
						return cached;
				}
			}
		}
	}

	ThingTemplate *tmpl = TheThingFactory->findTemplate(m_name);
	if (tmpl != 0)
	{
		ThingTemplatePortraitShim *portrait = (ThingTemplatePortraitShim *)tmpl;
		if (portrait->getSelectedPortraitImage() != 0)
			return portrait->getSelectedPortraitImage();
	}
	return 0;
}
