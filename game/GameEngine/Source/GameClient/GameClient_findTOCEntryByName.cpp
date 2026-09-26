// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// The retail body at 0x00430B80 walks GameClient's drawable TOC list and
// returns the matching DrawableTOCEntry. The matching GameLogic TOC body at
// 0x00388AC0 proves this STLport list and BFMERetailAsciiString layout.

#include <list>

extern "C" int __cdecl memcmp( const void *, const void *, unsigned int );
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	AsciiString( const AsciiString &other ) : m_data( other.m_data ) {}
	~AsciiString() { releaseBuffer(); }

	int compare( const AsciiString &other ) const
	{
		int otherLength = other.m_data ? *(const unsigned short *)(other.m_data + 4) : 0;
		const char *otherText = other.m_data ? other.m_data + 8 : "";
		int thisLength = m_data ? *(const unsigned short *)(m_data + 4) : 0;
		const char *thisText = m_data ? m_data + 8 : "";
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp( thisText, otherText, length );
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	bool operator==( const AsciiString &other ) const
	{
		return compare( other ) == 0;
	}

protected:
	void releaseBuffer();

private:
	char *m_data;
};

class GameClient
{
public:
	struct DrawableTOCEntry
	{
		AsciiString name;
		unsigned short id;
	};
	typedef std::list<DrawableTOCEntry> DrawableTOCList;
	typedef DrawableTOCList::iterator DrawableTOCListIterator;

private:
	DrawableTOCEntry *findTOCEntryByName( AsciiString name );

	char m_pad[0xf0];
	DrawableTOCList m_drawableTOC;
};

GameClient::DrawableTOCEntry *GameClient::findTOCEntryByName( AsciiString name )
{
	for ( GameClient::DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it )
		if ( (*it).name.compare( name ) == 0 )
			return &(*it);

	return 0;
}
