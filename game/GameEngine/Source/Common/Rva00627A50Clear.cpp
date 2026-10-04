// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail's callee here is the five-byte ILT thunk at 0x00042A50, which
// tail-jumps to the body; the thunk is what defines that address, so name it.
void j_00042a50();

extern volatile bool g_Va012F70A4;
extern void (*okFunc)();
extern void (*cancelFunc)();

void rva00627A50Clear()
{
	if (g_Va012F70A4)
	{
		j_00042a50();
		g_Va012F70A4 = 0;
	}
	if (okFunc)
		okFunc = 0;
	if (cancelFunc)
		cancelFunc = 0;
}
