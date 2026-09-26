// ?rva0027ACF0MoodTargetCheck@AIUpdateInterface@@QAE_NXZ
// partial score=0.5 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// Retail 0x0027ACF0, 263B, thiscall on AIUpdateInterface (ecx used as
// "this" throughout, never clobbered). No caller/vtable slot proves the
// method's own identity or purpose, but every field/callee is proven by
// existing landed siblings: Object::m_id at +0x74 and ThingTemplate::
// m_kindof at +0xc8 (tools/name_oracle.py), the getFinalOverride idiom
// already landed for CastleBehavior siblings, the AIUpdateInterface vtable
// slot-127 padding idiom from AIUpdate.cpp's chooseLocomotorSet (our vcall
// is the very next slot, +0x200), and AIUpdateInterface::getCurrentVictim /
// friend_setGoalObject / getNextMoodTarget / destroyPath (all matched in
// AIUpdate.cpp; this caller's own REL32 targets the ILT thunks pinned to
// those same decorated names in reverse/symbols.csv, so the additive
// candidate resolver tries both addresses). Address-derived method name
// kept per naming rules.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum KindOfType { };

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xc8 - 0x8];
	unsigned int m_kindof;
};

class Thing
{
public:
	bool isKindOf(KindOfType) const;

	void *m_vtable;
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	unsigned char m_pad08[0x74 - 0x8];
	int m_id;
	unsigned char m_pad78[0x94 - 0x78];
	unsigned char m_flagsAt94;
};

class Rva00032B46Pathfinder
{
public:
	bool check(Object *, Coord3D *, bool, bool);
};

class AI
{
public:
	unsigned char m_pad00[0x0c];
	Rva00032B46Pathfinder *m_pathfinder;
};
extern AI *TheAI;

class AssistedTargetingObjectShim
{
public:
	void *find(int slotOut);
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	int m_frame;
};
extern GameLogic *TheBfmeGameLogic;

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
	void friend_setGoalObject(Object *object);
	Object *getNextMoodTarget(bool a, bool b);
	void destroyPath();

	bool rva0027ACF0MoodTargetCheck();

	void *m_vtable;
	unsigned char m_pad04[4];
	Object *m_object;
	unsigned char m_pad0c[0x30 - 0x0c];
	void *m_stateMachine;
};

