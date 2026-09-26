// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived thirty-six-byte entry accessor at 0x000CD7D0.

struct Rva000CD7D0Entry
{
	unsigned int m_words[9];
};

struct Rva000CD7D0Object
{
	unsigned char m_prefix[0x2c4];
	Rva000CD7D0Entry *m_entries;

	Rva000CD7D0Entry *entryAt(int index) const;
};

Rva000CD7D0Entry *Rva000CD7D0Object::entryAt(int index) const
{
	return &m_entries[index];
}
