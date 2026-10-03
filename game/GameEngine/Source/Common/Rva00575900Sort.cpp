// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x00575900 is an STLport sort driver over twelve-byte elements,
// a twin of Rva00533650 (0x00533650) and Rva00533760 (0x00533760). The two
// call targets are the S4SortElem12/S4Cmp00574DF0 introsort and
// final-insertion bodies matched at 0x00575320 and 0x00574DF0, through this
// driver's own ILT thunks at 0x0001D241 and 0x000498CD.

struct Rva00575900Elem
{
	unsigned char m_bytes[12];
};

void j_0001d241(void);
void j_000498cd(void);

void Rva00575900(Rva00575900Elem *first, Rva00575900Elem *last)
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
			j_0001d241)(first, last, 0, lg + lg,
			*(Rva00575900Elem * volatile *)&first);
		reinterpret_cast<void (__cdecl *)(void *, void *, void *)>(
			j_000498cd)(first, last, *(Rva00575900Elem * volatile *)&first);
	}
}
