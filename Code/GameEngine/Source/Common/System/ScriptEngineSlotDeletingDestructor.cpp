// cl: /O2

// SubsystemSlot<ScriptEngine> scalar-deleting destructor, retail
// 0x00071670 (30 bytes). The exact constructor at 0x00071650 installs the
// one-slot vtable, whose slot routes here.

class ScriptEngine;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceScriptEngineSlotDeletingDestructor()
{
	SubsystemSlot<ScriptEngine> value;
}
