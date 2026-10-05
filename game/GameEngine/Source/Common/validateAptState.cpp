// Clean reconstruction of the retail state check at RVA 0x00569BA0.

class BfmeAptScreenSaveLoad;
extern BfmeAptScreenSaveLoad *TheAptSaveLoad;
class BfmeAptScreenOptions;
extern BfmeAptScreenOptions *g_obj12F4AD4;
extern void __stdcall notifyState(int value);

int __stdcall validateAptState(int kind, unsigned char flag, unsigned char mode)
{
	if (kind != 0x15 || (int)flag - 1 != 0 || reinterpret_cast<int &>(TheAptSaveLoad) || reinterpret_cast<void * &>(g_obj12F4AD4))
		return 0;

	if (mode & 1)
		notifyState(0);
	return 1;
}
