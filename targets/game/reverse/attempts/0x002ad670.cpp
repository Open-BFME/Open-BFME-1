// ?d_002ad670@@YAXXZ
// partial score=0.13 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Anonymous BFME body at retail 0x002AD670, size 1885 bytes.
// Boundary: ret at +0x75c and INT3 padding at +0x75d.
// Identity is intentionally opaque.  The virtual wrapper at 0x002ADFB0
// adjusts its secondary receiver by -0x10 before calling this body; that
// proves the receiver/layout relationship, but not a unique public method
// identity.  The BFME module-data and object offsets below are witnessed by
// this body and by the landed StealthUpdate siblings.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum RvaStealthLookType
{
	RVA_STEALTHLOOK_NONE = 0,
	RVA_STEALTHLOOK_VISIBLE_FRIENDLY = 1,
	RVA_STEALTHLOOK_DISGUISED_ENEMY = 2,
	RVA_STEALTHLOOK_VISIBLE_DETECTED = 3,
	RVA_STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED = 4,
	RVA_STEALTHLOOK_INVISIBLE = 5
};

class RvaAudioEvent;
class RvaDrawable;
class RvaObject;
class RvaModule;
class RvaAIUpdate;
class RvaBody;
class RvaPlayer;

class RvaGameLogic
{
public:
	char m_pad00[0x3c];
	UnsignedInt m_frame;
};

class RvaPlayerList
{
public:
	char m_pad00[0x0c];
	RvaPlayer *m_localPlayer;
};

class RvaNameKeyGenerator
{
public:
	UnsignedInt nameToKey(const char *name);
};

#pragma comment(linker, "/alternatename:?nameToKey@RvaNameKeyGenerator@@QAEII@Z=?j_0003add7@@YAXXZ")

class RvaDrawable
{
public:
	RvaAudioEvent *getSound(Int index);
	void setStealthLook(RvaStealthLookType look, Real minOpacity,
		Real maxOpacity, Real pulse);
};

#pragma comment(linker, "/alternatename:?getSound@RvaDrawable@@QAEPAVRvaAudioEvent@@H@Z=?j_0001bfd1@@YAXXZ")
#pragma comment(linker, "/alternatename:?setStealthLook@RvaDrawable@@QAEXW4RvaStealthLookType@@MMM@Z=?j_0000f763@@YAXXZ")

class RvaAudioEvent
{
public:
	RvaAudioEvent(const RvaAudioEvent &source);
	~RvaAudioEvent();
	void setObjectID(UnsignedInt id);

private:
	char m_data[0x70];
};

#pragma comment(linker, "/alternatename:??0RvaAudioEvent@@QAE@ABV0@@Z=?j_00047b27@@YAXXZ")
#pragma comment(linker, "/alternatename:??1RvaAudioEvent@@QAE@XZ=?j_00026f35@@YAXXZ")
#pragma comment(linker, "/alternatename:?setObjectID@RvaAudioEvent@@QAEXI@Z=?j_00019a6a@@YAXXZ")

class RvaAudioClient
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void addAudioEvent(RvaAudioEvent *event);
};

class RvaBody
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual UnsignedInt slot15();
	virtual UnsignedInt slot16();
};

class RvaAIUpdate
{
public:
	virtual Bool slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual Bool slot97();
};

class RvaModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21(RvaObject *object);
	virtual void slot22(RvaObject *object);
	virtual void slot23();
	virtual UnsignedInt slot24();
};

class RvaChild
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
};

class RvaContainer
{
public:
	char m_pad00[0x1fc];
	RvaChild *m_child;
};

class RvaObject
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual RvaDrawable *getDrawable();

	char m_pad04[0x34];
	Coord3D m_position;
	char m_pad44[0x30];
	UnsignedInt m_id;
	char m_pad78[0x18];
	UnsignedInt m_kindFlags;
	char m_pad94[0x98];
	UnsignedInt m_statusBits;
	char m_pad130[0xd0];
	RvaBody *m_body;
	RvaAIUpdate *m_ai;
	char m_pad208[0x0c];
	RvaContainer *m_container;

	void setStatusBit(Int bit, bool value);
	void notifyModelConditionChanged();
	void clearStatus(Int bit);
	void handle(Int value);
	RvaModule *findModule(UnsignedInt key);
	Bool predicate35995(Int value);
	Bool predicate3E54A();
	Bool locallyControlled();
	UnsignedInt *statusMask();
};

