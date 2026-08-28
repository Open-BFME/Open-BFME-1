// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DSupplyDraw@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DSupplyDraw.cpp

// W3DSupplyDraw's constructor, retail 0x0077DB70.
//
// The base is W3DScriptedModelDraw - the call goes to 0x00773360, the 1185-byte
// constructor that still has no source. Two vftable pointers rather than one:
// the model-draw side adds an interface whose pointer lands at +0x0C, right
// after the draw base's own pointer and its eight bytes of state.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	virtual void drawModuleAnchor();

private:
	unsigned char m_data[8];
};

class W3DModelDrawInterface
{
public:
	virtual void w3dModelDrawInterfaceAnchor();
};

class W3DScriptedModelDraw : public DrawModule, public W3DModelDrawInterface
{
public:
	W3DScriptedModelDraw( Thing *thing, const ModuleData *moduleData );

private:
	// The two vftable pointers reach +0x10; W3DSupplyDraw's own first member is
	// at +0x27C, so this is what sits between. Only its size is claimed.
	unsigned char m_unmodelled_10[ 0x27C - 0x10 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DSupplyDraw.h
class W3DSupplyDraw : public W3DScriptedModelDraw
{
public:
	W3DSupplyDraw( Thing *thing, const ModuleData *moduleData );

private:
	int m_unmodelled_27C;			// +0x27C, set to -1
	int m_unmodelled_280;			// +0x280, zeroed
};

W3DSupplyDraw::W3DSupplyDraw( Thing *thing, const ModuleData *moduleData )
	: W3DScriptedModelDraw( thing, moduleData ), m_unmodelled_27C( -1 ), m_unmodelled_280( 0 )
{
}
