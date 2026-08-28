// cl: /DNDEBUG /MD /EHsc

// SpecialPowerModuleData::buildFieldParse, retail 0x0077D380. Seventeen bytes:
// one call to MultiIniFieldParse::add with this class's own table and an offset
// of zero, and a tail return.
//
// No inherited table is added ahead of it, which is what makes this the top of
// that chain - BroadcastStealthUpdateModuleData's version adds two, its base's
// at 0x2C and its own at 0.

typedef unsigned int UnsignedInt;

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	void add( const FieldParse *table, UnsignedInt offset );
};

extern const FieldParse TheSpecialPowerModuleDataFieldParse[];		// 0x01124F90

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	static void buildFieldParse( MultiIniFieldParse &p );
};

// ?buildFieldParse@SpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
/*static*/ void SpecialPowerModuleData::buildFieldParse( MultiIniFieldParse &p )
{
	p.add( TheSpecialPowerModuleDataFieldParse, 0 );
}
