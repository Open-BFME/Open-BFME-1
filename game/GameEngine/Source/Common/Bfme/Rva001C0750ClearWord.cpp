// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001C0750 (11 bytes).

struct Rva001C0750Target
{
	unsigned char m_unmodelled_000[2];
	unsigned short m_value;
};

class Rva001C0750
{
public:
	static void clear(Rva001C0750Target *target);
};

void Rva001C0750::clear(Rva001C0750Target *target)
{
	target->m_value = 0;
}
