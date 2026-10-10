// ?update@Rva008D3610Owner@@QAEXHPAX@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern void rva008CC540ZeroThirdForwarder(void *, void *, void *);
extern void (__cdecl *TheBfmeFree)(void *, unsigned int);

class Gen0089C880
{
public:
	void handle();
};

// The child is destroyed through the body at retail 0x0089C900,
// ??1Q3EhMember0089C900@@QAE@XZ, matched in
// game/GameEngine/Source/GameClient/EvaSideSoundsArrayDtor.cpp.  Retail's
// call at +0x201 lands on the first jump of the incremental-link chain
// 0x008976E0 -> 0x0089CC70 -> 0x0089C900, so it must relocate against
// ?j_008976e0@@YAXXZ (game/gen_small/thunks_037.cpp), the row that owns that
// call target.  The destructor is declared but not defined here; the destroy
// routes through the jump, as in BfmeSubB1035Destroy.cpp.
extern void j_008976e0();

class Q3EhMember0089C900
{
public:
	~Q3EhMember0089C900();
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
			itemIndex < m_groups[groupIndex].m_count;
			++itemIndex)
		{
			switch (m_groups[groupIndex].m_items[itemIndex]->m_type - 1)
			{
			case 0:
				rva008CC540ZeroThirdForwarder((void *)m_groups[groupIndex].m_items[itemIndex]->m_value04, (void *)amount, context);
				if (m_groups[groupIndex].m_items[itemIndex]->m_value04 != 0)
					m_groups[groupIndex].m_items[itemIndex]->m_value04 -= amount;
				break;

			case 7:
				rva008CC540ZeroThirdForwarder((void *)m_groups[groupIndex].m_items[itemIndex]->m_value08, (void *)amount, context);
				if (m_groups[groupIndex].m_items[itemIndex]->m_value08 != 0)
					m_groups[groupIndex].m_items[itemIndex]->m_value08 -= amount;
				if (m_groups[groupIndex].m_items[itemIndex]->m_value04 < 0)
					m_groups[groupIndex].m_items[itemIndex]->m_value04 = -m_groups[groupIndex].m_items[itemIndex]->m_value04;
				break;

			case 2:
			{
				Rva008D3610Nested *nested =
					(Rva008D3610Nested *)m_groups[groupIndex].m_items[itemIndex]->m_nested;
				if (nested != 0)
				{
					int nestedIndex = 0;
					while (nestedIndex < nested->m_count)
					{
						rva008CC540ZeroThirdForwarder((void *)((Rva008D3610NestedEntry *)nested->m_buffer)[nestedIndex].m_value, (void *)amount, context);
						if (((Rva008D3610NestedEntry *)nested->m_buffer)[nestedIndex].m_value != 0)
							((Rva008D3610NestedEntry *)nested->m_buffer)[nestedIndex].m_value -= amount;
						++nestedIndex;
					}

					if (nested->m_buffer != 0)
						nested->m_buffer -= amount;
				}

				if (m_groups[groupIndex].m_items[itemIndex]->m_value34 != 0)
					m_groups[groupIndex].m_items[itemIndex]->m_value34 -= amount;

				RVA008D3610_SUBTRACT(m_groups[groupIndex].m_items[itemIndex]->m_nested);
				break;
			}
			case 1:
				if (m_groups[groupIndex].m_items[itemIndex]->m_value04 != 0)
					m_groups[groupIndex].m_items[itemIndex]->m_value04 -= amount;
				break;


			}
			RVA008D3610_SUBTRACT(m_groups[groupIndex].m_items[itemIndex]);
		}
		RVA008D3610_SUBTRACT(m_groups[groupIndex].m_items);
	}

	RVA008D3610_SUBTRACT(m_groups);

	if (m_child != 0)
	{
		Gen0089C880 *child = (Gen0089C880 *)m_child;
		child->handle();
		if (child != 0)
		{
			((void (__fastcall *)(Q3EhMember0089C900 *))j_008976e0)((Q3EhMember0089C900 *)child);
			TheBfmeFree(child, 16);
		}
		m_child = 0;
	}
}
