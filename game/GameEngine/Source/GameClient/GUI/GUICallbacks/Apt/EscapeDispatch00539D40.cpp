// Retail 0x00539D40: escape-key dispatch by screen state.
// Address-qualified identity; offsets and switch values witnessed in retail.
class BfmeC995 { public: void bfmeGo995C(int); };
class BfmeAptScreenOnlineCustomMatch { public: void leaveStagingRoom(int); };
// Retail calls ILT 0x00015235 -> 0x004675F0, defined in BfmeLevelPathAN.cpp as
// BfmeLevelAN::bfmeBuildAN; this call names that symbol.
extern "C" void __identifier("?bfmeBuildAN@BfmeLevelAN@@QAEPADIHHHHHHH@Z")(void);
class GenActionSink
{
public:
	void add(void *a, const char *b, int c, const char *d, int e, int f, int g, int h)
	{
		typedef void (GenActionSink::*Call)(void *, const char *, int, const char *,
			int, int, int, int);
		union { void (*raw)(); Call member; } call;
		call.raw = __identifier("?bfmeBuildAN@BfmeLevelAN@@QAEPADIHHHHHHH@Z");
		(this->*call.member)(a, b, c, d, e, f, g, h);
	}
};
class WindowManager;
// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager
class EscapeDispatch00539D40 {
public:
 int dispatch(int, int, unsigned char, unsigned int);
};
int EscapeDispatch00539D40::dispatch(int unused, int message, unsigned char key, unsigned int flags)
{
 if (message != 0x15) return 0;
 switch (key) {
 case 1:
  if (flags & 1) {
   if (*(int*)((char*)this+0x1d0) <= 0) {
    switch (*(int*)((char*)this+0x188)) {
    case 10: ((BfmeC995*)this)->bfmeGo995C(0); return 1;
    case 2: return 0;
    case 3:
     ((GenActionSink*)g_theWindowManager)->add(*(void**)(*(char**)((char*)this+0x34)+0x250), "CallChild", 1, "EscapeKeyPressed",0,0,0,0);
     *(int*)((char*)this+0x188)=1;
     *((char*)this+0x1b4)=0;
     return 1;
    case 6:
    case 12: ((BfmeAptScreenOnlineCustomMatch*)this)->leaveStagingRoom(0); break;
    }
   }
   return 1;
  }
 }
 return 0;
}

