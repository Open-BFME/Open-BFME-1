// cl: /DNDEBUG /MD /EHsc
// readable body of ?makeAssistanceRequest@@: game/GameEngine/Source/GameLogic/Object/Weapon.cpp
// makeAssistanceRequest at 0x001E4AA0 (267 B): Zero Hour's Weapon.cpp
// PartitionManager callback. Retail's only pointer reference to this body is
// the push at 0x001E4C29 inside the matched Weapon::processRequestAssistance
// (0x001E4BF0), which builds the AssistanceRequestData read here. The string
// "AssistedTargetingUpdate" and the matched isFreeToAssist callee agree.
//
// BFME differences from the ZH source, as in the matched SpawnBehavior
// findClosestOrphan callback: the iterator callback returns int (1 keeps the
// walk going), Object::getTemplate inlines the first override-chain step, and
// the 2D center distance is computed inline. The Weapon.cpp TU builds against
// the ZH headers, which have neither, so this body lives in its own TU.

typedef float Real;
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride != 0)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *m_vtable;
	const Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Module;
class UpdateModule;

class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		if (m_template == 0)
			return 0;
		return static_cast<const ThingTemplate *>(m_template->getFinalOverride());
	}
	const Coord3D *getPosition() const
	{
		return &m_position;
	}
	UpdateModule *findUpdateModule(NameKeyType key) const
	{
		return (UpdateModule *)findModule(key);
	}
protected:
	Module *findModule(NameKeyType key) const;
private:
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_unreconstructed08[0x30];
	Coord3D m_position;
};

class AssistedTargetingUpdate
{
public:
	bool isFreeToAssist() const;
};

// Ledger placeholder for AssistedTargetingUpdate::assistAttack (0x0027FED0).
class Gen_0027FED0
{
public:
	void bfmeRun(void *requestingObject, Object *victimObject);
};

struct AssistanceRequestData
{
	Object *m_requestingObject;
	Object *m_victimObject;
	Real m_requestDistanceSquared;
};

// ?makeAssistanceRequest@@YAHPAVObject@@PAX@Z
int makeAssistanceRequest( Object *requestOf, void *userData )
{
	AssistanceRequestData *requestData = (AssistanceRequestData *)userData;

	// Don't ask ourselves (can't believe I forgot this one)
	if( requestOf == requestData->m_requestingObject )
		return 1;

	// Only request of our kind of people
	if( !requestOf->getTemplate()->isEquivalentTo( requestData->m_requestingObject->getTemplate() ) )
		return 1;

	// Who are close enough
	const Coord3D *requesterPos = requestData->m_requestingObject->getPosition();
	Real dx = requestOf->getPosition()->x - requesterPos->x;
	Real dy = requestOf->getPosition()->y - requesterPos->y;
	Real distSq = dx * dx + dy * dy;
	if( distSq > requestData->m_requestDistanceSquared )
		return 1;

	// and respond to requests
	static const NameKeyType key_assistUpdate = NAMEKEY("AssistedTargetingUpdate");
	AssistedTargetingUpdate *assistModule = (AssistedTargetingUpdate*)requestOf->findUpdateModule(key_assistUpdate);
	if( assistModule == 0 )
		return 1;

	// and say yes
	if( !assistModule->isFreeToAssist() )
		return 1;

	((Gen_0027FED0 *)assistModule)->bfmeRun( requestData->m_requestingObject, requestData->m_victimObject );
	return 1;
}
