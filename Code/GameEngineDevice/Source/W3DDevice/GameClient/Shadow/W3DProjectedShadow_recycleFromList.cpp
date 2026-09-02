// Open-BFME: unlink a projected shadow from a caller-supplied list, drop the
// decal count for the five decal-typed kinds, and push the node onto the free
// list at this+0x10. Retail 0x007AFAA0, 133 bytes.

struct Rva007AFAA0Shadow
{
	unsigned char m_pad0[0x34];
	int m_type;
	unsigned char m_pad1[0x9C];
	Rva007AFAA0Shadow *m_next;
	void recycle(void);
};

class Rva007AFAA0Manager
{
public:
	bool recycleFromList(Rva007AFAA0Shadow *shadow, Rva007AFAA0Shadow **list);

private:
	unsigned char m_pad0[0x10];
	Rva007AFAA0Shadow *m_free;
	unsigned char m_pad1[0x23C];
	int m_decalCount;
};

bool Rva007AFAA0Manager::recycleFromList(Rva007AFAA0Shadow *shadow, Rva007AFAA0Shadow **list)
{
	Rva007AFAA0Shadow *prev = 0;
	Rva007AFAA0Shadow *cur = *list;

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
			shadow->recycle();
			return true;
		}

		prev = cur;
		cur = cur->m_next;
	}

	return false;
}
