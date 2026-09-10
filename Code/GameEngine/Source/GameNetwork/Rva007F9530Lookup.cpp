// cl: /O2 /GX- /GS-
// Retail 0x007F9530 is the FESL transactor's thiscall record lookup.  The
// same layout is reused by the adjacent slot allocator caller.

struct Rva007F9A40Key
{
	const char *m_a;
	const char *m_b;
	int m_c;

	bool matches(const Rva007F9A40Key *other) const;
};

struct Rva007F96C0Rec
{
	char m_active;
	char m_pad[3];
	Rva007F9A40Key m_key;
	void *m_10;
	void *m_14;
};

class Rva007FA2C0
{
public:
	Rva007F96C0Rec *lookup(void *rawKey);

private:
	char m_pad00[0x10];
	int m_count;
	char m_pad14[0x394];
	Rva007F96C0Rec m_records[0x20];
};

Rva007F96C0Rec *Rva007FA2C0::lookup(void *rawKey)
{
	Rva007F9A40Key *key = (Rva007F9A40Key *)rawKey;
	int index = 0;
	Rva007F96C0Rec *record = key != 0 ? m_records : 0;
	while (key != 0 && index < m_count)
	{
		if (record->m_active != 0 && key->matches(&record->m_key))
			return record;
		++index;
		++record;
	}
	return 0;
}
