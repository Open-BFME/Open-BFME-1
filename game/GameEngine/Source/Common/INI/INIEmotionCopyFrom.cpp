// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// The EmotionNugget CopyFrom field parser, retail 0x0037B1B0.  The field table
// identifies this callback directly: it resolves a named nugget and copies its
// BfmeThing payload into the field at offset zero.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"

// The BFME string implementation is shared by several source-level aliases.
// This one-word view preserves the proven findNugget parameter spelling while
// making the retail const-char constructor and release body explicit callees.
class BfmeStringLiteralBase
{
	friend class BfmeEmotionName;

private:
	BfmeStringLiteralBase( const char *text );
};

class BfmeEmotionName
{
public:
	BfmeEmotionName( const char *text )
	{
		((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::BfmeStringLiteralBase( text );
	}
	~BfmeEmotionName();

private:
	char *m_data;
};

class EmotionNugget;

class EmotionSystem
{
public:
	EmotionNugget *findNugget( const BfmeEmotionName &name );
};

extern EmotionSystem *TheEmotionSystem; // 0x012F0878

class BfmeThingVKC
{
public:
	void bfmeCopyVKC( const BfmeThingVKC &source );
};

// ?parseEmotionNuggetCopyFrom@@YAXPAVINI@@PAX1PBX@Z
void parseEmotionNuggetCopyFrom( INI *ini, void *, void *store, const void * )
{
	const char *token = ini->getNextToken();
	if( token == 0 )
		throw INIException( 3, "Name of emotion nugget to copy data from expected." );

	EmotionNugget *source;
	{
		BfmeEmotionName name( token );
		source = TheEmotionSystem->findNugget( name );
	}
	if( source == 0 )
		throw INIException( 3, "Emotion nugget to copy from not found." );

	((BfmeThingVKC *)store)->bfmeCopyVKC( *(BfmeThingVKC *)source );
}
