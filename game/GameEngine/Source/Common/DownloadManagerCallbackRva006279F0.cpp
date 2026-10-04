// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x006279F0: invoke and clear the message-box OK callback.
extern volatile bool g_Va012F70A4;
extern void (*okFunc)();

void rva006279F0InvokeCallback()
{
	void (*callback)() = okFunc;
	g_Va012F70A4 = 0;
	if (callback)
	{
		callback();
		okFunc = 0;
	}
}
