// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: _STL::__copy<const ModuleInfo::Nugget *, ModuleInfo::Nugget *, int>,
// retail 0x00761B70, 159 bytes. The name sat on the 5-byte incremental-link
// thunk; the body it jumps to carried only a machine byte-dump row.
//
// The element is the twenty bytes its _M_allocate_and_copy sibling measures
// (the divide is by 20), and the inlined assignment walks it in five steps:
// three plain dwords at +0, +4 and +8, StringBase<char>::set on the
// AsciiString at +0x0C, and a reference-counted handle at +0x10.
//
// That handle is what the second half of the loop is. Its assignment guards
// against self-assignment, addrefs the source, then releases the old target:
// the pointee carries a reference-count base at +0x24, so the count lives at
// +0x28 and the release calls virtual slot 0 with 1 when it falls to zero --
// which is the lea ecx, [eax + 0x24] and the call dword ptr [edx] retail has.
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

template <class T>
class StringBase
{
public:
	StringBase &operator=(const StringBase &other) { set(other); return *this; }

	void set(const StringBase &other);			// retail 0x00887C90

private:
	T *m_data;
};

class BfmeRefCountObject
{
public:
	virtual void bfmeDeleteThis(int freeIt);		// vtable slot 0

	void bfmeAddRef(void) { ++m_bfmeNumRefs; }
	void bfmeReleaseRef(void)
	{
		--m_bfmeNumRefs;
		if (m_bfmeNumRefs <= 0)
			bfmeDeleteThis(1);
	}

	int m_bfmeNumRefs;
};

// The reference-count subobject is a member at +0x24 rather than a base: MSVC
// orders a polymorphic base ahead of a plain one, which would put the vtable
// pointer at +0 and cost the lea retail spends reaching +0x24.
class BfmeNuggetTarget
{
public:
	char m_bfmeHead[0x24];
	BfmeRefCountObject m_bfmeRc;				// +0x24
};

class BfmeNuggetRef
{
public:
	BfmeNuggetRef &operator=(const BfmeNuggetRef &other)
	{
		if (this != &other)
		{
			if (other.m_bfmePtr)
				other.m_bfmePtr->m_bfmeRc.bfmeAddRef();
			if (m_bfmePtr)
				m_bfmePtr->m_bfmeRc.bfmeReleaseRef();
			m_bfmePtr = other.m_bfmePtr;
		}
		return *this;
	}

	BfmeNuggetTarget *m_bfmePtr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ModuleInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
	struct Nugget
	{
		int m_bfmeA;					// +0x00
		int m_bfmeB;					// +0x04
		int m_bfmeC;					// +0x08
		StringBase<char> m_bfmeName;			// +0x0C
		BfmeNuggetRef m_bfmeRef;			// +0x10
	};
};

typedef ModuleInfo::Nugget *(*BfmeNuggetCopyFn)(
	const ModuleInfo::Nugget *, const ModuleInfo::Nugget *,
	ModuleInfo::Nugget *, const _STL::random_access_iterator_tag &, int *);

BfmeNuggetCopyFn BfmeModuleInfoNuggetConstCopyAnchor =
	&_STL::__copy<const ModuleInfo::Nugget *, ModuleInfo::Nugget *, int>;
