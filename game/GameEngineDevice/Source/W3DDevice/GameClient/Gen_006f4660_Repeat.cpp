// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F4660. helper(a, a, a, a).

void d_0093eb50();

// ?wrap_006f4660@@YGXH@Z
void __stdcall wrap_006f4660(int a)
{
	reinterpret_cast<void (__stdcall *)(int, int, int, int)>(
		d_0093eb50)(a, a, a, a);
}
