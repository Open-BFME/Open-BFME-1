// cl: /DNDEBUG /MD /EHsc

// Retail 0x00783D50 copies three eight-byte entries with no calls. The
// semantic owner is not proven, so this address-derived class preserves the
// verified copy shape without claiming ProductionPrerequisite ownership.
struct Rva00783D50PodCopyEntry
{
	Rva00783D50PodCopyEntry(const Rva00783D50PodCopyEntry &other)
	{
		m_first = other.m_first;
		m_second = other.m_second;
	}

	unsigned int m_first;
	unsigned int m_second;
};

class Rva00783D50PodCopy
{
public:
	Rva00783D50PodCopy();

private:
	Rva00783D50PodCopyEntry m_entries[3];
};

Rva00783D50PodCopy copyRva00783D50PodCopy(const Rva00783D50PodCopy &other)
{
	return other;
}
