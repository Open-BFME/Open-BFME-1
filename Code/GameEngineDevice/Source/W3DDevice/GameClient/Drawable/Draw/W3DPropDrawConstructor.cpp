// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DPropDraw@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDraw.cpp

// W3DPropDraw's constructor, retail 0x007592C0.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DPropDraw.h
class W3DPropDraw : public DrawModule
{
public:
	W3DPropDraw( Thing *thing, const ModuleData *moduleData );

private:
	bool m_unmodelled_0C;			// +0x0C
};

W3DPropDraw::W3DPropDraw( Thing *thing, const ModuleData *moduleData )
	: DrawModule( thing, moduleData ), m_unmodelled_0C( false )
{
}
