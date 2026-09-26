// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00243D50 (carved 268B, ret 4): walk an STLport map<int,int> of object
// IDs at +0x30; offer each object in its AI's range to the target's contain
// (vtable +0x88, slot 34), otherwise if the AI isIdle (vtable +0x180) issue aiEnter.
// Owner identity unproven: the sole caller reaches it through an ILT thunk.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>

struct Rva00243D50RangeData
{
	unsigned char lead[0x38];
	float range;
};

class Object;

class Rva00243D50Contain
{
public:
#define RVA243D50_SLOT(N) virtual void slot##N() = 0
	RVA243D50_SLOT(00); RVA243D50_SLOT(01); RVA243D50_SLOT(02); RVA243D50_SLOT(03);
	RVA243D50_SLOT(04); RVA243D50_SLOT(05); RVA243D50_SLOT(06); RVA243D50_SLOT(07);
	RVA243D50_SLOT(08); RVA243D50_SLOT(09); RVA243D50_SLOT(10); RVA243D50_SLOT(11);
	RVA243D50_SLOT(12); RVA243D50_SLOT(13); RVA243D50_SLOT(14); RVA243D50_SLOT(15);
	RVA243D50_SLOT(16); RVA243D50_SLOT(17); RVA243D50_SLOT(18); RVA243D50_SLOT(19);
	RVA243D50_SLOT(20); RVA243D50_SLOT(21); RVA243D50_SLOT(22); RVA243D50_SLOT(23);
	RVA243D50_SLOT(24); RVA243D50_SLOT(25); RVA243D50_SLOT(26); RVA243D50_SLOT(27);
	RVA243D50_SLOT(28); RVA243D50_SLOT(29); RVA243D50_SLOT(30); RVA243D50_SLOT(31);
	RVA243D50_SLOT(32); RVA243D50_SLOT(33);
	// slot 34 (+0x88): HordeGarrisonContain vtable 0x010AFB40 overrides it with
	// ILT 0x000061BD -> 0x00248C60, ledger ?step@Rva00248C60Owner (address-derived).
	virtual void slot34(Object *object) = 0;
#undef RVA243D50_SLOT
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiEnter(Object *object, CommandSourceType source);
};

