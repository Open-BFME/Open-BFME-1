// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00627A20: invoke and clear the message-box Cancel callback.
extern volatile bool g_Va012F70A4;
extern void (*cancelFunc)();

void rva00627A20InvokeCallback()
{
	void (*callback)() = cancelFunc;
	g_Va012F70A4 = 0;
	if (callback)
	{
		callback();
		cancelFunc = 0;
	}
}
