struct Rva0093C9A0Src
{
	unsigned short m_half;
	char m_gap[2];
	int m_word;
};
class Rva0093C9A0Box
{
public:
	Rva0093C9A0Box *copyFrom(const Rva0093C9A0Src *a, const int *b);
	unsigned short m_half;
	char m_gap[2];
	int m_word;
};
// mov eax,ecx / halfword copy / word copy off the second pointer.
Rva0093C9A0Box *Rva0093C9A0Box::copyFrom(const Rva0093C9A0Src *a, const int *b)
{
	m_half = a->m_half;
	m_word = *b;
	return this;
}
