// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F9FD0. Store a byte into a global. cdecl (ret not ret 4).

unsigned char g_006f9fd0;

// ?set_006f9fd0@@YAXE@Z
void set_006f9fd0(unsigned char v)
{
	g_006f9fd0 = v;
}
