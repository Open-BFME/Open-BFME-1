// Recovered interface dispatch at retail RVA 0x000D4770.

class BfmeY982
{
public:
	virtual void unused0(void);
	virtual void unused1(void);
	virtual void apply(void *value);
	BfmeY982 *bfmeConv982B(void);
};

class StructureCompletionInterface
{
public:
	virtual void unused0(void);
	virtual void finish(int enabled);
	virtual void unused2(void);
	virtual void unused3(void);
	virtual void unused4(void);
	virtual void unused5(void);
	virtual void unused6(void);
	virtual void unused7(void);
	virtual void unused8(void);
	virtual void begin(int enabled);
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
	StructureCompletionInterface *getStructureCompletionInterface(void);

private:
	char m_padding[0x74];

public:
	void *m_id;
};

void __stdcall rva000D4770InterfaceDispatch(Thing *thing, Object *object)
{
	if (thing == 0 || object == 0 || !thing->isKindOf((KindOfType)0x67))
		return;

	StructureCompletionInterface *completion = object->getStructureCompletionInterface();
	BfmeY982 *production = ((BfmeY982 *)thing)->bfmeConv982B();
	if (completion == 0 || production == 0)
		return;

	production->apply(object->m_id);
	completion->begin(1);
	completion->finish(1);
}
