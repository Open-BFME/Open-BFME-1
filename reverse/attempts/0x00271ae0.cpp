// ?count@Rva00271AE0Owner@@QAEHXZ
// partial score=0.96 date=2026-09-03
// cl: /DNDEBUG /MD

class Rva00271AE0Named
{
public:
	virtual void bfmeAnchor(void);

	int getID(void) const { return m_id; }

	int m_id;
};

class Rva00271AE0Host
{
public:
	char m_pad00[0x1c];
	Rva00271AE0Named *m_fallback;
	char m_pad20[0x44 - 0x20];
	char *m_begin;
	char *m_end;
	char m_pad4c[0x58 - 0x4c];
	Rva00271AE0Named *m_primary;
};

class Rva00271AE0Owner
{
public:
	int count(void);

private:
	char m_pad00[0x30];
	Rva00271AE0Host *m_host;
};

// ?count@Rva00271AE0Owner@@QAEHXZ
int Rva00271AE0Owner::count(void)
{
	int id = m_host->m_primary != 0
		? m_host->m_primary->getID() : 0xF423F;
	if (id == 0xF423F)
	{
		id = m_host->m_fallback != 0
			? m_host->m_fallback->getID() : 0xF423F;
	}
	if (id != 6)
		return 0;
	return (m_host->m_end - m_host->m_begin) / 6;
}
