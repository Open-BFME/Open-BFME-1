// cl: /O2 /Ob1

struct Rva001C3A00Entry { char m_body[0x5c]; };

struct Rva001C3A00Vector
{
	Rva001C3A00Entry *m_begin;
	Rva001C3A00Entry *m_end;

	int size() const { return m_end - m_begin; }
	Rva001C3A00Entry *begin() const { return m_begin; }
};

struct Rva001C3A00Owner
{
	char m_pad[0xac];
	Rva001C3A00Entry m_default;
	char m_pad2[0x10c - 0xac - 0x5c];
	Rva001C3A00Vector *m_entries;

	Rva001C3A00Entry *getEntryOrDefault(int index);
};

Rva001C3A00Entry *Rva001C3A00Owner::getEntryOrDefault(int index)
{
	if (index >= 0)
	{
		if ((unsigned int)index < (unsigned int)m_entries->size())
			return m_entries->begin() + index;
	}
	return &m_default;
}
