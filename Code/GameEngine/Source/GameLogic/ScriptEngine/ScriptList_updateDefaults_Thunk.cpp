// cl: /DNDEBUG /MD /EHsc
// readable body of ??0ScriptList@@QAE@XZ: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class ScriptList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
struct SidesInfo
{
	void *m_dict;
	void *m_buildList;
	ScriptList *m_scriptList;
	void *m_rest[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
class SidesList
{
public:
	unsigned char m_head[0x28];
	int m_numSides;
	SidesInfo m_sides[1];

	int getNumSides(void) { return m_numSides; }
	SidesInfo *getSideInfo(int i)
	{
		return (i >= 0 && i < m_numSides) ? &m_sides[i] : 0;
	}
};

extern SidesList *TheSidesList;

// The two 0x20-byte blocks at +0x0C and +0x2C are byte-for-byte the same
// initialiser, so they are one member type used twice rather than sixteen
// separate fields.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
struct ScriptGroup
{
	void *m_a;
	void *m_b;
	void *m_c;
	void *m_d;
	void *m_e;
	void *m_f;
	int m_g;
	int m_h;
	ScriptGroup(void) : m_a(0), m_b(0), m_c(0), m_d(0), m_e(0), m_f(0), m_g(-1), m_h(-1) {}
};

// Zeroed before the vtable store, so they belong to a base with no virtuals of
// its own: MSVC puts the derived vfptr at +0 and pushes such a base to +4.
class ScriptListBase
{
public:
	void *m_x;
	void *m_y;
	ScriptListBase(void) : m_x(0), m_y(0) {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptList : public ScriptListBase
{
public:
	ScriptGroup m_first;
	ScriptGroup m_second;

	virtual void reset(void);
	static void updateDefaults(void);
};

// ?updateDefaults@ScriptList@@SAXXZ
void ScriptList::updateDefaults(void)
{
	for (int i = 0; i < TheSidesList->getNumSides(); i++) {
		if (TheSidesList->getSideInfo(i)->m_scriptList == 0)
			TheSidesList->getSideInfo(i)->m_scriptList = new ScriptList;
	}
}
