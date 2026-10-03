// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BaseRegenerateUpdateModuleData constructor lifted from retail.
//
// Retail body 0x0028C2A0 (9 bytes): mov eax,ecx / mov [eax],0x010bd400 / ret --
// the vftable store of a ModuleData with no members of its own.
//
// The virtual destructor is defined in-class so vftable slot 0 resolves inside
// this TU.  Declared with no body it left ??1BaseRegenerateUpdateModuleData@@UAE@XZ
// as the file's one link blocker, because the class's vftable
// (retail 0x010BD400, whose slot 0 is a scalar deleting destructor, retail
// 0x0040FF38 -> ?j_0000ff38@@YAXXZ -> ??_GGen_dtor_0028c450@@UAEPAXI@Z owned by
// game/gen_small/dtors_003.cpp) references it.  This body claims no retail
// address: the destructor body belongs to that other ledger row.
//
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BaseRegenerateUpdate.h
class BaseRegenerateUpdateModuleData
{
public:
	BaseRegenerateUpdateModuleData();

	virtual ~BaseRegenerateUpdateModuleData() {}
};

// ??0BaseRegenerateUpdateModuleData@@QAE@XZ
BaseRegenerateUpdateModuleData::BaseRegenerateUpdateModuleData()
{
}