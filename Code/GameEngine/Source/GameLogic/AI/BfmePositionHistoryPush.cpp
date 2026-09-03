// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmePositionOwner
{
	unsigned char m_pad00[0x44];
	unsigned int m_frame;
};

struct BfmePositionHistoryEntry
{
	Coord3D m_position;
	unsigned int m_frame;
};

class BfmePositionHistory
{
public:
	void bfmePushPosition(const Coord3D *position);

private:
	unsigned char m_pad00[8];
	BfmePositionOwner *m_owner;
	unsigned char m_pad0C[0x244];
	BfmePositionHistoryEntry m_entries[60];
	int m_count;
};

void BfmePositionHistory::bfmePushPosition(const Coord3D *position)
{
	int index = m_count;
	if (index == 60)
		index = 59;
	else
		m_count = index + 1;

	for (; index > 0; --index)
		m_entries[index] = m_entries[index - 1];

	m_entries[0].m_position = *position;
	m_entries[0].m_frame = m_owner->m_frame;
}
