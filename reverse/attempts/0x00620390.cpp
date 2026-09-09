// ?getSlotNum@GameInfo@@QBEHVAsciiString@@@Z
// partial score=0.72 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Clean BFME ABI slice for GameInfo::getSlotNum; the named callers are
// GameLogic::bfmePopulateGameReport and WOLQuickMatchMenuUpdate.

typedef int Int;
typedef bool Bool;

class UnicodeString;

#define ASCIISTRING_H
#define UNICODESTRING_H

template <typename T>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class UnicodeString;

	protected:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	public:
	int compareNoCase(const StringBase<T> &other) const;

	private:
	void releaseBuffer();

	StringInlineData<T> *m_data;
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const char *text) : m_data(0) { (void)text; }
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other);
	const char *str(void) const { return ""; }
	int getLength(void) const;
	int compareNoCase(const AsciiString &other) const;
	void toLower(void);
	static AsciiString TheEmptyString;

private:
	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other);
	const unsigned short *str(void) const;
	int getLength(void) const;
	int compareNoCase(const UnicodeString &other) const
	{
		return ((const StringBase<unsigned short> *)this)->compareNoCase(
			*(const StringBase<unsigned short> *)&other);
	}
	static UnicodeString TheEmptyString;
	void translate(const AsciiString &source);
	void releaseBuffer()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}
};

#pragma comment(linker, "/alternatename:?compareNoCase@?$StringBase@G@@QBEHABV1@@Z=?j_0001609f@@YAXXZ")

int operator==(const AsciiString &left, const AsciiString &right);
bool operator<(const AsciiString &left, const AsciiString &right);

#include "../../../../../reference/shims/sweep/PreRTS.h"

class GameSlot
{
public:
	virtual void reset(void) = 0;
	Bool isPlayer(UnicodeString userName) const;

protected:
	int m_state;
	unsigned char m_gap08[0x28 - 0x08];
	UnicodeString m_name;
};

__forceinline Bool GameSlot::isPlayer(UnicodeString userName) const
{
	Bool result;
	if (m_state == 5 && m_name.compareNoCase(userName) == 0)
		result = true;
	else
		result = false;

	userName.releaseBuffer();
	return result;
}

class GameInfo
{
private:
	unsigned char m_pad0[0x0c];
	Bool m_inGame;
	unsigned char m_pad0d[3];
	void *m_pad10;
	GameSlot *m_slots[8];

public:
	Int getSlotNum(AsciiString userName) const;
};

Int GameInfo::getSlotNum(AsciiString userName) const
{
	Int i = 0;
	if (!m_inGame)
		return -1;

	UnicodeString uName;
	uName.translate(userName);
	GameSlot *const *slots = m_slots;
	for (; i < 8; ++i, ++slots)
	{
		const GameSlot *slot = *slots;
		if (slot->isPlayer(uName))
			return i;
	}
	return -1;
}
