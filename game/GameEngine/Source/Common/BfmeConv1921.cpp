#include "../../../Libraries/Include/Lib/Coord3D.h"

class BfmeResBX
{
public:
	unsigned char m_bfmeHeadBX[0xb0];
	int m_bfmeValueBX;
};

// BFME's damage and death enums; the values match the kill(8, 0) call that
// ScriptActions_KillHordeMembers.cpp spells DAMAGE_UNRESISTABLE, DEATH_NORMAL.
enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

// The owner held at this-8 is an Object. Thing is its polymorphic primary
// base; only the eleventh virtual slot is called here.
class Thing
{
public:
	virtual void bfmeSlot00BX();
	virtual void bfmeSlot01BX();
	virtual void bfmeSlot02BX();
	virtual void bfmeSlot03BX();
	virtual void bfmeSlot04BX();
	virtual void bfmeSlot05BX();
	virtual void bfmeSlot06BX();
	virtual void bfmeSlot07BX();
	virtual void bfmeSlot08BX();
	virtual void bfmeSlot09BX();
	virtual BfmeResBX *bfmeGetBX();

	void setPosition(const Coord3D *pos);			// retail ILT 0x0003A1A7 -> 0x00132CE0
};

class Object : public Thing
{
public:
	void kill(DamageType damageType, DeathType deathType);	// retail ILT 0x00014506 -> 0x001C30F0

	unsigned char m_bfmeHeadBX[0x38 - 4];
	Coord3D m_bfmeAtBX;							// +0x38
	unsigned char m_bfmeMidBX[0x344 - 0x44];
	unsigned char m_bfmeFlagsBX;				// +0x344
};

// The retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined
// once in game/GameEngine/Source/GameLogic/System/GameLogic.cpp.
class GameLogic
{
public:
	Object *findObjectByID(int id);				// retail ILT 0x0001F253 -> 0x0009A510
};

extern GameLogic *TheGameLogic;

class BfmeCfgBX
{
public:
	unsigned char m_bfmeHeadBX[0x34];
	unsigned char m_bfmeOnBX;
};

class BfmeSubBX
{
public:
	bool bfmeQueryBX(int *first, int *second);

	int m_bfme00BX;
	float m_bfme04BX;
	float m_bfme08BX;
	unsigned int m_bfme0cBX;
	unsigned int m_bfme10BX;
	int m_bfme14BX;
	int m_bfme18BX;
	unsigned int m_bfme1cBX;
	int m_bfme20BX;
	int m_bfme24BX;
};

extern float g_bfmeDefaultBU;
extern float g_bfmeUint32Scale;
extern const float g_rva01075350;

bool BfmeSubBX::bfmeQueryBX(int *first, int *second)
{
	(void)first;

	switch (m_bfme24BX)
	{
	case 0:
		if (m_bfme0cBX++ >= m_bfme10BX)
		{
			m_bfme24BX = 1;
			m_bfme0cBX = 0;
			*(volatile int *)second = m_bfme00BX;
		}
		*second = 0;
		return true;

	case 1:
		{
			float phase = (float)(unsigned int)m_bfme14BX;
			float value = (m_bfme04BX - *(float *)&m_bfme00BX) /
				(g_bfmeDefaultBU > phase ? g_bfmeDefaultBU : phase);
			value += *(float *)second;
			*(float *)second = value;
			if (*(float *)second >= m_bfme04BX)
			{
				*(int *)second = *(int *)&m_bfme04BX;
				m_bfme24BX = 2;
			}
			return true;
		}

	case 2:
		{
			float phase = (float)(unsigned int)m_bfme18BX;
			float value = (m_bfme04BX - m_bfme08BX) /
				(g_bfmeDefaultBU > phase ? g_bfmeDefaultBU : phase);
			value = *(float *)second - value;
			*(float *)second = value;
			if (*(float *)second <= m_bfme08BX)
			{
				*(int *)second = *(int *)&m_bfme08BX;
				m_bfme24BX = 3;
				m_bfme0cBX = 0;
			}
			return true;
		}

	case 3:
		if (m_bfme0cBX++ >= m_bfme1cBX)
			m_bfme24BX = 4;
		*(int *)second = *(int *)&m_bfme08BX;
		return true;

	case 4:
		{
			float phase = (float)(unsigned int)m_bfme20BX;
			float value = m_bfme08BX /
				(g_bfmeDefaultBU > phase ? g_bfmeDefaultBU : phase);
			value = *(float *)second - value;
			*(float *)second = value;
			if (*(float *)second <= g_rva01075350)
			{
				*(int *)second = 0;
				m_bfme24BX = 5;
				m_bfme0cBX = 0;
			}
			return true;
		}

	default:
		*second = 0;
		return false;
	}
}

class BfmeHostBX
{
public:
	int bfmeStartBX();

	unsigned char m_bfmeHeadBX[0x10];
	int m_bfmeIdBX;
	int m_bfmeAtBX;
	BfmeSubBX m_bfmeSubBX;
};

int BfmeHostBX::bfmeStartBX()
{
	Object *owner = *(Object **)((char *)this - 8);

	if ((*(BfmeCfgBX **)((char *)this - 0xc))->m_bfmeOnBX != 0)
	{
		Object *o = 0;

		if (m_bfmeIdBX != 0)
			o = TheGameLogic->findObjectByID(m_bfmeIdBX);

		if (o != 0 && (o->m_bfmeFlagsBX & 1) == 0)
			owner->setPosition(&o->m_bfmeAtBX);
		else
			owner->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}

	BfmeResBX *r = owner->bfmeGetBX();

	if (r != 0)
	{
		m_bfmeSubBX.bfmeQueryBX(&m_bfmeAtBX, &m_bfmeAtBX);
		r->m_bfmeValueBX = m_bfmeAtBX;
	}

	return 1;
}
