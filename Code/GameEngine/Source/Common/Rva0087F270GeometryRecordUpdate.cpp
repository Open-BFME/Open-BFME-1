// cl: /O2 /Ob2 /G6
// Open-BFME5: clean C++ conversion of the geometry-record pointer update.

struct Rva0087F270Record
{
	int m_type;
	void *m_primary;
	void *m_secondary;
	unsigned char m_unused00c[0x14];
	unsigned char m_active;
	unsigned char m_unused021[3];
};

class BfmeSubCNG
{
public:
	void bfmeOneCNG(void *value);
	void calcBoundingStuff();

private:
	unsigned char m_unused000[0x2c];
	Rva0087F270Record *m_begin;
	Rva0087F270Record *m_end;
};

void BfmeSubCNG::bfmeOneCNG(void *value)
{
	for (Rva0087F270Record *record = m_begin; record != m_end; ++record)
	{
		if (record->m_active)
		{
			if (record->m_type != 0)
			{
				if (record->m_type > 0 && record->m_type <= 2)
					record->m_primary =
						*reinterpret_cast<void * volatile *>(&value);
			}
			else
			{
				record->m_secondary =
					*reinterpret_cast<void * volatile *>(&value);
			}
		}
	}

	calcBoundingStuff();
}
