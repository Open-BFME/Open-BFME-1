// ?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.18 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc
//
// EmotionTrackerUpdate::update, retail RVA 0x00290E50, 2052 bytes.
//
// The identity is anchored by the slot-zero entry in the secondary
// UpdateModuleInterface vtable 0x010BE1D8 installed by the matched constructor
// at 0x00290740.  The entry is the ILT at 0x0002B71A.  This method therefore
// receives the interface subobject: the owning Object and ModuleData are at
// this-0x08 and this-0x0c, while the recovered tracker state starts at
// this+0x14.  The BFME emotion-selection code has no Zero Hour twin; the
// address-derived helper views below describe only the proven call ABIs and
// stack layouts.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum Relationship
{
	RELATIONSHIP_ENEMIES = 0,
	RELATIONSHIP_NEUTRAL = 1,
	RELATIONSHIP_ALLIES = 2
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Emotion;

// The named direct callees are existing ledger identities.  The other calls
// remain on their retail ILT spellings, as reported by tools/callees.py.
class Object
{
public:
	float getShroudClearingRange(void) const;
	Relationship getRelationship(const Object *other) const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

class BfmeC1050
{
public:
	void bfmeGo1050D(int a, int b, int c, int d);
};

class Player
{
};

class PlayerList
{
};

class Gen_008f7470
{
public:
	void m(void *position, int include, UnsignedShort playerMask);
};

class Registry
{
};

class TerrainLogic
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual float slot18(float x, float y, int normal) = 0;
};

class TacticalView
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2c(void) = 0;
	virtual void slot30(Coord3D *position, float radius,
		UnsignedInt color, int flags) = 0;
};

// These are the retail absolute globals annotated by the disassembler.  The
// address forms keep this TU independent of unrelated BFME class-name shims.
#define TheWritableGlobalData (*(unsigned char **)0x012ED5C8)
#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define TheTacticalView (*(TacticalView **)0x012F1600)
#define ThePartitionManager (*(BfmeC1050 **)0x012ED5B8)
#define ThePlayers (*(PlayerList **)0x012ED748)
#define TheShroudManager (*(Gen_008f7470 **)0x012ED5BC)
#define TheRegistry (*(Registry **)0x012EF1D8)
#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheEmotionSystem (*(unsigned char **)0x012F0878)
#define BfmeZeroRange (*(const float *)0x01075350)

extern void j_000016a4(void);
extern void j_000084b8(void);
extern void j_0000c69e(void);
extern void j_00015e2e(void);
extern void j_00019056(void);
extern void j_0001da34(void);
extern void j_0001f253(void);
extern void j_00020824(void);
extern void j_000283d0(void);
extern void j_00028560(void);
extern void j_000326cd(void);
extern void j_0003251f(void);
extern void j_0003a391(void);
extern void j_0003e80b(void);
extern void j_00043ced(void);
extern void j_00044c60(void);
extern void j_000466b4(void);
extern void j_00049f0d(void);
extern void j_000326cd(void);

extern float GetGameLogicRandomValueReal(float low, float high,
	char *file, int line);

// The two direct bodies below are declared with their callee names.  Their
// retail declarations return through EAX even though the old ILT spelling is
// a QAEX void symbol; the aliases make the call ABI explicit without adding a
// new pin or a semantic name.
class BfmeC1050Result
{
public:
	Object *bfmeGo1050D(int a, int b, int c, int d);
};

#pragma comment(linker, "/alternatename:?bfmeGo1050D@BfmeC1050Result@@QAEPAVObject@@HHHH@Z=?bfmeGo1050D@BfmeC1050@@QAEXHHHH@Z")

class Gen_008f7470Result
{
public:
	UnsignedInt m(void *position, int include, UnsignedShort playerMask);
};

#pragma comment(linker, "/alternatename:?m@Gen_008f7470Result@@QAEIPAXHG@Z=?m@Gen_008f7470@@QAEXPAXHG@Z")

