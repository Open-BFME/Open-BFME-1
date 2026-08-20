// cl: /DNDEBUG /MD /EHsc

// Retail 0x006FC8D0. Store a byte into a global. cdecl (ret not ret 4).

unsigned char g_006fc8d0;

// ?set_006fc8d0@@YAXE@Z
void set_006fc8d0(unsigned char v)
{
	g_006fc8d0 = v;
}
