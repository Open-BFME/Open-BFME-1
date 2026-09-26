// cl: /DNDEBUG /MD
// Retail 0x007AED00: update two entry-relative offsets when their bases are nonzero.

struct Rva007AED00Entry
{
	char m_padding[0x58];
	float m_firstBase;
	float m_secondBase;
	char m_padding2[0x0C];
	float m_firstOffset;
	float m_secondOffset;
};

class Rva007AED00Table
{
private:
	char m_padding[0x58];
	Rva007AED00Entry *m_entries[1];

public:
	void updateOffsets( int index, float first, float second );
};

void Rva007AED00Table::updateOffsets( int index, float first, float second )
{
	Rva007AED00Entry *entry = m_entries[index];
	if ( entry == 0 )
		return;

	if ( entry->m_firstBase == 0.0f )
		entry->m_firstOffset = 0.0f;
	else
		entry->m_firstOffset = first / entry->m_firstBase;

	if ( entry->m_secondBase == 0.0f )
		entry->m_secondOffset = 0.0f;
	else
		entry->m_secondOffset = second / entry->m_secondBase;
}
