// cl: /DNDEBUG /MD /O2
// Address-derived record accessor at retail 0x003A7460 (94 bytes).

struct Rva003A7460Mission
{
	unsigned char m_bytes[0xDC];
};

struct Rva003A7460MissionRange
{
	Rva003A7460Mission *m_begin;
	Rva003A7460Mission *m_end;

	__forceinline unsigned int size() const
	{
		return m_end - m_begin;
	}

	__forceinline Rva003A7460Mission *operator[](unsigned int index) const
	{
		return m_begin + index;
	}
};

class Rva003A7460Owner
{
public:
	Rva003A7460Mission *getCurrentMission() const;

private:
	unsigned char m_pad[0x08];
	int m_index;
	Rva003A7460MissionRange m_missions;
};

Rva003A7460Mission *Rva003A7460Owner::getCurrentMission() const
{
	int index = m_index;
	if (index >= 0 && static_cast<unsigned int>(index) < m_missions.size())
		return m_missions[index];
	return m_missions[m_missions.size() - 1];
}