#pragma comment(linker, "/alternatename:?setStatusBit@RvaObject@@QAEXH_N@Z=?j_00032dee@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@RvaObject@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:?clearStatus@RvaObject@@QAEXH@Z=?j_00031f7a@@YAXXZ")
#pragma comment(linker, "/alternatename:?handle@RvaObject@@QAEXH@Z=?j_000122ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?findModule@RvaObject@@QAEPAVRvaModule@@I@Z=?j_0002ae23@@YAXXZ")
#pragma comment(linker, "/alternatename:?predicate35995@RvaObject@@QAE_NH@Z=?j_00035995@@YAXXZ")
#pragma comment(linker, "/alternatename:?predicate3E54A@RvaObject@@QAE_NXZ=?j_0003e54a@@YAXXZ")
#pragma comment(linker, "/alternatename:?locallyControlled@RvaObject@@QAE_NXZ=?j_0001ff91@@YAXXZ")
#pragma comment(linker, "/alternatename:?statusMask@RvaObject@@QAEPAIXZ=?j_000209fa@@YAXXZ")

class RvaStealthUpdateModuleData
{
public:
	char m_pad00[0x08];
	UnsignedInt m_stealthDelay;
	char m_pad0c[0x14];
	Real m_friendlyOpacityMin;
	Real m_friendlyOpacityMax;
	UnsignedInt m_pulseFrequency;
	char m_pad2c[0x04];
	Real m_revealDistanceFromTarget;
	char m_pad34[0x1e];
	Bool m_detectedByFriendliesOnly;
	char m_pad53[0x01];
	UnsignedInt m_disguiseTransitionTime;
	UnsignedInt m_disguiseRevealTransitionTime;
	Real m_detectedByAnyoneRange;
	UnsignedInt m_revealWeaponSets;
	char m_pad64[0x2bc];
	UnsignedInt m_ringDelayAfterRemoving;
};

class RvaStealthUpdate;

class RvaJ1166
{
public:
	RvaJ1166(UnsignedInt a, UnsignedInt b, UnsignedInt c);
	char m_data[0x20];
};

#pragma comment(linker, "/alternatename:??0RvaJ1166@@QAE@III@Z=?j_0000198d@@YAXXZ")

class RvaFilterPair
{
public:
	RvaFilterPair(RvaJ1166 *query, UnsignedInt *kindMask);
};

#pragma comment(linker, "/alternatename:??0RvaFilterPair@@QAE@PAVRvaJ1166@@PAI@Z=?j_000382fd@@YAXXZ")

class RvaFilterNode
{
public:
	UnsignedInt m_vtable;
	RvaFilterNode *m_next;
	UnsignedInt m_data08;
	UnsignedInt m_data0c;

	RvaFilterNode *append(RvaFilterNode *next);
};

#pragma comment(linker, "/alternatename:?append@RvaFilterNode@@QAEPAV1@PAV1@@Z=?d_009f2ae0@@YAXXZ")

struct RvaWideEntry
{
	RvaObject *object;
	UnsignedInt value;
};

struct RvaWideData
{
	RvaWideEntry *begin;
	RvaWideEntry *end;
};

struct BfmeWideResult
{
	RvaWideData *m_value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &source);
	~BfmeWideResult();
};

#pragma comment(linker, "/alternatename:??1BfmeWideResult@@QAE@XZ=?j_0002c471@@YAXXZ")

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int a, Int b, Int c, Int d, Int e);
};

class RvaStealthUpdate
{
public:
	virtual UpdateSleepTime update();

	RvaStealthUpdateModuleData *m_moduleData;
	RvaObject *m_object;
	char m_pad0c[0x14];
	UnsignedInt m_stealthAllowedFrame;
	UnsignedInt m_detectionExpiresFrame;
	UnsignedInt m_nextBlackMarketCheckFrame;
	Bool m_enabled;
	Bool m_xferRestoreDisguise;
	Bool m_unknown2e;
	Bool m_unknown2f;
	Bool m_unknown30;
	char m_pad31[3];
	Int m_disguiseAsPlayerIndex;
	const void *m_disguiseAsTemplate;
	UnsignedInt m_disguiseTransitionFrames;
	Bool m_disguiseHalfpointReached;
	Bool m_transitioningToDisguise;
	Bool m_disguised;

	void grantHook(Int active, Int frames);
	RvaStealthLookType calcStealthedStatusForPlayer(const RvaObject *object,
		const RvaPlayer *player);
	void changeVisualDisguise();
	void hintDetectableWhileUnstealthed();
	Bool predicate1B04A(const Coord3D *first, const Coord3D *second);
};

