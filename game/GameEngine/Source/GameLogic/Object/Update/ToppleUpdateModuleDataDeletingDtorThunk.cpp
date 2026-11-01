// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ToppleUpdate.h
class ToppleUpdateModuleData
{
public:
    __declspec(noinline) virtual ~ToppleUpdateModuleData();
};

// The scalar destructor remains ledger-backed by its retail MASM dump; this
// definition emits the compiler-owned deleting destructor at the vtable slot.
// ~ToppleUpdateModuleData is matched out of line (ToppleUpdateModuleDataDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceToppleUpdateModuleDataDeletingDestructorCopy(const ToppleUpdateModuleData &that)
{
	ToppleUpdateModuleData value(that);
}
