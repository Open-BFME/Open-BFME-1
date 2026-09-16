// ?recruitUnits@Rva000F2FB0Team@@QAEXPBVRva000F2FB0ThingTemplate@@PAVRva000F2FB0ObjectTypes@@HM@Z
// partial score=0.14 date=2026-09-16
// Scratch reconstruction of the BFME Team recruitment loop at 0x000F2FB0.
typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Player;
class Rva000F2FB0Team;
class Rva000F2FB0ThingTemplate;

class Rva000F2FB0Overridable
{
public:
	void *m_vtable;
	Rva000F2FB0Overridable *m_nextOverride;
	Rva000F2FB0Overridable *getFinalOverride(void) const;
};

class Rva000F2FB0ThingTemplate : public Rva000F2FB0Overridable
{
public:
	Bool isEquivalentTo(const Rva000F2FB0ThingTemplate *) const;
	Bool isInBuildVariations(const Rva000F2FB0ThingTemplate *) const;
};

class Rva000F2FB0ObjectTypes
{
public:
	Bool isInSet(const Rva000F2FB0ThingTemplate *) const;
};

class Rva000F2FB0Player
{
public:
	unsigned char m_unmodelled_000[0x230];
	Rva000F2FB0Team *m_defaultTeam;
};

class Rva000F2FB0TeamPrototype
{
public:
	unsigned char m_unmodelled_000[0x08];
	Rva000F2FB0Player *m_owningPlayer;
	unsigned char m_unmodelled_00c[0x1bc - 0x0c];
	Bool m_isAIRecruitable;
	unsigned char m_unmodelled_1bd[0x1c8 - 0x1bd];
	Int m_productionPriority;
};

class Rva000F2FB0Object
{
public:
#define RVA_OBJECT_SLOT(n) virtual void objectSlot##n(void) = 0;
	RVA_OBJECT_SLOT(00) RVA_OBJECT_SLOT(01) RVA_OBJECT_SLOT(02)
	RVA_OBJECT_SLOT(03) RVA_OBJECT_SLOT(04) RVA_OBJECT_SLOT(05)
	RVA_OBJECT_SLOT(06) RVA_OBJECT_SLOT(07) RVA_OBJECT_SLOT(08)
	RVA_OBJECT_SLOT(09) RVA_OBJECT_SLOT(10) RVA_OBJECT_SLOT(11)
	RVA_OBJECT_SLOT(12) RVA_OBJECT_SLOT(13) RVA_OBJECT_SLOT(14)
	RVA_OBJECT_SLOT(15) RVA_OBJECT_SLOT(16) RVA_OBJECT_SLOT(17)
	RVA_OBJECT_SLOT(18) RVA_OBJECT_SLOT(19)
	virtual void setTeam(Rva000F2FB0Team *) = 0;
#undef RVA_OBJECT_SLOT

	Rva000F2FB0Player *getControllingPlayer(void) const;

	Rva000F2FB0ThingTemplate *m_template;
	unsigned char m_unmodelled_008[0x38 - 0x08];
	Real m_x;
	Real m_y;
	unsigned char m_unmodelled_040[0x88 - 0x40];
	Rva000F2FB0Object *m_next;
	unsigned char m_unmodelled_08c[0x1a4 - 0x8c];
	unsigned char m_disabled;
	unsigned char m_unmodelled_1a5[0x204 - 0x1a5];
	void *m_aiUpdate;
	unsigned char m_unmodelled_208[0x23c - 0x208];
	Rva000F2FB0Team *m_team;
};

class Rva000F2FB0GameLogic
{
public:
	Rva000F2FB0Object *getFirstObject(void);
};

#define TheGameLogic (*(Rva000F2FB0GameLogic **)0x012F0898)