struct Rva00290E50VoidCall
{
	typedef void (Rva00290E50VoidCall::*Function)(void);
};

static __forceinline void rva00290e50VoidCall(void *object, void (*raw)(void))
{
	union { void (*raw)(void); Rva00290E50VoidCall::Function member; } route;
	route.raw = raw;
	(reinterpret_cast<Rva00290E50VoidCall *>(object)->*route.member)();
}

static __forceinline void rva00290e50StopEmotion(Emotion *emotion)
{
	rva00290e50VoidCall((void *)emotion, j_00015e2e);
}

struct Rva00290E50BoolNoArgsCall
{
	typedef Bool (Rva00290E50BoolNoArgsCall::*Function)(void);
};

static __forceinline Bool rva00290e50BoolNoArgs(void *object, void (*raw)(void))
{
	union { void (*raw)(void); Rva00290E50BoolNoArgsCall::Function member; } route;
	route.raw = raw;
	return (reinterpret_cast<Rva00290E50BoolNoArgsCall *>(object)->*route.member)();
}

static __forceinline Bool rva00290e50EmotionStillActive(Emotion *emotion)
{
	return rva00290e50BoolNoArgs((void *)emotion, j_0000c69e);
}

struct Rva00290E50TestStatusCall
{
	typedef Bool (Rva00290E50TestStatusCall::*Function)(int);
};

static __forceinline Bool rva00290e50TestStatus(Object *object, int status)
{
	union { void (*raw)(void); Rva00290E50TestStatusCall::Function member; } route;
	route.raw = j_000016a4;
	return (reinterpret_cast<Rva00290E50TestStatusCall *>(object)->*route.member)(status);
}

struct Rva00290E50AcceptCall
{
	typedef Bool (Rva00290E50AcceptCall::*Function)(Object *, int);
};

static __forceinline Bool rva00290e50Accept(const void *filter, Object *object)
{
	union { void (*raw)(void); Rva00290E50AcceptCall::Function member; } route;
	route.raw = j_0001da34;
	return (reinterpret_cast<Rva00290E50AcceptCall *>(const_cast<void *>(filter))->*route.member)(object, 0);
}

struct Rva00290E50DistanceCall
{
	typedef float (Rva00290E50DistanceCall::*Function)(const Object *);
};

static __forceinline float rva00290e50Distance(Object *object, Object *other)
{
	union { void (*raw)(void); Rva00290E50DistanceCall::Function member; } route;
	route.raw = j_00043ced;
	return (reinterpret_cast<Rva00290E50DistanceCall *>(object)->*route.member)(other);
}

struct Rva00290E50ShroudRangeCall
{
	typedef float (Rva00290E50ShroudRangeCall::*Function)(void);
};

static __forceinline float rva00290e50ShroudRange(Object *object)
{
	union { void (*raw)(void); Rva00290E50ShroudRangeCall::Function member; } route;
	route.raw = j_000326cd;
	return (reinterpret_cast<Rva00290E50ShroudRangeCall *>(object)->*route.member)();
}

struct Rva00290E50PlayerCall
{
	typedef Player *(Rva00290E50PlayerCall::*Function)(void);
};

static __forceinline Player *rva00290e50ControllingPlayer(Object *object)
{
	union { void (*raw)(void); Rva00290E50PlayerCall::Function member; } route;
	route.raw = j_00020824;
	return (reinterpret_cast<Rva00290E50PlayerCall *>(object)->*route.member)();
}

struct Rva00290E50MaskCall
{
	typedef UnsignedShort (Rva00290E50MaskCall::*Function)(int, int, int);
};

static __forceinline UnsignedShort rva00290e50Mask(PlayerList *players,
	int player, int relationship)
{
	union { void (*raw)(void); Rva00290E50MaskCall::Function member; } route;
	route.raw = j_00044c60;
	return (reinterpret_cast<Rva00290E50MaskCall *>(players)->*route.member)(
		player, relationship, 0);
}

struct Rva00290E50FindObjectCall
{
	typedef Object *(Rva00290E50FindObjectCall::*Function)(int);
};

