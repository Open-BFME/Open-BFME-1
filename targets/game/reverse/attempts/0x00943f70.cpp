// ?clear@BfmeSceneVector@@AAEXPAUGen_uw_0002e866@@@Z
// partial score=0.85 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

void * __cdecl operator new(unsigned int size);

namespace _STL
{
struct __new_alloc
{
	static void *allocate(unsigned int size);
};
}

struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *next;
	void *object;
};

struct BfmeSceneListNode
{
	unsigned char unused[0xc];
	void *object_link;
};

struct BfmeSceneVectorElement
{
	unsigned char unused[8];
	BfmeSceneListNode *sentinel;
	BfmeSceneListNode *head;
	unsigned char tail[0xc];
};

struct Gen_uw_0002e866
{
	Gen_00943CF0_Node *head;
};

class BfmeSceneVector
{
public:
	void dummy_public_marker();

private:
	void clear(Gen_uw_0002e866 *objects);

	unsigned char unused[0x18];
	BfmeSceneVectorElement *vector;
	int vector_max;
	float scale;
	unsigned int level_mask;
};

class Gen_00943CF0
{
public:
	void unlink(void *object);
};

void BfmeSceneVector::clear(Gen_uw_0002e866 *objects)
{
	register BfmeSceneVector *self = this;
	register Gen_uw_0002e866 *list = objects;
	int index = 0;
	if (self->vector_max <= 0)
		return;
	BfmeSceneListNode **head = (BfmeSceneListNode **)((char *)self->vector + 0xc);
	while (index < self->vector_max)
	{
		while (*head != head[-1])
		{
			BfmeSceneListNode *node = *head;
			void *object_link = node->object_link;
			if (object_link != 0)
			{
				void *object = (char *)object_link - 8;
				if (object != 0)
				{
					Gen_00943CF0_Node *entry = (Gen_00943CF0_Node *)_STL::__new_alloc::allocate(8);
					if (entry != 0)
					{
						entry->next = 0;
						entry->next = list->head;
						entry->object = object;
						list->head = entry;
					}
					((Gen_00943CF0 *)self)->unlink(object);
				}
			}
		}
		++index;
		head += 7;
	}
}
