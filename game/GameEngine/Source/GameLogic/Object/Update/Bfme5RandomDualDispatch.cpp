class Object {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
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

int StructureCollapseRandom(int low, int high, const char *source, int line);

class Coord3D;

// EA's CritterEmitterUpdate (ea_evidence.csv names 0x0028B910
// CritterEmitterUpdate::onCollide; the ILT oracle fits the virtual spelling).
// `this` is the collide-interface subobject, so the owner fields sit below it.
class CritterEmitterUpdate
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);

private:
	unsigned char m_bfmeComplete;
};

// ?onCollide@CritterEmitterUpdate@@UAEXPAVObject@@PBVCoord3D@@1@Z
void CritterEmitterUpdate::onCollide(Object *, const Coord3D *, const Coord3D *)
{
	if (m_bfmeComplete)
		return;

	BfmeDualDispatchOwner *owner = *reinterpret_cast<BfmeDualDispatchOwner **>(
		reinterpret_cast<char *>(this) - 0x1C);
	int fxCount = owner->m_bfmeFXEnd - owner->m_bfmeFXBegin;
	if (fxCount > 0) {
		int index = StructureCollapseRandom(0, fxCount - 1,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\CritterEmitter.cpp", 127);
		FXList *fx = owner->m_bfmeFXBegin[index];
		Object *object = *reinterpret_cast<Object **>(
			reinterpret_cast<char *>(this) - 0x18);
		if (fx != 0 && !fx->isEmpty())
			fx->doFXObj(object, 0);
	}

	int targetCount = owner->m_bfmeTargetEnd - owner->m_bfmeTargetBegin;
	if (targetCount > 0) {
		int index = StructureCollapseRandom(0, targetCount - 1,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\CritterEmitter.cpp", 138);
		BfmeSecondaryTarget *target = owner->m_bfmeTargetBegin[index];
		if (target != 0) {
			Object *object = *reinterpret_cast<Object **>(
				reinterpret_cast<char *>(this) - 0x18);
			target->bfmeRun(object, 0, 0);
		}
	}

	m_bfmeComplete = 1;
}
