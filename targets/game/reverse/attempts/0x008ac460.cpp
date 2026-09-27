// ?d_008ac460@@YAXXZ
// partial score=0.87 date=2026-09-27
// ?at@Rva008AC460Node@@QAEPAV1@H@Z
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeS1238
{
public:
	BfmeS1238 *bfmeAt1238B(int index);
};

class Rva008AC460Node;

struct Rva008AC460Record
{
	unsigned char m_pad00[4];
	Rva008AC460Node *m_child04;
	unsigned char m_pad08[0x3c];
};

class Rva008AC190Node
{
public:
	int size();
};

class Rva008AC460Node
{
public:
	Rva008AC460Node *at(int index);

	int m_kind;
	unsigned char m_pad04[4];
	Rva008AC460Node *m_child08;
	union
	{
		int m_count0c;
		Rva008AC460Node *m_child0c;
	};
	void *m_data10;
	int m_count14;
	Rva008AC460Node **m_children18;
	unsigned char m_pad1c[0x10];
	int m_count2c;
	Rva008AC460Record *m_records30;
	unsigned char m_pad34[8];
	Rva008AC460Node **m_children3c;
};

Rva008AC460Node *Rva008AC460Node::at(int index)
{
	int i;
	Rva008AC460Node *node = this;

	for (;;)
	{
		switch (node->m_kind)
		{
		case 3:
		{
			for (i = 0; i < node->m_count0c; ++i)
			{
				Rva008AC460Node *child =
					((Rva008AC460Node **)node->m_data10)[i];
				int count = ((Rva008AC190Node *)child)->size();
				if (index < count)
				{
					node = ((Rva008AC460Node **)node->m_data10)[i];
					goto next_node;
				}
				index -= count;
			}
			return 0;
		}

		case 4:
		{
			int offset = 0;
			for (i = 0; i < node->m_count2c; ++i)
			{
				Rva008AC460Node *child = *(Rva008AC460Node **)
					((unsigned char *)node->m_records30 + offset + 4);
				if (child)
				{
					int count = ((Rva008AC190Node *)child)->size();
					if (index < count)
					{
						node = node->m_records30[i].m_child04;
						goto next_node;
					}
					index -= count;
				}
				offset += 0x44;
			}

			if (!node->m_children3c)
				return 0;
			Rva008AC460Node *child = node->m_children3c[0];
			if (child)
			{
				int count = ((Rva008AC190Node *)child)->size();
				if (index < count)
				{
					node = node->m_children3c[0];
					goto next_node;
				}
				index -= count;
			}

			child = node->m_children3c[1];
			if (child)
			{
				int count = ((Rva008AC190Node *)child)->size();
				if (index < count)
				{
					node = node->m_children3c[1];
					goto next_node;
				}
				index -= count;
			}

			child = node->m_children3c[2];
			if (child)
			{
				int count = ((Rva008AC190Node *)child)->size();
				if (index < count)
				{
					node = node->m_children3c[2];
					goto next_node;
				}
				index -= count;
			}

			child = node->m_children3c[3];
			if (!child)
				return 0;
			int count = ((Rva008AC190Node *)child)->size();
			if (index < count)
			{
				node = node->m_children3c[3];
				goto next_node;
			}
			return 0;
		}

		case 5:
			return (Rva008AC460Node *)
				((BfmeS1238 *)node->m_data10)->bfmeAt1238B(index);

		case 6:
		case 7:
			((Rva008AC190Node *)node->m_child0c)->size();
			return 0;

		case 8:
		{
			Rva008AC460Node *child = node->m_child08;
			int count;
			if (child)
			{
				count = ((Rva008AC190Node *)child)->size();
				if (index < count)
				{
					node = node->m_child08;
					goto next_node;
				}
				index -= count;
			}

			child = node->m_child0c;
			if (!child)
				return 0;
			count = ((Rva008AC190Node *)child)->size();
			if (index < count)
			{
				node = node->m_child0c;
				goto next_node;
			}
			return 0;
		}

		case 9:
			for (i = 0; i < node->m_count14; ++i)
			{
				Rva008AC460Node *child = node->m_children18[i];
				if (child == node)
					return 0;
				int count = ((Rva008AC190Node *)child)->size();
				if (index < count)
				{
					node = node->m_children18[i];
					goto next_node;
				}
				index -= count;
			}
			return 0;
		}

		return 0;

	next_node:
		;
	}
}
