// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?setCashValue@SupplyWarehouseDockUpdate@@QAEXH@Z: Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate.cpp
// Lift the SupplyWarehouseDockUpdate::setCashValue naked dump to clean C++.
//
// Zero Hour's SupplyWarehouseDockUpdate.cpp carries this body: convert a cash
// amount into whole supply boxes, then push the new count at the drawable if
// there is one. Retail pins what ZH leaves symbolic --
// m_baseValuePerSupplyBox at GlobalData+0xB24, m_boxesStored at this+0x88, the
// module data at this+0x04, the owning object at this+0x08, and getDrawable on
// the object vtable at +0x28.
//
// The `fild` / `fidiv` pair is the tell that the divisor stays an int operand:
// the numerator is promoted and the int is divided in place, so the source
// divides a floating-point cashValue by the raw int rather than casting both.

typedef int Int;

// /MD pulls ceil from the CRT DLL, so retail calls it indirectly through the
// import table (`ff 15`) rather than with a direct rel32.
extern "C" __declspec(dllimport) double __cdecl ceil(double);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void updateDrawableSupplyStatus(Int maxBoxes, Int currentBoxes);	///< ILT thunk at 0x00031615
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual Drawable *getDrawable(void) const;							///< vtable +0x28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0xB24];
	Int m_baseValuePerSupplyBox;										///< retail this+0xB24
};

extern GlobalData *TheWritableGlobalData;								///< retail [0x012ED5C8]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseDockUpdate.h
class SupplyWarehouseDockUpdateModuleData
{
public:
	unsigned char m_unreconstructed_00[0x10];
	Int m_startingBoxesData;											///< retail this+0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseDockUpdate.h
class SupplyWarehouseDockUpdate
{
public:
	void setCashValue(Int);

private:
	unsigned char m_unreconstructed_00[4];
	SupplyWarehouseDockUpdateModuleData *m_moduleData;					///< retail this+0x04
	Object *m_object;													///< retail this+0x08
	unsigned char m_unreconstructed_0C[0x88 - 0x0C];
	Int m_boxesStored;													///< retail this+0x88
};

// ?setCashValue@SupplyWarehouseDockUpdate@@QAEXH@Z
void SupplyWarehouseDockUpdate::setCashValue(Int cashValue)
{
	// A script can tell us our set value, and we need to figure out the boxes needed to provide that.
	m_boxesStored = (Int)ceil((double)cashValue / TheWritableGlobalData->m_baseValuePerSupplyBox);

	Drawable *draw = m_object->getDrawable();
	if (draw)
	{
		draw->updateDrawableSupplyStatus(m_moduleData->m_startingBoxesData, m_boxesStored);
	}
}
