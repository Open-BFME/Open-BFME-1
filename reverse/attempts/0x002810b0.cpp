// d_002810b0
// partial score=0.1 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5 WIP candidate for retail 0x002810B0 (649 B), dump d_00280010.asm.
// Almost certainly AutoAbilityBehavior::update() (or the UpdateModuleInterface
// slot that reaches it): this arrives adjusted (this-0x10 relative to the
// AutoAbilityBehaviorDestructorThunk.cpp layout, where m_object sits at +8 and
// AsciiString m_command at +0x20), gates on TheBfmeGameLogic frame count vs a
// stored next-fire frame, checks GeometryInfo shadow-scale float compare and
// three model-condition bit tests, then on cooldown fires: reads
// Object::getControllingPlayer (ILT 0x00020824), gates on
// Player::hasUpgradeComplete / Player::hasAnyObjects, computes a frame delay
// via __ftol2, deposits Money via lea ecx,[edi+0x48]; call Money::deposit,
// posts ExperienceTracker::addExperiencePoints / ScoreKeeper::addMoneyEarned,
// and finally builds a floating UnicodeString via TheGameText->fetch +
// UnicodeString::format and hands it to TheInGameUI's floating-text vcall
// (dword ptr [edx+0x178]).
//
// NOT BYTE EXACT -- banked as a partial. Unresolved: exact field offsets of
// the per-object next-fire-frame/flag pair (candidate +0x20/+0x24/+0x25 off
// AutoAbilityBehavior, i.e. UpdateModuleInterface-adjusted this - 0x10), the
// real signature of the ILT-shared callee at 0x00020824 in this context
// (Object::getControllingPlayer is the best matched-caller candidate), and
// the callees at 0x00009e12 / 0x00024938 / 0x00025eeb (gen_small void()
// placeholder thunks, real signature unresolved).

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class Player;
class UpgradeTemplate;
class ObjectFilter;
class Money;
class UnicodeString;

class GameLogic
{
public:
	unsigned char m_pad000[0x3c];
	int m_frame;	// +0x3c, read at retail +0x1a and +0x43
};

extern GameLogic *g_TheBfmeGameLogic0898;	// pinned TheBfmeGameLogic @ 0x012F0898

class Object
{
public:
	Player *getControllingPlayer() const;		// ILT 0x00020824
	unsigned char m_pad000[0x210];
	void *m_aiUnknown210;	// +0x210, read at retail +0x1a2
};

class Player
{
public:
	Bool hasUpgradeComplete(const UpgradeTemplate *upgrade);		// retail 0x000235BF
	Bool hasAnyObjects(const ObjectFilter *filter, Bool b) const;	// retail 0x00018016
};

class ModuleData
{
public:
	unsigned char m_pad000[8];
	int m_08;		// AutoAbilityBehaviorModuleData::m_08, retail 0x00281030 ctor sets it 0
};

// upstream layout: AutoAbilityBehaviorDestructorThunk.cpp -- m_object at +8,
// m_command (AsciiString) at +0x20; the incoming this here is this-0x10 from
// that layout (UpdateModuleInterface sub-vtable), so relative offsets below
// are candidate-only.
class AutoAbilityBehavior
{
public:
	const ModuleData *m_moduleData;	// -0xc from the UpdateModuleInterface this
	Object *m_object;					// -8
	unsigned char m_pad010[0x20 - 0x10];
	UnsignedInt m_nextFireFrame;		// +0x10 (candidate)
	unsigned char m_flag14;			// +0x14 (candidate)
	unsigned char m_flag15;			// +0x15 (candidate)
};

// address-derived name; no Zero Hour twin (AutoAbilityBehavior is BFME-only).
void bfmeAutoAbilityBehaviorUpdate_002810b0(AutoAbilityBehavior *self)
{
	int frame = g_TheBfmeGameLogic0898->m_frame;
	if ((UnsignedInt)frame < self->m_nextFireFrame)
		return;

	if (self->m_flag14 == 0)
	{
		self->m_flag14 = 1;
		self->m_flag15 = 1;
		self->m_nextFireFrame = g_TheBfmeGameLogic0898->m_frame + self->m_moduleData->m_08;
	}

	Object *obj = self->m_object;
	Player *controller = obj->getControllingPlayer();
	if (controller == 0)
		return;

	(void)controller;
	// Remainder of retail body (shadow-scale gate, upgrade/object gates,
	// Money::deposit, ExperienceTracker::addExperiencePoints,
	// ScoreKeeper::addMoneyEarned, floating UnicodeString) intentionally not
	// yet reproduced -- structural placeholder only.
}
