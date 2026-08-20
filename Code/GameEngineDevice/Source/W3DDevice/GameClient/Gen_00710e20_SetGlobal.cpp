// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710E20. Store a byte into a global. cdecl (ret not ret 4).

unsigned char g_00710e20;

// ?set_00710e20@@YAXE@Z
void set_00710e20(unsigned char v)
{
	g_00710e20 = v;
}
