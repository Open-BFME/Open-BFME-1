// cl: /DNDEBUG /MD /EHsc
// Retail 0x002871F0.  The concrete update owner is not proven, so the local
// owner name retains the RVA.  The relation/filter callees are named from
// their existing retail pins.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

struct RvaC4390Interface
{
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual Int slot07() = 0;
};

struct RvaC4390First
{
public:
	RvaC4390Interface *getInterface();

	unsigned char m_pad00[0x74];
	UnsignedInt m_value74;
};

class RvaC4390Second
{
public:
	RvaC4390First *resolve(Int mode);
};

class Player
{
};

class Object
{
public:
	Player *getControllingPlayer() const;

	unsigned char m_pad00[0x74];
	UnsignedInt m_id;
};

class BfmeRvaA760Object
{
};

class BfmeRvaA760ProbeInterface
{
public:
	Bool accepts(BfmeRvaA760Object *object, Int player);
};

class Rva002871F0Self
{
public:
	Bool Rva002871F0(RvaC4390Second *input);

	unsigned char m_pad00[4];
	UnsignedInt m_value04;
};

Bool Rva002871F0Self::Rva002871F0(RvaC4390Second *input)
{
	Rva002871F0Self *self = this;
	RvaC4390First *resolved = input->resolve(0);
	BfmeRvaA760Object *filterOwner =
		*(BfmeRvaA760Object **)((char *)self - 0x1c);

	if (resolved == 0)
		return false;

	RvaC4390Interface *interfaceValue = resolved->getInterface();
	if (interfaceValue == 0)
		return false;

	Object *owner = *(Object **)((char *)self - 0x18);
	BfmeRvaA760ProbeInterface *probe =
		(BfmeRvaA760ProbeInterface *)((char *)filterOwner + 8);
	if (probe->accepts(
			(BfmeRvaA760Object *)resolved,
			(Int)owner->getControllingPlayer()))
	{
		UnsignedInt ownerValue = owner->m_id;
		if (interfaceValue->slot07() == (Int)ownerValue)
		{
			Bool equal = self->m_value04 == resolved->m_value74;
			return equal;
		}
	}

	return false;
}
