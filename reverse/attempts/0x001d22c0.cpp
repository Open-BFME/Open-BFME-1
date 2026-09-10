// ?defect@Object@@QAEXPAVTeam@@I@Z
// partial score=0.94 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME: readable reconstruction of Object::defect, retail RVA 0x001D22C0.
//
// This TU keeps the BFME field and vtable views local.  The existing Object
// declarations describe the Zero Hour layout, while this packet reads the
// BFME fields at +0x204/+0x20c and uses the BFME containment/audio slots.
// Calls through the address-derived Rva0041A2E0 and Rva005AA450 views retain
// the honest names of the two anonymous retail callees; neither is given a
// guessed semantic identity here.

#include <list>

typedef unsigned int UnsignedInt;
typedef bool Bool;

class Team;
class Player;
class Object;
class Drawable;
class ProductionUpdateInterface;
class ObjectDefectionHelper;
class ContainModuleInterface;
class PartitionData;

// These TU-local call views are pinned below to the retail ILTs.  Keeping the
// view names unique avoids the several matched body copies of the public
// methods from becoming an identity choice during relocation verification.
class BfmeDefectTeamCall
{
public:
	Player *getControllingPlayer(void) const;
};
#pragma comment(linker, "/alternatename:?getControllingPlayer@BfmeDefectTeamCall@@QBEPAVPlayer@@XZ=?j_0002369b@@YAXXZ")

// ILT 0x0001C503 is the BFME playable-side predicate used by this packet.
// Its final body is address-derived in the current symbol ledger, so retain
// the local call name rather than asserting a different owner for that body.
class BfmeDefectPlayerCall
{
public:
	Bool isPlayableSide(void) const;
};
#pragma comment(linker, "/alternatename:?isPlayableSide@BfmeDefectPlayerCall@@QBE_NXZ=?j_0001c503@@YAXXZ")

class ProductionUpdateInterface
{
public:
#define BFME_DEFECT_PRODUCTION_SLOT(n) virtual void slot##n(void) = 0;
	BFME_DEFECT_PRODUCTION_SLOT(00) BFME_DEFECT_PRODUCTION_SLOT(01)
	BFME_DEFECT_PRODUCTION_SLOT(02) BFME_DEFECT_PRODUCTION_SLOT(03)
	BFME_DEFECT_PRODUCTION_SLOT(04) BFME_DEFECT_PRODUCTION_SLOT(05)
	BFME_DEFECT_PRODUCTION_SLOT(06) BFME_DEFECT_PRODUCTION_SLOT(07)
	BFME_DEFECT_PRODUCTION_SLOT(08) BFME_DEFECT_PRODUCTION_SLOT(09)
	BFME_DEFECT_PRODUCTION_SLOT(10) BFME_DEFECT_PRODUCTION_SLOT(11)
	BFME_DEFECT_PRODUCTION_SLOT(12)
	virtual void cancelAndRefundAllProduction(void) = 0;
#undef BFME_DEFECT_PRODUCTION_SLOT
};

class BfmeDefectHelperCall
{
public:
	void startDefectionTimer(UnsignedInt detectionTime, Bool showEffect);
};
#pragma comment(linker, "/alternatename:?startDefectionTimer@BfmeDefectHelperCall@@QAEXI_N@Z=?j_00024e79@@YAXXZ")

enum BfmeDefectCommandSourceType
{
	BFME_DEFECT_FROM_AI = 2
};

class BfmeDefectAICommandCall
{
public:
	void aiIdle(BfmeDefectCommandSourceType source);
};
#pragma comment(linker, "/alternatename:?aiIdle@BfmeDefectAICommandCall@@QAEXW4BfmeDefectCommandSourceType@@@Z=?j_00024d70@@YAXXZ")

class Radar
{
public:
};

class BfmeDefectRadarCall
{
public:
	void tryInfiltrationEvent(Object *object);
};
#pragma comment(linker, "/alternatename:?tryInfiltrationEvent@BfmeDefectRadarCall@@QAEXPAVObject@@@Z=?j_0000d805@@YAXXZ")

extern Radar *TheRadar;

class PartitionData
{
public:
	void makeDirty(void);
};

