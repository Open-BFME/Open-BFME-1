// Recovered interface dispatch at retail RVA 0x000D4770.
//
// The two leaf calls are real Object behaviour-module getters, not invented
// members. Retail's ILT 0x0000DE9F fronts
// ?getProjectileUpdateInterface@Object@@QBEPAVProjectileUpdateInterface@@XZ
// (matched body at RVA 0x001BF630) and ILT 0x000351D9 fronts
// ?getCountermeasuresBehaviorInterface@Object@@QBEPBVCountermeasuresBehaviorInterface@@XZ
// (matched body at RVA 0x001BF670). Both are const members returning their
// interface pointer, which is why both are declared const here; that is also
// what makes the reference resolve against the matched definitions.

class ProjectileUpdateInterface
{
public:
	virtual void unused0(void);
	virtual void unused1(void);
	virtual void apply(void *value);
};

class CountermeasuresBehaviorInterface
{
public:
	virtual void unused0(void) const;
	virtual void finish(int enabled) const;
	virtual void unused2(void) const;
	virtual void unused3(void) const;
	virtual void unused4(void) const;
	virtual void unused5(void) const;
	virtual void unused6(void) const;
	virtual void unused7(void) const;
	virtual void unused8(void) const;
	virtual void begin(int enabled) const;
};

enum KindOfType;

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object
{
public:
	ProjectileUpdateInterface *getProjectileUpdateInterface(void) const;
	const CountermeasuresBehaviorInterface *getCountermeasuresBehaviorInterface(void) const;

private:
	char m_padding[0x74];

public:
	void *m_id;
};

void __stdcall rva000D4770InterfaceDispatch(Thing *thing, Object *object)
{
	if (thing == 0 || object == 0 || !thing->isKindOf((KindOfType)0x67))
		return;

	const CountermeasuresBehaviorInterface *completion = object->getCountermeasuresBehaviorInterface();
	ProjectileUpdateInterface *production = ((Object *)thing)->getProjectileUpdateInterface();
	if (completion == 0 || production == 0)
		return;

	production->apply(object->m_id);
	completion->begin(1);
	completion->finish(1);
}