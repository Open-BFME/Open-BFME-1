// cl: /DNDEBUG /MD /EHsc

// W3DModelDrawModuleData::buildFieldParse, retail 0x0077D380. Seventeen bytes:
// one call to MultiIniFieldParse::add with this class's own table and an offset
// of zero, and a tail return.
//
// The module data factory for W3DScriptedModelDraw at 0x006BF0C0 pushes this
// address before it calls INI::initFromINIMultiProc, which is what names the
// class. The table it adds sits at 0x01124F90 and starts InitialRecoilSpeed,
// MaxRecoilDistance, RecoilDamping. Its EmbedPortal row carries member offset
// 0xF0, the same offset the matched parser
// ?parseEmbedPortal@W3DModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z records.
//
// Five bodies call this one through the incremental-link thunk at 0x00022584:
// the buildFieldParse of W3DHordeModelDraw, W3DQuadrupedDraw, W3DSupplyDraw,
// W3DTankDraw and W3DTruckDraw. Every one of those derives from W3DModelDraw,
// so this is the top of that chain.

typedef unsigned int UnsignedInt;

struct FieldParse;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	void add( const FieldParse *table, UnsignedInt offset );
};

extern const FieldParse TheW3DModelDrawModuleDataFieldParse[];		// 0x01124F90

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DModelDrawModuleData
{
public:
	static void buildFieldParse( MultiIniFieldParse &p );
};

// ?buildFieldParse@W3DModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z
/*static*/ void W3DModelDrawModuleData::buildFieldParse( MultiIniFieldParse &p )
{
	p.add( TheW3DModelDrawModuleDataFieldParse, 0 );
}
