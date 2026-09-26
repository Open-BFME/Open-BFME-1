// ??0SkirmishBattleHonors@@QAE@VUnicodeString@@@Z
// Retail 0x0009E130, 534 bytes; identity is proven by vtable 0x01080460,
// matched dtor 0x0009C1E0, and the callers recorded in the live brief.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_NO_EXCEPTIONS /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib

#define _STLP_NO_EXCEPTIONS 1

#include "ascii_string.h"
#include "unicode_string.h"

// The canonical WWLib headers omit this exported static member. The binary's
// const export is the same UnicodeString object used by the retail body.
extern const UnicodeString BFMEUnicodeEmptyString;
#pragma comment(linker, "/alternatename:?BFMEUnicodeEmptyString@@3VUnicodeString@@B=?TheEmptyString@UnicodeString@@2V1@B")

typedef bool Bool;
typedef unsigned short WideChar;
typedef int Int;

#define TRUE 1

// The UserPreferences setBool call takes the native AsciiString by value.
// Its canonical inline const-char constructor produces the retail call shape.

class UserPreferences
{
public:
	UserPreferences(void);
	virtual ~UserPreferences(void);
	virtual Bool load(const UnicodeString &filename);
	virtual Bool load(AsciiString filename);
	void setAsciiString(AsciiString key, AsciiString value);
	void setBool(AsciiString key, Bool value);

private:
	unsigned char m_bfmeBody[0x10];
};

class GameSlot
{
public:
	GameSlot(void);
	~GameSlot(void);

private:
	unsigned char m_storage[0x44];
};

class GameInfo
{
public:
	GameInfo(void);
	virtual ~GameInfo(void);
	void setSlotPointer(Int index, GameSlot *slot);
	GameSlot *getSlot(Int slot);

private:
	unsigned char m_storage[0x54];
};

class Snapshot
{
public:
	virtual ~Snapshot(void);
};

class Rva00003409Open2SlotOwner : public GameInfo, public Snapshot
{
public:
	Rva00003409Open2SlotOwner(void);
	virtual ~Rva00003409Open2SlotOwner(void);

private:
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess(void);
	GameSlot m_slots[8];
};

// The native UnicodeString facade declares its copy constructor out of line.
// Retail's by-value GameSlot::setName argument instead inlines a one-word
// forwarding view; the base copy and destructor target the matched wide
// StringBase bodies. This adapter changes only the caller's scheduling.
class BfmeUnicodeStringBaseCopyView0009E130
{
protected:
	BfmeUnicodeStringBaseCopyView0009E130(const BfmeUnicodeStringBaseCopyView0009E130 &other);
	~BfmeUnicodeStringBaseCopyView0009E130();
private:
	void *m_data;
};

class BfmeUnicodeStringArgumentView0009E130 : private BfmeUnicodeStringBaseCopyView0009E130
{
public:
	BfmeUnicodeStringArgumentView0009E130(const UnicodeString &other)
		: BfmeUnicodeStringBaseCopyView0009E130(
			*(const BfmeUnicodeStringBaseCopyView0009E130 *)&other) {}
	~BfmeUnicodeStringArgumentView0009E130() {}
};

class Rva0000F150GameSlot
{
public:
	void setName(BfmeUnicodeStringArgumentView0009E130 name);
};

class Rva004D8EE0
{
public:
	Rva004D8EE0(void);

private:
	Int m_values[10];
};

class Rva0000BAD7Owner
{
public:
	AsciiString getSlotList(void);
};

class SkirmishBattleHonors : public UserPreferences
{
public:
	SkirmishBattleHonors(UnicodeString userName);

private:
	Rva004D8EE0 m_values;
};

extern AsciiString GameInfoToAsciiString(const GameInfo *game, Bool includeSlots);
extern Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options,
	Bool includeSlots);

#pragma comment(linker, "/alternatename:?compare@UnicodeString@@QBEHABV1@@Z=?j_000226ec@@YAXXZ")
#pragma comment(linker, "/alternatename:??0UserPreferences@@QAE@XZ=?j_0004b19b@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00003409Open2SlotOwner@@QAE@XZ=?j_00003409@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00003409Open2SlotOwner@@UAE@XZ=?j_00008797@@YAXXZ")
#pragma comment(linker, "/alternatename:?setName@Rva0000F150GameSlot@@QAEXVBfmeUnicodeStringArgumentView0009E130@@@Z=?j_0000f150@@YAXXZ")
#pragma comment(linker, "/alternatename:??0BfmeUnicodeStringBaseCopyView0009E130@@IAE@ABV0@@Z=??0?$StringBase@G@@AAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:??1BfmeUnicodeStringBaseCopyView0009E130@@IAE@XZ=??1?$StringBase@G@@AAE@XZ")
#pragma comment(linker, "/alternatename:?getSlotList@Rva0000BAD7Owner@@QAE?AVAsciiString@@XZ=?j_0000bad7@@YAXXZ")

SkirmishBattleHonors::SkirmishBattleHonors(UnicodeString userName)
{
	if (userName.compare(BFMEUnicodeEmptyString) != 0)
	{
		BfmeUnicodeStringArgumentView0009E130 filename(userName);
		// The facade omits concat(text, length); retail calls StringBase's
		// underlying native overload directly.
		((StringBase<unsigned short> *)&filename)->concat(
			(const unsigned short *)0x01080684,
			(Int)wcslen((const wchar_t *)0x01080684));
		if (!UserPreferences::load(*(const UnicodeString *)&filename))
		{
			AsciiString asciiFilename;
			asciiFilename.translate(userName);
			((StringBase<char> *)&asciiFilename)->concat(
				(const char *)0x0108066c, 0x11);
			if (UserPreferences::load(asciiFilename))
			{
				Rva00003409Open2SlotOwner gameInfo;
				GameInfo *game = (GameInfo *)&gameInfo;
				ParseAsciiStringToGameInfo(&gameInfo,
					((Rva0000BAD7Owner *)this)->getSlotList(), TRUE);
				Rva0000F150GameSlot *slot =
					(Rva0000F150GameSlot *)game->getSlot(0);
				slot->setName(BfmeUnicodeStringArgumentView0009E130(userName));
				UserPreferences::setAsciiString(
					AsciiString((const char *)0x0108063c),
					GameInfoToAsciiString(&gameInfo, TRUE));
			}
			UserPreferences::load(*(const UnicodeString *)&filename);
		}
		UserPreferences::setBool(AsciiString((const char *)0x01080654), TRUE);
	}
}
