// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

typedef int Int;
typedef bool Bool;

template <class Type>
class StringBase
{
private:
	StringBase();
	StringBase(const Type *text);
	StringBase(const StringBase &other);
	~StringBase();
	friend class AsciiString;
	friend class UnicodeString;

	void *m_data;
};

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
