// cl: /DNDEBUG /MD /EHs-c-
// AVIFIL32.dll import stubs: six-byte FF 25 [IAT] thunks.

extern "C" __declspec(dllimport) int __stdcall AVIFileReadDataIat(void *pf, unsigned long ckid, void *lp, long *lpread);
extern "C" __declspec(dllimport) int __stdcall AVIMakeCompressedStreamIat(void **pps, void *pas, void *opt, void *clsid);
extern "C" __declspec(dllimport) int __stdcall AVIFileCreateStreamAIat(void *pfile, void **ppavi, void *psi);
extern "C" __declspec(dllimport) int __stdcall AVIFileOpenIat(void **ppfile, const char *szFile, unsigned int mode, void *clsid);
extern "C" __declspec(dllimport) void __stdcall AVIFileInitIat(void);

extern "C" int __stdcall AVIFileReadData(void *pf, unsigned long ckid, void *lp, long *lpread)
{
	return AVIFileReadDataIat(pf, ckid, lp, lpread);
}

extern "C" int __stdcall AVIMakeCompressedStream(void **pps, void *pas, void *opt, void *clsid)
{
	return AVIMakeCompressedStreamIat(pps, pas, opt, clsid);
}

extern "C" int __stdcall AVIFileCreateStreamA(void *pfile, void **ppavi, void *psi)
{
	return AVIFileCreateStreamAIat(pfile, ppavi, psi);
}

extern "C" int __stdcall AVIFileOpen(void **ppfile, const char *szFile, unsigned int mode, void *clsid)
{
	return AVIFileOpenIat(ppfile, szFile, mode, clsid);
}

extern "C" void __stdcall AVIFileInit(void)
{
	AVIFileInitIat();
}
