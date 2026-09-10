int __cdecl Rva008791E0Remove(void *key, void **out);
extern "C" __declspec(dllimport) void __cdecl free(void *memory);

void d_008794c0(int entry, int *status)
{
	if (Rva008791E0Remove((void *)entry, (void **)&entry) != 0) {
		*status = 3;
		return;
	}
	free((void *)entry);
	*status = 0;
}
