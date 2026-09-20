// ?Rva00351830IndexedListMark@Rva00351830Holder@@QAEXXZ
// partial score=0.99 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc

struct Rva00351830Record
{
	int m_next;
	int m_value04;
	int m_value08;
	unsigned char m_marked;
	unsigned char m_padding0D[ 7 ];
};

class Rva00351830Holder
{
public:
	void mark();

private:
	unsigned char m_padding00[ 0x0C ];
	unsigned int m_records;
	unsigned char m_padding10[ 0x0C ];
	int m_index;
};

void Rva00351830Holder::mark()
{
	int index = m_index;
	if (index != -1)
	{
		do
		{
			index *= 20;
			*reinterpret_cast<unsigned char *>(index + m_records + 0x0C) = 1;
			index = *reinterpret_cast<int *>(index + m_records);
		} while (index != -1);
	}
}
