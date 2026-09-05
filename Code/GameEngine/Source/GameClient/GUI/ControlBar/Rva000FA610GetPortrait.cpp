// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME: GondorGandalf portrait chooser, retail 0x000FA610, 392 bytes.
//
// this is a named image-key: AsciiString at +0, cached Image* at +4, flag at
// +0x38. In multiplayer/skirmish, a GondorGandalf key whose player lacks
// SCIENCE_GandalftheWhite returns HIGandalTheGrey. Else ThingFactory
// findTemplate(name) + getSelectedPortraitImage. Address-derived owner;
// image names do not identify the class.

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

#define TheGameLogic (*(GameLogicPortraitShim **)0x012F0898)
#define TheScienceStore (*(ScienceStore **)0x012ED7AC)
#define TheMappedImageCollection (*(MappedImageCollection **)0x012F6924)
#define TheThingFactory (*(ThingFactory **)0x012EF1D8)

class Rva000FA610
{
public:
	const Image *getPortrait(Player *player);

	AsciiString m_name;
	const Image *m_image;
	unsigned char m_mid[0x38 - 8];
	unsigned char m_flag;
};

class Player
{
public:
	bool hasScience(ScienceType science) const;
};

// ?getPortrait@Rva000FA610@@QAEPBVImage@@PAVPlayer@@@Z
const Image *Rva000FA610::getPortrait(Player *player)
{
	if (m_flag)
		return m_image;

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
