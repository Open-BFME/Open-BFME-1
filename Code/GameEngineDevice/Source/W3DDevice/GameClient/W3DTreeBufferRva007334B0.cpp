// ?bfmeForward@Gen_006C8A60Target@@QAE_NPAX@Z
// BFME retail 0x007334B0..0x00733551 (161 bytes), including all RET 4 tails.
// Identity: matched Gen_006C8A60::bfmeForward at 0x006C8A60 tail-jumps
// through ILT 0x0001F640 to this body. Keep its established opaque target name.
// Array extents are independently witnessed by the matched tree-buffer
// destructor at 0x00736590: 12000 records of 0xE8 and 64 types of 0x5C.
// The lookup is a separate inlined operation: embedding the mutation inside
// the search loop makes VC7.1 merge distinct retail failure tails.

typedef unsigned char Bool;

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
	unsigned char m_pad00[0x20];
	void *m_object;
	unsigned char m_pad24[0x38];
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
    __forceinline Gen006C8A60Entry *find(void *key) {
        for (int i=0; i<m_entryCount; ++i)
            if (m_entries[i].m_key == key) return m_entries+i;
        return 0;
    }

private:
	unsigned char m_pad000[0x1B0];
	Gen006C8A60Entry m_entries[12000];
	int m_entryCount;
	unsigned char m_pad2a7cb4[8];
	Gen006C8A60StateSlot m_states[64];
	int m_stateLimit;
	unsigned char m_pad2a93c0[0x538];
	float m_scale;
};


bool Gen_006C8A60Target::bfmeForward(void *key)
{
    if (!key) return false;
    Gen006C8A60Entry *entry = find(key);
    if (!entry) return false;
    if (entry->m_state < 0) return false;
    if (entry->m_state >= m_stateLimit) return false;
    if (entry->m_object) return false;
    Gen006C8A60StateObject *state =
        (Gen006C8A60StateObject *)m_states[entry->m_state].m_object;
    float scaled = (float)state->m_value;
    scaled *= m_scale;
    entry->m_handle = (int)scaled;
    entry->m_ready = 1;
    return true;
}
