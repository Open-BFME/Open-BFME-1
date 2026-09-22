// ?isAgeOkay@@YA_NAAVAsciiString@@0V1@@Z at retail 0x004FFB80.
// The local view preserves BFME's witnessed string layout and ABI.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include <windows.h>
#include <stdlib.h>

typedef bool Bool;
typedef int Int;

struct AsciiStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	AsciiStringData *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	Bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}

	void format(AsciiString format, ...);
};

static Bool isAgeOkay(AsciiString &month, AsciiString &day, AsciiString year)
{
	if(month.isEmpty() || day.isEmpty() || year.isEmpty() || year.getLength() != 4)
		return FALSE;

	Int monthInt = atoi(month.str());
	Int dayInt = atoi(day.str());

	if(monthInt > 12 || dayInt > 31)
		return FALSE;
		// setup date buffer for local region date format
	month.format("%02.2d",monthInt);
	day.format("%02.2d",dayInt);

	// test the year first
	#define DATE_BUFFER_SIZE 256
	char dateBuffer[ DATE_BUFFER_SIZE ];
	GetDateFormat( LOCALE_SYSTEM_DEFAULT,
														 0, NULL,
														 "yyyy",
														 dateBuffer, DATE_BUFFER_SIZE );
	Int sysVal = atoi(dateBuffer);
	Int userVal = atoi(year.str());
	if(sysVal - userVal >= 14)
		return TRUE;
	else if( sysVal - userVal <= 12)
		return FALSE;

	GetDateFormat( LOCALE_SYSTEM_DEFAULT,
														 0, NULL,
														 "MM",
														 dateBuffer, DATE_BUFFER_SIZE );
	sysVal = atoi(dateBuffer);
	userVal = atoi(month.str());
	if(sysVal - userVal >0 )
		return TRUE;
	else if( sysVal -userVal < 0 )
		return FALSE;
	// month.format("%02.2d",userVal);
	GetDateFormat( LOCALE_SYSTEM_DEFAULT,
														 0, NULL,
														 "dd",
														 dateBuffer, DATE_BUFFER_SIZE );
	sysVal = atoi(dateBuffer);
	userVal = atoi(day.str());
	if(sysVal - userVal< 0)
		return FALSE;
	// day.format("%02.2d",userVal);
	return TRUE;
}

extern "C" __declspec(noinline) Bool Rva004FFB80IsAgeOkayEmitter(AsciiString &month, AsciiString &day, AsciiString year)
{
	return isAgeOkay(month, day, year);
}
