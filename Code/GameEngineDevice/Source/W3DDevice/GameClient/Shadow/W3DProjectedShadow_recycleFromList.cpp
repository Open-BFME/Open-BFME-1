// Open-BFME: unlink a projected shadow from a caller-supplied list, drop the
// decal count for the five decal-typed kinds, and push the node onto the free
// list at this+0x10. Retail 0x007AFAA0, 133 bytes.

struct W3DProjectedShadow
{
	unsigned char m_pad0[0x34];
	int m_type;
	unsigned char m_pad1[0x9C];
	W3DProjectedShadow *m_next;
	~W3DProjectedShadow(void);
};

class Rva007AFAA0Manager
{
public:
	bool recycleFromList(W3DProjectedShadow *shadow, W3DProjectedShadow **list);

private:
	unsigned char m_pad0[0x10];
	W3DProjectedShadow *m_free;
	unsigned char m_pad1[0x23C];
	int m_decalCount;
};

bool Rva007AFAA0Manager::recycleFromList(W3DProjectedShadow *shadow, W3DProjectedShadow **list)
{
	W3DProjectedShadow *prev = 0;
	W3DProjectedShadow *cur = *list;

	if (!cur)
		return false;

	while (cur)
	{
		if (cur == shadow)
		{
			if (prev)
				prev->m_next = shadow->m_next;
			else
				*list = shadow->m_next;

			switch (shadow->m_type)
			{
			case 0x40:
			case 1:
			case 0x20:
			case 0x400:
			case 0x800:
				m_decalCount--;
				break;
			}

			shadow->m_next = m_free;
			m_free = shadow;
			shadow->~W3DProjectedShadow();
			return true;
		}

		prev = cur;
		cur = cur->m_next;
	}

	return false;
}
