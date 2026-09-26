// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x006279F0: invoke and clear the first download-completion callback.
unsigned char g_rva006279F0CallbackActive;
void (*g_rva006279F0Callback)();

void rva006279F0InvokeCallback()
{
	void (*callback)() = g_rva006279F0Callback;
	g_rva006279F0CallbackActive = 0;
	if (callback)
	{
		callback();
		g_rva006279F0Callback = 0;
	}
}
