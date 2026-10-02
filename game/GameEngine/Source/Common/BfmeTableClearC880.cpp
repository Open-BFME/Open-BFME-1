// cl: /O2 /DNDEBUG /MD

class BfmeHeldC880
{
public:
	virtual void bfmeSpare000C880(void) = 0;
	virtual void bfmeReleaseC880(void) = 0;
};

struct BfmeSlotC880
{
	void *m_key;
	void *m_held;
};

// The shared empty EA string block at 0x012D5298 is defined once, as
// EAStringC::StringDataC, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp;
// this TU only compares its address, never a field.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;

class Gen0089C880
{
public:
	void handle();

private:
	int m_count;
	BfmeSlotC880 *m_array;
	void *m_a;
	void *m_b;
};

void Gen0089C880::handle()
{
	void *p = m_b;
	if (p != 0)
	{
		if ((unsigned)p & 1)
		{
			BfmeHeldC880 *h = (BfmeHeldC880 *)((unsigned)p & ~1u);
			h->bfmeReleaseC880();
			m_b = 0;
		}
	}

	p = m_a;
	if (p != 0)
	{
		if ((unsigned)p & 1)
		{
			BfmeHeldC880 *h = (BfmeHeldC880 *)((unsigned)p & ~1u);
			h->bfmeReleaseC880();
			m_a = 0;
		}
	}

	if (m_array == 0)
		return;

	int i = 0;
	if (m_count > 0)
	{
		do
		{
			void *key = m_array[i].m_key;
			if (key != 0 && key != &g_rva012D5298Empty)
			{
				void *held = m_array[i].m_held;
				if ((unsigned)held & 1)
				{
					BfmeHeldC880 *h = (BfmeHeldC880 *)((unsigned)held & ~1u);
					h->bfmeReleaseC880();
					m_array[i].m_held = 0;
				}
			}
			++i;
		}
		while (i < m_count);
	}
}
