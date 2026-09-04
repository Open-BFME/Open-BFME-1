// Address-derived flag refresh at retail 0x003CA710.

int __cdecl bfmeCallFHA(void *left, void *right);

struct Rva003CA710State
{
	char m_pad00[0x18];
	unsigned char m_flag;
};

struct Rva003CA710Entry
{
	char m_pad00[0xA8];
	unsigned char m_enabled;
	char m_padA9[0x0B];
	void *m_probe;
	char m_padB8[0x34];
	Rva003CA710State *m_state;
};

struct Rva003CA710Vector
{
	Rva003CA710Entry **m_begin;
	Rva003CA710Entry **m_end;
};

struct Rva003CA710Container
{
	char m_pad00[0x30];
	Rva003CA710Vector m_entries;
};

class Rva003CA710Owner
{
public:
	void refresh(bool includeDisabled, bool requireSecond);

private:
	char m_pad00[4];
	Rva003CA710Container *m_container;
};

void Rva003CA710Owner::refresh(bool includeDisabled, bool requireSecond)
{
	Rva003CA710Container *container = m_container;
	Rva003CA710Vector *entries =
		(Rva003CA710Vector *)((char *)container + 0x30);
	unsigned int index = 0;
	if ((unsigned int)(entries->m_end - entries->m_begin) > 0)
	{
		do
		{
		unsigned char value = 0;
		if (includeDisabled)
		{
			Rva003CA710Entry *entry = entries->m_begin[index];
			if (entry->m_enabled)
			{
				if (requireSecond)
				{
					void *probe = entry->m_probe;
					if (bfmeCallFHA(probe, probe) == 1)
						value = 1;
				}
				else
					value = 1;
			}
		}
		else
		{
			if (requireSecond)
			{
				Rva003CA710Entry *entry = entries->m_begin[index];
				void *probe = entry->m_probe;
				if (bfmeCallFHA(probe, probe) == 1)
					value = 1;
			}
			else
				value = 1;
		}
		entries->m_begin[index]->m_state->m_flag = value;
		++index;
		}
		while (index < (unsigned int)(entries->m_end - entries->m_begin));
	}
}
