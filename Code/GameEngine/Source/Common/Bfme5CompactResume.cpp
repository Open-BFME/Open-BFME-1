// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x0018B9F0 is the body reached by Gen_0018BC70::bfmeCompact(false)
// through the existing ILT at 0x0000764E. The thunk has a void wrapper, but
// the body returns the rebuilt vector address in EAX, so this view uses the
// pointer return type that decorates the body itself.
//
// The sibling compaction body witnesses the ID vector at +0x04 and the
// pointer vector at +0x10. The inlined STLport hash lookup matches
// GameLogicFindObjectByID.cpp, including TheGameLogic's bucket vector at
// +0xB4 and +0xB8. The pointer-vector overflow call reaches the existing
// four-byte STLport body at 0x0018B700 through ILT 0x0001F6CC.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>

typedef int ObjectID;

class Rva00261F40Subject
{
};

typedef _STL::hash_map<ObjectID, Rva00261F40Subject *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectHash;

class GameLogic
{
public:
	char m_pad00[0xB0];
	ObjectHash m_objectHash;

	__forceinline Rva00261F40Subject *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectHash::iterator found = m_objectHash.find(id);
		if (found == m_objectHash.end())
			return 0;

		return (*found).second;
	}
};

extern GameLogic *TheGameLogic;

class BfmeVecAK
{
public:
	Rva00261F40Subject **m_start;
	Rva00261F40Subject **m_finish;
	Rva00261F40Subject **m_end;
};

class Gen_0018BC70
{
private:
	BfmeVecAK *bfmeResume();

	int m_unknown00;
	_STL::vector<ObjectID> m_objectIDs;
	_STL::vector<Rva00261F40Subject *> m_objects;
};

BfmeVecAK *Gen_0018BC70::bfmeResume()
{
	m_objects.clear();
	Rva00261F40Subject *object;
	for (_STL::vector<ObjectID>::iterator it = m_objectIDs.begin();
		it != m_objectIDs.end(); ++it)
	{
		ObjectID id = *it;
		object = TheGameLogic->findObjectByID(id);
		if (object != 0)
			m_objects.push_back(object);
	}
	return (BfmeVecAK *)&m_objects;
}
