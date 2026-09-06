// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Structural BFME recovery, retail 0x000F95C0 (71 bytes).

struct Rva000F95C0Record
{
	unsigned char m_pad00[0x34];
	int m_value34;
	unsigned char m_pad38[4];
	int m_key3c;
};

class AsciiStringBN
{
};

class BfmeOtherBN
{
public:
	void *bfmeLookupBN(const AsciiStringBN &name);
};

class BfmeUseB980
{
public:
	void *bfmeApply980B(int first, int second);
};

extern BfmeOtherBN * volatile g_bfmeOtherBN;

class Rva000F95C0
{
public:
	void *lookup(int key);

private:
	unsigned m_pad00;
	Rva000F95C0Record *m_begin;
	Rva000F95C0Record *m_end;
	unsigned m_pad0c;
	void *m_value10;
};

void *Rva000F95C0::lookup(int key)
{
	Rva000F95C0Record *record = m_begin;
	while (record != m_end)
	{
		if (record->m_key3c == key)
		{
			int value = (int)m_value10;
			BfmeUseB980 *use = static_cast<BfmeUseB980 *>(
				g_bfmeOtherBN->bfmeLookupBN(
					*reinterpret_cast<const AsciiStringBN *>(record)));
			if (!use)
				return 0;
			return use->bfmeApply980B(value, record->m_value34);
		}
		record = reinterpret_cast<Rva000F95C0Record *>(
			reinterpret_cast<unsigned char *>(record) + 0x60);
	}
	return 0;
}
