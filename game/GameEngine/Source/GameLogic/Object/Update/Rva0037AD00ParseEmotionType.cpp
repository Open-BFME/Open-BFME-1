// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME7: parseEmotionType (retail 0x0037AD00 72 B; a gap claimed through its
// exception literal).  The next token uses the matched
// BitFlags<10>::getSingleBitFromName helper at 0x0037A9D0 (ILT 0x000448AF)
// and is stored into the field the store argument points at;
// a missing token throws INIException(3 "Emotion type expected.").

#include "Common/BitFlags.h"

template<>
int BitFlags<10>::getSingleBitFromName(const char *name);

typedef int Int;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );
	~INIException();

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
};

class Rva0037AD00
{
public:
	static void parseEmotionType( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseEmotionType@Rva0037AD00@@SAXPAVINI@@PAX1PBX@Z
void Rva0037AD00::parseEmotionType( INI *ini, void *, void *store, const void * )
{
	const char *token = ini->getNextToken();
	if( token )
		*(Int *)store = BitFlags<10>::getSingleBitFromName( token );
	else
		throw INIException( 3, "Emotion type expected." );
}
