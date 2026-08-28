// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DSupplyDrawModuleData@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DSupplyDraw.cpp

// W3DSupplyDrawModuleData's constructor, retail 0x0077DD50. The base's
// constructor, this class's own vftable pointer, and one field at +0x15C
// zeroed - which is what fixes the base's size.

class W3DSupplyDrawModuleDataBase
{
public:
	W3DSupplyDrawModuleDataBase();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x15C - 4 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DSupplyDraw.h
class W3DSupplyDrawModuleData : public W3DSupplyDrawModuleDataBase
{
public:
	W3DSupplyDrawModuleData();

private:
	int m_unmodelled_15C;					// +0x15C
};

// ??0W3DSupplyDrawModuleData@@QAE@XZ
W3DSupplyDrawModuleData::W3DSupplyDrawModuleData()
	: m_unmodelled_15C( 0 )
{
}
