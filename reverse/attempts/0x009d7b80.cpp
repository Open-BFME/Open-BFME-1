// ?d_009d7b80@@YAXXZ
// partial score=0.982 date=2026-08-27
// cl: /DNDEBUG /MD /O2
struct BfmeCharRange { const char *begin; const char *end; };
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
	for (unsigned int i = 0; i < length; ++i)
		value = value * 5 + static_cast<signed char>(i[key->begin]);
	return value % static_cast<unsigned int>(m_end - m_begin);
}
