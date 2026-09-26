// cl: /DNDEBUG /MD /EHsc
// The runtime label is "GlowMaterial"; the original C++ class spelling is unknown.
// Preserve retail's second referent reload after registry erasure.

typedef int Int;

struct Gen_t_0040abb0_p12cd
{
	char m_bfmeBody[12];
};

namespace _STL
{

template <class _T1, class _T2> struct pair
{
	_T1 first;
	_T2 second;
};

template <class _Pair> struct _Select1st
{
};

template <class _Tp> struct less
{
};

template <class _Tp> class allocator
{
};

template <class _Key, class _Value, class _KeyOfValue, class _Compare,
		class _Alloc> class _Rb_tree
{
public:
	unsigned int erase(const _Key &key);

private:
	char m_bfmeBody[0x18];
};

}

typedef _STL::_Rb_tree<Int, _STL::pair<const Int, Gen_t_0040abb0_p12cd>,
		_STL::_Select1st<_STL::pair<const Int, Gen_t_0040abb0_p12cd> >,
		_STL::less<Int>,
		_STL::allocator<_STL::pair<const Int, Gen_t_0040abb0_p12cd> > >
	ReferenceStateTree;

extern ReferenceStateTree g_rva012F10DCTree;			// 0x012F10DC

class ReferenceStateReferent
{
public:
	virtual void destroy(void);				// slot 0

	Int m_referenceCount;					// +0x04
	char m_bfmeBody[0x38 - 0x08];
	Int m_key;						// +0x38
};

// PE exports identify the Snapshot base; only its used lifetime interface is declared here.
class Snapshot
{
public:
    virtual ~Snapshot() {}
};

class Rva0040AD80ReferenceState : public Snapshot
{
public:
	virtual ~Rva0040AD80ReferenceState();
	__declspec(noinline) void releaseReferences(void);

private:
	ReferenceStateReferent *m_firstReferent;				// +0x04
	ReferenceStateReferent *m_secondReferent;				// +0x08
};

// ?releaseReferences@Rva0040AD80ReferenceState@@QAEXXZ
void Rva0040AD80ReferenceState::releaseReferences(void)
{
	ReferenceStateReferent *second = m_secondReferent;

	if (second)
	{
		if (second->m_referenceCount == 1)
		{
			Int key = second->m_key;

			g_rva012F10DCTree.erase(key);
		}

		ReferenceStateReferent *again = m_secondReferent;

		if (again)
		{
			if (--again->m_referenceCount == 0)
				again->destroy();

			m_secondReferent = 0;
		}
	}

	ReferenceStateReferent *first = m_firstReferent;

	if (first)
	{
		if (--first->m_referenceCount == 0)
			first->destroy();

		m_firstReferent = 0;
	}
}

Rva0040AD80ReferenceState::~Rva0040AD80ReferenceState()
{
    releaseReferences();
}
