// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x00533650 is an STLport sort driver over twelve-byte elements,
// a twin of Rva00533760 (0x00533760) and Rva00575900 (0x00575900). The two
// call targets are the S4SortElem12/S4Cmp00531FA0 introsort and
// final-insertion bodies already matched at 0x005331E0 and 0x00531FA0
// through the ILT thunks at 0x00025B03 and 0x0000C71B.

struct Rva00533650Elem
{
	unsigned char m_bytes[12];
};

void Gen00533650Intro(void *, ...);
void Gen00533650Final(void *, ...);

void Rva00533650(Rva00533650Elem *first, Rva00533650Elem *last)
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
		Gen00533650Intro(first, last, 0, lg + lg,
			*(Rva00533650Elem * volatile *)&first);
		Gen00533650Final(first, last, *(Rva00533650Elem * volatile *)&first);
	}
}
