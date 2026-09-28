// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the WayPoint INI field parser at retail 0x001FA0B0, 254 bytes.
//
// The FieldParse table at 0x010A3B28 pairs the string "WayPoint" with ILT
// 0x0003BBF1, which jumps here, and writes member offset 0xA8. The table's own
// owner is the buildFieldParse at 0x001FAB70, whose historical class name is
// not recovered, so the class is tagged by that address.
//
// The offsets confirm the owner. The table writes BonePrefix to 0xA4, WayPoint
// to 0xA8, Link to 0xB4 and WallBoundsMesh to 0xC0, and the module data whose
// destructor game/GameEngine/Source/Common/
// CritterEmitterUpdateModuleDataDestructorThunk.cpp reconstructs holds an
// AsciiString at 0xA4, a vector of eight-byte elements at 0xA8, a twelve-byte
// member at 0xB4 and another AsciiString at 0xC0.
//
// Each entry reads an Index sub-token and a Type sub-token. The three type
// spellings are Walk, Climb and PreClimb, and they store 2, 3 and 4. Retail
// leaves the type member alone when none of the three matches, so the source
// leaves it uninitialized too.
#include <vector>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString() { releaseBuffer(); }
	int bfmeCompare1294( const char *text ) const;

private:
	void releaseBuffer( void );
	void *m_data;
};

class INI
{
public:
	static int scanInt( const char *token );
	const char *getNextSubToken( const char *expected );
};

// The element tag has to keep this spelling. The inlined push_back calls
// _STL::vector<T>::_M_insert_overflow, and the ledger pins that body at
// 0x001F9E80 under this element name.
struct Gen_t_001fa030_p8pod
{
	int m_index;
	int m_type;
};

class Rva001FAB70
{
public:
	static void parseWayPoint( INI *ini, void *instance, void *store, const void *userData );
};

void Rva001FAB70::parseWayPoint( INI *ini, void *, void *store, const void * )
{
	Gen_t_001fa030_p8pod entry;
	entry.m_index = INI::scanInt( ini->getNextSubToken( "Index" ) );
	AsciiString type( ini->getNextSubToken( "Type" ) );
	if ( type.bfmeCompare1294( "Walk" ) == 0 )
		entry.m_type = 2;
	else if ( type.bfmeCompare1294( "Climb" ) == 0 )
		entry.m_type = 3;
	else if ( type.bfmeCompare1294( "PreClimb" ) == 0 )
		entry.m_type = 4;
	( (_STL::vector<Gen_t_001fa030_p8pod> *)store )->push_back( entry );
}
