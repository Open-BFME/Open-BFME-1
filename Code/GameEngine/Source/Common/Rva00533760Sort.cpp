// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x00533760 is an STLport sort driver over twelve-byte elements.
// The two call targets match the existing introsort and final-insertion bodies.

struct Rva00533760Elem
{
	unsigned char m_bytes[12];
};

void Gen00533760Intro(void *, ...);
void Gen00533760Final(void *, ...);

void Rva00533760(Rva00533760Elem *first, Rva00533760Elem *last)
{
	if (first != last)
	{
		int n = last - first;
		int lg = 0;
		if (n != 1)
		{
			do
			{
				n >>= 1;
				++lg;
			}
			while (n != 1);
		}
		Gen00533760Intro(first, last, 0, lg + lg,
			*(Rva00533760Elem * volatile *)&first);
		Gen00533760Final(first, last, *(Rva00533760Elem * volatile *)&first);
	}
}
