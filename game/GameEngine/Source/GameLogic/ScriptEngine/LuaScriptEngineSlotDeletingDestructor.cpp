// cl: /O2

// SubsystemSlot<LuaScriptEngine> scalar-deleting destructor, retail
// 0x00071730 (30 bytes). The exact constructor at 0x00071710 installs the
// one-slot vtable, whose slot routes here.

class LuaScriptEngine;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceLuaScriptEngineSlotDeletingDestructor()
{
	SubsystemSlot<LuaScriptEngine> value;
}
