// A clear that tells each element twice before dropping it, then empties the
// list that follows the vector.
//
// The list clear reloads its node pointer for every one of the three stores it
// makes through it: storing through the node could reach the pointer itself,
// so MSVC cannot keep it in a register.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class GameWindow
{
public:
    int winSetSize(int, int);
    int winSetPosition(int, int);
};
class BfmeElemW {};
struct Gen_t_004b07d0_k4;
struct Gen_t_004b07d0_p4pod;
class BfmeListW;
namespace _STL
{
template <class First, class Second> struct pair;
template <class Value> struct _Select1st;
template <class Key> struct less;
template <class Value> class allocator;
template <class Value> struct _Rb_tree_node;
template <class Key, class Value, class Extract, class Compare, class Alloc>
class _Rb_tree
{
    friend class ::BfmeListW;
    void _M_erase(_Rb_tree_node<Value> *);
};
}

inline BfmeElemW **bfmeCopyElems(BfmeElemW **destination, BfmeElemW **first, BfmeElemW **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeElemW **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecW
{
public:
	void bfmeErase(BfmeElemW **first, BfmeElemW **last)
	{
		m_bfmeFinish = bfmeCopyElems(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeElemW **m_bfmeStart;				// +0x00
	BfmeElemW **m_bfmeFinish;				// +0x04
	BfmeElemW **m_bfmeEnd;					// +0x08
};

class BfmeNodeW
{
public:
	int m_bfmeTag;						// +0x00
	BfmeNodeW *m_bfmeHead;					// +0x04
	BfmeNodeW *m_bfmeNext;					// +0x08
	BfmeNodeW *m_bfmePrev;					// +0x0C
};

class BfmeListW
{
public:
	void bfmeClear(void)
	{
		if (m_bfmeCount)
		{
			reinterpret_cast<_STL::_Rb_tree<Gen_t_004b07d0_k4,
                _STL::pair<const Gen_t_004b07d0_k4, Gen_t_004b07d0_p4pod>,
                _STL::_Select1st<_STL::pair<const Gen_t_004b07d0_k4, Gen_t_004b07d0_p4pod> >,
                _STL::less<Gen_t_004b07d0_k4>,
                _STL::allocator<_STL::pair<const Gen_t_004b07d0_k4, Gen_t_004b07d0_p4pod> > > *>(this)
                ->_M_erase(reinterpret_cast<_STL::_Rb_tree_node<_STL::pair<const Gen_t_004b07d0_k4,
                    Gen_t_004b07d0_p4pod> > *>(m_bfmeNode->m_bfmeHead));

			m_bfmeNode->m_bfmeNext = m_bfmeNode;
			m_bfmeNode->m_bfmeHead = 0;
			m_bfmeNode->m_bfmePrev = m_bfmeNode;

			m_bfmeCount = 0;
		}
	}


	BfmeNodeW *m_bfmeNode;					// +0x00
	int m_bfmeCount;					// +0x04
};

class Gen_004B1720
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[3];					// +0x00
	BfmeVecW m_bfmeVector;					// +0x0C
	int m_bfmeGap[11];					// +0x18
	BfmeListW m_bfmeList;					// +0x44
};

// ?bfmeClear@Gen_004B1720@@QAEXXZ
void Gen_004B1720::bfmeClear(void)
{
	BfmeElemW **it = m_bfmeVector.m_bfmeStart;

	while (it != m_bfmeVector.m_bfmeFinish)
	{
		BfmeElemW *element = *it;

		if (element)
		{
			reinterpret_cast<GameWindow *>(element)->winSetSize(1, 1);

			reinterpret_cast<GameWindow *>(element)->winSetPosition(-1, -1);
		}

		++it;
	}

	m_bfmeVector.bfmeClear();

	m_bfmeList.bfmeClear();
}
