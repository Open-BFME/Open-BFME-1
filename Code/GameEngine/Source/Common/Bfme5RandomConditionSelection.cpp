class BfmeConditionFlags
{
	public:
	unsigned int m_bits[10];
};

struct BfmeConditionChoice
{
	BfmeConditionFlags m_flags;
	int m_bfmeValue;
	int m_bfmeUnused;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void clearAndSetModelConditionFlags(const BfmeConditionFlags &clear,
		const BfmeConditionFlags &set);
	void bfmeSetConditionState(int state);
};

struct BfmeConditionChoiceOwner
{
	char m_bfmeFields[8];
	BfmeConditionChoice *m_bfmeBegin;
	BfmeConditionChoice *m_bfmeEnd;
};

extern "C" const char g_bfmeD8F0Source[];
int StructureCollapseRandom(int low, int high, const char *source, int line);

class Gen_0028D8F0
{
public:
	void bfmeSelectCondition(void);
	void bfmeComplete(Object *object, int value);

private:
	char m_bfmeFields[4];
	BfmeConditionChoiceOwner *m_bfmeOwner;
	Object *m_bfmeObject;
	char m_bfme0C[0x14];
	unsigned char m_bfmeActive;
	unsigned char m_bfmeAlternate;
};

// ?bfmeSelectCondition@Gen_0028D8F0@@QAEXXZ
void Gen_0028D8F0::bfmeSelectCondition(void)
{
	Object *object = m_bfmeObject;
	BfmeConditionChoiceOwner *owner = m_bfmeOwner;
	int count = owner->m_bfmeEnd - owner->m_bfmeBegin;
	if (count < 1)
		return;

	bool alternate = StructureCollapseRandom(0, count - 1,
		g_bfmeD8F0Source, 276) != 0;
	BfmeConditionFlags clear = {};
	m_bfmeAlternate = alternate;
	object->clearAndSetModelConditionFlags(clear,
		owner->m_bfmeBegin[alternate].m_flags);
	object->bfmeSetConditionState(4);
	m_bfmeActive = 1;
	bfmeComplete(object, owner->m_bfmeBegin[m_bfmeAlternate].m_bfmeValue);
}
