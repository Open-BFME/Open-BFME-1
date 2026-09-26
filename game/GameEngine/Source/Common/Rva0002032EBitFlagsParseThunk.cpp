// ?Rva0002032EBitFlagsParseThunk@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2

// Retail keeps the four parseFromINI arguments on the caller's stack and
// enters the existing BitFlags<116> body through this five-byte tail thunk.
extern void bitFlags116Parse();
#pragma comment(linker, "/alternatename:?bitFlags116Parse@@YAXXZ=?parseFromINI@?$BitFlags@$0HE@@@SAXPAVINI@@PAX1PBX@Z")

void Rva0002032EBitFlagsParseThunk()
{
	bitFlags116Parse();
}
