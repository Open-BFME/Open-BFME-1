// ?removeByKey@Rva00699180Owner@@QAEXI@Z
// partial score=0.62 date=2026-09-12
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x0069F2F0. Same 6x12-byte buckets at +0x4C as productClamp /
// refreshPair: erase every 8-byte entry whose key dword matches the
// argument, then recompute that bucket.

struct Rva00699180Pair
{
	float m_value;
	unsigned int m_key;
};

class Rva00699180Owner
{
public:
	void removeByKey(unsigned int key);
	void productClamp(int index);
	void refreshPair(int a, int b);

	char m_pad[0x4C];
	struct Bucket
	{
		Rva00699180Pair *begin;
		Rva00699180Pair *end;
		Rva00699180Pair *cap;
	} m_buckets[6];
};

void Rva00699180Owner::removeByKey(unsigned int key)
{
	int i = 0;
	char *cursor = (char *)this + 0x50;
	do
	{
		Rva00699180Pair *cur = *(Rva00699180Pair **)(cursor - 4);
		Rva00699180Pair *finish = *(Rva00699180Pair **)cursor;
		unsigned char removed = 0;
		if (cur != finish)
		{
			Rva00699180Pair *next = cur + 1;
			do
			{
				if (*(unsigned int *)((char *)next - 4) == key)
				{
					Rva00699180Pair *end = *(Rva00699180Pair **)cursor;
					if (next != end)
					{
						int n = end - next;
						if (n > 0)
						{
							Rva00699180Pair *dest = cur;
							do
							{
								dest[0] = dest[1];
								++dest;
								--n;
							} while (n);
						}
					}
					*(Rva00699180Pair **)cursor = *(Rva00699180Pair **)cursor - 1;
					removed = 1;
				}
				else
				{
					cur = (Rva00699180Pair *)((char *)cur + 8);
					next = (Rva00699180Pair *)((char *)next + 8);
				}
			} while (cur != *(Rva00699180Pair **)cursor);
		}
		if (removed)
		{
			productClamp(i);
			int j = 0;
			do
			{
				refreshPair(i, j);
				++j;
			} while (j < 2);
		}
		++i;
		cursor += 0xC;
	} while (i < 6);
}
