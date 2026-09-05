// cl: /DNDEBUG /MD /EHsc
// Open-BFME: AIGroup stealth-module walk, retail 0x00156B10, 173 bytes.
// Same member list as groupHunt (sentinel at +4, object at node+8, AI at +0x204).
// For each non-null member, NAMEKEY("StealthUpdate") then findUpdateModule.
// If the stealth module exists: aiIdle(CMD_FROM_AI) on AI+0x20 when AI is
// present, then a niladic thiscall on the stealth module (ILT 0x000272AF).
// Descriptive name: identity is the group walk plus the StealthUpdate string;
// the owning method is not ZH groupIdle (no CommandSourceType argument).

enum NameKeyType { NAMEKEY_INVALID = 0 };

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);		// ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			// 0x012ED600

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);		// ILT 0x00024D70
};

class BfmeGroupAI
{
public:
	char m_bfmeHead[0x20];
	AICommandInterface m_bfmeCommands;			// +0x20
};

class StealthUpdate
{
public:
	void update002AD250();					// ILT 0x000272AF -> 0x002ad250; RVA-derived
};

class Object
{
public:
	StealthUpdate *findUpdateModule(NameKeyType key);	// ILT 0x0002AE23

	char m_bfmeHead[0x204];
	BfmeGroupAI *m_bfmeAI;					// +0x204
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;
	BfmeListNodeBase *m_bfmePrev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;
};

class AIGroup
{
public:
	void groupStealthIdle();

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;
};

void AIGroup::groupStealthIdle()
{
	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		if (!obj)
			continue;

		BfmeGroupAI *ai = obj->m_bfmeAI;
		static const NameKeyType key_StealthUpdate = NAMEKEY("StealthUpdate");
		StealthUpdate *stealth = obj->findUpdateModule(key_StealthUpdate);
		if (!stealth)
			continue;

		if (ai)
			ai->m_bfmeCommands.aiIdle(CMD_FROM_AI);
		stealth->update002AD250();
	}
}
