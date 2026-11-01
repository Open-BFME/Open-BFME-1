// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InstantDeathBehavior.h
class InstantDeathBehaviorModuleData
{
public:
    virtual ~InstantDeathBehaviorModuleData();
};

// The scalar destructor is matched out of line in
// InstantDeathBehaviorModuleDataDestructorThunk.cpp. The implicit copy
// constructor (no retail twin) emits the vftable and with it the
// compiler-owned deleting destructor, without a second destructor body.
void forceInstantDeathBehaviorModuleDataDeletingDestructor(const InstantDeathBehaviorModuleData &that)
{
	InstantDeathBehaviorModuleData value(that);
}