class Rva00243D50AI
{
public:
#define RVA243D50_AI_SLOT(N) virtual void slot##N() = 0
	RVA243D50_AI_SLOT(00); RVA243D50_AI_SLOT(01); RVA243D50_AI_SLOT(02); RVA243D50_AI_SLOT(03);
	RVA243D50_AI_SLOT(04); RVA243D50_AI_SLOT(05); RVA243D50_AI_SLOT(06); RVA243D50_AI_SLOT(07);
	RVA243D50_AI_SLOT(08); RVA243D50_AI_SLOT(09); RVA243D50_AI_SLOT(10); RVA243D50_AI_SLOT(11);
	RVA243D50_AI_SLOT(12); RVA243D50_AI_SLOT(13); RVA243D50_AI_SLOT(14); RVA243D50_AI_SLOT(15);
	RVA243D50_AI_SLOT(16); RVA243D50_AI_SLOT(17); RVA243D50_AI_SLOT(18); RVA243D50_AI_SLOT(19);
	RVA243D50_AI_SLOT(20); RVA243D50_AI_SLOT(21); RVA243D50_AI_SLOT(22); RVA243D50_AI_SLOT(23);
	RVA243D50_AI_SLOT(24); RVA243D50_AI_SLOT(25); RVA243D50_AI_SLOT(26); RVA243D50_AI_SLOT(27);
	RVA243D50_AI_SLOT(28); RVA243D50_AI_SLOT(29); RVA243D50_AI_SLOT(30); RVA243D50_AI_SLOT(31);
	RVA243D50_AI_SLOT(32); RVA243D50_AI_SLOT(33); RVA243D50_AI_SLOT(34); RVA243D50_AI_SLOT(35);
	RVA243D50_AI_SLOT(36); RVA243D50_AI_SLOT(37); RVA243D50_AI_SLOT(38); RVA243D50_AI_SLOT(39);
	RVA243D50_AI_SLOT(40); RVA243D50_AI_SLOT(41); RVA243D50_AI_SLOT(42); RVA243D50_AI_SLOT(43);
	RVA243D50_AI_SLOT(44); RVA243D50_AI_SLOT(45); RVA243D50_AI_SLOT(46); RVA243D50_AI_SLOT(47);
	RVA243D50_AI_SLOT(48); RVA243D50_AI_SLOT(49); RVA243D50_AI_SLOT(50); RVA243D50_AI_SLOT(51);
	RVA243D50_AI_SLOT(52); RVA243D50_AI_SLOT(53); RVA243D50_AI_SLOT(54); RVA243D50_AI_SLOT(55);
	RVA243D50_AI_SLOT(56); RVA243D50_AI_SLOT(57); RVA243D50_AI_SLOT(58); RVA243D50_AI_SLOT(59);
	RVA243D50_AI_SLOT(60); RVA243D50_AI_SLOT(61); RVA243D50_AI_SLOT(62); RVA243D50_AI_SLOT(63);
	RVA243D50_AI_SLOT(64); RVA243D50_AI_SLOT(65); RVA243D50_AI_SLOT(66); RVA243D50_AI_SLOT(67);
	RVA243D50_AI_SLOT(68); RVA243D50_AI_SLOT(69); RVA243D50_AI_SLOT(70); RVA243D50_AI_SLOT(71);
	RVA243D50_AI_SLOT(72); RVA243D50_AI_SLOT(73); RVA243D50_AI_SLOT(74); RVA243D50_AI_SLOT(75);
	RVA243D50_AI_SLOT(76); RVA243D50_AI_SLOT(77); RVA243D50_AI_SLOT(78); RVA243D50_AI_SLOT(79);
	RVA243D50_AI_SLOT(80); RVA243D50_AI_SLOT(81); RVA243D50_AI_SLOT(82); RVA243D50_AI_SLOT(83);
	RVA243D50_AI_SLOT(84); RVA243D50_AI_SLOT(85); RVA243D50_AI_SLOT(86); RVA243D50_AI_SLOT(87);
	RVA243D50_AI_SLOT(88); RVA243D50_AI_SLOT(89); RVA243D50_AI_SLOT(90); RVA243D50_AI_SLOT(91);
	RVA243D50_AI_SLOT(92); RVA243D50_AI_SLOT(93); RVA243D50_AI_SLOT(94); RVA243D50_AI_SLOT(95);
	// slot 96 (+0x180) is AIUpdateInterface::isIdle: AIGroupStatePredicates.cpp,
	// AutoFindHealingUpdate.cpp:174, DozerAIUpdate.cpp:1156.
	virtual bool isIdle( void ) = 0;
#undef RVA243D50_AI_SLOT

	unsigned char pad004[0x1c];
	AICommandInterface command;
	unsigned char pad021[0x1ab];
	Rva00243D50RangeData *rangeData;
};

class Object
{
public:
	unsigned char pad000[0x38];
	float x;
	float y;
	unsigned char pad040[0x1bc];
	Rva00243D50Contain *contain;
	unsigned char pad200[4];
	Rva00243D50AI *ai;
};

struct Rva00367E30Logic
{
public:
	Object *findObjectByID(int objectID)
	{
		if (objectID == 0)
			return 0;

		ObjectPtrHash::iterator it = objects.find(objectID);
		if (it == objects.end())
			return 0;
		return (*it).second;
	}

	unsigned char pad000[0xb0];
	typedef _STL::hash_map<int, Object *> ObjectPtrHash;
	ObjectPtrHash objects;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Rva00243D50Owner
{
public:
	void processNearbyEntries00243D50(Object *target);

private:
	unsigned char pad000[0x30];
	typedef _STL::map<int, int> EntryMap;
	EntryMap entries;
};

void Rva00243D50Owner::processNearbyEntries00243D50(Object *target)
{
	for (EntryMap::iterator it = entries.begin(); it != entries.end(); ++it)
	{
		int objectID = (*it).first;
		Object *object = TheBfmeGameLogic->findObjectByID(objectID);

		if (object)
		{
			float dx = object->x - target->x;
			float dy = object->y - target->y;
			{
				Rva00243D50AI *ai = object->ai;
				if (ai)
				{
					float range = ai->rangeData->range;
					float distance = dx * dx;
					distance += dy * dy;
					if (distance < range * range)
					{
						Rva00243D50Contain *contain = target->contain;
						if (contain)
						{
							contain->slot34(object);
							goto next_entry;
						}
					}
				}
			}

			Rva00243D50AI *ai = object->ai;
			if (ai && ai->isIdle())
				ai->command.aiEnter(target, CMD_FROM_AI);
		}

	next_entry:
		;
	}
}
