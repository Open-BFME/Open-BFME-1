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

void j_00025b03(void);
void j_0000c71b(void);

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
		reinterpret_cast<void (__cdecl *)(void *, void *, int, int, void *)>(
			j_00025b03)(first, last, 0, lg + lg,
			*(Rva00533650Elem * volatile *)&first);
		reinterpret_cast<void (__cdecl *)(void *, void *, void *)>(
			j_0000c71b)(first, last, *(Rva00533650Elem * volatile *)&first);
	}
}
