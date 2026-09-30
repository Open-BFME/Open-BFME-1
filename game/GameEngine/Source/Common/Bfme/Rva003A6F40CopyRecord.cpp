// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x003A6F40 (37 bytes).

extern "C" const void *bfmeVftRva003B7190Record[];
#pragma comment(linker, "/alternatename:_bfmeVftRva003B7190Record=??_7Rva003B7190Record@@6B@")

struct Rva003A6F40Record
{
	unsigned m_marker;
	unsigned m_word;
	unsigned char m_byte;
	unsigned m_tail;
};

struct Rva003A6F40
{
	static void copy(Rva003A6F40Record *target, const Rva003A6F40Record *source);
};

void Rva003A6F40::copy(Rva003A6F40Record *target, const Rva003A6F40Record *source)
{
	if (target != 0)
	{
		target->m_marker = (unsigned)bfmeVftRva003B7190Record;
		target->m_word = source->m_word;
		target->m_byte = source->m_byte;
		target->m_tail = source->m_tail;
	}
}
