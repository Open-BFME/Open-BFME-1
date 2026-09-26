// ?update@ProductionUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.2 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME retail 0x0029E330.  The update entry point is the secondary
// UpdateModuleInterface subobject at ProductionUpdate + 0x10.
// Keep the BFME object and queue views local; the Zero Hour headers describe
// neither the interface adjustment nor the queue-entry additions.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef bool Bool;

enum RvaUpdateSleepTime
{
	RVA_UPDATE_SLEEP_NONE = 0
};

struct RvaProductionUpdateModuleData;
struct RvaProductionEntry;
struct RvaObject;
struct RvaPlayer;
struct RvaExitInterface;

struct RvaGameLogic
{
	UnsignedByte m_head[0x3c];
	UnsignedInt m_frame;
};

struct RvaDoorInfo
{
	UnsignedInt m_opened;
	UnsignedInt m_waitOpen;
	UnsignedInt m_closed;
	Bool m_holdOpen;
	UnsignedByte m_padding[3];
};

struct RvaProductionUpdateFull
{
	void *m_primaryVtable;
	RvaProductionUpdateModuleData *m_moduleData;
	RvaObject *m_object;
	UnsignedByte m_prefix[0x1c];
	RvaProductionEntry *m_queue;
	RvaProductionEntry *m_queueTail;
	Int m_productionCount;
	UnsignedInt m_uniqueID;
	UnsignedInt m_constructionCompleteFrame;
	RvaDoorInfo m_doors[4];
	UnsignedInt m_clearFlags[10];
	UnsignedInt m_setFlags[10];
	Bool m_flagsDirty;
	UnsignedByte m_flagsPadding[3];
	UnsignedInt m_specialPowerConstructionCommandButton;
	Bool m_specialPowerConstructionActive;
	UnsignedByte m_specialPadding[3];
	UnsignedInt m_objectID;
	void *m_queueIterator;
	UnsignedInt m_queueIteratorCount;
	UnsignedInt m_specialValue;
};

struct RvaProductionEntry
{
	virtual void deleteEntry(Int);
	Int m_type;
	void *m_objectToProduce;
	void *m_upgradeToResearch;
	UnsignedInt m_productionID;
	Real m_percentComplete;
	Real m_rate;
	Real m_framesUnderConstruction;
	Int m_quantityTotal;
	Int m_quantityProduced;
	Int m_unknown28;
	Int m_exitDoor;
	Int m_unknown30;
	Bool m_special;
	UnsignedByte m_padding35[3];
	Int m_unknown38;
	RvaProductionEntry *m_next;
	RvaProductionEntry *m_previous;
};

struct RvaProductionUpdateModuleData
{
	UnsignedByte m_head[8];
	Int m_numDoorAnimations;
	UnsignedByte m_padding0c[0x0c];
	UnsignedInt m_constructionCompleteDuration;
	UnsignedByte m_padding1c[0x14];
	Bool m_bfmeDoorMode;
	UnsignedByte m_padding31[3];
	UnsignedInt m_bfmeProductionDuration;
	UnsignedInt m_bfmeProductionValue;
};

struct RvaObject
{
	UnsignedByte m_head[4];
};

struct RvaPlayer
{
	UnsignedByte m_head[4];
};

struct RvaExitInterface
{
	virtual void slot00();
	virtual Int reserveDoor(void *, void *);
	virtual void exitObject(RvaObject *, Int);
};

struct RvaAudioEvent
{
	UnsignedByte m_storage[0x70];
};

struct RvaAudioClient
{
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
	virtual Int addAudio(RvaAudioEvent *);
	virtual void slot18();
	virtual void releaseAudio(Int);
};

