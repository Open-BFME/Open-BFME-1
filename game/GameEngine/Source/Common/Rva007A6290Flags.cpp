// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

unsigned int g_rva007A6290Flags;

int __cdecl rva007A6290Has(unsigned int mask)
{
	return (g_rva007A6290Flags & mask) == mask;
}

void __cdecl rva007A62B0Clear(unsigned int mask)
{
	g_rva007A6290Flags &= ~mask;
}