class Rva000F2FB0Team
{
public:
	virtual void teamVtableAnchor(void) = 0;
	Rva000F2FB0Player *getControllingPlayer(void) const
	{
		if (m_proto)
			return m_proto->m_owningPlayer;
		return 0;
	}
	void recruitUnits(const Rva000F2FB0ThingTemplate *,
		Rva000F2FB0ObjectTypes *, Int, Real);
	Coord3D *getEstimateTeamPosition(Coord3D *) const;

	Rva000F2FB0TeamPrototype *m_proto;
};

void Rva000F2FB0Team::recruitUnits(
	const Rva000F2FB0ThingTemplate *thingTemplate,
	Rva000F2FB0ObjectTypes *objectTypes,
	Int count, Real maxDistance)
{
	Int recruited;
	Rva000F2FB0Object *recruit;
	Rva000F2FB0Player *player = getControllingPlayer();

	Real maxDistanceSquared = maxDistance * maxDistance;
	recruited = 0;
	Coord3D teamPosition;
	getEstimateTeamPosition(&teamPosition);

	while (recruited < count)
	{
		recruit = 0;
		Real distanceSquared = maxDistanceSquared;

		for (Rva000F2FB0Object *object = TheGameLogic->getFirstObject();
			object != 0; object = object->m_next)
		{
			Rva000F2FB0Player *objectPlayer = object->getControllingPlayer();
			if (objectPlayer != player)
				continue;

			Bool templateMatch = false;
			if (thingTemplate)
			{
				Rva000F2FB0ThingTemplate *candidate = object->m_template;
				if (candidate && candidate->m_nextOverride)
					candidate = (Rva000F2FB0ThingTemplate *)candidate->m_nextOverride->getFinalOverride();
				if (candidate->isEquivalentTo(thingTemplate))
					templateMatch = true;

				candidate = object->m_template;
				if (candidate && candidate->m_nextOverride)
					candidate = (Rva000F2FB0ThingTemplate *)candidate->m_nextOverride->getFinalOverride();
				if (thingTemplate->isInBuildVariations(candidate))
					templateMatch = true;
			}

			Bool objectTypeMatch = false;
			if (objectTypes)
			{
				Rva000F2FB0ThingTemplate *candidate = object->m_template;
				if (candidate && candidate->m_nextOverride)
					candidate = (Rva000F2FB0ThingTemplate *)candidate->m_nextOverride->getFinalOverride();
				if (objectTypes->isInSet(candidate))
					objectTypeMatch = true;
			}
			if (!objectTypeMatch && !templateMatch)
				continue;

			Rva000F2FB0Team *objectTeam = object->m_team;
			Bool isDefaultTeam = false;
			if (objectTeam == objectPlayer->m_defaultTeam)
				isDefaultTeam = true;
			if (!(*(Bool *)((char *)objectTeam + 0x31)))
				continue;
			if (objectTeam == this)
				continue;

			Rva000F2FB0TeamPrototype *objectPrototype = objectTeam->m_proto;
			Rva000F2FB0TeamPrototype *myPrototype = m_proto;
			if (objectPrototype->m_productionPriority >= myPrototype->m_productionPriority)
				continue;

			if (!objectPrototype->m_isAIRecruitable && !isDefaultTeam)
			{
				if (!(*(Bool *)((char *)objectTeam + 0xe4)))
					continue;
			}
			if (*(Bool *)((char *)objectTeam + 0xe4)
				&& !(*(Bool *)((char *)objectTeam + 0xe5)))
				continue;

			if (object->m_aiUpdate
				&& !(*(Bool *)((char *)object->m_aiUpdate + 0x32c)))
				continue;
			if ((object->m_disabled & 8) != 0)
				continue;

			Real dx = teamPosition.x - object->m_x;
			Real dy = teamPosition.y - object->m_y;
			Real candidateDistance = dx * dx + dy * dy;
			if (candidateDistance <= distanceSquared)
			{
				distanceSquared = candidateDistance;
				recruit = object;
			}
		}

		if (!recruit)
			return;
		recruit->setTeam(this);
		++recruited;
	}
}