static __forceinline Object *rva00290e50FindObject(GameLogic *logic, int id)
{
	union { void (*raw)(void); Rva00290E50FindObjectCall::Function member; } route;
	route.raw = j_0001f253;
	return (reinterpret_cast<Rva00290E50FindObjectCall *>(logic)->*route.member)(id);
}

struct Rva00290E50ShroudCall
{
	typedef UnsignedInt (Rva00290E50ShroudCall::*Function)(void *, int, UnsignedShort);
};

static __forceinline UnsignedInt rva00290e50Shroud(Gen_008f7470 *shroud,
	void *position, UnsignedShort playerMask)
{
	return reinterpret_cast<Gen_008f7470Result *>(shroud)->m(
		position, 1, playerMask);
}

struct Rva00290E50KindCall
{
	typedef Bool (Rva00290E50KindCall::*Function)(int);
};

static __forceinline Bool rva00290e50Kind(Object *object, int kind)
{
	union { void (*raw)(void); Rva00290E50KindCall::Function member; } route;
	route.raw = j_0003251f;
	return (reinterpret_cast<Rva00290E50KindCall *>(object)->*route.member)(kind);
}

struct Rva00290E50LayerCall
{
	typedef int (Rva00290E50LayerCall::*Function)(void);
};

static __forceinline int rva00290e50Layer(Object *object)
{
	union { void (*raw)(void); Rva00290E50LayerCall::Function member; } route;
	route.raw = j_0003a391;
	return (reinterpret_cast<Rva00290E50LayerCall *>(object)->*route.member)();
}

struct Rva00290E50EmotionTestCall
{
	typedef Bool (Rva00290E50EmotionTestCall::*Function)(int, int, Object *);
};

static __forceinline Bool rva00290e50EmotionTest(Emotion *emotion,
	int firstMask, int secondMask, Object *object)
{
	union { void (*raw)(void); Rva00290E50EmotionTestCall::Function member; } route;
	route.raw = j_000466b4;
	return (reinterpret_cast<Rva00290E50EmotionTestCall *>(emotion)->*route.member)(
		firstMask, secondMask, object);
}

struct Rva00290E50TemplateCall
{
	typedef void *(Rva00290E50TemplateCall::*Function)(void);
};

static __forceinline void *rva00290e50Template(Object *object)
{
	union { void (*raw)(void); Rva00290E50TemplateCall::Function member; } route;
	route.raw = j_000084b8;
	return (reinterpret_cast<Rva00290E50TemplateCall *>(object)->*route.member)();
}

struct Rva00290E50EquivalentCall
{
	typedef Bool (Rva00290E50EquivalentCall::*Function)(void *);
};

static __forceinline Bool rva00290e50Equivalent(void *thing, void *candidate)
{
	union { void (*raw)(void); Rva00290E50EquivalentCall::Function member; } route;
	route.raw = j_0003e80b;
	return (reinterpret_cast<Rva00290E50EquivalentCall *>(thing)->*route.member)(candidate);
}

struct Rva00290E50RegistryCall
{
	typedef void *(Rva00290E50RegistryCall::*Function)(void *);
};

static __forceinline void *rva00290e50RegistryLookup(Registry *registry,
	void *name)
{
	union { void (*raw)(void); Rva00290E50RegistryCall::Function member; } route;
	route.raw = j_00028560;
	return (reinterpret_cast<Rva00290E50RegistryCall *>(registry)->*route.member)(name);
}

struct Rva00290E50SelectCall
{
	typedef Emotion *(Rva00290E50SelectCall::*Function)(void);
};

static __forceinline Emotion *rva00290e50Select(void *primary)
{
	union { void (*raw)(void); Rva00290E50SelectCall::Function member; } route;
	route.raw = j_000283d0;
	return (reinterpret_cast<Rva00290E50SelectCall *>(primary)->*route.member)();
}

