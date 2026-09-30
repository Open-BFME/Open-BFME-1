// cl: /MD

extern "C" __declspec(dllimport) void __cdecl fclose(void *file);

void Rva008792A0CloseFile(void *file, void **slot)
{
    fclose(file);
    *slot = 0;
}
