// cl: /DNDEBUG /MD /EHsc

struct Rva001B3F60Payload
{
	unsigned int m_first;
	unsigned int m_second;
	unsigned int m_third;
};

struct Rva001B3F60Target
{
	unsigned char m_unmodelled_000[0x178];
	Rva001B3F60Payload m_payload;
	unsigned char m_unmodelled_184[2];
	unsigned char m_enabled;

	void copy(Rva001B3F60Payload *source);
};

void Rva001B3F60Target::copy(Rva001B3F60Payload *source)
{
	m_enabled = 1;
	m_payload = *source;
}
