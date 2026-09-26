// cl: /DNDEBUG /MD /EHsc
// BFME AIUpdateInterface::chooseLocomotorSetExplicit, retail 0x00272C10, 144 bytes.
//
// Identity: canonical AIUpdate.cpp / Zero-Hour twin chooseLocomotorSetExplicit
// (private in ZH AIUpdate.h). Callers: chooseLocomotorSet (0x00272ED0, vtable
// slot 127) and the AIUpdateInterface constructor (0x0027F4B0), both through
// ILT 0x00001127. Callees: the override walk (0x00087A80 via ILT 0x000022BB),
// the template's locomotor-set map lookup (0x00141940 via ILT 0x00032614),
// LocomotorSet::clear (ILT 0x00023ECA) and LocomotorSet::addLocomotor
// (0x001BAD80 via ILT 0x0002C700).
//
// BFME moved the locomotor-set map from AIUpdateModuleData to the object's
// template (map at template+0x34C). The template is read through the native
// OVERRIDE<T> wrapper embedded at Object+4: calling its inline operator on the
// +4 subobject gives retail's separate `add eax,4` / `mov eax,[eax]`, and the
// inline Overridable::getFinalOverride unrolls one link before calling the
// out-of-line copy, exactly as retail does.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0
};

class LocomotorTemplate;

// upstream: typedef std::vector<const LocomotorTemplate*> LocomotorTemplateVector
class LocomotorTemplateVector
{
public:
	UnsignedInt size() const { return (UnsignedInt)(m_finish - m_start); }
	const LocomotorTemplate *operator[](UnsignedInt n) const { return *(m_start + n); }

private:
	const LocomotorTemplate **m_start;
	const LocomotorTemplate **m_finish;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T> class OVERRIDE
{
public:
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}

	operator const T *() const { return operator*(); }

private:
	const T *m_overridable;
};

// 0x00141940 as the ledger names it: a map lookup at +0x34C returning a
// pointer to the found value, or 0.
class Gen_00141940
{
public:
	float *bfmeFindFloat(const void *key);
};

class BfmeThingTemplate : public Overridable
{
public:
	const LocomotorTemplateVector *findLocomotorTemplateVector(LocomotorSetType type) const
	{
		return (const LocomotorTemplateVector *)((Gen_00141940 *)this)->bfmeFindFloat((const void *)type);
	}
};

class BfmeObject
{
public:
	virtual ~BfmeObject();

	const BfmeThingTemplate *getTemplate() const { return m_template; }

	OVERRIDE<BfmeThingTemplate> m_template;
};

class LocomotorSet
{
public:
	void clear();
	void addLocomotor(const LocomotorTemplate *lt);

	char m_fields[0x24];
};

class AIUpdateInterface
{
private:
	// this should only be called by load/save, or by chooseLocomotorSet.
	Bool chooseLocomotorSetExplicit(LocomotorSetType wst);
	BfmeObject *getObject() const { return m_object; }

	char m_fields[8];
	BfmeObject *m_object;
	char m_fieldsBeforeLocomotorSet[0x1a8 - 0x0c];
	LocomotorSet m_locomotorSet;
	void *m_curLocomotor;
	LocomotorSetType m_curLocomotorSet;
};

// ?chooseLocomotorSetExplicit@AIUpdateInterface@@AAE_NW4LocomotorSetType@@@Z
Bool AIUpdateInterface::chooseLocomotorSetExplicit(LocomotorSetType wst)
{
	const LocomotorTemplateVector *set = getObject()->getTemplate()->findLocomotorTemplateVector(wst);
	if (set)
	{
		m_locomotorSet.clear();
		m_curLocomotor = 0;
		for (Int i = 0; i < set->size(); ++i)
		{
			const LocomotorTemplate *lt = (*set)[i];
			if (lt)
				m_locomotorSet.addLocomotor(lt);
		}
		m_curLocomotorSet = wst;
		return true;
	}
	return false;
}