static RvaGameLogic *&RvaTheGameLogic = *(RvaGameLogic **)0x012F0898;
static RvaAudioClient *&RvaTheAudioClient = *(RvaAudioClient **)0x012ED668;
static UnsignedInt &RvaStaticNameKey = *(UnsignedInt *)0x012F0008;
static UnsignedInt &RvaNameKeyGuard = *(UnsignedInt *)0x012F000C;
static UnsignedInt &RvaControlBar = *(UnsignedInt *)0x012F33F8;
static Real &RvaZeroRange = *(Real *)0x01075350;
static Real &RvaScale = *(Real *)0x0107FAC4;

extern void j_0003add7();
extern void j_000157f3();
extern void j_00020824();
extern void j_00043cca();
extern void j_0002191d();
extern void j_00008e86();
extern void j_0003ac88();
extern void j_00026f35();
extern void j_00037038();
extern void j_000095ed();
extern void j_0002f3c4();
extern void j_0001a276();
extern void j_00022336();
extern void j_0002b5f3();
extern void j_000077b6();
extern void j_00030a1c();
extern void j_0002fbb7();
extern void j_0004b01f();
extern void j_0002abf8();
extern void j_0000a7a9();
extern void j_0001e204();
extern void j_00023d4e();
extern void j_0003f8d7();
extern void j_00010096();

typedef Int (RvaProductionUpdateFull::*RvaCurrentProductionCall)();
typedef RvaProductionEntry *(RvaProductionUpdateFull::*RvaCurrentEntryCall)();
typedef RvaPlayer *(RvaObject::*RvaControllerCall)();
typedef void (RvaObject::*RvaNotifyCall)();
typedef void (RvaProductionUpdateFull::*RvaDoorUpdateCall)();
typedef void (RvaObject::*RvaClearSetCall)(const UnsignedInt *,
	const UnsignedInt *);
typedef void (RvaProductionUpdateFull::*RvaRemoveCall)(RvaProductionEntry *);
typedef void (RvaPlayer::*RvaGoCall)(void *);
typedef Bool (RvaPlayer::*RvaCanBuildCall)(void *);
typedef Bool (RvaPlayer::*RvaTemplateCheckCall)(void *);
typedef void (RvaPlayer::*RvaUpgradeCall)(void *);
typedef void (RvaAudioEvent::*RvaThinAudioCtor)(void *, void *);
typedef void (RvaAudioEvent::*RvaAudioPlayerIndexCall)(Int);
typedef void (RvaAudioEvent::*RvaAudioDtorCall)();
typedef RvaExitInterface *(RvaObject::*RvaExitCall)();

static __forceinline RvaProductionEntry *rvaCurrentProduction(
	RvaProductionUpdateFull *update)
{
	union { void (*raw)(); RvaCurrentEntryCall member; } call;
	call.raw = j_000157f3;
	return (update->*call.member)();
}

static __forceinline RvaPlayer *rvaController(RvaObject *object)
{
	union { void (*raw)(); RvaControllerCall member; } call;
	call.raw = j_00020824;
	return (object->*call.member)();
}

static __forceinline void rvaNotify(RvaObject *object)
{
	union { void (*raw)(); RvaNotifyCall member; } call;
	call.raw = j_0002191d;
	(object->*call.member)();
}

static __forceinline void rvaUpdateDoors(RvaProductionUpdateFull *update)
{
	union { void (*raw)(); RvaDoorUpdateCall member; } call;
	call.raw = j_00037038;
	(update->*call.member)();
}

static __forceinline void rvaClearAndSet(RvaObject *object,
	const UnsignedInt *clearFlags, const UnsignedInt *setFlags)
{
	union { void (*raw)(); RvaClearSetCall member; } call;
	call.raw = j_000095ed;
	(object->*call.member)(clearFlags, setFlags);
}

static __forceinline void rvaRemove(RvaProductionUpdateFull *update,
	RvaProductionEntry *production)
{
	union { void (*raw)(); RvaRemoveCall member; } call;
	call.raw = j_0002f3c4;
	(update->*call.member)(production);
}

static __forceinline Bool rvaCanBuild(RvaPlayer *player, void *thing)
{
	union { void (*raw)(); RvaCanBuildCall member; } call;
	call.raw = j_0001a276;
	return (player->*call.member)(thing);
}

