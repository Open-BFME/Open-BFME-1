enum DamageType
{
	BFME_DAMAGE_TYPE_8 = 8
};

enum DeathType
{
	BFME_DEATH_TYPE_0 = 0
};

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);

	char m_bfmeFields[0x38];
	char m_bfmePosition[0x58];
	unsigned int m_bfmeFlags;
};

struct BfmeKillContext
{
	char m_bfmeFields[8];
	void *m_bfmeOwner;
};

class ObjectCreationListStore
{
public:
	void bfmeCreate(void *owner, Object *object, void *position);
};

extern ObjectCreationListStore *TheObjectCreationListStore;

class Gen_0028CA70
{
public:
	void bfmeKill(void);

private:
	char m_bfmeFields[4];
	BfmeKillContext *m_bfmeContext;
	Object *m_bfmeObject;
	char m_bfme0C[0x18];
	bool m_bfmeFinished;
};

// ?bfmeKill@Gen_0028CA70@@QAEXXZ
void Gen_0028CA70::bfmeKill(void)
{
	Object *object = m_bfmeObject;

	if ((object->m_bfmeFlags & 4) == 0 &&
		(object->m_bfmeFlags & 0x00080000) == 0)
	{
		TheObjectCreationListStore->bfmeCreate(
			m_bfmeContext->m_bfmeOwner, object, object->m_bfmePosition);
	}

	object->kill(BFME_DAMAGE_TYPE_8, BFME_DEATH_TYPE_0);
	m_bfmeFinished = true;
}
