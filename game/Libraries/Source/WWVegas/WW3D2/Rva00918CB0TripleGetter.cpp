// cl: /O2 /Ob0

struct Rva00918CB0Triple
{
	unsigned words[3];
};
class Rva00918CB0TripleGetter
{
	unsigned char m_prefix[0x110];
	Rva00918CB0Triple m_value;
public:
	void get(Rva00918CB0Triple *out) const;
};
void Rva00918CB0TripleGetter::get(Rva00918CB0Triple *out) const
{
	out->words[0] = m_value.words[0];
	out->words[1] = m_value.words[1];
	out->words[2] = m_value.words[2];
}
