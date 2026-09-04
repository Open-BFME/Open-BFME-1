// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::groupAttackMoveToPosition, retail 0x0015A030, 198 bytes.
//
// ZH twin in AIGroup.cpp (the per-member isAbleToAttack / aiAttackMove /
// aiMoveToPosition walk) plus a BFME formation preamble: when the group has
// more than one member, TAiData+0xB6 and +0xB9 are set, and the command is
// CMD_FROM_PLAYER, tryGroupSpecial (ILT 0x00046876, body 0x001599A0) may
// consume the order. Named caller is GameLogic::logicMessageDispatcher
// MSG_DO_ATTACKMOVETO. m_memberList is the STLport list at +4; AI lives at
// Object+0x204 and the command interface at AI+0x20.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class TAiData
{
public:
	unsigned char m_unmodelled_000[0xB6];
	unsigned char m_bfmeB6;					// +0xB6
	unsigned char m_bfmeB7;
	unsigned char m_bfmeB8;
	unsigned char m_bfmeB9;					// +0xB9
};

class AI
{
public:
	TAiData *getAiData()
	{
		return m_aiData;
	}

private:
	unsigned char m_unmodelled_000[0x14];
	TAiData *m_aiData;						// +0x14
};

extern AI *TheAI;

class AICommandInterface
{
public:
	void aiAttackMoveToPosition(const Coord3D *pos, int maxShotsToFire,
		CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class BfmeGroupAI
{
public:
	unsigned char m_unmodelled_000[0x20];
	AICommandInterface m_commands;			// +0x20
};

class Object
{
public:
	bool isAbleToAttack() const;
	BfmeGroupAI *getAI()
	{
		return m_ai;
	}

private:
	unsigned char m_unmodelled_000[0x204];
	BfmeGroupAI *m_ai;						// +0x204
};

class AIGroup
{
public:
	void groupAttackMoveToPosition(const Coord3D *pos, int maxShotsToFire,
		CommandSourceType cmdSource);
	bool tryGroupSpecial(const Coord3D *pos, int a, int b, int c, int d);

private:
	unsigned char m_unmodelled_000[4];
	_STL::list<Object *> m_memberList;		// +0x04
};

void AIGroup::groupAttackMoveToPosition(const Coord3D *pos, int maxShotsToFire,
	CommandSourceType cmdSource)
{
	unsigned int count = m_memberList.size();
	float countF = (float)count;
	const Coord3D *dest = pos;
	CommandSourceType src = cmdSource;
	if (countF > 1.0f)
	{
		TAiData *data = TheAI->getAiData();
		if (data->m_bfmeB6 && src == CMD_FROM_PLAYER && data->m_bfmeB9)
		{
			if (tryGroupSpecial(dest, src, 1, src, 1))
				return;
		}
	}

	_STL::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		BfmeGroupAI *ai = obj->getAI();
		if (ai)
		{
			if (obj->isAbleToAttack())
				ai->m_commands.aiAttackMoveToPosition(dest, maxShotsToFire, src);
			else
				ai->m_commands.aiMoveToPosition(dest, src);
		}
	}
}
