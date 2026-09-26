// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F4660. helper(a, a, a, a).

void __stdcall helper_006f4660(int, int, int, int);

// ?wrap_006f4660@@YGXH@Z
void __stdcall wrap_006f4660(int a)
{
	helper_006f4660(a, a, a, a);
}
