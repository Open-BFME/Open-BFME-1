// cl: /O2
// STLport sort driver, retail 0x005154F0, 75 bytes. Same outermost layer as
// Q3IntrosortFamilies.cpp's 74-byte drivers and ScoreRowSort.cpp's 75-byte
// driver: first != last, SGI __lg depth, introsort then final-insertion.
// There is no third comparator argument -- retail reloads `first` from its
// parameter home for both dummy slots (`[esp+0xC]` / `[esp+0x20]`), which is
// why this copy is one byte longer than the ebx-cached Q3 drivers. The first
// callee is the introsort loop at 0x005150A0; the second is the already-landed
// final-insertion pass Rva00513980 at 0x00513980. Element width is four
// (`sar eax,2`). Identity is not recovered; names are address-derived.

struct Rva005154F0Elem
{
	int m_v;
};

void Gen005150A0( Rva005154F0Elem *first, Rva005154F0Elem *last,
	Rva005154F0Elem *, int depth, void *comp );
void Gen00513980( Rva005154F0Elem *first, Rva005154F0Elem *last, void *comp );

void Rva005154F0( Rva005154F0Elem *first, Rva005154F0Elem *last )
{
	if ( first != last )
	{
		int n = last - first;
		int k;
		for ( k = 0; n != 1; n >>= 1 )
			++k;
		Gen005150A0( first, last, (Rva005154F0Elem *)0, k * 2,
			*(void * volatile *)&first );
		Gen00513980( first, last, *(void * volatile *)&first );
	}
}
