// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0062E8B0: clean queued downloads and resume the online flow.
class Gen00627270Owner { public: void cleanup(); };
Gen00627270Owner g_rva012F7180DownloadQueue;
extern bool mustDownloadPatch;
extern bool cantConnectBeforeOnline;
class Rva012F49B4Thing { public: char m_beforeFlag[0x259]; bool m_flagAt259; };
extern Rva012F49B4Thing *g_rva012F49B4;
// Defined by the matched retail body at 0x0062EA60 (Rva0062EA60StartOnline.cpp).
extern void Rva0062EA60StartOnline();

void rva0062E8B0ResetOnlineDownload()
{
	g_rva012F7180DownloadQueue.cleanup();
	if (!mustDownloadPatch && !cantConnectBeforeOnline)
		return Rva0062EA60StartOnline();
	Rva012F49B4Thing *state = g_rva012F49B4;
	if (state)
		state->m_flagAt259 = false;
}