// The two methods below are vtable calls in the retail packet.  The slot
// declarations are deliberately unnamed; no unverified member identity is
// introduced for the intervening entries.
class ContainModuleInterface
{
public:
#define BFME_DEFECT_CONTAIN_SLOT(n) virtual void slot##n(void) = 0;
	BFME_DEFECT_CONTAIN_SLOT(00) BFME_DEFECT_CONTAIN_SLOT(01)
	BFME_DEFECT_CONTAIN_SLOT(02) BFME_DEFECT_CONTAIN_SLOT(03)
	BFME_DEFECT_CONTAIN_SLOT(04) BFME_DEFECT_CONTAIN_SLOT(05)
	BFME_DEFECT_CONTAIN_SLOT(06) BFME_DEFECT_CONTAIN_SLOT(07)
	BFME_DEFECT_CONTAIN_SLOT(08) BFME_DEFECT_CONTAIN_SLOT(09)
	BFME_DEFECT_CONTAIN_SLOT(10) BFME_DEFECT_CONTAIN_SLOT(11)
	BFME_DEFECT_CONTAIN_SLOT(12) BFME_DEFECT_CONTAIN_SLOT(13)
	BFME_DEFECT_CONTAIN_SLOT(14) BFME_DEFECT_CONTAIN_SLOT(15)
	BFME_DEFECT_CONTAIN_SLOT(16) BFME_DEFECT_CONTAIN_SLOT(17)
	BFME_DEFECT_CONTAIN_SLOT(18) BFME_DEFECT_CONTAIN_SLOT(19)
	BFME_DEFECT_CONTAIN_SLOT(20) BFME_DEFECT_CONTAIN_SLOT(21)
	BFME_DEFECT_CONTAIN_SLOT(22) BFME_DEFECT_CONTAIN_SLOT(23)
	BFME_DEFECT_CONTAIN_SLOT(24) BFME_DEFECT_CONTAIN_SLOT(25)
	BFME_DEFECT_CONTAIN_SLOT(26) BFME_DEFECT_CONTAIN_SLOT(27)
	BFME_DEFECT_CONTAIN_SLOT(28) BFME_DEFECT_CONTAIN_SLOT(29)
	BFME_DEFECT_CONTAIN_SLOT(30) BFME_DEFECT_CONTAIN_SLOT(31)
	BFME_DEFECT_CONTAIN_SLOT(32) BFME_DEFECT_CONTAIN_SLOT(33)
	BFME_DEFECT_CONTAIN_SLOT(34) BFME_DEFECT_CONTAIN_SLOT(35)
	BFME_DEFECT_CONTAIN_SLOT(36)
	virtual void removeAllContained(Bool ejectAll) = 0;
	BFME_DEFECT_CONTAIN_SLOT(38) BFME_DEFECT_CONTAIN_SLOT(39)
	BFME_DEFECT_CONTAIN_SLOT(40) BFME_DEFECT_CONTAIN_SLOT(41)
	BFME_DEFECT_CONTAIN_SLOT(42) BFME_DEFECT_CONTAIN_SLOT(43)
	BFME_DEFECT_CONTAIN_SLOT(44) BFME_DEFECT_CONTAIN_SLOT(45)
	BFME_DEFECT_CONTAIN_SLOT(46)
	virtual Bool isKickOutOnCapture(void) = 0;
#undef BFME_DEFECT_CONTAIN_SLOT
};

// Retail calls the anonymous Drawable body through ILT 0x0004067E.  The
// address-derived type and method name intentionally do not claim that the
// unresolved body is definitively Drawable::flashAsSelected.
class Rva0041A2E0Drawable
{
public:
	void rva0041A2E0Flash(UnsignedInt mode);
};
#pragma comment(linker, "/alternatename:?rva0041A2E0Flash@Rva0041A2E0Drawable@@QAEXI@Z=?j_0004067e@@YAXXZ")

