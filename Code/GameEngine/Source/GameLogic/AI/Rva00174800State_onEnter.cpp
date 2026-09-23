// cl: /DNDEBUG /MD
//
// Retail 0x00174800: an AIInternalMoveToState-derived state's onEnter().
// The state-machine owner and its AI update are fetched, a critter-desync
// log line is emitted when TheCRCParameterCheck is live, and -- when the
// AI's byte flag at +0x336 is set -- the state removes the owner's goal
// from TheAI's pathfinder (TheAI->pathfinder()->removeGoal(owner)),
// computes a fixed-distance offset from the owner toward the (normalized)
// direction away from the goal object, requests a path there, then chains
// to the shared AIInternalMoveToState::onEnter(). When the flag is clear
// the state just flips its own continue/wait bookkeeping and returns
// STATE_CONTINUE without chaining to the base. Callees are spelled with their
// ledger identities (StateMachine::getGoalObject, chooseLocomotorSet slot 127,
// Pathfinder::removeGoal, bfmeRetailCritterDesyncLog); address-derived class
// and field names where identity is unknown; landed twins
// Rva00174730State_update.cpp / Rva00174A20State_update.cpp establish the
// AIInternalMoveToState machine/adjustDestinations layout reused here.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};

// Local minimal Coord3D: normalize() declared, not defined, so the call links
// against the already-matched ?normalize@Coord3D@@QAEXXZ (coord3d.cpp);
// set()/add() are the ZH BaseType.h inlines.
struct Coord3D
{
	float x;
	float y;
	float z;

	void normalize(void);

	void add(const Coord3D *a)
	{
		x += a->x;
		y += a->y;
		z += a->z;
	}

	void set(const Coord3D *a)
	{
		x = a->x;
		y = a->y;
		z = a->z;
	}
};

class Object;

// getGoalObject declared, not defined: links against the pinned
// ?getGoalObject@StateMachine@@QAEPAVObject@@XZ (ILT 0x0000E570 -> 0x000A1490).
class StateMachine
{
public:
	Object *getGoalObject();

	unsigned char m_pad00[0x10];
	Object *m_owner;
};

enum LocomotorSetType
{
};

// Local minimal AIUpdateInterface: requestPath declared, not defined, so
// the call links against the already-matched
// ?requestPath@AIUpdateInterface@@QAEXPAUCoord3D@@_N@Z (AIUpdate.cpp).
// chooseLocomotorSet is vtable +0x1fc (slot 127), per the matched
// ?chooseLocomotorSet@AIUpdateInterface@@UAE_NW4LocomotorSetType@@@Z at
// 0x00272ED0; the virtual call needs no linked symbol.
class AIUpdateInterface
{
public:
	virtual void _pad0(void) = 0;	virtual void _pad1(void) = 0;
	virtual void _pad2(void) = 0;	virtual void _pad3(void) = 0;
	virtual void _pad4(void) = 0;	virtual void _pad5(void) = 0;
	virtual void _pad6(void) = 0;	virtual void _pad7(void) = 0;
	virtual void _pad8(void) = 0;	virtual void _pad9(void) = 0;
	virtual void _pad10(void) = 0;	virtual void _pad11(void) = 0;
	virtual void _pad12(void) = 0;	virtual void _pad13(void) = 0;
	virtual void _pad14(void) = 0;	virtual void _pad15(void) = 0;
	virtual void _pad16(void) = 0;	virtual void _pad17(void) = 0;
	virtual void _pad18(void) = 0;	virtual void _pad19(void) = 0;
	virtual void _pad20(void) = 0;	virtual void _pad21(void) = 0;
	virtual void _pad22(void) = 0;	virtual void _pad23(void) = 0;
	virtual void _pad24(void) = 0;	virtual void _pad25(void) = 0;
	virtual void _pad26(void) = 0;	virtual void _pad27(void) = 0;
	virtual void _pad28(void) = 0;	virtual void _pad29(void) = 0;
	virtual void _pad30(void) = 0;	virtual void _pad31(void) = 0;
	virtual void _pad32(void) = 0;	virtual void _pad33(void) = 0;
	virtual void _pad34(void) = 0;	virtual void _pad35(void) = 0;
	virtual void _pad36(void) = 0;	virtual void _pad37(void) = 0;
	virtual void _pad38(void) = 0;	virtual void _pad39(void) = 0;
	virtual void _pad40(void) = 0;	virtual void _pad41(void) = 0;
	virtual void _pad42(void) = 0;	virtual void _pad43(void) = 0;
	virtual void _pad44(void) = 0;	virtual void _pad45(void) = 0;
	virtual void _pad46(void) = 0;	virtual void _pad47(void) = 0;
	virtual void _pad48(void) = 0;	virtual void _pad49(void) = 0;
	virtual void _pad50(void) = 0;	virtual void _pad51(void) = 0;
	virtual void _pad52(void) = 0;	virtual void _pad53(void) = 0;
	virtual void _pad54(void) = 0;	virtual void _pad55(void) = 0;
	virtual void _pad56(void) = 0;	virtual void _pad57(void) = 0;
	virtual void _pad58(void) = 0;	virtual void _pad59(void) = 0;
	virtual void _pad60(void) = 0;	virtual void _pad61(void) = 0;
	virtual void _pad62(void) = 0;	virtual void _pad63(void) = 0;
	virtual void _pad64(void) = 0;	virtual void _pad65(void) = 0;
	virtual void _pad66(void) = 0;	virtual void _pad67(void) = 0;
	virtual void _pad68(void) = 0;	virtual void _pad69(void) = 0;
	virtual void _pad70(void) = 0;	virtual void _pad71(void) = 0;
	virtual void _pad72(void) = 0;	virtual void _pad73(void) = 0;
	virtual void _pad74(void) = 0;	virtual void _pad75(void) = 0;
	virtual void _pad76(void) = 0;	virtual void _pad77(void) = 0;
	virtual void _pad78(void) = 0;	virtual void _pad79(void) = 0;
	virtual void _pad80(void) = 0;	virtual void _pad81(void) = 0;
	virtual void _pad82(void) = 0;	virtual void _pad83(void) = 0;
	virtual void _pad84(void) = 0;	virtual void _pad85(void) = 0;
	virtual void _pad86(void) = 0;	virtual void _pad87(void) = 0;
	virtual void _pad88(void) = 0;	virtual void _pad89(void) = 0;
	virtual void _pad90(void) = 0;	virtual void _pad91(void) = 0;
	virtual void _pad92(void) = 0;	virtual void _pad93(void) = 0;
	virtual void _pad94(void) = 0;	virtual void _pad95(void) = 0;
	virtual void _pad96(void) = 0;	virtual void _pad97(void) = 0;
	virtual void _pad98(void) = 0;	virtual void _pad99(void) = 0;
	virtual void _pad100(void) = 0;	virtual void _pad101(void) = 0;
	virtual void _pad102(void) = 0;	virtual void _pad103(void) = 0;
	virtual void _pad104(void) = 0;	virtual void _pad105(void) = 0;
	virtual void _pad106(void) = 0;	virtual void _pad107(void) = 0;
	virtual void _pad108(void) = 0;	virtual void _pad109(void) = 0;
	virtual void _pad110(void) = 0;	virtual void _pad111(void) = 0;
	virtual void _pad112(void) = 0;	virtual void _pad113(void) = 0;
	virtual void _pad114(void) = 0;	virtual void _pad115(void) = 0;
	virtual void _pad116(void) = 0;	virtual void _pad117(void) = 0;
	virtual void _pad118(void) = 0;	virtual void _pad119(void) = 0;
	virtual void _pad120(void) = 0;	virtual void _pad121(void) = 0;
	virtual void _pad122(void) = 0;	virtual void _pad123(void) = 0;
	virtual void _pad124(void) = 0;	virtual void _pad125(void) = 0;
	virtual void _pad126(void) = 0;
	virtual bool chooseLocomotorSet(LocomotorSetType wst) = 0;

