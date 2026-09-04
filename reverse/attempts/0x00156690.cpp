// ?groupEvacuate@AIGroup@@QAEXW4CommandSourceType@@@Z
// partial score=0.94 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc

// Open-BFME: AIGroup::groupEvacuate, retail 0x00156690, 260 bytes.
//
// Same member walk as groupHunt / groupTightenToPosition. Identity is the
// matched aiEvacuate (ILT 0x000344C3 -> 0x000D8AC0) and aiMoveToAndEvacuate
// (ILT 0x00027903 -> 0x001528E0) callees, plus the ZH aircraft-vs-structure
// split: airborne aircraft drop via TerrainLogic layer height, structures
// order passengers out through contain+0x1FC virt+0x6C.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType { BFME_COMMAND_SOURCE_PLAYER };
enum KindOfType { KINDOF_STRUCTURE = 7, KINDOF_AIRCRAFT = 12 };
enum PathfindLayerEnum { LAYER_GROUND = 1 };

class Object;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(unsigned int)t >> 5] & (1u << ((unsigned int)t & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	unsigned int m_kindof[3];
};

class AICommandInterface
{
public:
	void aiMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource);
	void aiEvacuate(bool exposeStealthUnits, CommandSourceType cmdSource);
};

class BfmeGroupAI
{
public:
	char m_bfmeHead[0x20];
	AICommandInterface m_bfmeCommands;
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void orderAllPassengersToExit(CommandSourceType cmdSource);
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
			Coord3D *normal, bool clip);

	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, bool onlyHealthy);
};

extern TerrainLogic *TheTerrainLogic;

class Object
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}

	bool isKindOf(KindOfType t) const
	{
		return getTemplate()->isKindOf(t);
	}

	const Coord3D *getPosition(void) const { return &m_position; }
	BfmeGroupAI *getAI(void) { return m_ai; }
	bool isAirborneTarget(void) const { return (m_status90 & 0x40) != 0; }
	ContainModuleInterface *getContain(void) { return m_contain; }

private:
	virtual ~Object();
	const ThingTemplate *m_template;
	unsigned char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unreconstructed_44[0x90 - 0x44];
	unsigned char m_status90;
	unsigned char m_unreconstructed_91[0x1FC - 0x91];
	ContainModuleInterface *m_contain;
	unsigned char m_unreconstructed_200[0x204 - 0x200];
	BfmeGroupAI *m_ai;
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;
	BfmeListNodeBase *m_bfmePrev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;
};

class AIGroup
{
public:
	void groupEvacuate(CommandSourceType cmdSource);

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;
};

// ?groupEvacuate@AIGroup@@QAEXW4CommandSourceType@@@Z
void AIGroup::groupEvacuate(CommandSourceType cmdSource)
{
	BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
	CommandSourceType src = cmdSource;
	Object *obj;
	BfmeGroupAI *ai;
	for (;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		ai = obj->getAI();
		if (ai)
		{
			if (obj->isKindOf(KINDOF_AIRCRAFT) && obj->isAirborneTarget())
			{
				Coord3D pos = *obj->getPosition();
				PathfindLayerEnum layerAtDest =
						TheTerrainLogic->getHighestLayerForDestination(&pos, false);
				pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layerAtDest, 0, true);
				ai->m_bfmeCommands.aiMoveToAndEvacuate(&pos, src);
			}
			else
			{
				ai->m_bfmeCommands.aiEvacuate(false, src);
			}
		}
		else if (obj->isKindOf(KINDOF_STRUCTURE))
		{
			ContainModuleInterface *contain = obj->getContain();
			if (contain)
				contain->orderAllPassengersToExit(src);
		}
	}
}
