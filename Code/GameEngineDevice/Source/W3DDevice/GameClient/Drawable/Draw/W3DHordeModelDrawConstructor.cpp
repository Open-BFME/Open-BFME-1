// cl: /DNDEBUG /MD /EHsc

// W3DHordeModelDraw's constructor, retail 0x00751CF0.
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
	// The two vftable pointers reach +0x10; W3DHordeModelDraw's own first member
	// is at +0x27C, so this is what sits between. Only its size is claimed.
	unsigned char m_unmodelled_10[ 0x27C - 0x10 ];
};

class W3DHordeModelDraw : public W3DScriptedModelDraw
{
public:
	W3DHordeModelDraw( Thing *thing, const ModuleData *moduleData );

private:
	int m_unmodelled_27C;			// +0x27C
	int m_unmodelled_280;			// +0x280
	int m_unmodelled_284;			// +0x284
};

// The counter the constructor bumps. Nothing in the image names it; it is
// reached by what this body does to it.
extern int TheW3DHordeModelDrawCount;	// 0x01304B60

W3DHordeModelDraw::W3DHordeModelDraw( Thing *thing, const ModuleData *moduleData )
	: W3DScriptedModelDraw( thing, moduleData ),
	  m_unmodelled_27C( 0 ), m_unmodelled_280( 0 ), m_unmodelled_284( 0 )
{
	++TheW3DHordeModelDrawCount;
}
