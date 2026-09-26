// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: LuaScriptEngine scalar-deleting destructor at retail RVA
// 0x002EB990 (30 bytes). The exact constructor at 0x002EB4A0, complete
// destructor at 0x002EB5C0, subsystem registration, global, and vtable
// 0x010CFAC4 establish the class. The destructor ILT is 0x0000AC22.

class LuaScriptEngine
{
public:
	virtual ~LuaScriptEngine();
};

void forceLuaScriptEngineDeletingDestructor()
{
	LuaScriptEngine value;
}
