// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ActiveBody::shouldRetaliate(Object *), retail 0x002102E0, 154B.
//
// The identity is anchored by the vendored GeneralsMD ActiveBody.cpp body:
// its two KINDOF early-outs, AI-idle test, stealth/detected test, and
// IS_USING_ABILITY tail occur in this exact order.  BFME's Thing/Object
// layout is represented locally because the retail object puts the template,
// status words, and AI pointer at offsets different from the ZH headers.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad_008[0xC8 - 0x08];
	unsigned char m_flagsC8;
	unsigned char m_pad_C9[0xDC - 0xC9];
	UnsignedInt m_flagsDC;
};

extern void j_0000572c(void);

class BfmeStatusBits
{
public:
	__forceinline Bool test(UnsignedInt bit) const
	{
		typedef Bool (BfmeStatusBits::*TestThunk)(UnsignedInt) const;
		union
		{
			void (*function)(void);
			TestThunk member;
		} thunk;
		thunk.function = j_0000572c;
		return (this->*thunk.member)(bit);
	}

	UnsignedInt m_word0;
};

// The local view calls the existing retail ILT 0x0000572C with its proven
// const-thiscall bit-test ABI. Its 37-byte target remains a generated claim;
// this adapter introduces no alternate global identity or pin.

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;

	unsigned char m_pad_004[0x34 - 0x04];
	void *m_field34;
};

class Object
{
public:
	const BfmeStatusBits &getStatusBits() const
	{
		return m_status;
	}

	Bool testStatus(Int status) const;

	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad_008[0x90 - 0x08];
	BfmeStatusBits m_status;
	unsigned char m_pad_094[0x204 - 0x94];
	AIUpdateInterface *m_ai;
};

class ActiveBody
{
protected:
	static Bool shouldRetaliate(Object *obj);
};

// ?shouldRetaliate@ActiveBody@@KA_NPAVObject@@@Z
Bool ActiveBody::shouldRetaliate(Object *obj)
{
	// These are the BFME inline form of Thing::isKindOf used by this body.
	// Keep the raw flag tests in the caller so MSVC preserves the retail
	// test-ch/branch shape instead of normalising a helper's Bool return.
	ThingTemplate *tmpl = obj->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if ((tmpl->m_flagsDC & 0x800) != 0)
		return false;

	tmpl = obj->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if ((tmpl->m_flagsC8 & 4) != 0)
		return false;

	AIUpdateInterface *ai = obj->m_ai;
	if (ai != 0 && *(void **)((char *)ai + 0x34) != 0)
		return false;
	AIUpdateInterface *aiForIdle = obj->m_ai;
	if (aiForIdle == 0 || !aiForIdle->isIdle())
		return false;

	if (obj->getStatusBits().test(15) &&
		!obj->getStatusBits().test(17))
		return false;
	if (obj->testStatus(24))
		return false;
	return true;
}