// Reaches the AIUpdateInterface's own vtable slot 128 (+0x200), one past
// the vtable-127 chooseLocomotorSet idiom already landed in AIUpdate.cpp.
class AIUpdateInterface_Slot128
{
public:
	virtual void _pad0(void) = 0;
	virtual void _pad1(void) = 0;
	virtual void _pad2(void) = 0;
	virtual void _pad3(void) = 0;
	virtual void _pad4(void) = 0;
	virtual void _pad5(void) = 0;
	virtual void _pad6(void) = 0;
	virtual void _pad7(void) = 0;
	virtual void _pad8(void) = 0;
	virtual void _pad9(void) = 0;
	virtual void _pad10(void) = 0;
	virtual void _pad11(void) = 0;
	virtual void _pad12(void) = 0;
	virtual void _pad13(void) = 0;
	virtual void _pad14(void) = 0;
	virtual void _pad15(void) = 0;
	virtual void _pad16(void) = 0;
	virtual void _pad17(void) = 0;
	virtual void _pad18(void) = 0;
	virtual void _pad19(void) = 0;
	virtual void _pad20(void) = 0;
	virtual void _pad21(void) = 0;
	virtual void _pad22(void) = 0;
	virtual void _pad23(void) = 0;
	virtual void _pad24(void) = 0;
	virtual void _pad25(void) = 0;
	virtual void _pad26(void) = 0;
	virtual void _pad27(void) = 0;
	virtual void _pad28(void) = 0;
	virtual void _pad29(void) = 0;
	virtual void _pad30(void) = 0;
	virtual void _pad31(void) = 0;
	virtual void _pad32(void) = 0;
	virtual void _pad33(void) = 0;
	virtual void _pad34(void) = 0;
	virtual void _pad35(void) = 0;
	virtual void _pad36(void) = 0;
	virtual void _pad37(void) = 0;
	virtual void _pad38(void) = 0;
	virtual void _pad39(void) = 0;
	virtual void _pad40(void) = 0;
	virtual void _pad41(void) = 0;
	virtual void _pad42(void) = 0;
	virtual void _pad43(void) = 0;
	virtual void _pad44(void) = 0;
	virtual void _pad45(void) = 0;
	virtual void _pad46(void) = 0;
	virtual void _pad47(void) = 0;
	virtual void _pad48(void) = 0;
	virtual void _pad49(void) = 0;
	virtual void _pad50(void) = 0;
	virtual void _pad51(void) = 0;
	virtual void _pad52(void) = 0;
	virtual void _pad53(void) = 0;
	virtual void _pad54(void) = 0;
	virtual void _pad55(void) = 0;
	virtual void _pad56(void) = 0;
	virtual void _pad57(void) = 0;
	virtual void _pad58(void) = 0;
	virtual void _pad59(void) = 0;
	virtual void _pad60(void) = 0;
	virtual void _pad61(void) = 0;
	virtual void _pad62(void) = 0;
	virtual void _pad63(void) = 0;
	virtual void _pad64(void) = 0;
	virtual void _pad65(void) = 0;
	virtual void _pad66(void) = 0;
	virtual void _pad67(void) = 0;
	virtual void _pad68(void) = 0;
	virtual void _pad69(void) = 0;
	virtual void _pad70(void) = 0;
	virtual void _pad71(void) = 0;
	virtual void _pad72(void) = 0;
	virtual void _pad73(void) = 0;
	virtual void _pad74(void) = 0;
	virtual void _pad75(void) = 0;
	virtual void _pad76(void) = 0;
	virtual void _pad77(void) = 0;
	virtual void _pad78(void) = 0;
	virtual void _pad79(void) = 0;
	virtual void _pad80(void) = 0;
	virtual void _pad81(void) = 0;
	virtual void _pad82(void) = 0;
	virtual void _pad83(void) = 0;
	virtual void _pad84(void) = 0;
	virtual void _pad85(void) = 0;
	virtual void _pad86(void) = 0;
	virtual void _pad87(void) = 0;
	virtual void _pad88(void) = 0;
	virtual void _pad89(void) = 0;
	virtual void _pad90(void) = 0;
	virtual void _pad91(void) = 0;
	virtual void _pad92(void) = 0;
	virtual void _pad93(void) = 0;
	virtual void _pad94(void) = 0;
	virtual void _pad95(void) = 0;
	virtual void _pad96(void) = 0;
	virtual void _pad97(void) = 0;
	virtual void _pad98(void) = 0;
	virtual void _pad99(void) = 0;
	virtual void _pad100(void) = 0;
	virtual void _pad101(void) = 0;
	virtual void _pad102(void) = 0;
	virtual void _pad103(void) = 0;
	virtual void _pad104(void) = 0;
	virtual void _pad105(void) = 0;
	virtual void _pad106(void) = 0;
	virtual void _pad107(void) = 0;
	virtual void _pad108(void) = 0;
	virtual void _pad109(void) = 0;
	virtual void _pad110(void) = 0;
	virtual void _pad111(void) = 0;
	virtual void _pad112(void) = 0;
	virtual void _pad113(void) = 0;
	virtual void _pad114(void) = 0;
	virtual void _pad115(void) = 0;
	virtual void _pad116(void) = 0;
	virtual void _pad117(void) = 0;
	virtual void _pad118(void) = 0;
	virtual void _pad119(void) = 0;
	virtual void _pad120(void) = 0;
	virtual void _pad121(void) = 0;
	virtual void _pad122(void) = 0;
	virtual void _pad123(void) = 0;
	virtual void _pad124(void) = 0;
	virtual void _pad125(void) = 0;
	virtual void _pad126(void) = 0;
	virtual void _pad127(void) = 0;
	virtual int slot128(void) = 0;
};

// ?d_0027acf0@@YAXXZ
bool AIUpdateInterface::rva0027ACF0MoodTargetCheck()
{
	Object *object = m_object;
	if (object->m_flagsAt94 & 0x20)
		return false;

	ThingTemplate *tmpl = object->m_template;
	const ThingTemplate *finalTemplate = tmpl;
	if (tmpl)
	{
		if (tmpl->m_nextOverride)
			finalTemplate = (const ThingTemplate *)
				tmpl->m_nextOverride->getFinalOverride();
		else
			finalTemplate = tmpl;
	}
	if (finalTemplate->m_kindof & 4)
		return false;

	if (object->m_id % 10 != TheBfmeGameLogic->m_frame % 10)
		return false;

	int stateID;
	void *inner = *(void **)((char *)m_stateMachine + 0x1c);
	if (inner)
		stateID = *(int *)((char *)inner + 4);
	else
		stateID = 0xf423f;

	if (stateID == 0x11)
		return false;

	int vcallResult = reinterpret_cast<AIUpdateInterface_Slot128 *>(this)
		->slot128();
	if (vcallResult != 2 && stateID != 0x21)
		return false;

	Object *victim = getCurrentVictim();
	if (!victim)
		return false;
	if (!victim->isKindOf((KindOfType)7))
		return false;

	Object *candidate = getNextMoodTarget(true, false);
	if (!candidate)
		return false;
	if (candidate == victim)
		return false;
	if (candidate->isKindOf((KindOfType)7))
		return false;

	void *slot = ((AssistedTargetingObjectShim *)object)->find(0);
	if (!TheAI->m_pathfinder->check(object,
		(Coord3D *)((char *)candidate + 0x38), slot != 0, false))
		return false;

	friend_setGoalObject(candidate);
	destroyPath();
	return true;
}
