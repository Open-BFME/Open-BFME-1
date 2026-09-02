// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern void *__cdecl Rva0088EB30(unsigned int);

struct Rva00889D70Node
{
	Rva00889D70Node *next;
	void *arg1;
	void *arg2;
};

class Rva00889D70Class
{
public:
	char pad[0x10];
	Rva00889D70Node *head_10;

	bool d_00889d70(void *arg1, void *arg2);
};

bool Rva00889D70Class::d_00889d70(void *arg1, void *arg2)
{
	if (!arg1 || !arg2)
		return true;

	Rva00889D70Node *slot = (Rva00889D70Node *)&head_10;
	if (head_10)
	{
		do
		{
			slot = slot->next;
			if (slot->arg2 == arg2)
				return true;
		}
		while (slot->next);
	}

	Rva00889D70Node *node = (Rva00889D70Node *)Rva0088EB30(0xC);
	node->next = 0;
	node->arg1 = arg1;
	node->arg2 = arg2;
	slot->next = node;
	return true;
}