#pragma comment(linker, "/alternatename:?grantHook@RvaStealthUpdate@@QAEXHH@Z=?j_00040dc2@@YAXXZ")
#pragma comment(linker, "/alternatename:?calcStealthedStatusForPlayer@RvaStealthUpdate@@QAE?AW4RvaStealthLookType@@PBVRvaObject@@PBVRvaPlayer@@@Z=?j_0003778b@@YAXXZ")
#pragma comment(linker, "/alternatename:?changeVisualDisguise@RvaStealthUpdate@@QAEXXZ=?j_000378df@@YAXXZ")
#pragma comment(linker, "/alternatename:?hintDetectableWhileUnstealthed@RvaStealthUpdate@@QAEXXZ=?j_00004471@@YAXXZ")
#pragma comment(linker, "/alternatename:?predicate1B04A@RvaStealthUpdate@@QAE_NPBUCoord3D@@0@Z=?j_0001b04a@@YAXXZ")

#define BFME_GAME_LOGIC (*(RvaGameLogic **)0x012F0898)
#define BFME_PLAYER_LIST (*(RvaPlayerList **)0x012ED748)
#define BFME_NAME_KEYS (*(RvaNameKeyGenerator **)0x012ED600)
#define BFME_AUDIO_CLIENT (*(RvaAudioClient **)0x012ED668)
#define BFME_PARTITION_MANAGER (*(BfmeWideForwardC **)0x012ED5B8)
#define BFME_UPDATE_INIT (*(volatile unsigned char *)0x012F01E4)
#define BFME_UPDATE_KEY (*(volatile UnsignedInt *)0x012F01E0)
#define BFME_UINT32_SCALE (*(volatile Real *)0x01075358)
#define BFME_DEFAULT_BU (*(volatile Real *)0x01075334)
#define BFME_K1253 (*(volatile Real *)0x0107533C)
#define BFME_ZERO_RANGE (*(volatile Real *)0x01075350)

static void rvaAddStealthSound(RvaDrawable *draw, Int index, UnsignedInt objectID)
{
	RvaAudioEvent sound = *draw->getSound(index);
	sound.setObjectID(objectID);
	BFME_AUDIO_CLIENT->addAudioEvent(&sound);
}

