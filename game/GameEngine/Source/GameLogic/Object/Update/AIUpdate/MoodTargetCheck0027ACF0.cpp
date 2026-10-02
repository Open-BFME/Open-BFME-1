// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// Retail 0x0027ACF0 (263 bytes), address-derived AIUpdateInterface method.
// Receiver +8 and +0x30 agree with the AIUpdateInterface layout; calls to
// getCurrentVictim / getNextMoodTarget / friend_setGoalObject / destroyPath
// and virtual slot 128 establish the receiver family, not a semantic name.
// The native OVERRIDE and State::getID accessor layers are intentional:
// flattening them changes allocation and the null-current-state branch.
// Frame modulo is unsigned; Object::m_id modulo is signed (retail div/idiv).
// Pathfinder takes the actual Weapon pointer, not a boolean presence test.
// Object::m_id@0x74 and ThingTemplate::m_kindof@0xC8 are layout witnesses.

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
	const Overridable *getFinalOverride() const { if(m_nextOverride) return m_nextOverride->getFinalOverride(); return this; }

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xc8 - 0x8];
	unsigned int m_kindof;
};

template<class T> class OVERRIDE { public: const T *operator->() const { if(!value) return 0; return (const T*)value->getFinalOverride(); } operator const T*() const { return operator->(); } const T *value; };
class Thing
{
public:
	bool isKindOf(KindOfType) const;

	void *m_vtable;
	OVERRIDE<ThingTemplate> m_template;
};

class Object : public Thing
{
public:
	unsigned char m_pad08[0x74 - 0x8];
	int m_id;
	unsigned char m_pad78[0x94 - 0x78];
	unsigned char m_flagsAt94;
};

class Weapon;
class BfmePathfinderMethods
{
public:
	bool check(const Object *, const Coord3D *, const Weapon *, int);
};
void j_00032b46();

class AI
{
public:
	unsigned char m_pad00[0x0c];
	BfmePathfinderMethods *m_pathfinder;
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
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

class MoodState0027ACF0 { public: void *vptr; int m_ID; int getID() const { return m_ID; } };
class MoodMachine0027ACF0 { public: char pad[0x1c]; MoodState0027ACF0 *m_currentState; int getStateID() const { return m_currentState ? m_currentState->getID() : 0xf423f; } };
class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
	void friend_setGoalObject(Object *object);
	Object *getNextMoodTarget(bool a, bool b);
	void destroyPath();

	bool rva0027ACF0MoodTargetCheck();

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

	unsigned char m_pad04[4];
	Object *m_object;
	unsigned char m_pad0c[0x30 - 0x0c];
	MoodMachine0027ACF0 *m_stateMachine;
};

// ?rva0027ACF0MoodTargetCheck@AIUpdateInterface@@QAE_NXZ
bool AIUpdateInterface::rva0027ACF0MoodTargetCheck()
{
	Object *object = m_object;
	if (object->m_flagsAt94 & 0x20)
		return false;

	const ThingTemplate *finalTemplate = object->m_template;
	if (finalTemplate->m_kindof & 4)
		return false;

	if (TheGameLogic->m_frame % 10 != object->m_id % 10)
		return false;

	int stateID = m_stateMachine->getStateID();

	if (stateID == 0x11)
		return false;

	if(slot128() == 2 || stateID == 0x21)
    {
        Object *victim = getCurrentVictim();
        if(victim && victim->isKindOf((KindOfType)7))
        {
            Object *candidate = getNextMoodTarget(true,false);
            if(candidate && candidate != victim && !candidate->isKindOf((KindOfType)7))
            {
                BfmePathfinderMethods *pathfinder = TheAI->m_pathfinder;
                typedef bool (BfmePathfinderMethods::*PathfinderCheckFunction)(
                    const Object *, const Coord3D *, const Weapon *, int);
                union { void (*raw)(void); PathfinderCheckFunction member; }
                    pathfinderCheck;
                pathfinderCheck.raw = j_00032b46;
                if((pathfinder->*pathfinderCheck.member)(
                    object, (Coord3D*)((char*)candidate+0x38),
                    (const Weapon*)((AssistedTargetingObjectShim*)object)->find(0),0))
                {
                    friend_setGoalObject(candidate);
                    destroyPath();
                    return true;
                }
            }
        }
    }
    return false;
}
