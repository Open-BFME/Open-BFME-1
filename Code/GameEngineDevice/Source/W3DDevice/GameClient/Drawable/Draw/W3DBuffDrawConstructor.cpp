// cl: /DNDEBUG /MD /EHsc

// W3DBuffDraw's constructor, retail 0x00750240.
//
// One vftable store and one byte: DrawModule's constructor is out of line and
// leaves +0x00 to the most derived class, and the flag the derived class adds
// lands at +0x0C - immediately after DrawModule's vftable pointer and its eight
// bytes of state. Nothing else about either class is claimed here.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	DrawModule( Thing *thing, const ModuleData *moduleData );

	virtual void drawModuleAnchor();

private:
	unsigned char m_data[8];
};

class W3DBuffDraw : public DrawModule
{
public:
	W3DBuffDraw( Thing *thing, const ModuleData *moduleData );

private:
	bool m_unmodelled_0C;			// +0x0C
};

W3DBuffDraw::W3DBuffDraw( Thing *thing, const ModuleData *moduleData )
	: DrawModule( thing, moduleData ), m_unmodelled_0C( false )
{
}