static __forceinline Bool rvaCreateButton(RvaPlayer *player, void *thing)
{
	union { void (*raw)(); RvaTemplateCheckCall member; } call;
	call.raw = j_00022336;
	return (player->*call.member)(thing);
}

static __forceinline RvaExitInterface *rvaExitInterface(RvaObject *object)
{
	union { void (*raw)(); RvaExitCall member; } call;
	call.raw = j_00023d4e;
	return (object->*call.member)();
}

static __forceinline void rvaAudioCtor(RvaAudioEvent *sound,
	void *first, void *second)
{
	union { void (*raw)(); RvaThinAudioCtor member; } call;
	call.raw = j_00008e86;
	(sound->*call.member)(first, second);
}

static __forceinline void rvaAudioSetPlayerIndex(RvaAudioEvent *sound,
	Int index)
{
	union { void (*raw)(); RvaAudioPlayerIndexCall member; } call;
	call.raw = j_0003ac88;
	(sound->*call.member)(index);
}

static __forceinline void rvaAudioDestroy(RvaAudioEvent *sound)
{
	union { void (*raw)(); RvaAudioDtorCall member; } call;
	call.raw = j_00026f35;
	(sound->*call.member)();
}

static __forceinline Bool rvaAffectedByUpgrade(RvaObject *object,
	void *upgrade)
{
	typedef Bool (RvaObject::*AffectedCall)(void *);
	union { void (*raw)(); AffectedCall member; } call;
	call.raw = j_000077b6;
	return (object->*call.member)(upgrade);
}

static __forceinline void rvaDeleteEntry(RvaProductionEntry *entry)
{
	entry->deleteEntry(1);
}

