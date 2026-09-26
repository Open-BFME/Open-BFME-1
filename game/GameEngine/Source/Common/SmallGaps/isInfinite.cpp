// ?isInfinite@@YAHN@Z
extern "C" __declspec(dllimport) int __cdecl _fpclass(double);
int isInfinite(double x)
{
	int c = _fpclass(x);
	if (c == 4 || c == 0x200)
		return 1;
	return 0;
}
