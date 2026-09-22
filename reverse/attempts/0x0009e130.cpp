// ??0SkirmishBattleHonors@@QAE@VUnicodeString@@@Z
// partial score=0.47 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_NO_EXCEPTIONS /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include

#define _STLP_NO_EXCEPTIONS 1

typedef bool Bool;
typedef unsigned short WideChar;
typedef int Int;

#define TRUE 1

template <typename T> class StringBase
{
friend class AsciiString;
friend class UnicodeString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	void concat(const T *text, Int length);
	Int compare(const StringBase<T> &other) const;
	void *m_data;
};

class UnicodeString;

class AsciiString : private StringBase<char>
{
public:
	__forceinline AsciiString(void) { *(void **)this = 0; }
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	void translate(const UnicodeString &text);
	void concat(const char *text, Int length)
	{
		StringBase<char>::concat(text, length);
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString(void) {}
	Int compare(const UnicodeString &other) const;
	void concat(const WideChar *text, Int length)
	{
		StringBase<WideChar>::concat(text, length);
	}

	static UnicodeString TheEmptyString;
};

extern "C" __declspec(dllimport) unsigned int __cdecl bfmeLenVGI(
	const WideChar *text);

class UserPreferences
{
public:
	UserPreferences(void);
	virtual ~UserPreferences(void);

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

class Rva0001EC18GameInfo
{
public:
	GameSlot *getSlot(Int slot);
};

class Rva0000F150GameSlot
{
public:
	void setName(UnicodeString name);
};

class Rva00010807Values
{
public:
	Rva00010807Values(void);

private:
	Int m_values[10];
};

class SkirmishBattleHonors : public UserPreferences
{
public:
	SkirmishBattleHonors(UnicodeString userName);
	Bool rva00021AD5Load(UnicodeString filename);
	Bool rva00014308LoadAscii(AsciiString filename);
	AsciiString rva0000BAD7GetSlotList(void);
	void rva0000E377SetAsciiString(AsciiString key, AsciiString value);
	void rva00017CC9SetBool(AsciiString key, Bool value);

private:
	Rva00010807Values m_values;
};

extern AsciiString GameInfoToAsciiString(const GameInfo *game, Bool includeSlots);
extern Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options,
	Bool includeSlots);

#pragma comment(linker, "/alternatename:?compare@UnicodeString@@QBEHABV1@@Z=?j_000226ec@@YAXXZ")
#pragma comment(linker, "/alternatename:??0UserPreferences@@QAE@XZ=?j_0004b19b@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00010807Values@@QAE@XZ=?j_00010807@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00003409Open2SlotOwner@@QAE@XZ=?j_00003409@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00003409Open2SlotOwner@@UAE@XZ=?j_00008797@@YAXXZ")
#pragma comment(linker, "/alternatename:?getSlot@Rva0001EC18GameInfo@@QAEPAVGameSlot@@H@Z=?j_0001ec18@@YAXXZ")
#pragma comment(linker, "/alternatename:?setName@Rva0000F150GameSlot@@QAEXVUnicodeString@@@Z=?j_0000f150@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00021AD5Load@SkirmishBattleHonors@@QAE_NVUnicodeString@@@Z=?j_00021ad5@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00014308LoadAscii@SkirmishBattleHonors@@QAE_NVAsciiString@@@Z=?j_00014308@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000BAD7GetSlotList@SkirmishBattleHonors@@QAE?AVAsciiString@@XZ=?j_0000bad7@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000E377SetAsciiString@SkirmishBattleHonors@@QAEXVAsciiString@@0@Z=?j_0000e377@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00017CC9SetBool@SkirmishBattleHonors@@QAEXVAsciiString@@_N@Z=?j_00017cc9@@YAXXZ")

SkirmishBattleHonors::SkirmishBattleHonors(UnicodeString userName)
{
	if (userName.compare(UnicodeString::TheEmptyString) != 0)
	{
		UnicodeString filename(userName);
		filename.concat((const WideChar *)0x01080684,
			(Int)bfmeLenVGI((const WideChar *)0x01080684));
		if (!rva00021AD5Load(filename))
		{
			AsciiString asciiFilename;
			asciiFilename.translate(userName);
			asciiFilename.concat((const char *)0x0108066c, 0x11);
			if (rva00014308LoadAscii(asciiFilename))
			{
				Rva00003409Open2SlotOwner gameInfo;
				Rva0001EC18GameInfo *game =
					(Rva0001EC18GameInfo *)&gameInfo;
				ParseAsciiStringToGameInfo(&gameInfo,
					rva0000BAD7GetSlotList(), TRUE);
				Rva0000F150GameSlot *slot =
					(Rva0000F150GameSlot *)game->getSlot(0);
				slot->setName(userName);
				rva0000E377SetAsciiString(
					AsciiString((const char *)0x0108063c),
					GameInfoToAsciiString(&gameInfo, TRUE));
			}
			rva00021AD5Load(filename);
		}
	}

	rva00017CC9SetBool(AsciiString((const char *)0x01080654), TRUE);
}
