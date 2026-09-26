// ?d_00290b90@@YAXXZ
// partial score=0.93 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// ?Rva00290B90@EmotionTrackerUpdate@@QAEPAVEmotion@@XZ
// Emotion selection walk; layout taken from the matched constructor at 0x00290740.

class Object;
class Player;
class Emotion;
class ModuleData;
class EmotionTrackerUpdateEntry;
class Overridable;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Overridable
{
public:
	Overridable *getFinalOverride() const;
};

struct Rva00290B90Template
{
	unsigned char m_pad00[4];
	Overridable *m_override;
	unsigned char m_pad08[0xc0];
	unsigned int m_flags;
};

struct Rva00290B90Slot
{
	unsigned char m_pad00[0x28];
	int m_value28;
};

class Player
{
public:
	unsigned char m_pad00[0x24];
	int m_index;
};

class Object
{
public:
	Player *getControllingPlayer() const;

	unsigned char m_pad00[4];
	Rva00290B90Template *m_template;
	unsigned char m_pad08[0x30];
	Coord3D m_position;
	unsigned char m_pad44[0x4c];
	unsigned int m_status;
	unsigned char m_pad94[0x17c];
	Rva00290B90Slot *m_slot210;
};

class EmotionTrackerUpdateEntry
{
public:
	unsigned char m_pad00[4];
	int m_type;
	unsigned char m_pad08[4];
	int m_flag0c;
};

class Emotion
{
public:
	unsigned char m_pad00[4];
	EmotionTrackerUpdateEntry *m_entry;
};

class Rva0037C310Owner
{
public:
	bool Rva0037C310(int a, int b, Object *target);
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

struct PlayerList
{
	unsigned short getPlayersWithRelationship(int index, int relation, bool flag);
};

struct Rva002EEDA0ShroudManager
{
	int lookup(const Coord3D *position, int mode, unsigned int mask);
};

struct Gen_001BEC20
{
	int bfmeScale() const;
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPlayersWithRelationship@PlayerList@@QAEGHH_N@Z=?j_00044c60@@YAXXZ")
#pragma comment(linker, "/alternatename:?lookup@Rva002EEDA0ShroudManager@@QAEHPBUCoord3D@@HI@Z=?m@Gen_008f7470@@QAEXXZ")
#pragma comment(linker, "/alternatename:?findObjectByID@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva0037C310@Rva0037C310Owner@@QAE_NHHPAVObject@@@Z=?j_000466b4@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeScale@Gen_001BEC20@@QBEHXZ=?j_0003a391@@YAXXZ")

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define Rva002EE330ThePlayers (*(PlayerList **)0x012ED748)
#define Rva002EEDA0TheShroudManager (*(Rva002EEDA0ShroudManager **)0x012ED5BC)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Object *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Object *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData) {}
	virtual ~BehaviorModule();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Object *thing, const ModuleData *moduleData)
		: BehaviorModule(thing, moduleData) {}
	virtual ~UpdateModule();

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class EmotionTrackerUpdateSecondaryBase
{
public:
	virtual void slot();
};

class EmotionTrackerUpdateModuleData
{
public:
	unsigned char m_pad00[0x2c];
	bool m_flag2c;
};

class EmotionTrackerUpdate
	: public UpdateModule,
	  public EmotionTrackerUpdateSecondaryBase
{
public:
	Emotion *Rva00290B90();

private:
	bool m_active[10];
	unsigned int m_startFrame[10];
	unsigned int m_endFrame[10];
	Emotion **m_emotionsBegin;
	Emotion **m_emotionsEnd;
	Emotion **m_emotionsCapacity;
	Emotion *m_currentEmotion;
	unsigned int m_distributionIndex;
	unsigned char m_pad94[0x0c];
	int m_activeEmotionType;
	int m_forcedRetry;
};

Emotion *EmotionTrackerUpdate::Rva00290B90()
{
	for (;;)
	{
		int shroudOther;
		int shroudSelf = 0;

		if (m_object != 0)
		{
			Player *player = m_object->getControllingPlayer();
			if (player != 0)
			{
				unsigned int maskA =
					Rva002EE330ThePlayers->getPlayersWithRelationship(player->m_index, 3, false);
				unsigned int maskB =
					Rva002EE330ThePlayers->getPlayersWithRelationship(player->m_index, 4, false);
				shroudOther =
					Rva002EEDA0TheShroudManager->lookup(&m_object->m_position, 1, maskB);
				shroudSelf =
					Rva002EEDA0TheShroudManager->lookup(&m_object->m_position, 1, maskA);
			}
		}

		int level = 0;
		int selfLayer;
		if (m_object->m_slot210 != 0)
			level = m_object->m_slot210->m_value28;

		for (Emotion **it = m_emotionsBegin; it != m_emotionsEnd; ++it)
		{
			Emotion *e = *it;

			if (e == m_currentEmotion && e->m_entry->m_flag0c != 0)
			{
				Object *held =
					TheBfmeGameLogic->findObjectByID(m_endFrame[e->m_entry->m_type]);
				if (((Rva0037C310Owner *)e)->Rva0037C310(shroudOther, shroudSelf, held))
					return e;
			}

			if (m_forcedRetry > 0)
			{
				if (e->m_entry->m_type != m_activeEmotionType)
					continue;
			}
			else if (!m_active[e->m_entry->m_type])
			{
				continue;
			}

			if (!((const EmotionTrackerUpdateModuleData *)m_moduleData)->m_flag2c && level >= 2)
			{
				if (e->m_entry->m_type == 4)
					continue;
				if (e->m_entry->m_type == 5)
					continue;
				if (e->m_entry->m_type == 6)
					continue;
			}

			if (e->m_entry->m_type == 6)
			{
				Object *other = TheBfmeGameLogic->findObjectByID(m_endFrame[6]);
				if (other != 0)
				{
					Rva00290B90Template *t = other->m_template;
					if (t != 0 && t->m_override != 0)
						t = (Rva00290B90Template *)t->m_override->getFinalOverride();
					if ((t->m_flags & 0x2000000) == 0 &&
						(other->m_status & 0x40) == 0 &&
						(selfLayer = ((Gen_001BEC20 *)m_object)->bfmeScale()) !=
							((Gen_001BEC20 *)other)->bfmeScale())
						continue;
				}
			}

			Object *target =
				TheBfmeGameLogic->findObjectByID(m_endFrame[e->m_entry->m_type]);
			if (((Rva0037C310Owner *)e)->Rva0037C310(shroudOther, shroudSelf, target))
				return e;
		}

		if (m_forcedRetry <= 0)
			return 0;
		m_forcedRetry = 0;
	}
}
