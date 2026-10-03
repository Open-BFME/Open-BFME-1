// Open-BFME: guarded global flag update reconstructed from retail RVA 0x002E2B50.

class Rva002E2B50Object
{
public:
	char m_pad0[0x14];
	unsigned char m_flag;
};

class Rva002E2B50Global
{
public:
	char m_pad0[0x78];
	Rva002E2B50Object *m_object;
};

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

int Rva002E2B50Update(void)
{
	Rva002E2B50Global *global = reinterpret_cast<Rva002E2B50Global *>(TheLuaScriptEngine);
	Rva002E2B50Object *object = global->m_object;
	if (object != 0)
		object->m_flag = 1;
	return false;
}
