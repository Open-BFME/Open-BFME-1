// Clean reconstruction of the retail state check at RVA 0x00569BA0.

extern int g_Va012F4B44;
extern void *g_quitMenuLayout;
extern void __stdcall notifyState(int value);

int __stdcall validateAptState(int kind, unsigned char flag, unsigned char mode)
{
	if (kind != 0x15 || (int)flag - 1 != 0 || g_Va012F4B44 || g_quitMenuLayout)
		return 0;

	if (mode & 1)
		notifyState(0);
	return 1;
}
