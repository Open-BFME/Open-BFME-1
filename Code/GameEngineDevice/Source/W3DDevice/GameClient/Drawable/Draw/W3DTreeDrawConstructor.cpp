// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DTreeDraw@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTreeDraw.cpp

// W3DTreeDraw's constructor, retail 0x0077F1C0.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTreeDraw.h
class W3DTreeDraw : public DrawModule
{
public:
	W3DTreeDraw( Thing *thing, const ModuleData *moduleData );

private:
	bool m_unmodelled_0C;			// +0x0C
};

W3DTreeDraw::W3DTreeDraw( Thing *thing, const ModuleData *moduleData )
	: DrawModule( thing, moduleData ), m_unmodelled_0C( false )
{
}
