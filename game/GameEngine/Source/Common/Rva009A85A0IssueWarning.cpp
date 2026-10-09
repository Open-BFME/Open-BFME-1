// cl: /O2 /G6 /MD
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void *, const char *, const char *, unsigned int);

// ?Rva009A85A0IssueWarning@@YAXPBD@Z
// Ported from Open BFME 2 Code/Libraries/Source/VP6/system.cpp.
void __cdecl Rva009A85A0IssueWarning(const char *message)
{
    MessageBoxA(0, message, 0, 0x2030);
}