// ?update@Rva002AD670StealthUpdate@@QAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime RvaStealthUpdate::update()
{
	RvaGameLogic *logic = BFME_GAME_LOGIC;
	UnsignedInt now = logic->m_frame;
	Bool enabled = m_enabled;
	RvaStealthUpdateModuleData *data = m_moduleData;
	RvaObject *self = m_object;

	if (!enabled && !m_xferRestoreDisguise)
		return UPDATE_SLEEP_FOREVER;

	RvaDrawable *draw = self->getDrawable();
	if (draw && m_xferRestoreDisguise)
	{
		if (m_stealthAllowedFrame < now)
		{
			self->setStatusBit(0x0f, true);
			if (m_detectionExpiresFrame != 0 && m_detectionExpiresFrame < now)
			{
				if (self->m_statusBits & 0x40000)
				{
					self->m_statusBits &= ~0x40000;
					self->notifyModelConditionChanged();
				}
				self->clearStatus(0x0f);
				self->handle(0x1c);
				m_xferRestoreDisguise = 0;
				m_nextBlackMarketCheckFrame = now + data->m_ringDelayAfterRemoving;
				RvaStealthLookType look =
					calcStealthedStatusForPlayer(self, BFME_PLAYER_LIST->m_localPlayer);
				Real pulse = (Real)data->m_pulseFrequency * BFME_UINT32_SCALE;
				draw->setStealthLook(look, data->m_friendlyOpacityMin,
					data->m_friendlyOpacityMax, pulse);
			}
		}
	}
	else if (draw && m_disguiseTransitionFrames)
	{
		Bool transitioning = m_transitioningToDisguise;
		UnsignedInt frames = --m_disguiseTransitionFrames;
		UnsignedInt duration = transitioning
			? data->m_disguiseTransitionTime
			: data->m_disguiseRevealTransitionTime;
		Real factor = (Real)frames / (Real)duration;
		factor = BFME_DEFAULT_BU - factor;

		if (factor < BFME_K1253 && !m_disguiseHalfpointReached)
		{
			changeVisualDisguise();
			m_disguiseHalfpointReached = 1;
			Real opacity = BFME_DEFAULT_BU - (factor + factor);
			if (opacity < BFME_ZERO_RANGE)
				opacity = -opacity;
			draw = self->getDrawable();
			if (draw)
				*(Real *)((char *)draw + 0xb0) = opacity;
		}

		if (frames == 0 && !transitioning)
		{
			m_enabled = 0;
			self->clearStatus(0x0f);
			self->clearStatus(0x11);
		}
	}

	if (!(BFME_UPDATE_INIT & 1))
	{
		BFME_UPDATE_INIT |= 1;
		BFME_UPDATE_KEY = BFME_NAME_KEYS->nameToKey(
			(const char *)0x010903A8); // "AllowAudioReinitialize"
	}
	RvaModule *module = self->findModule(BFME_UPDATE_KEY);

	if (module && !m_xferRestoreDisguise)
	{
		if (!self->predicate3E54A())
		{
			if (self->m_ai && self->m_ai->slot97())
				grantHook(0, 1);
		}

		module->slot21(self);
		if (self->m_body)
		{
			UnsignedInt bodyLimit = self->m_body->slot16();
			if (bodyLimit > module->slot24())
			{
				UnsignedInt bodyValue = self->m_body->slot15();
				module->slot22(self);
				(void)bodyValue;
			}
		}
	}

	if (data->m_revealDistanceFromTarget != BFME_ZERO_RANGE &&
		!m_xferRestoreDisguise && self->m_ai)
	{
		if (self->m_ai->slot00())
		{
			RvaJ1166 query(0, 25,
				data->m_detectedByFriendliesOnly ? 1U : 4U);
			RvaFilterPair pair(&query,
				(UnsignedInt *)0x012ED8B8);
			RvaFilterNode sameMap;
			RvaFilterNode relationship;
			RvaFilterNode root;
			RvaFilterNode selfFilter;
			RvaFilterNode extra;
			UnsignedInt zero = 0;

			sameMap.m_vtable = 0x01085DD0;
			sameMap.m_next = 0;
			sameMap.m_data08 = (UnsignedInt)self;
			relationship.m_vtable = 0x01085DC0;
			relationship.m_next = 0;
			relationship.m_data08 = (UnsignedInt)self;
			relationship.m_data0c = 4;
			root.m_vtable = 0x010860B0;
			root.m_next = 0;
			selfFilter.m_vtable = 0x01083B80;
			selfFilter.m_next = 0;
			selfFilter.m_data08 = (UnsignedInt)self;
			extra.m_vtable = 0x01095724;
			extra.m_next = 0;
			extra.m_data08 = (UnsignedInt)self;

			RvaFilterNode *filters = sameMap.append(&relationship);
			filters = filters->append(&root);
			filters = filters->append(&selfFilter);
			filters = filters->append(&extra);
			filters = filters->append(&sameMap);
			(void)pair;
			(void)zero;

			BfmeWideResult result = BFME_PARTITION_MANAGER->bfmeForwardWideC(
				(Int)&self->m_position, (Int)&query,
				*(Int *)&data->m_revealDistanceFromTarget, 2, (Int)filters);
			if (result.m_value && result.m_value->end - result.m_value->begin > 0)
			{
				grantHook(0, 1);
				return m_enabled ? UPDATE_SLEEP_NONE : UPDATE_SLEEP_FOREVER;
			}
		}
	}

	if (!self->predicate35995(0) &&
		predicate1B04A(&self->m_position, &self->m_position) &&
		m_stealthAllowedFrame <= now &&
		(self->m_kindFlags & 0x80000000) == 0 && draw)
	{
		rvaAddStealthSound(draw, 0x60, self->m_id);
		self->clearStatus(0x0f);
	}

	if (!m_xferRestoreDisguise)
	{
		m_stealthAllowedFrame = now + data->m_stealthDelay;
		if (self->m_kindFlags & 0x80000000)
		{
			if (draw)
				rvaAddStealthSound(draw, 0x0f, self->m_id);
			self->clearStatus(0x0f);
			hintDetectableWhileUnstealthed();
			grantHook(0, 1);
		}
	}

	if (m_detectionExpiresFrame > now)
	{
		if (!(self->m_statusBits & 0x20000))
		{
			if (draw)
				rvaAddStealthSound(draw, 0x61, self->m_id);
			self->setStatusBit(0x11, true);
		}
	}
	else if (self->m_statusBits & 0x20000)
	{
		Bool notify = self->locallyControlled();
		if (notify && draw)
			rvaAddStealthSound(draw, 0x60, self->m_id);
		self->clearStatus(0x11);
		if (notify && self->m_container && self->m_container->m_child)
		{
			RvaChild *child = self->m_container->m_child;
			if (child->slot02())
				child->slot16();
		}
	}

	return m_enabled ? UPDATE_SLEEP_NONE : UPDATE_SLEEP_FOREVER;
}
