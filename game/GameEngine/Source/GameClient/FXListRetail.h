#pragma once
#include <list>

class Object;
struct Coord3D;
class Matrix3D;
struct FXNuggetNode;

// Canonical list implementation from FXList_bfmeIsBlocked.cpp.
class PlayTimeList : public _STL::list<unsigned int>
{
public:
	typedef _STL::list<unsigned int>::iterator iterator;
	typedef _STL::_List_node_base NodeBase;
	typedef _STL::_List_node<unsigned int> Node;

	unsigned int size() const;
	__declspec(noinline) iterator insert(iterator position, const unsigned int &value)
	{
		return _STL::list<unsigned int>::insert(position, value);
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

	void putNode(NodeBase *node, unsigned int count);
};

// Joined retail layout: playback fields (0x04..0x10) and culling (0x14..).
class FXList
{
public:
	virtual ~FXList();
	static void doFXObj(const FXList *, const Object *, const Object *);
	static void doFXPos(const FXList *, const Coord3D *, const Matrix3D *, float, const Coord3D *);
	bool bfmeIsBlocked();
	void doFXObj(const Object *, const Object *) const;
	void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;

private:
	FXNuggetNode *m_nuggetSentinel;
	char m_bfmeFields[8];
	bool m_playEvenIfShrouded;
	unsigned int m_trackingFrames;
	PlayTimeList m_playTimes;
	unsigned int m_startCullingAbove;
	unsigned int m_cullAllAbove;
};