// The Object vtable slots used by this body are getDrawable (+0x28) and
// setTeam (+0x50).  The class has no data members because the BFME data view
// below is the object representation used for direct field accesses.
class Object
{
public:
	void defect(Team *newTeam, UnsignedInt detectionTime);

#define BFME_DEFECT_OBJECT_SLOT(n) virtual void slot##n(void) = 0;
	BFME_DEFECT_OBJECT_SLOT(00) BFME_DEFECT_OBJECT_SLOT(01)
	BFME_DEFECT_OBJECT_SLOT(02) BFME_DEFECT_OBJECT_SLOT(03)
	BFME_DEFECT_OBJECT_SLOT(04) BFME_DEFECT_OBJECT_SLOT(05)
	BFME_DEFECT_OBJECT_SLOT(06) BFME_DEFECT_OBJECT_SLOT(07)
	BFME_DEFECT_OBJECT_SLOT(08) BFME_DEFECT_OBJECT_SLOT(09)
	virtual Drawable *getDrawable(void) = 0;
	BFME_DEFECT_OBJECT_SLOT(11) BFME_DEFECT_OBJECT_SLOT(12)
	BFME_DEFECT_OBJECT_SLOT(13) BFME_DEFECT_OBJECT_SLOT(14)
	BFME_DEFECT_OBJECT_SLOT(15) BFME_DEFECT_OBJECT_SLOT(16)
	BFME_DEFECT_OBJECT_SLOT(17) BFME_DEFECT_OBJECT_SLOT(18)
	BFME_DEFECT_OBJECT_SLOT(19)
	virtual void setTeam(Team *newTeam) = 0;
#undef BFME_DEFECT_OBJECT_SLOT

};

class BfmeDefectObjectCall
{
public:
	ProductionUpdateInterface *getProductionUpdateInterface(void);
	void friend_setUndetectedDefector(Bool status);
};
#pragma comment(linker, "/alternatename:?getProductionUpdateInterface@BfmeDefectObjectCall@@QAEPAVProductionUpdateInterface@@XZ=?j_00003b52@@YAXXZ")
#pragma comment(linker, "/alternatename:?friend_setUndetectedDefector@BfmeDefectObjectCall@@QAEX_N@Z=?j_0001c864@@YAXXZ")

// BFME Object fields proven by the target's direct offsets.  In particular,
// AI is +0x204 and radar data is +0x20c in this build, not the Zero Hour
// offsets exposed by the shared Object header.
class BfmeDefectObjectFields
{
public:
	void *m_vtable;
	unsigned char m_beforeID[0x74 - 0x04];
	UnsignedInt m_id;
	unsigned char m_beforeStatus[0x90 - 0x78];
	UnsignedInt m_status;
	unsigned char m_beforeDefectionHelper[0x1e4 - 0x94];
	BfmeDefectHelperCall *m_defectionHelper;
	unsigned char m_beforeContain[0x1fc - 0x1e8];
	ContainModuleInterface *m_contain;
	unsigned char m_beforeAI[0x204 - 0x200];
	void *m_ai;
	unsigned char m_beforeRadar[0x20c - 0x208];
	void *m_radarData;
	unsigned char m_beforeContainedBy[0x214 - 0x210];
	void *m_containedBy;
	unsigned char m_beforeTeam[0x23c - 0x218];
	Team *m_team;
	unsigned char m_beforePartition[0x3b0 - 0x240];
	PartitionData *m_partitionData;
};

// This is the only anonymous tail callee.  It is called with cdecl stack
// arguments (&list, 0x7df, false); the ILT target is exactly RVA 0x005AA450.
extern "C" void __cdecl Rva005AA450(void *drawables, UnsignedInt tag, Bool enabled);
#pragma comment(linker, "/alternatename:Rva005AA450=?j_000196c8@@YAXXZ")

class Rva005A00B0AudioEvent
{
public:
	Rva005A00B0AudioEvent(const Rva005A00B0AudioEvent &other);
	~Rva005A00B0AudioEvent(void);
	void setObjectID(UnsignedInt objectID);
	void setPlayerIndex(int playerIndex);

private:
	unsigned char m_data[0x70];
};
#pragma comment(linker, "/alternatename:??0Rva005A00B0AudioEvent@@QAE@ABV0@@Z=?j_00047b27@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva005A00B0AudioEvent@@QAE@XZ=?j_00026f35@@YAXXZ")
#pragma comment(linker, "/alternatename:?setObjectID@Rva005A00B0AudioEvent@@QAEXI@Z=?j_00019a6a@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPlayerIndex@Rva005A00B0AudioEvent@@QAEXH@Z=?j_0003ac88@@YAXXZ")

