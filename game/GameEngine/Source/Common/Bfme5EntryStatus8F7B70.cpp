// Classify the leading word of each six-byte entry.
struct BfmeEntry8F7B70
{
	unsigned short m_status;
	unsigned short m_other[2];
};

class Gen_008F7B70
{
public:
	int bfmeEntryStatus(unsigned index) const;

private:
	unsigned m_reserved;
	BfmeEntry8F7B70 m_entries[1];
};

int Gen_008F7B70::bfmeEntryStatus(unsigned index) const
{
	unsigned short value = m_entries[index].m_status;
	if (value == 0xffff)
		return 2;
	return value == 0;
}
