// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InstantDeathBehavior.h
class InstantDeathBehaviorModuleData
{
public:
    __declspec(noinline) virtual ~InstantDeathBehaviorModuleData();
};

// The scalar destructor's retail body remains ledger-backed by its MASM dump;
// this definition emits the compiler-owned deleting destructor at the vtable
// slot.
InstantDeathBehaviorModuleData::~InstantDeathBehaviorModuleData()
{
}
