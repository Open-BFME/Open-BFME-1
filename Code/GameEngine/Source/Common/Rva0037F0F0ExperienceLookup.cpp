// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc-
//
// Retail 0x0037F0F0 is the ExperienceLevelSystem lookup reached through
// ILT 0x00027953.  ExperienceLevelMin001B20D0.cpp supplies the direct caller
// and its member-call ABI: (void *, int, int *), returning an int.
//
// The first callee returns an STLport list view.  Its sentinel is the first
// dword, and each node exposes the value at +8. The value's +4 pointer
// may redirect through BfmeSubBOB::bfmeFindBOB; the selected record's level
// key is at +0xCC and its experience result at +0x10.

struct BfmeGotBOB;

class BfmeSubBOB
{
public:
	BfmeGotBOB *bfmeFindBOB();

	int m_vtable;
	BfmeSubBOB *m_nested;
};

struct Rva0037F0F0Record
{
	int m_vtable;
	BfmeSubBOB *m_redirect;
	int m_pad08;
	int m_pad0c;
	int m_experience;
	unsigned char m_pad14[0xCC - 0x14];
	int m_level;
};

struct Rva0037F0F0Node
{
	Rva0037F0F0Node *m_next;
	Rva0037F0F0Node *m_prev;
	Rva0037F0F0Record m_value;
};

struct Rva0037F0F0List
{
	Rva0037F0F0Node *m_node;
};

class ExperienceLevelSystem
{
public:
	int bfmeQuery0037F0F0(void *object, int level, int *found);
	void *bfmeQuery0037F050(void *record);
};



// ?bfmeQuery0037F0F0@ExperienceLevelSystem@@QAEHPAXHPAH@Z
int ExperienceLevelSystem::bfmeQuery0037F0F0(
	void *object, int level, int *found)
{
	void *list = bfmeQuery0037F050(object);
	if (found != 0)
		*found = 0;

	if (list == 0)
		return 0;

	Rva0037F0F0Node *sentinel =
		((Rva0037F0F0List *)list)->m_node;
	Rva0037F0F0Node *node = sentinel->m_next;
	Rva0037F0F0Record *selected = 0;
	if (node != sentinel)
	{
		do
		{
			Rva0037F0F0Record *value = &node->m_value;
			BfmeSubBOB *redirect = value->m_redirect;
			if (redirect != 0)
			{
				BfmeSubBOB *nested = redirect->m_nested;
				if (nested != 0)
					selected = (Rva0037F0F0Record *)nested->bfmeFindBOB();
				else
					selected = (Rva0037F0F0Record *)redirect;
			}
			else
			{
				selected = value;
			}

			if (selected->m_level == level)
				return selected->m_experience;

			node = node->m_next;
		} while (node != sentinel);

		if (found != 0)
			*found = 1;
		return selected->m_experience;
	}
	return 0;
}
