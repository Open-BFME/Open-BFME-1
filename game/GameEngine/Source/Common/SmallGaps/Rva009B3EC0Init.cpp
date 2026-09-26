// ?initBlocksRva009B3EC0@@YAXPAX@Z
extern int g_Rva009B3E40Arr0[];
extern int g_Rva009B3E40Arr1[];
extern int g_Rva009B3E40Arr2[];
extern int g_Rva009B3E40Arr3[];
extern void* g_Rva009B3EC0Blocks[];

void initBlocksRva009B3EC0(void* self)
{
	*(void***)((char*)self + 0x13c) = g_Rva009B3EC0Blocks;

	for (int i = 0; i < 0x40; i += 4) {
		*((char*)g_Rva009B3EC0Blocks[g_Rva009B3E40Arr0[i]] + (unsigned)self + 0x140) = (char)(i + 0);
		*((char*)g_Rva009B3EC0Blocks[g_Rva009B3E40Arr1[i]] + (unsigned)self + 0x140) = (char)(i + 1);
		*((char*)g_Rva009B3EC0Blocks[g_Rva009B3E40Arr2[i]] + (unsigned)self + 0x140) = (char)(i + 2);
		*((char*)g_Rva009B3EC0Blocks[g_Rva009B3E40Arr3[i]] + (unsigned)self + 0x140) = (char)(i + 3);
	}
}
