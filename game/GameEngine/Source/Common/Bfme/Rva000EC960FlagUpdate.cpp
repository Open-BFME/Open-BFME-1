// cl: /DNDEBUG /MD /EHsc

struct Rva000EC960FlagUpdate
{
	unsigned char m_unmodelled_000[0xe6];
	unsigned char m_ready;
	unsigned char m_enabled;

	void update(unsigned char enabled);
};

void Rva000EC960FlagUpdate::update(unsigned char enabled)
{
	m_enabled = enabled;
	if (enabled != 0)
		m_ready = 1;
}
