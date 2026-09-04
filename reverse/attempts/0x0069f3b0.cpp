// ?notify@Rva0069F4D0Block@@QAEXPAXH@Z
// partial score=0.72 date=2026-09-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
void __stdcall refreshPair(int a, int b);
void __stdcall productClamp(int index);

struct Node { float m_val; int m_key; };
struct Ent { int m_index; float m_val; };

class Rva0069F4D0Block
{
public:
	void notify(void *arg, int key);
	char m_bytes[0x60];
};

void Rva0069F4D0Block::notify(void *arg, int key)
{
	Ent *it;
	Ent *end;
	char *base = *(char **)arg + 0x8c;
	it = *(Ent **)base;
	end = *(Ent **)(base + 4);
	if (it == end)
		return;
	do
	{
		int index = it->m_index;
		if (index != -1)
		{
			float want = it->m_val;
			char *slot = m_bytes + index * 12;
			Node *ne = *(Node **)(slot + 0x50);
			Node *p = *(Node **)(slot + 0x4c);
			for (; p != ne; p = (Node *)((char *)p + 8))
			{
				if (p->m_val == want && p->m_key == key)
					break;
			}
			if (p != ne)
			{
				Node *src = (Node *)((char *)p + 8);
				if (src != ne)
				{
					int n = ((char *)ne - (char *)src) >> 3;
					if (n > 0)
					{
						do
						{
							*(int *)p = *(int *)((char *)p + 8);
							*((int *)p + 1) = *(int *)((char *)p + 12);
							p = (Node *)((char *)p + 8);
						} while (--n);
					}
				}
				*(char **)(slot + 0x50) = *(char **)(slot + 0x50) - 8;
			}
			productClamp(index);
			int j = 0;
			do
			{
				refreshPair(index, j);
				++j;
			} while (j < 2);
		}
		++it;
	} while (it != end);
}
