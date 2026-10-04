// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PhysicsBehaviorModuleData@@QAE@XZ: game/GameEngine/Source/GameLogic/Object/Update/PhysicsUpdate.cpp

// PhysicsBehaviorModuleData default constructor (0x0029A090, 126 B). The
// factory 0x0011AA70 allocates 0x5C bytes and calls this; it installs the
// dedicated vtable 0x00CC0910. BFME's layout differs from the Zero Hour header
// PhysicsUpdate.cpp compiles against, so this TU keeps an offset-named view.
//
// The defaults are assigned in field order except the three integers at
// +0x18..+0x20, which come last. That order is what makes MSVC keep 1.3 and
// then 0 in ECX, 0.66 in EDX and 5 in ECX again while 0.33 stays immediate:
// each constant register lives from its first to its last store.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PhysicsUpdate.h
class PhysicsBehaviorModuleData
{
public:
	PhysicsBehaviorModuleData();

protected:
	virtual ~PhysicsBehaviorModuleData();

private:
	unsigned int m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	float m_28;
	float m_2C;
	float m_30;
	float m_34;
	float m_38;
	float m_3C;
	bool m_40;
	bool m_41;
	bool m_42;
	float m_44;
	float m_48;
	float m_4C;
	unsigned int m_50;
	unsigned int m_54;
	bool m_allowBouncing;
	bool m_killWhenRestingOnGround;
};

PhysicsBehaviorModuleData::PhysicsBehaviorModuleData()
{
	m_08 = 1.3f;
	m_0C = 1.3f;
	m_10 = 0.33f;
	m_14 = 0.66f;
	m_24 = 2;
	m_28 = 5.0f;
	m_2C = 1.3f;
	m_30 = 1.3f;
	m_34 = 0.33f;
	m_38 = 0.66f;
	m_3C = 0.0f;
	m_40 = false;
	m_41 = false;
	m_42 = false;
	m_44 = 0.33f;
	m_48 = 0.66f;
	m_4C = 1.0f;
	m_50 = 0;
	m_54 = 0;
	m_allowBouncing = false;
	m_killWhenRestingOnGround = false;
	m_18 = 5;
	m_1C = 10;
	m_20 = 5;
}
