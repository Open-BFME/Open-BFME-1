// cl: /DNDEBUG /MD /EHsc
//
// Exact constructor 0x00248F90, the sibling of the complete destructor
// 0x00249820 in HordeGarrisonContainDeletingDestructor.cpp. It installs the
// dedicated primary vtable 0x010AFDC0 pinned as ??_7HordeGarrisonContain@@6B@,
// which is the identity evidence for the class name carried over from the
// Open-BFME5 *Thunk.cpp lift.
//
// The retail body is OpenContain's nine polymorphic subobjects (vptrs at +0x00,
// +0x0c, +0x10, +0x20 .. +0x34) followed by the GarrisonContain members the
// base constructor at 0x0021D820 lays down (through +0x9b7). The +0x08 slot is
// the Thing pointer the base keeps, and the +0x118 word of that Thing is the
// model-condition word: the derived constructor sets bit 0x200 in it and, when
// the bit was clear, reapplies the model through
// Object::notifyModelConditionChanged, reached via ILT 0x0002191D.

class Thing;
class ModuleData;

typedef unsigned int UnsignedInt;

// upstream layout: .../GameEngine/Include/GameLogic/Object.h
//
// Only the member the body calls is declared: the notification is a direct
// call on the object this constructor was handed (the garrison's m_thing), and
// its address never depends on a layout, so no Object storage is spelled here.
class Object
{
public:
	void notifyModelConditionChanged(void);
};

// The model-condition record: the 40-byte word array starts at Object +0x110, so
// the word this body reads at +0x118 is word 2. The accessors return the masked
// WORD rather than a bool, which is what keeps VC7.1 materialising the mask in a
// register (mov eax,mask; test eax,edx; or edx,eax) instead of collapsing the
// TEST to a short immediate against the member.
class Rva00248F90ConditionBits
{
public:
	UnsignedInt test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}

	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}

private:
	UnsignedInt m_words[8];
};

// upstream layout: .../GameEngine/Include/GameLogic/Object/BaseType.h
//
// The base this TU used to declare for the notification call is gone: the
// notification belongs to the object the constructor is handed, which is an
// Object, and Object is not spelled with a layout here so it cannot be a base.
class Thing
{
public:
	unsigned char m_beforeConditionWords[ 0x110 ];
	Rva00248F90ConditionBits m_conditionBits;
};

// A free forceinline conditional-update helper, not a member call: see
// Rva0025EF90ChargeApplication.cpp, where spelling the same update as a member
// lost the native mask materialisation.
static __forceinline void rva00248f90SetCondition(Thing *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		reinterpret_cast<Object *>(object)->notifyModelConditionChanged();
	}
}

class OpenContainPrimaryBase
{
public:
	virtual ~OpenContainPrimaryBase() {}

	UnsignedInt m_unmodelled04;
	Thing *m_thing;
};

template <int Number>
class OpenContainSecondaryBase
{
public:
	virtual ~OpenContainSecondaryBase() {}
};

class OpenContainWideSecondaryBase
{
public:
	virtual ~OpenContainWideSecondaryBase() {}

private:
	unsigned char m_pad[12];
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase,
	  public OpenContainSecondaryBase<2>,
	  public OpenContainSecondaryBase<3>,
	  public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>,
	  public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
public:
	OpenContain(Thing *, const ModuleData *);
	virtual ~OpenContain();

protected:
	unsigned char m_pad38[0x9c];
	unsigned int m_unmodelled_d4;
};

// upstream layout: .../GameEngine/Include/GameLogic/Module/GarrisonContain.h
class GarrisonContain : public OpenContain
{
public:
	GarrisonContain(Thing *, const ModuleData *);
	virtual ~GarrisonContain();

private:
	unsigned char m_garrisonMembers[ 0x9b8 - 0xd8 ];
};

class HordeGarrisonContain : public GarrisonContain
{
public:
	HordeGarrisonContain(Thing *, const ModuleData *);

private:
	int m_unmodelled_9b8;
};

// ??0HordeGarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z
HordeGarrisonContain::HordeGarrisonContain(Thing *thing, const ModuleData *moduleData)
	: GarrisonContain(thing, moduleData)
{
	m_unmodelled_9b8 = 0;

	Thing *owner = m_thing;

	// Index 73: word 2 (the +0x118 the body reads) with bit 9 set (0x200).
	if (owner != 0)
		rva00248f90SetCondition(owner, 73);
}
