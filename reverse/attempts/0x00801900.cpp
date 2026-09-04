// ?get@Rva00801900Get@@QAEHPAX@Z
// partial score=0.94 date=2026-09-04
// ?get@Rva00801900Get@@QAEHPAX@Z
// partial score=0.9 date=2026-09-03
// cl: /O2
// partial score=0.90  lea-edx vs add-ecx on owner+0x2B0; xor-eax/load vs mov eax,[0] oob

struct Rva00801900TableBase
{
	int m_table[1];
};

int __stdcall bfmeLookRH(Rva00801900TableBase &table, void *key);

struct Rva00801900Owner
{
	char m_pad[0x2B0];
	Rva00801900TableBase m_table;

	Rva00801900TableBase &table() { return m_table; }
};

struct Rva00801900Entry
{
	volatile int m_value;
	int m_pad;
};

class Rva00801900Get
{
public:
	int get(void *key);

private:
	char m_pad00[4];
	Rva00801900Owner *m_owner;
	char m_pad08[0x10];
	volatile Rva00801900Entry *m_entries;
	int m_count;
};

// ?get@Rva00801900Get@@QAEHPAX@Z
int Rva00801900Get::get(void *key)
{
	int index = bfmeLookRH(m_owner->table(), key);
	if (index == -1)
		return 0;
	if (index >= m_count)
	{
		volatile int *crash = 0;
		return *crash;
	}
	volatile Rva00801900Entry *entry = m_entries + index;
	return entry->m_value;
}
