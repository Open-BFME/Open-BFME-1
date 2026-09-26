// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710E30. Store a byte into a global. cdecl (ret not ret 4).

unsigned char g_00710e30;

// ?set_00710e30@@YAXE@Z
void set_00710e30(unsigned char v)
{
	g_00710e30 = v;
}
