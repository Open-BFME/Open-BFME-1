// cl: /DNDEBUG /MD /EHsc

// W3DTruckDrawModuleData::buildFieldParse, retail 0x0077F760. Thirty bytes: it
// forwards to the base class builder through the incremental-link thunk at
// 0x00022584, then adds its own table at an offset of zero.
//
// The module data factory for W3DTruckDraw at 0x006BF4F0 pushes this address
// before it calls INI::initFromINIMultiProc, which names the class. The table
// it adds sits at 0x01126280 and runs Dust, DirtSpray, PowerslideSpray and the
// tire bones. Those rows carry member offsets 0x15C through 0x1AC, the same
// twenty-one strings the matched destructor
// ??1W3DTruckDrawModuleData@@UAE@XZ at 0x0077F920 releases in reverse.

typedef unsigned int UnsignedInt;

struct FieldParse;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	void add( const FieldParse *table, UnsignedInt offset );
};

extern const FieldParse TheW3DTruckDrawModuleDataFieldParse[];		// 0x01126280

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DModelDrawModuleData
{
public:
	static void buildFieldParse( MultiIniFieldParse &p );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTruckDraw.h
class W3DTruckDrawModuleData : public W3DModelDrawModuleData
{
public:
	static void buildFieldParse( MultiIniFieldParse &p );
};

// ?buildFieldParse@W3DTruckDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z
/*static*/ void W3DTruckDrawModuleData::buildFieldParse( MultiIniFieldParse &p )
{
	W3DModelDrawModuleData::buildFieldParse( p );
	p.add( TheW3DTruckDrawModuleDataFieldParse, 0 );
}
