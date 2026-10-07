// Clean reconstruction of the retail state check at RVA 0x00569BA0.

class BfmeAptScreenSaveLoad;
extern BfmeAptScreenSaveLoad *TheAptSaveLoad;
class BfmeAptScreenOptions;
extern BfmeAptScreenOptions *g_obj12F4AD4;
// Retail calls ILT 0xDBF2 -> 0x005693C0, matched bfmeGo985B (BfmeConv985.cpp).
extern void __stdcall bfmeGo985B(int value);

int __stdcall validateAptState(int kind, unsigned char flag, unsigned char mode)
{
	if (kind != 0x15 || (int)flag - 1 != 0 || reinterpret_cast<int &>(TheAptSaveLoad) || reinterpret_cast<void * &>(g_obj12F4AD4))
		return 0;

	if (mode & 1)
		bfmeGo985B(0);
	return 1;
}
