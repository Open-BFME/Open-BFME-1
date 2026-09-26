// cl: /DNDEBUG /MD /EHsc

class AsciiString;

class Rva000F72B0AsciiHash
{
public:
	int find(const AsciiString &key);
};

class Rva000F72B0AsciiHashOwner
{
public:
	unsigned char contains(const AsciiString &key);

private:
	unsigned char m_unmodelled_000[0x1c];
	Rva000F72B0AsciiHash m_values;
};

unsigned char Rva000F72B0AsciiHashOwner::contains(const AsciiString &key)
{
	return m_values.find(key) != 0;
}
