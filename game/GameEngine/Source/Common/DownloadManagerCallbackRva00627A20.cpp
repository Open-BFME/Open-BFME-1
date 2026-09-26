// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00627A20: invoke and clear the second download-completion callback.
extern unsigned char g_rva006279F0CallbackActive;
void (*g_rva00627A20Callback)();

void rva00627A20InvokeCallback()
{
	void (*callback)() = g_rva00627A20Callback;
	g_rva006279F0CallbackActive = 0;
	if (callback)
	{
		callback();
		g_rva00627A20Callback = 0;
	}
}