struct Rva00290E50SetObjectCall
{
	typedef void (Rva00290E50SetObjectCall::*Function)(Object *);
};

static __forceinline void rva00290e50SetObject(Emotion *emotion,
	Object *object)
{
	union { void (*raw)(void); Rva00290E50SetObjectCall::Function member; } route;
	route.raw = j_00019056;
	(reinterpret_cast<Rva00290E50SetObjectCall *>(emotion)->*route.member)(object);
}

struct Rva00290E50C1050Call
{
	typedef Object *(Rva00290E50C1050Call::*Function)(int, int, int, int);
};

static __forceinline Object *rva00290e50FindAround(BfmeC1050 *manager,
	int position, int range, int zero, int filter)
{
	return reinterpret_cast<BfmeC1050Result *>(manager)->bfmeGo1050D(
		position, range, zero, filter);
}

// The stack filter constructor is the body at 0x0028F2A0, reached through
// the exact ILT name printed by callees.py.  Its retail object is 0x24 bytes;
// the inline destructor is the vptr reset visible at update+0x024a.
class Rva0028F2A0Filter
{
public:
	Rva0028F2A0Filter(void *owner);
	~Rva0028F2A0Filter(void);

	unsigned int m_vptr;
	unsigned char m_storage[0x20];

private:
	struct Call
	{
		typedef void (Call::*Function)(void *);
	};
	typedef Call::Function Function;
};

#pragma comment(linker, "/alternatename:??0Rva0028F2A0Filter@@QAE@PAX@Z=?j_00049f0d@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva0028F2A0Filter@@QAE@XZ=?m@Gen_0028ee20@@QAEXXZ")

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString(void);
	void releaseBuffer(void);

	unsigned char m_storage[0x0c];
};

#pragma comment(linker, "/alternatename:??1BFMERetailAsciiString@@QAE@XZ=??1AsciiString@@QAE@XZ")

class EmotionTrackerUpdate
{
public:
	virtual UpdateSleepTime update(void);

	// The method is entered with the secondary interface pointer.  These
	// members describe the already-witnessed tracker tail at that pointer;
	// keeping the fields in the class gives VC7.1 the same long-lived `this`
	// value as the retail body instead of forcing every access through a
	// promoted byte pointer.
	unsigned char m_pad04[0x10];
	unsigned char m_active[10];
	unsigned char m_pad1e[2];
	UnsignedInt m_startFrame[10];
	UnsignedInt m_endFrame[10];
	Emotion **m_emotionsBegin;
	Emotion **m_emotionsEnd;
	unsigned char m_pad78[4];
	Emotion *m_currentEmotion;
	int m_distributionIndex;
	unsigned char m_pad84[0x10];
	int m_forcedRetry;
	int m_objectID;
	UnsignedInt m_deadline;
	unsigned char m_enabled;
};

static __forceinline UnsignedInt rva00290e50EmotionType(const Emotion *emotion)
{
	const unsigned char *raw = reinterpret_cast<const unsigned char *>(emotion);
	const unsigned char *entry = *reinterpret_cast<const unsigned char * const *>(raw + 4);
	return *reinterpret_cast<const UnsignedInt *>(entry + 4);
}

static __forceinline Object *rva00290e50FindByID(int id)
{
	return rva00290e50FindObject(TheBfmeGameLogic, id);
}

