// Retail 0x00539D40: escape-key dispatch by screen state.
// Address-qualified identity; offsets and switch values witnessed in retail.
class BfmeC995 { public: void bfmeGo995C(int); };
class BfmeAptScreenOnlineCustomMatch { public: void leaveStagingRoom(int); };
class GenActionSink { public: void add(void*, const char*, int, const char*, int,int,int,int); };
class WindowManager;
extern WindowManager *g_theWindowManager;
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

