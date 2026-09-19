class Object {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	bool isEmpty(void) const;
	void doFXObj(const Object *source, const Object *target) const;
};

class BfmeSecondaryTarget
{
public:
	void bfmeRun(Object *object, int mode, int enabled);
};

struct BfmeDualDispatchOwner
{
	char m_bfmeFields[8];
	FXList **m_bfmeFXBegin;
	FXList **m_bfmeFXEnd;
	char m_bfme10[4];
	BfmeSecondaryTarget **m_bfmeTargetBegin;
	BfmeSecondaryTarget **m_bfmeTargetEnd;
};

extern "C" const char g_bfmeDualDispatchSource[];
int StructureCollapseRandom(int low, int high, const char *source, int line);

class Gen_0028B910
{
public:
	void bfmeDispatch(void *a, void *b, void *c);

private:
	char m_bfmeFields[4];
	unsigned char m_bfmeComplete;
};

// ?bfmeDispatch@Gen_0028B910@@QAEXPAX00@Z
void Gen_0028B910::bfmeDispatch(void *, void *, void *)
{
	if (m_bfmeComplete)
		return;

	BfmeDualDispatchOwner *owner = *reinterpret_cast<BfmeDualDispatchOwner **>(
		reinterpret_cast<char *>(this) - 0x1C);
	int fxCount = owner->m_bfmeFXEnd - owner->m_bfmeFXBegin;
	if (fxCount > 0) {
		int index = StructureCollapseRandom(0, fxCount - 1,
			g_bfmeDualDispatchSource, 127);
		FXList *fx = owner->m_bfmeFXBegin[index];
		Object *object = *reinterpret_cast<Object **>(
			reinterpret_cast<char *>(this) - 0x18);
		if (fx != 0 && !fx->isEmpty())
			fx->doFXObj(object, 0);
	}

	int targetCount = owner->m_bfmeTargetEnd - owner->m_bfmeTargetBegin;
	if (targetCount > 0) {
		int index = StructureCollapseRandom(0, targetCount - 1,
			g_bfmeDualDispatchSource, 138);
		BfmeSecondaryTarget *target = owner->m_bfmeTargetBegin[index];
		if (target != 0) {
			Object *object = *reinterpret_cast<Object **>(
				reinterpret_cast<char *>(this) - 0x18);
			target->bfmeRun(object, 0, 0);
		}
	}

	m_bfmeComplete = 1;
}
