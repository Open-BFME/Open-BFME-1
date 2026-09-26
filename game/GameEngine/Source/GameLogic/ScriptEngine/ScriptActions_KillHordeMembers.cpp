// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME executeAction arm 0x1B4 (KILL_HORDE_MEMBERS), retail 0x002FD610.
// The arm passes the unit Parameter object and a Real percentage directly.

#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class ScriptActionParameter;
class Object;
class ContainModuleInterface;
class HordeContainInterface;

class ScriptEngine
{
public:
#define SCRIPT_ENGINE_SLOT(N) virtual void scriptEngineSlot##N() = 0
	SCRIPT_ENGINE_SLOT(00); SCRIPT_ENGINE_SLOT(01); SCRIPT_ENGINE_SLOT(02);
	SCRIPT_ENGINE_SLOT(03); SCRIPT_ENGINE_SLOT(04); SCRIPT_ENGINE_SLOT(05);
	SCRIPT_ENGINE_SLOT(06); SCRIPT_ENGINE_SLOT(07); SCRIPT_ENGINE_SLOT(08);
	SCRIPT_ENGINE_SLOT(09); SCRIPT_ENGINE_SLOT(10); SCRIPT_ENGINE_SLOT(11);
	SCRIPT_ENGINE_SLOT(12); SCRIPT_ENGINE_SLOT(13); SCRIPT_ENGINE_SLOT(14);
	SCRIPT_ENGINE_SLOT(15); SCRIPT_ENGINE_SLOT(16); SCRIPT_ENGINE_SLOT(17);
	SCRIPT_ENGINE_SLOT(18); SCRIPT_ENGINE_SLOT(19); SCRIPT_ENGINE_SLOT(20);
	SCRIPT_ENGINE_SLOT(21); SCRIPT_ENGINE_SLOT(22); SCRIPT_ENGINE_SLOT(23);
	SCRIPT_ENGINE_SLOT(24); SCRIPT_ENGINE_SLOT(25);
#undef SCRIPT_ENGINE_SLOT
	virtual Object *resolveUnit(ScriptActionParameter *parameter) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(N) virtual void containSlot##N() = 0
	CONTAIN_SLOT(00); CONTAIN_SLOT(01); CONTAIN_SLOT(02); CONTAIN_SLOT(03);
	CONTAIN_SLOT(04); CONTAIN_SLOT(05); CONTAIN_SLOT(06); CONTAIN_SLOT(07);
	CONTAIN_SLOT(08); CONTAIN_SLOT(09); CONTAIN_SLOT(10); CONTAIN_SLOT(11);
	CONTAIN_SLOT(12); CONTAIN_SLOT(13); CONTAIN_SLOT(14); CONTAIN_SLOT(15);
	CONTAIN_SLOT(16); CONTAIN_SLOT(17); CONTAIN_SLOT(18); CONTAIN_SLOT(19);
	CONTAIN_SLOT(20); CONTAIN_SLOT(21); CONTAIN_SLOT(22); CONTAIN_SLOT(23);
	CONTAIN_SLOT(24); CONTAIN_SLOT(25);
#undef CONTAIN_SLOT
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

class HordeContainInterface
{
public:
#define HORDE_SLOT(N) virtual void hordeSlot##N() = 0
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25); HORDE_SLOT(26); HORDE_SLOT(27);
	HORDE_SLOT(28); HORDE_SLOT(29); HORDE_SLOT(30); HORDE_SLOT(31);
	HORDE_SLOT(32); HORDE_SLOT(33); HORDE_SLOT(34); HORDE_SLOT(35);
	HORDE_SLOT(36); HORDE_SLOT(37); HORDE_SLOT(38); HORDE_SLOT(39);
	HORDE_SLOT(40); HORDE_SLOT(41); HORDE_SLOT(42); HORDE_SLOT(43);
	HORDE_SLOT(44); HORDE_SLOT(45); HORDE_SLOT(46); HORDE_SLOT(47);
	HORDE_SLOT(48); HORDE_SLOT(49); HORDE_SLOT(50); HORDE_SLOT(51);
	HORDE_SLOT(52); HORDE_SLOT(53); HORDE_SLOT(54); HORDE_SLOT(55);
	HORDE_SLOT(56); HORDE_SLOT(57); HORDE_SLOT(58);
#undef HORDE_SLOT
	virtual _STL::list<Object *> &getMemberList() = 0;
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
	void *getBodyModule() const { return m_body; }

	unsigned char m_beforeContain[0x1fc];
	ContainModuleInterface *m_contain;
	void *m_body;
};

class ScriptActions
{
protected:
	void doKillHordeMembers(ScriptActionParameter *unitParameter, Real percentage);
};

void ScriptActions::doKillHordeMembers(ScriptActionParameter *unitParameter, Real percentage)
{
	Int toKill = 0;
	Object *horde = TheScriptEngine->resolveUnit(unitParameter);
	if (horde == 0)
		return;

	ContainModuleInterface *contain = horde->m_contain;
	if (contain == 0)
		return;

	HordeContainInterface *hordeContain = contain->getHordeContainInterface();
	if (hordeContain == 0)
		return;

	{
		_STL::list<Object *> members(hordeContain->getMemberList());
		UnsignedInt memberCount = hordeContain->getMemberList().size();
		volatile Real &percentageView = percentage;
		toKill = (Int)((percentageView * 0.01f) * memberCount);
		if (toKill <= hordeContain->getMemberList().size() && toKill > 0)
		{
			for (_STL::list<Object *>::iterator it = members.begin(); it != members.end(); ++it)
			{
				Object *member = *it;
				if (member != 0 && member->getBodyModule() != 0 && toKill != 0)
				{
					member->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
					--toKill;
				}
			}
		}
	}
}
