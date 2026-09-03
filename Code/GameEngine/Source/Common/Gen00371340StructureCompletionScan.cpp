// ?hasIncompleteStructure@Gen_00371340@@QAE_NPAVBfmeY982@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

class Gen00371340Template : public Overridable
{
public:
	unsigned char m_unmodelled_08[0xd8 - 8];
	unsigned int m_kindOf;
};

class BfmeY982
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual bool isComplete();
	BfmeY982 *bfmeConv982B();

	Gen00371340Template *m_template;
	unsigned char m_unmodelled_08[0xcc - 8];
	int m_field;
};

typedef _STL::hash_map<ObjectID, BfmeY982 *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > Gen00371340ObjectMap;

class Gen00371340GameLogic
{
public:
	char m_pad000[0xb0];
	Gen00371340ObjectMap m_objects;
};

extern Gen00371340GameLogic *TheGameLogic;

class Gen_00371340
{
public:
	bool hasIncompleteStructure(BfmeY982 *argument);

private:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/Babylon/excel8.h
	struct Range
	{
		ObjectID *begin;
		ObjectID *end;
	};

	unsigned char m_pad000[0x9c];
	int m_state;
	unsigned char m_pad0a0[0x18];
	Range m_primary;
	unsigned char m_pad0c0[0x1c];
	Range m_secondary;
};

bool Gen_00371340::hasIncompleteStructure(BfmeY982 *argument)
{
	if (m_state != 4)
		return false;

	register Gen_00371340::Range *range = &m_primary;
	if (argument != 0 && (argument->m_field & 0x80000000) != 0)
		range = &m_secondary;

	ObjectID *current = range->begin;
	if (current != range->end)
	{
		Gen00371340GameLogic *logic = TheGameLogic;

		while (current != range->end)
		{
		ObjectID id = *current;
		if (id != 0)
		{
			Gen00371340ObjectMap::iterator it = logic->m_objects.find(id);
			if (it != logic->m_objects.end())
			{
				BfmeY982 *object = (*it).second;
				if (object != 0)
				{
					Gen00371340Template *templateValue = object->m_template;
					if (templateValue != 0 && templateValue->m_nextOverride != 0)
						templateValue = (Gen00371340Template *)templateValue->m_nextOverride->getFinalOverride();
					if ((templateValue->m_kindOf & 0x200000) != 0)
						goto next_object;

					BfmeY982 *completion = object->bfmeConv982B();
					if (completion != 0 && !completion->isComplete())
						return true;
					logic = TheGameLogic;
				}
			}
		}

	next_object:
			++current;
		}
	}

	return false;
}
