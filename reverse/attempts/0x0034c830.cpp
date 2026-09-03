// ?find@Rva0034C830Buckets@@QAE_NHH_N@Z
// partial score=0.8 date=2026-09-02
// cl: /DNDEBUG /MD /O2
// Search one of 32 pointer-range buckets (12 bytes each at +0x17474).  On a
// hit, optionally hand the slot to a helper and return true.

void __stdcall rva0034C830Erase(int *slot);

struct Rva0034C830Bucket
{
	int *m_begin;
	int *m_end;
	int *m_unused;
};

class Rva0034C830Buckets
{
public:
	bool find(int index, int key, bool erase);

private:
	char m_pad[0x17474];
	Rva0034C830Bucket m_buckets[32];
};

// ?find@Rva0034C830Buckets@@QAE_NHH_N@Z
bool Rva0034C830Buckets::find(int index, int key, bool erase)
{
	if (index < 0 || index >= 0x20)
		return false;

	unsigned int scaled = (unsigned int)index * 3;
	int *end = *(int **)((char *)this + scaled * 4 + 0x17478);
	int *slot = *(int **)((char *)this + scaled * 4 + 0x17474);
	if (slot != end)
	{
		int want = key;
		do
		{
			if (*slot == want)
			{
				if (erase)
					rva0034C830Erase(slot);
				return true;
			}
			++slot;
		}
		while (slot != end);
	}
	return false;
}
