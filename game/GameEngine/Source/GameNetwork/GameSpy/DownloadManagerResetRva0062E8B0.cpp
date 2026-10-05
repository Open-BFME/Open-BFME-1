// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0062E8B0: clean queued downloads and resume the online flow.
class Gen00627270Owner { public: void cleanup(); };
namespace _STL { template<class T> class allocator; template<class T, class A> class list; }
class QueuedDownload;
extern _STL::list<QueuedDownload, _STL::allocator<QueuedDownload> > queuedDownloads;
extern bool mustDownloadPatch;
extern bool cantConnectBeforeOnline;
class Rva012F49B4Thing { public: char m_beforeFlag[0x259]; bool m_flagAt259; };
class BfmeAptScreenMainMenu;
extern BfmeAptScreenMainMenu *g_rva012F49B4MainMenu;
// Defined by the matched retail body at 0x0062EA60 (Rva0062EA60StartOnline.cpp).
extern void Rva0062EA60StartOnline();

void rva0062E8B0ResetOnlineDownload()
{
	reinterpret_cast<Gen00627270Owner *>(&queuedDownloads)->cleanup();
	if (!mustDownloadPatch && !cantConnectBeforeOnline)
		return Rva0062EA60StartOnline();
	Rva012F49B4Thing *state = reinterpret_cast<Rva012F49B4Thing * &>(g_rva012F49B4MainMenu);
	if (state)
		state->m_flagAt259 = false;
}
