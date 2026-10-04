// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The overflow helper has no EH frame and uses the retail node allocator.
#define _STLP_NO_EXCEPTIONS 1

struct Rva0006AA90Element;

// Retail's copy _Construct for this record is defined in another translation
// unit: every vector helper instantiated below reaches it through its
// incremental-link thunk at 0x0001F285, which is what each rel32 encodes.
extern "C" void __identifier("?j_0001f285@@YAXXZ")();

typedef void (__cdecl *CurveRecordConstruct)(
	Rva0006AA90Element *destination,
	const Rva0006AA90Element &source);

namespace _STL
{
	// Declared before the STLport headers so the dependent calls inside
	// _vector.h and _construct.h bind here rather than to the primary
	// template, which would copy the record inline instead of calling out.
	inline void _Construct(
		Rva0006AA90Element *destination,
		const Rva0006AA90Element &source);
}

#include <vector>

// The 16-byte curve record is a one-word head followed by a trivially copied
// three-word tail.  Retail's 0x000699F0 constructor uses this nested layout;
// declaring four unrelated words changes the register schedule in insert().
struct Rva0006AA90ElementTail
{
	int m_value[3];
};

struct Rva0006AA90Element
{
	float m_time;
	Rva0006AA90ElementTail m_tail;

	Rva0006AA90Element() {}
	Rva0006AA90Element(const Rva0006AA90Element &other)
	{
		m_time = other.m_time;
		m_tail = other.m_tail;
	}
	~Rva0006AA90Element() {}
};

// TU-local forwarder: the thunk keeps its declared YAXXZ signature, so the
// call is typed through a view of the cdecl signature retail encodes.
static __forceinline void curveRecordConstruct(
	Rva0006AA90Element *destination,
	const Rva0006AA90Element &source)
{
	((CurveRecordConstruct)(void *)__identifier("?j_0001f285@@YAXXZ"))(
		destination, source);
}

namespace _STL
{
	inline void _Construct(
		Rva0006AA90Element *destination,
		const Rva0006AA90Element &source)
	{
		curveRecordConstruct(destination, source);
	}
}

template class _STL::vector<Rva0006AA90Element>;
