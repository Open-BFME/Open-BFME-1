// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport

typedef int Int;
typedef bool Bool;

#include "string_base.h"

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->~StringBase();
	}

	void __cdecl format(AsciiString format, ...);
	Int compare(const AsciiString &other) const;
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388b;
	}

	static AsciiString TheEmptyString;

private:
	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other)
	{
	}
	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->~StringBase();
	}

	static UnicodeString TheEmptyString;

};

class UserPreferences
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual AsciiString getAsciiString(AsciiString key, AsciiString defaultValue) = 0;
	virtual void setAsciiString(AsciiString key, AsciiString value) = 0;
};

class SkirmishBattleHonors : public UserPreferences
{
public:
	UnicodeString getFavoriteSideName(void);
};

class GameTextInterface
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

UnicodeString SkirmishBattleHonors::getFavoriteSideName(void)
{
	AsciiString favoriteSide = getAsciiString("FavoriteSide", AsciiString::TheEmptyString);
	if (favoriteSide.compare(AsciiString::TheEmptyString) == 0)
		return UnicodeString::TheEmptyString;

	{
		AsciiString side;
		side.format("Side:%s", favoriteSide.str());
		UnicodeString result = TheGameText->fetch(side);
		return result;
	}
}
