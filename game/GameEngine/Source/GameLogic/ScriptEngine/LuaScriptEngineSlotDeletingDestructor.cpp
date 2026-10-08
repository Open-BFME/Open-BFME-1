// cl: /O2

// SubsystemDeleter<LuaScriptEngine> scalar-deleting destructor, retail
// 0x00071730 (30 bytes). The exact constructor at 0x00071710 installs the
// one-slot vtable, whose slot routes here.

class LuaScriptEngine;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceLuaScriptEngineSlotDeletingDestructor()
{
	SubsystemDeleter<LuaScriptEngine> value;
}