	void requestPath(Coord3D *pos, bool immediately);
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

class CRCParameterCheck;

// Pinned _bfmeRetailCritterDesyncLog (ILT 0x0003A17A -> 0x00065C80).
extern "C" void bfmeRetailCritterDesyncLog(CRCParameterCheck *sink, const char *message);

// Pinned ?removeGoal@Pathfinder@@QAEXPAVObject@@@Z (ILT 0x00015D02 ->
// 0x003E3D20); TheAI+0x0C is the pathfinder (TheAI pin note, AIFearState).
class Pathfinder
{
public:
	void removeGoal(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }

private:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;			// +0x0c
};

extern AI *TheAI;						// retail 0x012EF214
extern CRCParameterCheck *TheCRCParameterCheck;	// retail 0x012ED4FC
extern bool Glo012F0239;				// retail 0x012F0239

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

protected:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;	// +0x1c
	unsigned char m_pad20[0x4c - 0x20];
	unsigned char m_adjustDestinations;	// +0x4c
	unsigned char m_pad4d[0x50 - 0x4d];
};

// The derived-state members follow the base, as ZH AIMoveAndTightenState's
// m_okToRepathTimes / m_checkForPath do: its onEnter() stores 1 and true to
// them right before TheAI->pathfinder()->removeGoal(obj), the same sequence
// this body runs on +0x50 / +0x54.
class Rva00174800State : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

protected:
	unsigned int m_field50;					// +0x50, address-derived
	unsigned char m_checkForPath;			// +0x54
	unsigned char m_pad55[0x58 - 0x55];
	unsigned char m_field58;					// +0x58, address-derived
};

static void rva00174800_log(const char *message)
{
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, message);
}

StateReturnType Rva00174800State::onEnter()
{
	rva00174800_log("CritterDesync: setAdjustDestination(FALSE) 16");

	StateMachine *machine = m_machine;
	m_adjustDestinations = 0;
	Object *owner = machine->m_owner;
	Object *goal = machine->getGoalObject();
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	if (!goal || !ai)
		return STATE_FAILURE;

	ai->chooseLocomotorSet((LocomotorSetType)9);

	if (*((unsigned char *)ai + 0x336))
	{
		m_field50 = 1;
		m_checkForPath = 1;
		m_field58 = 0;

		TheAI->pathfinder()->removeGoal(owner);

		Coord3D pos;
		pos.set(&owner->m_position);
		Coord3D offset;
		{
			// dir's scope closes before offset is consumed: retail's 0x18 frame
			// spills offset.z into dir.z's slot.
			Coord3D dir;
			dir.x = pos.x - goal->m_position.x;
			dir.y = pos.y - goal->m_position.y;
			dir.z = pos.z - goal->m_position.z;
			dir.normalize();
			offset.x = dir.x * 40.0f;
			offset.y = dir.y * 40.0f;
			offset.z = dir.z * 40.0f;
		}
		pos.add(&offset);

		ai->requestPath(&pos, true);
	}
	else
	{
		m_checkForPath = 0;
		m_field58 = 1;
		return STATE_CONTINUE;
	}

	return AIInternalMoveToState::onEnter();
}
