extern void d_008791e0();
extern "C" __declspec(dllimport) void __cdecl free(void *memory);

typedef int (__cdecl *D008791E0Lookup)(int key, int *value);

void d_008794c0(int entry, int *status)
{
	if (((D008791E0Lookup)d_008791e0)(entry, &entry) != 0) {
		*status = 3;
		return;
	}
	free((void *)entry);
	*status = 0;
}
