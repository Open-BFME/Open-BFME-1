// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

void b_00042a50();

unsigned char g_rva00627A50Flag;
void *g_rva00627A50A;
void *g_rva00627A50B;

void rva00627A50Clear()
{
	if (g_rva00627A50Flag)
	{
		b_00042a50();
		g_rva00627A50Flag = 0;
	}
	if (g_rva00627A50A)
		g_rva00627A50A = 0;
	if (g_rva00627A50B)
		g_rva00627A50B = 0;
}
