// ?bfmeForward@Gen_006C8A60Target@@QAE_NPAX@Z
// partial score=0.95 date=2026-09-04
// BFME retail 0x007334B0: locate an entry and publish its scaled state.

typedef unsigned char Bool;

extern float g_bfmeUint32Scale;

struct Gen006C8A60Entry
{
	unsigned char m_pad00[0x40];
	int m_state;
	unsigned char m_pad44[0x14];
	void *m_key;
	unsigned char m_pad5c[0x64];
	int m_handle;
	Bool m_ready;
	unsigned char m_padc5[3];
	void *m_object;
	unsigned char m_padcc[0x1C];
};

struct Gen006C8A60StateSlot
{
	void *m_object;
	unsigned char m_pad04[0x58];
};

struct Gen006C8A60StateObject
{
	unsigned char m_pad00[0x40];
	unsigned int m_value;
};

class Gen_006C8A60Target
{
public:
	bool bfmeForward(void *key);

private:
	unsigned char m_pad000[0x1B0];
	Gen006C8A60Entry m_entries[1];
	unsigned char m_pad298[0x2A7A18];
	int m_entryCount;
	unsigned char m_pad2a7cb4[0x28];
	Gen006C8A60StateSlot m_states[1];
	unsigned char m_pad2a7d38[0x1684];
	int m_stateLimit;
	unsigned char m_pad2a93c0[0x538];
	float m_scale;
};

// ?bfmeForward@Gen_006C8A60Target@@QAE_NPAX@Z
bool Gen_006C8A60Target::bfmeForward(void *key)
{
	if (key == 0)
		return false;

	int count = m_entryCount;
	int i = 0;
	if (count > 0)
	{
		for (; i < count; ++i)
		{
			if (m_entries[i].m_key == key)
			{
				Gen006C8A60Entry *entry = m_entries + i;
				if (entry != 0 && entry->m_state >= 0 &&
					entry->m_state < m_stateLimit && entry->m_object == 0)
				{
					Gen006C8A60StateObject *state =
						(Gen006C8A60StateObject *)m_states[entry->m_state].m_object;
					float scaled = (float)state->m_value;
					scaled *= m_scale;
					entry->m_handle = (int)scaled;
					entry->m_ready = 1;
					return true;
				}
				return false;
			}
		}
		return false;
	}
	return false;
}
