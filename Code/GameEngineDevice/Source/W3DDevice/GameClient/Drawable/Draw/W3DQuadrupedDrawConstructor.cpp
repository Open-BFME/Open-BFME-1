// cl: /DNDEBUG /MD /EHsc

// W3DQuadrupedDraw's constructor, retail 0x00759730.
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
};

class W3DQuadrupedDraw : public W3DScriptedModelDraw
{
public:
	W3DQuadrupedDraw( Thing *thing, const ModuleData *moduleData );
};

W3DQuadrupedDraw::W3DQuadrupedDraw( Thing *thing, const ModuleData *moduleData )
	: W3DScriptedModelDraw( thing, moduleData )
{
}
