// stlport
#include <vector>
// ?rva000d6030@Rva000D6030Owner@@QAEMPBVThingTemplate@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail RVA 0x000D6030: a null template returns 1.0f.
// Otherwise walk the sentinel-headed list at this+0x640. For each node,
// look up its object's ID and skip absent objects or objects with either
// disqualifying flag set. An accepted item overwrites the result with
// m_array[index] when index is below its size; the shared index
// increments after every accepted item, including an out-of-range one.
// Return the last in-range value (initially zero) plus the unit float. The
// caller does not prove the owning class identity.

class ThingTemplate;
#include "Thing/GameLogicObjectLookup.h"

extern GameLogic *TheBfmeGameLogic;

class Player;

struct Rva0039F0A0
{
	bool accepts(const void *tmpl, Player *player1, Player *player2);
};

struct Rva000D6030Item
{
	Rva0039F0A0 *m_accepts;	// +0x00
	_STL::vector<float> m_array; // +0x04
	int m_objectId;			// +0x10
};

struct Rva000D6030Node
{
	Rva000D6030Node *m_next;
	Rva000D6030Node *m_prev;
	Rva000D6030Item *m_data;
};

struct Rva000D6030Owner
{
	float rva000d6030(const ThingTemplate *tmpl);

	unsigned char m_bfmeHead[0x640];
	Rva000D6030Node *m_bfmeSentinel;	// +0x640
};

// Retail RVA 0x000D6030, 162 bytes. Native STLport vector access preserves
// the end/start load order; the final literal preserves the x87 operand order.
float Rva000D6030Owner::rva000d6030(const ThingTemplate *tmpl)
{
	Rva000D6030Owner *owner = this;
	if (!tmpl)
		return 1.0f;

	Rva000D6030Node *node = owner->m_bfmeSentinel->m_next;
	float result = 0.0f;
	unsigned int index = 0;

	while (node != owner->m_bfmeSentinel)
	{
		Rva000D6030Item *item = node->m_data;
		Object *obj = TheBfmeGameLogic->findObjectByID(item->m_objectId);

		if (obj)
		{
			unsigned char flagsA = *((unsigned char *)obj + 0x118);
			unsigned int flagsB = *(unsigned int *)((char *)obj + 0x90);

			if (!(flagsA & 8) && !(flagsB & 0x80000))
			{
				if (item->m_accepts->accepts(tmpl, 0, 0))
				{
					unsigned int count = item->m_array.size();

					if (index < count)
						result = item->m_array[index];

					++index;
				}
			}
		}

		node = node->m_next;
	}

	result += 1.0f;
	return result;
}
