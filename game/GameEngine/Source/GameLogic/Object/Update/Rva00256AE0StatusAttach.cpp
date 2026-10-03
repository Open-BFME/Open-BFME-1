// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// RVA00256AE0,108B: bank names retained under an address-qualified owner.
// BitFlags<86>(kInit,29) follows the matched neighboring status helpers
// 00256970/002569B0/002569F0 and Object::setStatus at001C7370.
// The old three-word command model hid native bitset initialization.
// ILT0000A3B2 reaches001BF4D0: that helper reads incoming receiver+1E8,
// so bfmeForward is a member call on thing, not a free stdcall function.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

// The lookup below is GameLogic::findObjectByID; GameLogicObjectLookup.h holds
// the declaration (its body stays in Thing/GameLogicFindObjectByID.cpp). It
// forward-declares Object, so it adds no second definition of this TU's class.
#include "../../../Common/Thing/GameLogicObjectLookup.h"

typedef int Int;
typedef bool Bool;

template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int index)
	{
		m_bits.set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set);
};

class BfmeObjESN;

class BfmeThingESN
{
public:
	// Retail leaves the incoming thing in ECX for the 0x0000A3B2 member thunk;
	// that thunk's body reads [this+0x1e8] before forwarding the stack arg.
	void bfmeForward(Object *object);

	unsigned char m_bfmeHeadESN[0x74];
	int m_bfme74ESN;
};

// Retail's GameLogic singleton at 0x012F0898; the one canonical spelling.
extern GameLogic *TheGameLogic;

// The two callees this body reaches are not members of the modelling classes
// above; retail's own code at those addresses is defined under other names, so
// the calls below have to carry those names for the link to resolve.
//
// ILT 0x0000A3B2 reaches 0x001BF4D0 (callees.py: 0xa3b2 -> 0x1bf4d0), whose
// matched owner is game/GameEngine/Source/Common/S3GuardedDelegates2.cpp as
// ?bfmeForward@Gen_001BF4D0@@QAEXPAX@Z. Declared, not defined, here: the call
// is still a plain ECX-this member call with the object on the stack.
class Gen_001BF4D0
{
public:
	void bfmeForward(void *a);
};

// ILT 0x0003DE5B reaches 0x002569F0 (callees.py: 0x3de5b -> 0x2569f0), whose
// matched owner is game/GameEngine/Source/GameLogic/Object/Update/
// Gen002569F0SetStatus.cpp as ?apply@Gen002569F0@@QAEXPAVGen_001BF4F0@@@Z.
class Gen_001BF4F0;

class Gen002569F0
{
public:
	void apply(Gen_001BF4F0 *obj);
};

namespace Rva00256AE0 {
class BfmeHostESN
{
public:
	void bfmeStepESN(BfmeThingESN *thing);
	void bfmeAttachESN(BfmeObjESN *obj);

	unsigned char m_bfmeHeadESN[8];
	Object *m_bfme08ESN;
	unsigned char m_bfmeMidESN[0x14];
	int m_bfme20ESN;
};

void BfmeHostESN::bfmeStepESN(BfmeThingESN *thing)
{
	int id = m_bfme20ESN;

	if (id != 0)
	{
		BfmeObjESN *obj = reinterpret_cast<BfmeObjESN *>(
			TheGameLogic->findObjectByID(id));

		if (obj == 0)
			m_bfme20ESN = 0;
		else
			reinterpret_cast<Gen002569F0 *>(this)->apply(
				reinterpret_cast<Gen_001BF4F0 *>(obj));
	}

	if (thing != 0)
	{
		m_bfme20ESN = thing->m_bfme74ESN;

		reinterpret_cast<Gen_001BF4D0 *>(thing)->bfmeForward(m_bfme08ESN);

		m_bfme08ESN->setStatus(
			ObjectStatusMaskType(ObjectStatusMaskType::kInit, 29), true);
	}
}

} // namespace Rva00256AE0
