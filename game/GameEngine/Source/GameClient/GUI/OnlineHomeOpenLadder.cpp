// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef void *HWND;

extern "C" __declspec(dllimport) void * __stdcall ShellExecuteA(
	HWND window, const char *operation, const char *file, const char *parameters,
	const char *directory, int showCommand );

#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	~AsciiString() {}
	void translate( const UnicodeString &text );
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};

extern GameTextInterface *TheGameText;
void bfmeMinimizeCurrentThreadWindow();

class BfmeAptScreenOnlineHome
{
public:
	void bfmeOpenLadderPage( const char *argument );
};

void BfmeAptScreenOnlineHome::bfmeOpenLadderPage( const char * )
{
	AsciiString url;
	url.translate( TheGameText->fetch( "URL:LotrLadder" ) );
	ShellExecuteA( 0, "open", "IEXPLORE.EXE", url.str(), 0, 5 );
	bfmeMinimizeCurrentThreadWindow();
}
