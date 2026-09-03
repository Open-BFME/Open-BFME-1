// ?get@Rva00801900Get@@QAEHPAX@Z
// partial score=0.9 date=2026-09-03
// cl: /O2
// partial score=0.90  lea-edx vs add-ecx on owner+0x2B0; xor-eax/load vs mov eax,[0] oob

int __stdcall bfmeLookRH(void *table, void *key);

struct Rva00801900Owner
{
	char m_pad[0x2B0];
	int m_table[1];
};

struct Rva00801900Entry
{
	int m_value;
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
	Rva00801900Entry *m_entries;
	int m_count;
};

// ?get@Rva00801900Get@@QAEHPAX@Z
int Rva00801900Get::get(void *key)
{
	int index = bfmeLookRH(m_owner->m_table, key);
	if (index == -1)
		return 0;
	if (index >= m_count)
	{
		int *crash = 0;
		return *crash;
	}
	return m_entries[index].m_value;
}
