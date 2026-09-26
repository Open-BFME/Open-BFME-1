// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x007416E0 (47 bytes).

struct Rva007416E0Record
{
	unsigned m_word0;
	unsigned m_word1;
	unsigned m_word2;
	unsigned m_word3;
	unsigned m_word4;
	unsigned char m_byte;
};

struct Rva007416E0
{
	static void copy(Rva007416E0Record *target, const Rva007416E0Record *source);
};

void Rva007416E0::copy(Rva007416E0Record *target, const Rva007416E0Record *source)
{
	if (target != 0)
	{
		target->m_word0 = source->m_word0;
		target->m_word1 = source->m_word1;
		target->m_word2 = source->m_word2;
		target->m_word3 = source->m_word3;
		target->m_word4 = source->m_word4;
		target->m_byte = source->m_byte;
	}
}
