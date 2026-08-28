// cl: /DNDEBUG /MD /EHsc

// BroadcastStealthUpdateModuleData::buildFieldParse, retail 0x00289800. The
// name was on its five-byte incremental-link thunk at 0x000094F3, whose source
// forwarded through a shim rather than describing anything. A thunk is not the
// method.
//
// Two calls to MultiIniFieldParse::add, a name the ledger already has. The
// second argument is the offset the table's stores are relative to: 0x2C for
// the inherited table and 0 for this class's own, which is what says the first
// belongs to a base whose data starts there.

typedef unsigned int UnsignedInt;

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	void add( const FieldParse *table, UnsignedInt offset );
};

extern const FieldParse TheBroadcastStealthInheritedFieldParse[];	// 0x010898A0
extern const FieldParse TheBroadcastStealthOwnFieldParse[];			// 0x010BCAA0

class BroadcastStealthUpdateModuleData
{
public:
	static void buildFieldParse( MultiIniFieldParse &p );
};

// ?buildFieldParse@BroadcastStealthUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
/*static*/ void BroadcastStealthUpdateModuleData::buildFieldParse( MultiIniFieldParse &p )
{
	p.add( TheBroadcastStealthInheritedFieldParse, 0x2C );
	p.add( TheBroadcastStealthOwnFieldParse, 0 );
}
