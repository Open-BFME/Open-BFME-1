// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

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

class GameLogic
{
public:
	struct ObjectTOCEntry
	{
		AsciiString name;
		unsigned short id;
	};
	typedef std::list<ObjectTOCEntry> ObjectTOCList;
	typedef ObjectTOCList::iterator ObjectTOCListIterator;

	private:
	ObjectTOCEntry *findTOCEntryByName( AsciiString name );

	char m_pad[0x1AC];
	ObjectTOCList m_objectTOC;
};

GameLogic::ObjectTOCEntry *GameLogic::findTOCEntryByName( AsciiString name )
{
	for ( GameLogic::ObjectTOCListIterator it = m_objectTOC.begin(); it != m_objectTOC.end(); ++it )
		if ( (*it).name.compare( name ) == 0 )
			return &(*it);

	return 0;
}
