// cl: /DNDEBUG /MD /EHsc
// readable body of ??0ToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/ToppleUpdate.cpp
//
// Open-BFME: the two constructors the module factory calls to make a topple
// update -- the module and its module data.
//
//   ??0ToppleUpdate@            0x002B1060, 187 bytes
//   ??0ToppleUpdateModuleData@  0x002B13A0, 123 bytes
//
// They were in two files, and the second one held the only real account of the
// class the first one takes a pointer to. ToppleUpdate's constructor had
// `class ModuleData;` and nothing else, so its `const ModuleData *moduleData`
// parameter said only that a pointer goes in; the module data's constructor knew
// the whole layout -- ModuleData at +0x00, two effect slots at +0x08 and +0x0C,
// the stump name at +0x10, four floats, and the five toppling flags at
// +0x24..+0x28. Together the parameter now points at something.
//
// The module base chain is the other thing stated once here, and the ledger
// settles a naming question the two files could not. The two pinned symbols the
// chain has to produce are spelled on DIFFERENT class names:
//
//   ??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z   ILT 0x000170E4
//   ??1Module@@UAE@XZ                                    -> body 0x00113D40
//
// and ??0TU_DeepBase@ -- the placeholder the constructor's file invented for its
// base -- is pinned to that SAME ILT 0x000170E4, so it was never a new symbol,
// only an unchecked alias for BehaviorModule. A most-derived constructor calls
// the first EXTERNAL constructor in the chain and a most-derived destructor calls
// the first external DESTRUCTOR, so the two real names sit on two different
// levels: the destructor's on Module at +0x00, the constructor's on
// BehaviorModule one level up, which adds no data and no vptr and exists only to
// carry that symbol where retail calls it from.
//
// GET THAT BACKWARDS AND NOTHING TELLS YOU SO DIRECTLY. Putting both names on one
// level, or swapping which level carries which, leaves the body byte-comparing
// against a DIFFERENT function: the build reports an unresolved callee, or worse,
// silently resolves to another address in the candidate list. On the way to this
// file it happened twice, once in each direction -- ??0 resolving through a name
// only the destructor's spelling owned, then ??1 resolving through a name only
// the constructor's spelling owned. The symptom is a call operand that will not
// settle while the surrounding bytes all match; the cause is the level, not the
// body. Check both spellings in reverse/symbols.csv before moving either.
//
// WHAT IS DELIBERATELY NOT HERE, and why. ToppleUpdate's destructor and its
// module data's destructor cannot join these two, because retail's bodies need
// class declarations that contradict the ones these need:
//
//   ??1ToppleUpdate@ stores its vptrs in the order +0x20, +0x10, +0x00, +0x0C,
//   which needs BehaviorModuleInterface declared on BehaviorModule. ??0ToppleUpdate@
//   stores +0x0C then +0x10 right after the base call, which needs BOTH
//   interfaces declared on UpdateModule. One class cannot do both; each of the
//   two original files had guessed the shape that suited its own body.
//
//   ??1ToppleUpdateModuleData@ stores the base vftable AFTER destroying the
//   string, which is what __declspec(novtable) on the derived class produces --
//   and that same novtable suppresses the vftable that ??_GToppleUpdateModuleData@
//   is emitted from. The two are mutually exclusive in one TU for the same reason.
//
// Both are real disagreements about the retail declarations rather than about
// these bodies, so the four destructor rows stay in their own files until
// something settles the hierarchy.

class Thing;
class Object;

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

// Retail destroys this member with a direct call to
// StringBase<char>::releaseBuffer (0x00887940) -- the member is a retail
// AsciiString, not the WWLib Buffer whose own destructor is the 40-byte body at
// 0x009E1E30, so name it the way the other lifted ModuleData destructors do.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString()
	{
		m_data = 0;
	}

	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void clear(void)
	{
		releaseBuffer();
	}

private:
	void releaseBuffer(void);

	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
// The destructor is empty and inline because retail's ??1ToppleUpdateModuleData
// makes exactly one call -- to the string's releaseBuffer -- and none to a base.
class ModuleData
{
public:
	virtual ~ModuleData() {}