// ?update@ProductionUpdate@@UAE?AW4UpdateSleepTime@@XZ
static __forceinline RvaUpdateSleepTime rvaProductionUpdateUpdate(
	RvaProductionUpdateFull *update)
{
	const RvaProductionUpdateModuleData *data = update->m_moduleData;
	RvaObject *object = update->m_object;
	UnsignedInt now = RvaTheGameLogic->m_frame;
	RvaProductionEntry *production = rvaCurrentProduction(update);
	RvaPlayer *player = rvaController(object);

	if (player == 0)
	{
		if (production != 0)
		{
			rvaRemove(update, production);
			rvaDeleteEntry(production);
		}
		return RVA_UPDATE_SLEEP_NONE;
	}

	if (data != 0 && data->m_numDoorAnimations > 0)
		rvaUpdateDoors(update);

	if (update->m_constructionCompleteFrame != 0 && data != 0 &&
		now - update->m_constructionCompleteFrame >
		data->m_constructionCompleteDuration)
	{
		update->m_constructionCompleteFrame = 0;
		update->m_clearFlags[0] |= 0x200;
		update->m_setFlags[0] &= ~0x200;
		update->m_flagsDirty = true;
	}

	if (update->m_flagsDirty)
	{
		rvaClearAndSet(object, update->m_clearFlags, update->m_setFlags);
		for (Int i = 0; i < 10; ++i)
		{
			update->m_clearFlags[i] = 0;
			update->m_setFlags[i] = 0;
		}
		update->m_flagsDirty = false;
	}

	if (production == 0)
		return RVA_UPDATE_SLEEP_NONE;

	if ((*(UnsignedInt *)((UnsignedByte *)object + 0x90) & 0x80000) != 0)
		return RVA_UPDATE_SLEEP_NONE;

	if ((*(UnsignedByte *)((UnsignedByte *)object + 0x134) & 1) != 0)
	{
		if (*(UnsignedByte *)((UnsignedByte *)data + 0x3d))
		{
			RvaProductionEntry *voiceEntry =
				*(RvaProductionEntry **)((UnsignedByte *)data + 0x40);
			if (voiceEntry != 0)
			{
				RvaAudioEvent sound;
				rvaAudioCtor(&sound, voiceEntry,
					*(void **)((UnsignedByte *)object + 0x74));
				rvaAudioSetPlayerIndex(&sound,
					*(Int *)((UnsignedByte *)player + 0x24));
				if (RvaTheAudioClient != 0)
					RvaTheAudioClient->addAudio(&sound);
				rvaAudioDestroy(&sound);
			}
		}
	}

	if (production->m_type == 1 && update->m_objectID == 0 &&
		update->m_specialPowerConstructionCommandButton == 0)
	{
		Bool allowed = rvaCanBuild(player, production->m_objectToProduce);
		Bool button = rvaCreateButton(player, production->m_objectToProduce);
		if (allowed && !button && !production->m_special)
		{
			update->m_specialPowerConstructionCommandButton = 1;
		}
	}

	if (production->m_type == 2 && production->m_upgradeToResearch != 0)
	{
		if (!rvaAffectedByUpgrade(object, production->m_upgradeToResearch))
			return RVA_UPDATE_SLEEP_NONE;
	}

	production->m_framesUnderConstruction += 1.0f;
	Int duration = (Int)production->m_rate;
	if (duration <= 0)
		duration = 1;
	production->m_percentComplete =
		production->m_framesUnderConstruction / (Real)duration * RvaScale;

	if (production->m_percentComplete < RvaScale)
		return RVA_UPDATE_SLEEP_NONE;

	if (production->m_type == 2)
	{
		union { void (*raw)(); RvaGoCall upgradeCall; } upgrade;
		upgrade.raw = j_00043cca;
		(player->*upgrade.upgradeCall)(production->m_upgradeToResearch);
		rvaRemove(update, production);
		rvaDeleteEntry(production);
		return RVA_UPDATE_SLEEP_NONE;
	}

	RvaExitInterface *exitInterface = rvaExitInterface(object);
	if (exitInterface == 0)
		goto remove_unit;

	Int remaining = production->m_quantityTotal - production->m_quantityProduced;
	for (Int attempt = 0; attempt < remaining; ++attempt)
	{
		Int door = production->m_exitDoor;
		if (door == -1)
		{
			door = exitInterface->reserveDoor(production->m_objectToProduce, 0);
			production->m_exitDoor = door;
		}
		if (door == -1)
			break;

		if (door >= 0 && door < 4 && data != 0 &&
			data->m_numDoorAnimations > 0)
		{
			RvaDoorInfo *doorInfo = &update->m_doors[door];
			if (doorInfo->m_opened == 0 && doorInfo->m_waitOpen == 0 &&
				doorInfo->m_closed == 0)
			{
				doorInfo->m_opened = now;
				update->m_setFlags[0] |= (1u << (18 + door * 4));
				update->m_flagsDirty = true;
			}
			else if (doorInfo->m_waitOpen != 0)
			{
				doorInfo->m_waitOpen = now;
			}
		}

		if (data == 0 || data->m_numDoorAnimations == 0 || door < 0 ||
			door >= 4 || update->m_doors[door].m_waitOpen != 0)
		{
			RvaObject *newObject = production->m_objectToProduce != 0 ?
				(RvaObject *)production->m_objectToProduce : 0;
			if (newObject != 0)
				exitInterface->exitObject(newObject, door);
			production->m_exitDoor = -1;
			++production->m_quantityProduced;
		}
	}

	if (production->m_quantityTotal - production->m_quantityProduced == 0)
	{
remove_unit:
		rvaRemove(update, production);
		rvaDeleteEntry(production);
	}
	return RVA_UPDATE_SLEEP_NONE;
}

class Rva0029E330ProductionUpdate
{
public:
	virtual RvaUpdateSleepTime update();
};

// ?update@ProductionUpdate@@UAE?AW4UpdateSleepTime@@XZ
RvaUpdateSleepTime Rva0029E330ProductionUpdate::update()
{
	return rvaProductionUpdateUpdate(
		(RvaProductionUpdateFull *)((UnsignedByte *)this - 0x10));
}
