// cl: /DNDEBUG /MD /EHsc
// readable body of ?makeEmpty@SimpleObjectIterator@@QAEXXZ: Code/GameEngine/Source/GameLogic/Object/SimpleObjectIterator.cpp

// Open-BFME5: SimpleObjectIterator::makeEmpty, retail 0x0040AD80, 88 bytes,
// from the thunk queue -- the name sat on a five-byte thunk and this is the
// body it jumps to.
//
// Two reference-counted nodes are let go, the one at +0x08 first and then the
// one at +0x04. Before the first is released, and only when its count still
// stands at one, the key it carries at +0x38 is erased from the global tree at
// 0x012F10DC; the key goes through a local because the tree takes it by
// reference.
//
// The node at +0x08 is re-read after that erase, which is what the second null
// test is for: the erase could have dropped it.

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
	BfmeIteratorTree;

extern BfmeIteratorTree TheBfmeIteratorTree;			// 0x012F10DC

class BfmeIterNode
{
public:
	virtual void bfmeDestroy(void);				// slot 0

	Int m_bfmeRefCount;					// +0x04
	char m_bfmeBody[0x38 - 0x08];
	Int m_bfmeKey;						// +0x38
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectIter.h
class SimpleObjectIterator
{
public:
	void makeEmpty(void);

private:
	char m_bfmeHead[0x04];
	BfmeIterNode *m_bfmeFirst;				// +0x04
	BfmeIterNode *m_bfmeSecond;				// +0x08
};

// ?makeEmpty@SimpleObjectIterator@@QAEXXZ
void SimpleObjectIterator::makeEmpty(void)
{
	BfmeIterNode *second = m_bfmeSecond;

	if (second)
	{
		if (second->m_bfmeRefCount == 1)
		{
			Int key = second->m_bfmeKey;

			TheBfmeIteratorTree.erase(key);
		}

		BfmeIterNode *again = m_bfmeSecond;

		if (again)
		{
			if (--again->m_bfmeRefCount == 0)
				again->bfmeDestroy();

			m_bfmeSecond = 0;
		}
	}

	BfmeIterNode *first = m_bfmeFirst;

	if (first)
	{
		if (--first->m_bfmeRefCount == 0)
			first->bfmeDestroy();

		m_bfmeFirst = 0;
	}
}
