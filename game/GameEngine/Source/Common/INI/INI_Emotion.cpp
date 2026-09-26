// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// The three EmotionSystem bodies, which are one feature:
//
//   0x0037B8A0  parseEmotionNugget      the EmotionNugget block parser
//   0x0037CD70  EmotionSystem::findNugget
//   0x0037CF10  EmotionSystem::addNugget
//
// The parser builds a nugget and hands it to addNugget; addNugget asks
// findNugget whether the name is already taken. Three files, one round trip.
//
// Both names come from the binary: GameEngine::init passes the literal
// "TheEmotionSystem" immediately before pushing 0x012F0878, and the registrar
// it calls is initSubsystem<EmotionSystem>.
//
// What the split hid is that no file held either class whole. EmotionSystem had
// its 8-byte head and nugget vector in two files and no layout at all in the
// parser, which only ever calls addNugget on it. EmotionNugget had its 0xF8
// size and field table in the parser and only getName in the other two. And
// BfmeEmotionName carried its inlined compare -- a 16-bit length at data+4 and
// characters at data+8 -- in findNugget alone, while addNugget declared the
// same class with nothing but a destructor, because a stripped copy is all its
// own body needs to pass one along.
//
// The nugget's first member is the AsciiString the parser fills from the block
// keyword, which is why the parser reaches StringBase<char>::set on the nugget
// pointer directly rather than through a shim: that symbol is already pinned.
#include "PreRTS.h"
#include "Common/INI.h"
#include "string_base.h"
#include <vector>

extern "C" int __cdecl memcmp( const void *left, const void *right, unsigned int count );
#pragma intrinsic(memcmp)

class BfmeEmotionName
{
public:
	~BfmeEmotionName();

	int compare( const BfmeEmotionName &that ) const
	{
		int thatLength = that.m_data ? *(unsigned short *)( that.m_data + 4 ) : 0;
		const char *thatData = that.m_data ? that.m_data + 8 : "";
		int thisLength = m_data ? *(unsigned short *)( m_data + 4 ) : 0;
		const char *thisData = m_data ? m_data + 8 : "";
		int length = thisLength < thatLength ? thisLength : thatLength;
		int result = memcmp( thisData, thatData, length );
		return result ? result : thisLength - thatLength;
	}

private:
	char *m_data;
};

inline bool operator==( const BfmeEmotionName &left, const BfmeEmotionName &right )
{
	return left.compare( right ) == 0;
}

class EmotionNugget
{
public:
	EmotionNugget();

	BfmeEmotionName getName() const;

	static const FieldParse m_fieldParseTable[];

private:
	char m_unmodelled[ 0xF8 ];
};

class EmotionSystem
{
public:
	void addNugget( EmotionNugget *nugget );
	EmotionNugget *findNugget( const BfmeEmotionName &name );

private:
	unsigned char m_unmodelled[ 8 ];
	std::vector<EmotionNugget *> m_nuggets;
};

extern EmotionSystem *TheEmotionSystem;			// 0x012F0878

// ?parseEmotionNugget@@YAXPAVINI@@@Z
void parseEmotionNugget( INI *ini )
{
	if( !TheEmotionSystem )
		return;

	const char *name = ini->getNextToken();

	EmotionNugget *nugget = new EmotionNugget();

	((StringBase<char> *)nugget)->set( name, name ? (int)strlen( name ) : 0 );

	ini->initFromINI( nugget, EmotionNugget::m_fieldParseTable );

	TheEmotionSystem->addNugget( nugget );
}

// ?findNugget@EmotionSystem@@QAEPAVEmotionNugget@@ABVBfmeEmotionName@@@Z
EmotionNugget *EmotionSystem::findNugget( const BfmeEmotionName &name )
{
	for( int i = 0; i < m_nuggets.size(); ++i )
	{
		if( m_nuggets[ i ]->getName() == name )
			return m_nuggets[ i ];
	}

	return 0;
}

// ?addNugget@EmotionSystem@@QAEXPAVEmotionNugget@@@Z
void EmotionSystem::addNugget( EmotionNugget *nugget )
{
	if( !nugget )
		return;

	EmotionNugget *existing = findNugget( nugget->getName() );
	if( existing )
		return;

	m_nuggets.push_back( nugget );
}
