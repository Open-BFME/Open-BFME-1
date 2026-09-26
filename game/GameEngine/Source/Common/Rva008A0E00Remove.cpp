// ?remove@Rva008A0E00Owner@@QAEHPAX@Z
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008A0E00 scans 128 sixteen-byte records.  Each record has four
// dwords, and the first dword owns a value released through virtual slot 1.
// The address-derived owner name reflects the lack of a named retail caller.

class Rva008A0E00Value
{
public:
	virtual void slot0();
	virtual void release();
};

struct Rva008A0E00Record
{
	Rva008A0E00Value *m_value;
	void *m_field1;
	void *m_field2;
	void *m_field3;
};

class Rva008A0E00Owner
{
public:
	int remove(void *key);

private:
	int m_count;
	Rva008A0E00Record m_records[128];
};

int Rva008A0E00Owner::remove(void *key)
{
	int index = 0;
	void **field = &m_records[0].m_field1;

	for (; index < 0x200; index += 4, field += 4)
	{
		if (field[-1] == key)
			goto found;
		if (field[0] == key)
		{
			++index;
			goto found;
		}
		if (field[1] == key)
		{
			index += 2;
			goto found;
		}
		if (field[2] == key)
		{
			index += 3;
			goto found;
		}
	}

	return 0;

found:
	if (index >= 0x200)
		return 0;

	--m_count;
	Rva008A0E00Record *record = (Rva008A0E00Record *)((char *)m_records + index * 4);
	record->m_value->release();
	record->m_value = 0;
	return 1;
}
