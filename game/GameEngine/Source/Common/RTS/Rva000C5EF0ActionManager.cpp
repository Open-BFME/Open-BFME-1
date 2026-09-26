// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x000C5EF0 (119 bytes) is an internal ActionManager helper
// reached by the GiveUpgrade case in the named
// ActionManager::canDoSpecialPowerAtObject body at 0x000C5FF0.  No original
// public spelling for this helper is established, so the method name below is
// deliberately address-derived.  The caller supplies the ActionManager this
// pointer, three stack arguments, and expects a bool; the body uses the first
// two object arguments and leaves the third opaque argument untouched.
//
// The control flow establishes the helper's role: allied relationship, target
// AI presence, rejection of kind 2, lookup of the literal
// SpecialAbilityGiveUpgrade, lookup of update type 0x34, and the named
// SpecialAbilityUpdate::checkTarget body.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum Relationship
{
	ALLIES = 2
};

enum KindOfType
{
	KINDOF_TARGET = 2
};

enum SpecialPowerType
{
	SPECIAL_GIVE_UPGRADE = 0x34
};

class SpecialPowerTemplate;
class ThingTemplate;
class Object;

// The matched Thing body and the named Object callers establish the first
// Thing subobject: a vptr at +0 and the template pointer at +4.
class Thing
{
private:
	virtual ~Thing();
	const ThingTemplate *m_template;

public:
	Bool isKindOf(KindOfType kind) const;
};

class SpecialAbilityUpdate;

// Object inherits the real Thing ABI.  Its AI module is independently named
// at Object+0x204; the pad begins after Thing's eight-byte prefix.
class Object : public Thing
{
public:
	Relationship getRelationship(const Object *other) const;
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType type) const;

private:
	unsigned char m_objectFields[0x1FC];

public:
	void *m_ai;
};

// Retail's one-word string constructor is the BFME StringBase<char>
// const-char constructor at 0x00888BC0.  StringBase owns the four-byte
// Header* representation; the header layout is the proven ref-counted
// character buffer, not an unrelated empty overlay.  The AsciiString wrapper
// privately inherits that base so MSVC constructs the by-value argument in
// the outgoing stack slot, as the target does.
template <typename T> class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	StringBase(const T *text);
	void releaseBuffer(void);
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString(void)
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}
};

class SubsystemInterface
{
protected:
	void *m_vtable;
};

class SpecialPowerStore : public SubsystemInterface
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(
		AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

// The real SpecialAbilityUpdate derives from the special-power update module;
// this ABI view retains its primary base slot while declaring the named
// target-check member used by the GiveUpgrade caller.
class SpecialPowerUpdateModule
{
protected:
	void *m_vtable;
};

class SpecialAbilityUpdate : public SpecialPowerUpdateModule
{
public:
	Bool checkTarget(Object *target);
};

class ActionManager
{
public:
	Bool queryRva000C5EF0(Object *object, Object *target, int source);
};

// ?queryRva000C5EF0@ActionManager@@QAE_NPAVObject@@0H@Z
Bool ActionManager::queryRva000C5EF0(Object *object, Object *target, int)
{
	const SpecialPowerTemplate *power;
	SpecialAbilityUpdate *update;

	if (object == 0)
		goto fail;
	if (target == 0)
		goto fail;
	if (object->getRelationship(target) != ALLIES)
		goto fail;
	if (target->m_ai == 0)
		goto fail;
	if (target->isKindOf(KINDOF_TARGET))
		goto fail;

	power =
		TheSpecialPowerStore->findSpecialPowerTemplate(
			(const char *)0x01083C00);
	if (power == 0)
		goto fail;

	update = object->findSpecialAbilityUpdate(SPECIAL_GIVE_UPGRADE);
	if (update != 0)
		return update->checkTarget(target);

fail:
	return false;
}
