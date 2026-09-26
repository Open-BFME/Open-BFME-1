// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0062E8B0: clean queued downloads and resume the online flow.
class Gen00627270Owner { public: void cleanup(); };
Gen00627270Owner g_rva012F7180DownloadQueue;
extern unsigned char g_rva012F716C;
extern unsigned char g_rva012F716D;
class Rva012F49B4Thing { public: char m_beforeFlag[0x259]; bool m_flagAt259; };
extern Rva012F49B4Thing *g_rva012F49B4;
void bfmeStartOnline();

void rva0062E8B0ResetOnlineDownload()
{
	g_rva012F7180DownloadQueue.cleanup();
	if (!g_rva012F716C && !g_rva012F716D)
		return bfmeStartOnline();
	Rva012F49B4Thing *state = g_rva012F49B4;
	if (state)
		state->m_flagAt259 = false;
}
