// cl: /O2 /MD

extern void w3dSmudgeManagerReleaseResources(void);

#pragma comment(linker, "/alternatename:?w3dSmudgeManagerReleaseResources@@YAXXZ=?deleteAllFonts@FontLibraryDeleteAllFontsShim@@QAEXXZ")

void j_000309cc(void)
{
	w3dSmudgeManagerReleaseResources();
}
