// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: FXList::bfmeIsBlocked, retail 0x0042DAA0 (188B).
// The FXList static object wrapper calls this BFME culling predicate through
// ILT 0x00011F77 before it plays an effect.
#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"

#pragma comment(linker, "/alternatename:?insert@PlayTimeList@@QAE?AU?$_List_iterator@IU?$_Nonconst_traits@I@_STL@@@_STL@@U23@ABI@Z=?j_00004fc5@@YAXXZ")
#pragma comment(linker, "/alternatename:?putNode@PlayTimeList@@QAEXPAU_List_node_base@_STL@@I@Z=?j_0000ebec@@YAXXZ")
#pragma comment(linker, "/alternatename:?size@PlayTimeList@@QBEIXZ=?j_0000e49e@@YAXXZ")

typedef unsigned int UnsignedInt;

extern int GetGameClientRandomValue(int lo, int hi, char *file, int line);

class PlayTimeList : public _STL::list<UnsignedInt>
{
public:
	typedef _STL::list<UnsignedInt>::iterator iterator;
	typedef _STL::_List_node_base NodeBase;
	typedef _STL::_List_node<UnsignedInt> Node;

	UnsignedInt size() const;
	__declspec(noinline) iterator insert(iterator position, const UnsignedInt &value)
	{
		return _STL::list<UnsignedInt>::insert(position, value);
	}

	iterator erase(iterator position)
	{
		NodeBase *previous = position._M_node->_M_prev;
		NodeBase *next = position._M_node->_M_next;
		previous->_M_next = next;
		next->_M_prev = previous;
		putNode(position._M_node, 1);
		return iterator((Node *)next);
	}

	void putNode(NodeBase *node, UnsignedInt count);
};

class GameLogic
{
	unsigned char m_pad[0x3C];

public:
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class FXList
{
public:
	bool bfmeIsBlocked();

private:
	unsigned char m_pad00[0x14];
	UnsignedInt m_trackingFrames;
	PlayTimeList m_playTimes;
	UnsignedInt m_startCullingAbove;
	UnsignedInt m_cullAllAbove;
};

bool FXList::bfmeIsBlocked()
{
	if (!m_trackingFrames)
		return false;

	PlayTimeList *times = &m_playTimes;
	register UnsignedInt frame = TheBfmeGameLogic->m_frame;
	PlayTimeList::iterator node = times->begin();

	while (node != times->end())
	{
		if (*node >= frame - m_trackingFrames)
			break;

		node = times->erase(node);
	}

	UnsignedInt n = times->size();
	UnsignedInt startCull = m_startCullingAbove;
	if (n > startCull)
		return true;

	UnsignedInt cullAll = m_cullAllAbove;
	if (n > cullAll)
	{
		UnsignedInt q = (n - m_cullAllAbove) / (startCull - m_cullAllAbove);
		if (!GetGameClientRandomValue(0, (int)q,
			"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\FXList.cpp", 0x845))
			return true;
	}

	m_playTimes.insert(m_playTimes.end(), frame);
	return false;
}