	unsigned int m_moduleTagNameKey;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ToppleUpdate.h
class ToppleUpdateModuleData : public ModuleData
{
public:
	ToppleUpdateModuleData();
	virtual ~ToppleUpdateModuleData();		// defined in ToppleUpdateModuleDataDestructorThunk.cpp

private:
	int m_toppleFX;					// +0x08
	int m_bounceFX;					// +0x0C
	BFMERetailAsciiString m_stumpName;		// +0x10
	float m_initialVelocityPercent;			// +0x14
	float m_initialAccelPercent;			// +0x18
	float m_bounceVelocityPercent;			// +0x1C
	float m_20;					// +0x20, no key in retail's INI table
	bool m_killWhenToppled;				// +0x24
	bool m_killWhenStartToppled;
	bool m_killStumpWhenToppled;
	bool m_toppleLeftOrRightOnly;
	bool m_reorientToppledRubble;			// +0x28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
// Only the destructor is declared here: it is the first EXTERNAL destructor in
// the chain, so it is the one ~ToppleUpdate calls, and ??1Module@@UAE@XZ is the
// spelling the ledger pins for it.
class Module
{
public:
	virtual ~Module();				// pinned as ??1Module@@UAE@XZ

protected:
	const ModuleData *m_moduleData;			// +0x04
	Object *m_object;				// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
// Only the constructor is declared here, for the mirror-image reason: it is the
// first external CONSTRUCTOR in the chain, so it is the one ToppleUpdate's calls,
// and ??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z is the spelling the
// ledger pins for it -- at ILT 0x000170E4, noted there as the exact retail rel32
// target of the six module constructors that call it.
//
// It adds no data and no vptr of its own, so it does not move anything: it exists
// to carry that one symbol at the level retail calls it from.
class BehaviorModule : public Module
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);	// ILT 0x000170E4
	virtual ~BehaviorModule() {}
};

class BehaviorModuleInterface { public: virtual void behaviorAnchor(); };
class UpdateModuleInterface { public: virtual void updateAnchor(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
// The two interface vptrs at +0x0C and +0x10 are initialized here, in this order,
// which is what retail's constructor stores right after the base call.
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: BehaviorModule(thing, moduleData), m_nextCallFrameAndPhase(0), m_f18(-1), m_f1c(-1) {}
	virtual ~UpdateModule() {}

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	Object *getObject() const { return m_object; }

private:
	unsigned int m_nextCallFrameAndPhase;				// +0x14
	int m_f18;					// +0x18
	int m_f1c;					// +0x1C
};

class CollideModuleInterface { public: virtual void onCollide(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ToppleUpdate.h
class ToppleUpdate : public UpdateModule, public CollideModuleInterface
{
public:
	ToppleUpdate(Thing *, const ModuleData *);

protected:
	virtual ~ToppleUpdate();

private:
	float m_angularVelocity;			// +0x24
	float m_angularAcceleration;
	float m_toppleDirectionX;
	float m_toppleDirectionY;
	float m_toppleDirectionZ;
	int m_toppleState;
	float m_angularAccumulation;
	float m_angleDeltaX;
	int m_numAngleDeltaX;
	bool m_doBounceFX;
	unsigned int m_options;
	unsigned int m_stumpID;
	unsigned int m_bfmeState;			// +0x54, BFME-only, sizeof is 0x58
};

// ??0ToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// The fields through +0x50 follow the Zero Hour source; +0x54 is BFME-only state
// that retail initializes in the same zeroing run.
ToppleUpdate::ToppleUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_angleDeltaX = 0.0f;
    m_doBounceFX = false;
    m_numAngleDeltaX = 0;
    m_angularVelocity = 0.0f;
    m_angularAccumulation = 0.0f;
    m_angularAcceleration = 0.0f;
    m_toppleDirectionX = 0.0f;
    m_toppleDirectionY = 0.0f;
    m_toppleDirectionZ = 0.0f;
    m_toppleState = 0;
    m_options = 0;
    m_stumpID = 0;
    m_bfmeState = 0;
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

// ??0ToppleUpdateModuleData@@QAE@XZ
// The string at +0x10 is constructed inline -- one zeroed word through the lea
// that stays live -- and then cleared, which is the call to the private
// releaseBuffer. Clearing a string that was just zeroed looks redundant and is
// not optional: it is the only call in the function.
ToppleUpdateModuleData::ToppleUpdateModuleData()
{
	m_toppleFX = 0;
	m_bounceFX = 0;
	m_stumpName.clear();
	m_initialVelocityPercent = 0.2f;
	m_bounceVelocityPercent = 0.2f;
	m_killWhenStartToppled = false;
	m_killStumpWhenToppled = false;
	m_toppleLeftOrRightOnly = false;
	m_reorientToppledRubble = false;
	m_killWhenToppled = true;
	m_initialAccelPercent = 0.01f;
	m_20 = 0.5f;
}
