// ?update@Rva008D3610Owner@@QAEXHPAX@Z
// partial score=0.285 date=2026-09-10
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Address-derived Apt update body at retail 0x008D3610.
// The caller is the named Rva008A25C0 Apt dispatcher; the original owner
// spelling is not recovered, so this TU keeps the witnessed offsets local.

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
	int m_buffer;
};

struct Rva008D3610Node;

struct Rva008D3610Group
{
	int m_count;
	int m_items;
};

struct Rva008D3610Node
{
	int m_type;
	int m_value04;
	int m_value08;
	char m_padding0c[0x28];
	int m_value34;
	char m_padding38[4];
	int m_nested;
};

class Rva008D3610Owner
{
public:
	static __forceinline int count(Rva008D3610Owner *owner)
	{
		return owner->m_groupCount;
	}

	void update(int delta, void *context);

	private:
	int m_groupCount;
	int m_groups;
	int m_child;
};

// ?update@Rva008D3610Owner@@QAEXHPAX@Z
void Rva008D3610Owner::update(int delta, void *context)
{
	Rva008D3610Group *groups = (Rva008D3610Group *)m_groups;
	for (int groupIndex = 0; groupIndex < m_groupCount; ++groupIndex)
	{
		int itemCount = groups[groupIndex].m_count;
		for (int itemIndex = 0; itemIndex < itemCount; ++itemIndex)
		{
			Rva008D3610Node **items = (Rva008D3610Node **)groups[groupIndex].m_items;
			Rva008D3610Node *node = items[itemIndex];
			int kind = node->m_type - 1;
			switch (kind)
			{
			case 0:
				rva008CC540ZeroThirdForwarder(
					(void *)((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value04,
					(void *)delta, (void *)context);
				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value04 != 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value04 -= delta;
				break;

			case 1:
				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value04 != 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value04 -= delta;
				break;

			case 2:
			{
				Rva008D3610Nested *nested =
					(Rva008D3610Nested *)((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_nested;
				if (nested != 0)
				{
					int nestedIndex = 0;
					while (nestedIndex < nested->m_count)
					{
						int offset = nestedIndex * 12;
						int *value = (int *)(nested->m_buffer + offset + 8);
						rva008CC540ZeroThirdForwarder(
							(void *)*value, (void *)delta, (void *)context);
						if (*value != 0)
							*value -= delta;
						++nestedIndex;
					}

					if (nested->m_buffer != 0)
						nested->m_buffer -= delta;
				}

				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value34 != 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value34 -= delta;

				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_nested != 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_nested -= delta;
				break;
			}

			case 7:
				rva008CC540ZeroThirdForwarder(
					(void *)((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value08,
					(void *)delta, (void *)context);
				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value08 != 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value08 -= delta;
				if (((Rva008D3610Node **)
					((Rva008D3610Group *)m_groups)[groupIndex].m_items)
					[itemIndex]->m_value04 < 0)
					((Rva008D3610Node **)
						((Rva008D3610Group *)m_groups)[groupIndex].m_items)
						[itemIndex]->m_value04 = -((Rva008D3610Node **)
							((Rva008D3610Group *)m_groups)[groupIndex].m_items)
							[itemIndex]->m_value04;
				break;
			}
		}
	}

	if (m_groups != 0)
		m_groups -= delta;

	if (m_child != 0)
	{
		Gen0089C880 *child = (Gen0089C880 *)m_child;
		child->handle();
		((BfmeChildA *)m_child)->~BfmeChildA();
		TheBfmeFree((void *)m_child, 16);
		m_child = 0;
	}
}
