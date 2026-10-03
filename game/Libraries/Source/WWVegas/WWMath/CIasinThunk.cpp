// Retail 0x009F7D86: the six-byte `jmp dword ptr [IAT]` thunk the CRT's
// incremental-link helper sits behind. Retail imports `_CIasin` by that exact
// name from MSVCR71.dll (IAT 0x01359234, see targets/game/reverse/imports.csv),
// so the thunk jumps through `__imp__CIasin`; a private spelling would name an
// import slot nothing defines.
extern "C" __declspec(dllimport) void __cdecl _CIasin(void);

extern "C" void __CIasin(void)
{
	_CIasin();
}