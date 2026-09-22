// cl: /DNDEBUG /MD /EHsc
// BFME AIUpdateInterface::chooseLocomotorSet, retail 0x00272ED0, 123 bytes.
//
// Identity: canonical AIUpdate.cpp / Zero-Hour twin chooseLocomotorSet, called
// through AIUpdateInterface vtable slot 127 (+0x1FC). It calls
// chooseLocomotorSetExplicit (0x00272C10 via ILT 0x00001127) and
// chooseGoodLocomotorFromCurrentSet (0x00270D40 via ILT 0x00036A3E).
//
// BFME additions over the ZH body: a byte at +0x337 that vetoes the switch,
// and a float at +0x1D4 refreshed from the object's template, keyed by the new
// m_curLocomotorSet (0x001418F0 via ILT 0x0002D763).
//
// Load-bearing: the template is read through the native OVERRIDE<T> wrapper
// embedded at Object+4. Calling its inline operator on the +4 subobject is what
// gives retail's separate `add eax,4` / `mov eax,[eax]`, and the inline
// Overridable::getFinalOverride unrolls one link before calling the out-of-line
// copy (0x00087A80 via ILT 0x000022BB), exactly as retail does.

typedef bool Bool;
typedef float Real;

enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
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

// The object's template; 0x001418F0 looks the float up in its map at +0x340.
class Gen_001418F0 : public Overridable
{
public:
	Real bfmeFindFloat(const void *key);
};

class BFMEChooseLocomotorObject
{
public:
	virtual ~BFMEChooseLocomotorObject();

	const Gen_001418F0 *getTemplate() const { return m_template; }

	OVERRIDE<Gen_001418F0> m_template;
};

class AIUpdateInterface
{
public:
	virtual Bool chooseLocomotorSet(LocomotorSetType wst);

protected:
	void chooseGoodLocomotorFromCurrentSet();

private:
	// this should only be called by load/save, or by chooseLocomotorSet.
	Bool chooseLocomotorSetExplicit(LocomotorSetType wst);

	char m_unreconstructed_004[4];
	BFMEChooseLocomotorObject *m_object;
	unsigned char m_unreconstructed_00C[0x1D0 - 0x0C];
	LocomotorSetType m_curLocomotorSet;
	Real m_unreconstructed_1D4;
	unsigned char m_unreconstructed_1D8[0x327 - 0x1D8];
	Bool m_upgradedLocomotors;
	unsigned char m_unreconstructed_328[0x337 - 0x328];
	Bool m_unreconstructed_337;
};

// ?chooseLocomotorSet@AIUpdateInterface@@UAE_NW4LocomotorSetType@@@Z
Bool AIUpdateInterface::chooseLocomotorSet(LocomotorSetType wst)
{
	if (wst == LOCOMOTORSET_NORMAL && m_upgradedLocomotors)
		wst = LOCOMOTORSET_NORMAL_UPGRADED;

	if (wst == m_curLocomotorSet)
		return true;

	if (!m_unreconstructed_337 && chooseLocomotorSetExplicit(wst))
	{
		chooseGoodLocomotorFromCurrentSet();
		m_unreconstructed_1D4 = const_cast<Gen_001418F0 *>(m_object->getTemplate())->bfmeFindFloat(
			(const void *)m_curLocomotorSet);
		return true;
	}

	return false;
}
