// cl: /MD

__declspec(dllimport) void __cdecl bfmeFreeUXB(void *file);

void Rva008792A0CloseFile(void *file, void **slot)
{
    bfmeFreeUXB(file);
    *slot = 0;
}
