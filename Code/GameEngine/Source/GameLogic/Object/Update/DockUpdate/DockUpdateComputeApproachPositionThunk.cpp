// readable body of ?computeApproachPosition@DockUpdate@@IAE?AUCoord3D@@HPAVObject@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h
class DockUpdate
{
protected:
	Coord3D computeApproachPosition(int, Object *);
};

__declspec(naked) Coord3D DockUpdate::computeApproachPosition(int, Object *)
{
	__asm {
		_emit 0E9h
		_emit 073h
		_emit 0DFh
		_emit 02Ah
		_emit 000h
	}
}
