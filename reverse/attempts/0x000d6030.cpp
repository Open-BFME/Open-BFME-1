// ?rva000d6030@Rva000D6030Owner@@QAEMPBVThingTemplate@@@Z
// partial score=0.55 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// retail RVA 0x000D6030. If the incoming ThingTemplate is null, returns
// g_bfmeDefaultBU. Otherwise walks the (sentinel-headed, doubly linked)
// list of Rva000D6030Item* at this+0x640; for each item whose object
// (GameLogic::findObjectByID on m_objectId) exists and clears both status
// flags, and whose accepts() approves the template, reads
// m_arrayStart[globalIndex] (globalIndex shared across accepted items,
// incrementing once per accepted read) into the running result and keeps
// going -- an item whose own array is too short for the current index ends
// the walk immediately. The final result adds g_bfmeDefaultBU. No caller or
// owner class identifies this body, so it is address-derived.

class ThingTemplate;
class Object;
typedef int ObjectID;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;
extern float g_bfmeDefaultBU;

struct Rva0039F0A0
{
	bool accepts(const ThingTemplate *tmpl, void *unused, bool flag);
};

struct Rva000D6030Item
{
	Rva0039F0A0 *m_accepts;	// +0x00
	float *m_arrayStart;		// +0x04
	float *m_arrayEnd;		// +0x08
	int m_pad0C;			// +0x0C
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

// retail RVA 0x000D6030
float Rva000D6030Owner::rva000d6030(const ThingTemplate *tmpl)
{
	if (!tmpl)
		return g_bfmeDefaultBU;

	Rva000D6030Node *sentinel = m_bfmeSentinel;
	Rva000D6030Node *node = sentinel->m_next;
	int index = 0;
	float result = 0.0f;

	while (node != sentinel)
	{
		Rva000D6030Item *item = node->m_data;
		Object *obj = TheBfmeGameLogic->findObjectByID(item->m_objectId);

		if (obj)
		{
			unsigned char flagsA = *((unsigned char *)obj + 0x118);
			unsigned int flagsB = *(unsigned int *)((char *)obj + 0x90);

			if (!(flagsA & 8) && !(flagsB & 0x80000))
			{
				if (item->m_accepts->accepts(tmpl, 0, false))
				{
					int count = item->m_arrayEnd - item->m_arrayStart;

					if (index >= count)
						break;

					result = item->m_arrayStart[index];
					++index;
				}
			}
		}

		node = node->m_next;
	}

	return result + g_bfmeDefaultBU;
}
