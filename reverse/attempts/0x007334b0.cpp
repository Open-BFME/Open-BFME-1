// ?bfmeForward@Gen_006C8A60Target@@QAE_NPAX@Z
// partial score=0.95 date=2026-09-03
// Open-BFME5: BFME target behind Gen_006C8A60::bfmeForward.
// Retail RVA 0x007334B0.  The guarded-delegate thunk at 0x006C8A60
// identifies this as the one-argument target method, not a generated dump.

typedef unsigned char Bool;

extern float g_bfmeUint32Scale; // retail 0x01075358

struct Gen006C8A60Entry
{
	unsigned char m_pad00[0x40];
	int m_state;                              // +0x40
	unsigned char m_pad44[0x14];
	void *m_key;                              // +0x58
	unsigned char m_pad5c[0x64];
	int m_handle;                             // +0xC0
	Bool m_ready;                              // +0xC4
	unsigned char m_padc5[3];
	void *m_object;                            // +0xC8
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
	int m_entryCount;                         // +0x2A7CB0
	unsigned char m_pad2a7cb4[0x28];
	Gen006C8A60StateSlot m_states[1];         // +0x2A7CDC, stride 0x5C
	unsigned char m_pad2a7d38[0x1684];
	int m_stateLimit;                         // +0x2A93BC
	unsigned char m_pad2a93c0[0x538];
	float m_scale;                             // +0x2A98F8
};

// ?bfmeForward@Gen_006C8A60Target@@QAE_NPAX@Z
bool Gen_006C8A60Target::bfmeForward(void *key)
{
	if (key == 0)
		return false;

	int count = m_entryCount;
	int i = 0;
	Gen006C8A60Entry *entry;
	if (count > 0)
	{
		for (; i < count; ++i)
		{
			if (m_entries[i].m_key == key)
				goto matched;
		}
		return false;
	}
	goto matchedFailure;

matched:
	entry = m_entries + i;
	if (entry == 0)
		goto matchedFailure;
	if (entry->m_state < 0 || entry->m_state >= m_stateLimit)
		goto matchedFailure;
	if (entry->m_object == 0)
		goto matchedWork;

matchedFailure:
	return false;

	matchedWork:
	{
		Gen006C8A60StateObject *state =
			(Gen006C8A60StateObject *)m_states[entry->m_state].m_object;
		float scaled = (float)state->m_value;
		scaled *= m_scale;
		entry->m_handle = (int)scaled;
		entry->m_ready = 1;
	}
	return true;

noMatch:
	return false;
}
