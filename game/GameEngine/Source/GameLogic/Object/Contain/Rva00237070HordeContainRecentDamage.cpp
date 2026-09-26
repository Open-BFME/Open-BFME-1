// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// Retail 0x00237070 (269 bytes): a HordeContain-family query on the interface
// subobject at owner+0xC4 (the member index at +0x30 and the member lookup
// are the ones Rva0023D720HordeContainGainLevel.cpp reads).  It reports who
// damaged the horde recently: its own cached source when that is fresh
// enough, else the first contained object or indexed member that has a
// recent damage source of its own.  The method is not proven, so it keeps the
// address.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt ObjectID;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeGetRecentDamageSource(ObjectID *sourceID, UnsignedInt frames) const;
};

struct BfmeMemberIndexNode
{
	UnsignedInt m_color;
	BfmeMemberIndexNode *m_parent;
	BfmeMemberIndexNode *m_next;
	BfmeMemberIndexNode *m_right;
	UnsignedInt m_key;
};

namespace _STL
{
struct _Rb_tree_node_base
{
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;
typedef _STL::list<Object *> BfmeMemberList;

class BfmeGameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

	__forceinline Object *findObjectByID(UnsignedInt key)
	{
		BfmeObjectPtrHash::iterator it = m_objectHash.find(key);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_head[0x3c];
	UnsignedInt m_frame;
	char m_head40[0xb0 - 0x40];
	BfmeObjectPtrHash m_objectHash;
};

extern BfmeGameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class Rva00237070ContainOwner
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64();
	virtual const BfmeMemberList *getContainedItemsList();
};

class BfmeHordeContainOwner
{
public:
	Bool rva00237070(ObjectID *sourceID, UnsignedInt frames);

private:
	Rva00237070ContainOwner *getContainOwner()
	{
		return (Rva00237070ContainOwner *)((char *)this - 0xc4);
	}

	char m_head[0x30];
	BfmeMemberIndexNode *m_memberIndex;
	char m_gap34[0x110 - 0x34];
	UnsignedInt m_lastDamageFrame;
	ObjectID m_lastDamageSource;
};

// ?rva00237070@BfmeHordeContainOwner@@QAE_NPAII@Z
Bool BfmeHordeContainOwner::rva00237070(ObjectID *sourceID, UnsignedInt frames)
{
	*sourceID = 0;

	UnsignedInt now = TheGameLogic->getFrame();
	if (frames >= now)
		return false;

	if (m_lastDamageFrame != (UnsignedInt)-1 && m_lastDamageFrame + frames >= now)
	{
		*sourceID = m_lastDamageSource;
		return true;
	}

	const BfmeMemberList *contained = getContainOwner()->getContainedItemsList();
	for (BfmeMemberList::const_iterator it = contained->begin(); it != contained->end(); ++it)
	{
		Object *object = *it;
		if (object != 0 && object->bfmeGetRecentDamageSource(sourceID, 4))
			return true;
	}

	for (BfmeMemberIndexNode *entry = m_memberIndex->m_next; entry != m_memberIndex;
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry))
	{
		UnsignedInt key = entry->m_key;
		if (key != 0)
		{
			Object *object = TheGameLogic->findObjectByID(key);
			if (object != 0 && object->bfmeGetRecentDamageSource(sourceID, 4))
				return true;
		}
	}

	return false;
}
