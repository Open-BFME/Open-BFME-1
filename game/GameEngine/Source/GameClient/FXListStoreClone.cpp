// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include
// Retail RVA 0x0042CDF0, 351 bytes: FXListStore clone of a named FXList into a
// ref-counted 44-byte copy returned through an owning handle. Ported from the
// BFME 2 donor Code/GameEngine/Source/GameClient/FXListStoreClone.cpp
// (open-bfme-2 b5a7b8290); BFME 1 inlines the list push_back and the copy's
// constructor. The matched caller FXEventParser007764E0.cpp (0x007766D7, ILT
// 0x000234B6) names this body and its handle type; the 0x2C allocation, the
// FXList constructor at 0x0042B4D0, the secondary vtable 0x00CEAD58 with its
// count at +28 and the final vtables 0x00CF3558/0x00CF3554 are read from the
// retail body.
#include "string_base.h"
#include "ascii_string.h"
#include <list>

class FXNugget;

class FXList
{
public:
	FXList(const AsciiString &name);
	virtual ~FXList();
	_STL::list<FXNugget *> m_nuggets;
	char m_rest08[0x24 - 0x08];
};

class Inner010EAD58
{
public:
	Inner010EAD58() : count(0) {}
	virtual ~Inner010EAD58();
	int count;
};

extern "C" unsigned char bfmeVftASAb[];
extern "C" unsigned char bfmeVftASAc[];

class __declspec(novtable) FxCopy0042CDF0 : public FXList, public Inner010EAD58
{
public:
	FxCopy0042CDF0(const AsciiString &name) : FXList(name)
	{
		*(void **)static_cast<FXList *>(this) = bfmeVftASAb;
		*(void **)static_cast<Inner010EAD58 *>(this) = bfmeVftASAc;
	}
};

class FxHandle0042CDF0
{
public:
	FxHandle0042CDF0() : pointer(0) {}
	FxHandle0042CDF0(FxCopy0042CDF0 *p) : pointer(p) { if (pointer) ++pointer->count; }
	FxHandle0042CDF0(const FxHandle0042CDF0 &v) : pointer(v.pointer) { if (pointer) ++pointer->count; }
	~FxHandle0042CDF0()
	{
		if (pointer)
		{
			Inner010EAD58 *ref = pointer;
			if (--ref->count <= 0)
				delete ref;
		}
	}
	FxCopy0042CDF0 *pointer;
};

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

class FxClone0042CDF0 : public FXListStore
{
public:
	FxHandle0042CDF0 clone(const char *name);
};

FxHandle0042CDF0 FxClone0042CDF0::clone(const char *name)
{
	const FXList *original = findFXList(name);
	if (!original)
		return FxHandle0042CDF0();
	FxHandle0042CDF0 result(new FxCopy0042CDF0(AsciiString(name)));
	for (_STL::list<FXNugget *>::const_iterator it = original->m_nuggets.begin(); it != original->m_nuggets.end(); ++it)
		result.pointer->m_nuggets.push_back(*it ? *it : 0);
	return result;
}
