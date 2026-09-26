// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x000F9730 (54 bytes).
// Retail scans 0x60-byte records, matches key +0x3C, and marks two fields -1.

struct Rva000F9730Record
{
	unsigned char m_unmodelled_000[0x30];
	int m_marker;
	unsigned char m_unmodelled_034[8];
	unsigned m_key;
};

class Rva000F9730
{
public:
	bool markKey(unsigned key);

private:
	unsigned m_unmodelled_000;
	Rva000F9730Record *m_begin;
	Rva000F9730Record *m_end;
};

bool Rva000F9730::markKey(unsigned key)
{
	for (Rva000F9730Record *record = m_begin; record != m_end;
		record = reinterpret_cast<Rva000F9730Record *>(
			reinterpret_cast<unsigned char *>(record) + 0x60))
	{
		if (record->m_key == key)
		{
			if (record->m_marker == -1)
				return false;
			record->m_marker = -1;
			record->m_key = static_cast<unsigned>(-1);
			return true;
		}
	}
	return false;
}
