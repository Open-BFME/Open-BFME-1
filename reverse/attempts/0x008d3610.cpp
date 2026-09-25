// ?update@Rva008D3610Owner@@QAEXHPAX@Z
// partial score=0.291 date=2026-09-25
// ?update@Rva008D3610Owner@@QAEXHPAX@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /FAsc /Fabuild/shape_008d3610.cod

extern void rva008CC540ZeroThirdForwarder(void *, void *, void *);
extern void (*TheBfmeFree)(void *, unsigned int);

class Gen0089C880
{
public:
	void handle();
};

class BfmeChildA
{
public:
	~BfmeChildA();
};

struct Rva008D3610Nested
{
	int m_count;
	char *m_buffer;
};

struct Rva008D3610NestedEntry
{
	int m_00;
	int m_04;
	char *m_value;
};

struct Rva008D3610Node;

struct Rva008D3610Group
{
	int m_count;
	Rva008D3610Node **m_items;
};

struct Rva008D3610Node
{
	int m_type;
	int m_value04;
	char *m_value08;
	char m_padding0c[0x28];
	char *m_value34;
	char m_padding38[4];
	Rva008D3610Nested *m_nested;
};

class Rva008D3610Owner
{
public:
	void update(int delta, void *context);

private:
	int m_groupCount;
	Rva008D3610Group *m_groups;
	void *m_child;
};

#define RVA008D3610_SUBTRACT(lvalue) if (lvalue != 0) (unsigned &)(lvalue) -= (unsigned)amount

// ?update@Rva008D3610Owner@@QAEXHPAX@Z
void Rva008D3610Owner::update(int delta, void *context)
{
	register int amount = delta;
	for (register int groupIndex = 0; groupIndex < m_groupCount; ++groupIndex)
	{
		for (int itemIndex = 0;
			itemIndex < ((Rva008D3610Group *)m_groups)[groupIndex].m_count;
			++itemIndex)
		{
			switch (((Rva008D3610Node **)
				((Rva008D3610Group *)m_groups)[groupIndex].m_items)
				[itemIndex]->m_type - 1)
			{
			case 0:
				rva008CC540ZeroThirdForwarder(
					(void *)((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value04,
					(void *)amount, (void *)context);
				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value04 != 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value04 -= amount;
				break;

			case 1:
				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value04 != 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value04 -= amount;
				break;

			case 7:
				rva008CC540ZeroThirdForwarder(
					(void *)((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value08,
					(void *)amount, (void *)context);
				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value08 != 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value08 -= amount;
				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value04 < 0)
					((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value04 = -((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value04;
				break;

			case 2:
			{
				Rva008D3610Nested *nested =
					(Rva008D3610Nested *)((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_nested;
				if (nested != 0)
				{
					Rva008D3610NestedEntry *entry =
						(Rva008D3610NestedEntry *)nested->m_buffer;
					int nestedIndex = 0;
					while (nestedIndex < nested->m_count)
					{
						rva008CC540ZeroThirdForwarder(
							(void *)entry->m_value, (void *)amount, (void *)context);
						if (entry->m_value != 0)
							entry->m_value -= amount;
						++nestedIndex;
						++entry;
					}

					if (nested->m_buffer != 0)
						nested->m_buffer -= amount;
				}

				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value34 != 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value34 -= amount;

				RVA008D3610_SUBTRACT(((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_nested);
				break;
			}

			}
		}
	}

	RVA008D3610_SUBTRACT(m_groups);

	if (m_child != 0)
	{
		Gen0089C880 *child = (Gen0089C880 *)m_child;
		child->handle();
		((BfmeChildA *)m_child)->~BfmeChildA();
		TheBfmeFree((void *)m_child, 16);
		m_child = 0;
	}
}
