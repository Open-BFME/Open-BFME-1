// cl: /DNDEBUG /MD /EHsc
// BFME stores only the string, address, and next pointer in EnumeratedIP; the
// released Zero Hour declaration adds a MemoryPoolObject word not present in
// the retail BFME layout.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	AsciiString &operator=(const char *text)
	{
		set(text, 0);
		return *this;
	}
	void set(const char *text, int length);

private:
	void *m_data;
};

class EnumeratedIP
{
public:
	EnumeratedIP();

private:
	AsciiString m_IPstring;
	unsigned int m_IP;
	EnumeratedIP *m_next;
};

EnumeratedIP::EnumeratedIP()
{
	m_IPstring = "";
	m_next = 0;
	m_IP = 0;
}
