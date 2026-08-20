// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710E10. Store a byte into a global. cdecl (ret not ret 4).

unsigned char g_00710e10;

// ?set_00710e10@@YAXE@Z
void set_00710e10(unsigned char v)
{
	g_00710e10 = v;
}