struct Rva005A00B0MiscAudio
{
	unsigned char m_beforeDefectorTimerSound[0x230];
	Rva005A00B0AudioEvent m_defectorTimerTickSound;
};

struct Rva005A00B0AudioClient
{
#define BFME_DEFECT_AUDIO_SLOT(n) virtual void slot##n(void) = 0;
	BFME_DEFECT_AUDIO_SLOT(00) BFME_DEFECT_AUDIO_SLOT(01)
	BFME_DEFECT_AUDIO_SLOT(02) BFME_DEFECT_AUDIO_SLOT(03)
	BFME_DEFECT_AUDIO_SLOT(04) BFME_DEFECT_AUDIO_SLOT(05)
	BFME_DEFECT_AUDIO_SLOT(06) BFME_DEFECT_AUDIO_SLOT(07)
	BFME_DEFECT_AUDIO_SLOT(08) BFME_DEFECT_AUDIO_SLOT(09)
	BFME_DEFECT_AUDIO_SLOT(10) BFME_DEFECT_AUDIO_SLOT(11)
	BFME_DEFECT_AUDIO_SLOT(12) BFME_DEFECT_AUDIO_SLOT(13)
	BFME_DEFECT_AUDIO_SLOT(14) BFME_DEFECT_AUDIO_SLOT(15)
	BFME_DEFECT_AUDIO_SLOT(16)
	virtual UnsignedInt addAudioEvent(Rva005A00B0AudioEvent *event) = 0;
	BFME_DEFECT_AUDIO_SLOT(18) BFME_DEFECT_AUDIO_SLOT(19)
	BFME_DEFECT_AUDIO_SLOT(20) BFME_DEFECT_AUDIO_SLOT(21)
	BFME_DEFECT_AUDIO_SLOT(22) BFME_DEFECT_AUDIO_SLOT(23)
	BFME_DEFECT_AUDIO_SLOT(24) BFME_DEFECT_AUDIO_SLOT(25)
	BFME_DEFECT_AUDIO_SLOT(26) BFME_DEFECT_AUDIO_SLOT(27)
	BFME_DEFECT_AUDIO_SLOT(28) BFME_DEFECT_AUDIO_SLOT(29)
	BFME_DEFECT_AUDIO_SLOT(30) BFME_DEFECT_AUDIO_SLOT(31)
	BFME_DEFECT_AUDIO_SLOT(32) BFME_DEFECT_AUDIO_SLOT(33)
	BFME_DEFECT_AUDIO_SLOT(34) BFME_DEFECT_AUDIO_SLOT(35)
	BFME_DEFECT_AUDIO_SLOT(36) BFME_DEFECT_AUDIO_SLOT(37)
	BFME_DEFECT_AUDIO_SLOT(38) BFME_DEFECT_AUDIO_SLOT(39)
	BFME_DEFECT_AUDIO_SLOT(40) BFME_DEFECT_AUDIO_SLOT(41)
	BFME_DEFECT_AUDIO_SLOT(42) BFME_DEFECT_AUDIO_SLOT(43)
	BFME_DEFECT_AUDIO_SLOT(44) BFME_DEFECT_AUDIO_SLOT(45)
	BFME_DEFECT_AUDIO_SLOT(46) BFME_DEFECT_AUDIO_SLOT(47)
	BFME_DEFECT_AUDIO_SLOT(48) BFME_DEFECT_AUDIO_SLOT(49)
	BFME_DEFECT_AUDIO_SLOT(50) BFME_DEFECT_AUDIO_SLOT(51)
	BFME_DEFECT_AUDIO_SLOT(52) BFME_DEFECT_AUDIO_SLOT(53)
	BFME_DEFECT_AUDIO_SLOT(54) BFME_DEFECT_AUDIO_SLOT(55)
	BFME_DEFECT_AUDIO_SLOT(56) BFME_DEFECT_AUDIO_SLOT(57)
	BFME_DEFECT_AUDIO_SLOT(58) BFME_DEFECT_AUDIO_SLOT(59)
	BFME_DEFECT_AUDIO_SLOT(60) BFME_DEFECT_AUDIO_SLOT(61)
	BFME_DEFECT_AUDIO_SLOT(62) BFME_DEFECT_AUDIO_SLOT(63)
	BFME_DEFECT_AUDIO_SLOT(64) BFME_DEFECT_AUDIO_SLOT(65)
	BFME_DEFECT_AUDIO_SLOT(66) BFME_DEFECT_AUDIO_SLOT(67)
	BFME_DEFECT_AUDIO_SLOT(68) BFME_DEFECT_AUDIO_SLOT(69)
	BFME_DEFECT_AUDIO_SLOT(70) BFME_DEFECT_AUDIO_SLOT(71)
	BFME_DEFECT_AUDIO_SLOT(72)
	virtual Rva005A00B0MiscAudio *getMiscAudio(void) = 0;
#undef BFME_DEFECT_AUDIO_SLOT
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

// ?defect@Object@@QAEXPAVTeam@@I@Z
void Object::defect(Team *newTeam, UnsignedInt detectionTime)
{
	BfmeDefectObjectFields *self = reinterpret_cast<BfmeDefectObjectFields *>(this);

	if (self->m_containedBy)
		return;

	if (!self->m_team)
		return;

	Player *player = reinterpret_cast<BfmeDefectTeamCall *>(self->m_team)->getControllingPlayer();
	if (!player)
		return;

	Team *myTeam = *reinterpret_cast<Team **>(reinterpret_cast<char *>(player) + 0x230);
	if (myTeam == newTeam)
		return;

	if ((self->m_status & 0x00000004) != 0 || (self->m_status & 0x00080000) != 0)
		return;

	ProductionUpdateInterface *production =
		reinterpret_cast<BfmeDefectObjectCall *>(this)->getProductionUpdateInterface();
	if (production)
		production->cancelAndRefundAllProduction();

	if (self->m_radarData &&
		reinterpret_cast<BfmeDefectPlayerCall *>(
			reinterpret_cast<BfmeDefectTeamCall *>(newTeam)->getControllingPlayer())->isPlayableSide() &&
		reinterpret_cast<BfmeDefectPlayerCall *>(
			reinterpret_cast<BfmeDefectTeamCall *>(myTeam)->getControllingPlayer())->isPlayableSide())
	{
		reinterpret_cast<BfmeDefectRadarCall *>(TheRadar)->tryInfiltrationEvent(this);
	}

	reinterpret_cast<BfmeDefectObjectCall *>(this)->friend_setUndetectedDefector(detectionTime > 0);

	if (self->m_defectionHelper)
		self->m_defectionHelper->startDefectionTimer(detectionTime, true);

	setTeam(newTeam);

	if (self->m_partitionData)
		self->m_partitionData->makeDirty();

	if (self->m_ai)
	{
		BfmeDefectAICommandCall *commands = reinterpret_cast<BfmeDefectAICommandCall *>(
			reinterpret_cast<char *>(self->m_ai) + 0x20);
		commands->aiIdle(BFME_DEFECT_FROM_AI);
	}

	Drawable *drawable = getDrawable();
	if (drawable)
	{
		reinterpret_cast<Rva0041A2E0Drawable *>(drawable)->rva0041A2E0Flash(0);

		Rva005A00B0MiscAudio *misc = TheAudioClientUpdate->getMiscAudio();
		Rva005A00B0AudioEvent defectorTimerSound(misc->m_defectorTimerTickSound);
		defectorTimerSound.setObjectID(self->m_id);
		if (reinterpret_cast<BfmeDefectTeamCall *>(newTeam)->getControllingPlayer())
		{
			Player *newPlayer = reinterpret_cast<BfmeDefectTeamCall *>(newTeam)->getControllingPlayer();
			int playerIndex = *reinterpret_cast<int *>(reinterpret_cast<char *>(newPlayer) + 0x24);
			defectorTimerSound.setPlayerIndex(playerIndex);
		}
		TheAudioClientUpdate->addAudioEvent(&defectorTimerSound);

		_STL::list<Drawable *> drawables;
		drawables.push_back(drawable);
		Rva005AA450(&drawables, 0x7df, false);
	}

	ContainModuleInterface *contain = self->m_contain;
	if (contain && contain->isKickOutOnCapture())
		contain->removeAllContained(true);
}
