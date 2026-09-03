// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int ObjectID;

class BfmeY982
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual bool isComplete();
	BfmeY982 *bfmeConv982B();
};

typedef _STL::hash_map<ObjectID, BfmeY982 *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > Rva0036F910ObjectMap;

class Rva0036F910GameLogic
{
public:
	char m_pad000[0xb0];
	Rva0036F910ObjectMap m_objects;
};

extern Rva0036F910GameLogic *TheGameLogic;

class Rva0036F910Owner
{
public:
	int countCompleteStructures();
	int countCompleteStructuresSecondary();

private:
	char m_pad000[0xb8];
	ObjectID *m_begin;
	ObjectID *m_end;
	char m_pad0c0[0xdc - 0xc0];
	ObjectID *m_secondaryBegin;
	ObjectID *m_secondaryEnd;
};

int Rva0036F910Owner::countCompleteStructures()
{
	int count = 0;
	ObjectID *current = m_begin;
	while (current != m_end)
	{
		ObjectID id = *current;
		if (id != 0)
		{
			Rva0036F910ObjectMap::iterator it = TheGameLogic->m_objects.find(id);
			if (it != TheGameLogic->m_objects.end())
			{
				BfmeY982 *object = (*it).second;
				if (object != 0)
				{
					BfmeY982 *completion = object->bfmeConv982B();
					if (completion != 0 && completion->isComplete())
						++count;
				}
			}
		}
		++current;
	}
	return count;
}

int Rva0036F910Owner::countCompleteStructuresSecondary()
{
	int count = 0;
	ObjectID *current = m_secondaryBegin;
	while (current != m_secondaryEnd)
	{
		ObjectID id = *current;
		if (id != 0)
		{
			Rva0036F910ObjectMap::iterator it = TheGameLogic->m_objects.find(id);
			if (it != TheGameLogic->m_objects.end())
			{
				BfmeY982 *object = (*it).second;
				if (object != 0)
				{
					BfmeY982 *completion = object->bfmeConv982B();
					if (completion != 0 && completion->isComplete())
						++count;
				}
			}
		}
		++current;
	}
	return count;
}