// ?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime EmotionTrackerUpdate::update(void)
{
	register EmotionTrackerUpdate *self = this;
	register Object *object;
	const unsigned char *moduleData = *reinterpret_cast<const unsigned char * const *>(
		reinterpret_cast<unsigned char *>(self) - 0x0c);

	if (moduleData == 0)
		return UPDATE_SLEEP_FOREVER;
	object = *reinterpret_cast<Object **>(
		reinterpret_cast<unsigned char *>(self) - 0x08);
	if (object == 0)
		return UPDATE_SLEEP_FOREVER;
	if (*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(object) + 0x214) == 0)
		return UPDATE_SLEEP_FOREVER;
	UnsignedInt zero = 0;

	Emotion *current = m_currentEmotion;
	if (current != 0)
	{
		rva00290e50StopEmotion(current);
		m_currentEmotion = 0;
		goto cleanup;
	}

	if (m_forcedRetry > (int)zero)
		--m_forcedRetry;

	if (*reinterpret_cast<unsigned char *>(TheWritableGlobalData + 0xec8) != 0)
	{
		Coord3D position;
		const float *objectPosition = reinterpret_cast<const float *>(
			reinterpret_cast<const unsigned char *>(object) + 0x38);
		position.y = objectPosition[1];
		position.z = objectPosition[2];
		position.x = objectPosition[0];
		position.z = TheTerrainLogic->slot18(position.x, position.y, 0);

		if (*reinterpret_cast<const int *>(moduleData + 0x0c) != 0)
		{
			TheTacticalView->slot30(&position,
				*reinterpret_cast<const float *>(moduleData + 0x08), 0xff0000ff, 0);
			if (*reinterpret_cast<const float *>(moduleData + 0x20) > BfmeZeroRange)
				TheTacticalView->slot30(&position,
					*reinterpret_cast<const float *>(moduleData + 0x20), 0xff00ffff, 0);
			if (*reinterpret_cast<const float *>(moduleData + 0x24) > BfmeZeroRange)
				TheTacticalView->slot30(&position,
					*reinterpret_cast<const float *>(moduleData + 0x24), 0xffff0000, 0);
		}
	}

	Object *type3Object = 0;
	Object *type4Object = 0;
	Object *type59Object = 0;
	float bestDistance = 0x7f7fffff;
	float type4Distance;
	Bool changedContainment = false;

	{
		int distribution = --m_distributionIndex;
		Object *initial = 0;
		if (distribution <= 0 &&
			*reinterpret_cast<const int *>(moduleData + 0x0c) != 0 &&
			m_forcedRetry <= 0)
		{
			Rva0028F2A0Filter filter(reinterpret_cast<unsigned char *>(self) - 0x10);
			if (!rva00290e50TestStatus(object, 0x43))
			{
				initial = rva00290e50FindAround(ThePartitionManager,
					(int)(unsigned long)(reinterpret_cast<unsigned char *>(object) + 0x38),
					*reinterpret_cast<const int *>(moduleData + 0x08), 0,
					(int)(unsigned long)&filter);
			}

			if (initial != 0)
			{
				Bool accepted = rva00290e50Accept(moduleData + 0x1c, initial);
				if (!accepted)
					accepted = rva00290e50Accept(moduleData + 0x14, initial);
				if (!accepted)
					accepted = rva00290e50Accept(moduleData + 0x18, initial);
				if (!accepted)
				{
					m_active[9] = 0;
					m_active[0] = 1;
					m_active[3] = 0;
				}
				else
				{
					m_active[9] = 0;
					m_active[0] = 0;
					m_active[3] = 1;
					bestDistance = rva00290e50Distance(object, initial);
				}
			}
			else
			{
				m_active[0] = 0;
				m_active[3] = 0;
				if (filter.m_storage[0x1c] != 0)
					m_active[9] = 1;
				else
					m_active[9] = 0;
			}
		}
	}

	{
		if (*reinterpret_cast<const float *>(moduleData + 0x20) <= BfmeZeroRange ||
			*reinterpret_cast<const float *>(moduleData + 0x24) <= BfmeZeroRange ||
			m_forcedRetry > 0)
			goto choose_emotion;

		Player *player = rva00290e50ControllingPlayer(object);
		if (player == 0)
			goto choose_emotion;
		int playerIndex = *reinterpret_cast<int *>(
			reinterpret_cast<unsigned char *>(player) + 0x24);
		UnsignedShort enemyMask = rva00290e50Mask(ThePlayers, playerIndex, 3);
		UnsignedShort otherMask = rva00290e50Mask(ThePlayers, playerIndex, 4);
		UnsignedInt objectMask = rva00290e50Shroud(TheShroudManager,
			reinterpret_cast<unsigned char *>(object) + 0x38, otherMask);
		UnsignedInt otherObjectMask = rva00290e50Shroud(TheShroudManager,
			reinterpret_cast<unsigned char *>(object) + 0x38, enemyMask);
		float shroudRange = rva00290e50ShroudRange(object);
		if (shroudRange * shroudRange < bestDistance)
			bestDistance = shroudRange * shroudRange;
		float range20Squared = *reinterpret_cast<const float *>(moduleData + 0x20) *
			*reinterpret_cast<const float *>(moduleData + 0x20);
		type4Distance = *reinterpret_cast<const float *>(moduleData + 0x24) *
			*reinterpret_cast<const float *>(moduleData + 0x24);

		int *id = *reinterpret_cast<int **>(TheEmotionSystem + 0x14);
		int *end = *reinterpret_cast<int **>(TheEmotionSystem + 0x18);
		for (; id != end; ++id)
		{
			Object *candidate = rva00290e50FindByID(*id);
			if (candidate == 0 ||
				*reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned char *>(candidate) + 0x368) == 0)
				continue;

			Relationship relationship = object->getRelationship(candidate);
			if (relationship == RELATIONSHIP_ALLIES &&
				!rva00290e50Accept(moduleData + 0x18, candidate))
				goto candidate_kind59;

			if (rva00290e50Kind(candidate, 0x8f))
			{
				float distance = rva00290e50Distance(object, candidate);
				if (distance <= type4Distance)
				{
					Bool accepted = rva00290e50Accept(moduleData + 0x14, candidate);
					if (!accepted)
						accepted = rva00290e50Accept(moduleData + 0x18, candidate);
					if (accepted)
					{
						if ((*reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned char *>(candidate) + 0x90) & 0x40) == 0 &&
							rva00290e50Layer(object) != rva00290e50Layer(candidate))
						{
							m_active[0] = 1;
							m_active[3] = 0;
						}
						Emotion **emotion = m_emotionsBegin;
						for (; emotion != m_emotionsEnd; ++emotion)
						{
							if (rva00290e50EmotionType(*emotion) == 4 &&
								rva00290e50EmotionTest(*emotion, objectMask,
									otherObjectMask, candidate))
							{
								type4Object = candidate;
								type4Distance = distance;
								goto next_candidate;
							}
						}
					}
				}
			}

			float distance = rva00290e50Distance(object, candidate);
			if (distance <= bestDistance)
			{
				Bool accepted = rva00290e50Accept(moduleData + 0x14, candidate);
				if (!accepted)
					accepted = rva00290e50Accept(moduleData + 0x18, candidate);
				if (!accepted)
					accepted = rva00290e50Accept(moduleData + 0x1c, candidate);
				if (accepted)
				{
					Emotion **emotion = m_emotionsBegin;
					for (; emotion != m_emotionsEnd; ++emotion)
					{
						if (rva00290e50EmotionType(*emotion) == 3 &&
							rva00290e50EmotionTest(*emotion, objectMask,
								otherObjectMask, candidate))
						{
							bestDistance = distance;
							type3Object = candidate;
							if ((*reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned char *>(candidate) + 0x90) & 0x40) == 0 &&
								rva00290e50Layer(object) != rva00290e50Layer(candidate))
							{
								m_active[0] = 1;
								m_active[3] = 0;
							}
							break;
						}
					}
				}
			}

