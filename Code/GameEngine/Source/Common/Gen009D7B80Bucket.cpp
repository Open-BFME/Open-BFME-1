// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the character-range bucket hash at retail RVA 0x009D7B80.
struct BfmeCharRange
{
	const char *begin;
	const char *end;
};

class Gen009D7B80
{
public:
	unsigned int bfmeBucket(const BfmeCharRange *key) const;

private:
	unsigned char m_pad[4];
	void **m_begin;
	void **m_end;
};

unsigned int Gen009D7B80::bfmeBucket(const BfmeCharRange *key) const
{
	unsigned int value = 0;
	unsigned int length = static_cast<unsigned int>(key->end - key->begin);
	unsigned int base = reinterpret_cast<unsigned int>(key->begin);
	for (unsigned int i = 0; i < length; ++i)
		value = value * 5 + *reinterpret_cast<const signed char *>(i + base);
	return value % static_cast<unsigned int>(m_end - m_begin);
}
