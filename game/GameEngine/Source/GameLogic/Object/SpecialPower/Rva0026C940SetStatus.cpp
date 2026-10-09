// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

extern const float g_rva01075350;

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);
};

class BfmeAIUpdateInterface;

class BfmeUpdateObject
{
public:
	BfmeAIUpdateInterface *getAIUpdateInterface();
};

class BfmeAIUpdateInterface
{
public:
	float getFormationMovementSpeed(BfmeUpdateObject *object);
};

class Rva001BE010
{
public:
	int get();
};

class BfmeSub1CC_EC3
{
public:
	float effectiveMaxSpeed(void *objectArgument);
};

class BfmeA1011
{
public:
	void bfmeSend1011(int a, int b, int c, int d, int e);
};

class Rva0026C940Owner : public BfmeA1011
{
public:
	void apply(int a, int b, int c, int d, int e);
};

static BfmeUpdateObject *rva0026C940Object(Rva0026C940Owner *self)
{
	return *(BfmeUpdateObject **)((char *)self - 0x18);
}

// ?apply@Rva0026C940Owner@@QAEXHHHHH@Z
void Rva0026C940Owner::apply(int a, int b, int c, int d, int e)
{
	BfmeAIUpdateInterface *ai = (BfmeAIUpdateInterface *)((Rva001BE010 *)rva0026C940Object(this))->get();
	if (ai != 0)
	{
		if (((BfmeSub1CC_EC3 *)ai)->effectiveMaxSpeed(rva0026C940Object(this)) == g_rva01075350)
			return;
	}
	bfmeSend1011(a, b, c, d, e);
	((Object *)rva0026C940Object(this))->setStatus(MAKE_OBJECT_STATUS_MASK(73), true);
}