candidate_kind59:
			if (rva00290e50Kind(candidate, 0x59))
			{
				void *nameObject;
				{
					BFMERetailAsciiString name((const char *)0x010BE578);
					nameObject = rva00290e50RegistryLookup(TheRegistry, &name);
				}
				if (nameObject != 0 &&
					rva00290e50Equivalent(nameObject, rva00290e50Template(candidate)))
					goto next_candidate;
				if (nameObject != 0 &&
					*reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(nameObject) + 8) == 2)
				{
					float distance = rva00290e50Distance(object, candidate);
					if (distance < range20Squared)
					{
						type59Object = candidate;
						changedContainment = true;
					}
				}
			}

next_candidate:
			;
		}

choose_emotion:
		if (type3Object != 0 || type4Object != 0 || type59Object != 0)
			m_enabled = 0;
		else if (m_enabled == 0)
			m_enabled = 1;

		if (m_enabled != 0 &&
			TheBfmeGameLogic->m_frame > m_deadline &&
			type59Object != 0)
		{
			m_deadline =
				TheBfmeGameLogic->m_frame + 0x12c;
			m_active[2] = 1;
			m_enabled = 0;
		}
		else
			m_active[2] = 0;

		m_active[4] = type4Object != 0;
		if (GetGameLogicRandomValueReal(0.0f, 1.0f,
			(char *)0x010BE518, 0x226) <= *reinterpret_cast<const float *>(moduleData + 0x28) &&
			rva00290e50Layer(object) == 1)
		{
			m_active[8] = 1;
			UnsignedInt frame = TheBfmeGameLogic->m_frame + 1;
			m_startFrame[8] = frame;
			m_endFrame[8] = 0;
			Emotion *selected = rva00290e50Select(
				reinterpret_cast<unsigned char *>(self) - 0x10);
			if (selected != 0)
			{
				UnsignedInt type = rva00290e50EmotionType(selected);
				if (type == 3 && type3Object != 0)
				{
					UnsignedInt selectedID = m_endFrame[type];
					UnsignedInt candidateID = *reinterpret_cast<UnsignedInt *>(
						reinterpret_cast<unsigned char *>(type3Object) + 0x74);
					if (selectedID != candidateID)
					{
						Object *selectedObject = rva00290e50FindByID(selectedID);
						Object *candidateObject = rva00290e50FindByID(candidateID);
						if (selectedObject != 0 && candidateObject != 0 &&
							*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(selectedObject) + 0x214) != 0 &&
							*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(candidateObject) + 0x214) != 0 &&
							*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(selectedObject) + 0x214) !=
							*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(candidateObject) + 0x214))
							changedContainment = true;
					}
				}

				current = m_currentEmotion;
				if (current == selected && !changedContainment)
				{
					if (rva00290e50EmotionStillActive(current))
						goto cleanup;
					rva00290e50StopEmotion(current);
					m_currentEmotion = 0;
					goto cleanup;
				}

				if (current != 0)
					rva00290e50StopEmotion(current);
				m_currentEmotion = selected;
				if (type == 2 && type3Object != 0)
					m_endFrame[2] =
						*reinterpret_cast<UnsignedInt *>(reinterpret_cast<unsigned char *>(type3Object) + 0x74);
				else if (type == 4 && type4Object != 0)
					m_endFrame[4] =
						*reinterpret_cast<UnsignedInt *>(reinterpret_cast<unsigned char *>(type4Object) + 0x74);
				else if (type != 0 && type != 3 && type3Object != 0)
					m_endFrame[type] =
						*reinterpret_cast<UnsignedInt *>(reinterpret_cast<unsigned char *>(type3Object) + 0x74);

				int objectID;
				if (m_forcedRetry > 0)
					objectID = m_objectID;
				else
					objectID = m_endFrame[type];
				rva00290e50SetObject(selected, rva00290e50FindByID(objectID));
			}
		}
	}

cleanup:
	if (m_startFrame[0] != 0 &&
		TheBfmeGameLogic->m_frame >= m_startFrame[0])
	{
		for (int i = 0; i < 10; ++i)
		{
			m_active[i] = 0;
			m_startFrame[i] = 0;
		}
	}
	return UPDATE_SLEEP_NONE;
}

#undef BfmeZeroRange
#undef TheEmotionSystem
#undef TheBfmeGameLogic
#undef TheRegistry
#undef TheShroudManager
#undef ThePlayers
#undef ThePartitionManager
#undef TheTacticalView
#undef TheTerrainLogic
#undef TheWritableGlobalData
