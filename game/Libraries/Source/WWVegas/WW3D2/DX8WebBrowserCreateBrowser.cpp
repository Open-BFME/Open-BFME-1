// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Identity: GeneralsMD WW3D2/dx8webbrowser.cpp CreateBrowser, including
// retained browser name, factory geometry, then SetUpdateRate. Existing
// wrapper ABI spellings are preserved from WebBrowserComWrappers.cpp.
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern void __stdcall _com_issue_error(long);
namespace _com_util { unsigned short *__stdcall ConvertStringToBSTR(const char *); }
class BfmeThingVGP {
public:
 void *m_bfme00, *m_bfme04;
 long m_bfme08;
 BfmeThingVGP(const char *value) { m_bfme04=0; m_bfme08=1; m_bfme00=_com_util::ConvertStringToBSTR(value); }
 int bfmeGoVGP() throw();
};
class BfmeBstrVGP {
public:
 BfmeThingVGP *m_data;
 __declspec(noinline) BfmeBstrVGP(const char *value) { m_data=new BfmeThingVGP(value); if(!m_data) _com_issue_error(0x8007000e); }
 BfmeBstrVGP(const BfmeBstrVGP &other) throw() : m_data(other.m_data) {
  if(m_data) InterlockedIncrement(&m_data->m_bfme08);
 }
 ~BfmeBstrVGP() throw() { if(m_data) m_data->bfmeGoVGP(); }
};
class Rva00958C80 {
public:
 long invoke(BfmeBstrVGP, BfmeBstrVGP, long, long, long, long, long, long, void*);
};
class Rva00958D30 {
public:
 long invoke(BfmeBstrVGP, void*);
};
struct Rva00959410Ptr {
 Rva00958D30 *m_p;
 Rva00958D30 *operator->() const {
  if(!m_p) _com_issue_error(0x80004003);
  return m_p;
 }
 operator bool() const { return m_p != 0; }
};
extern Rva00959410Ptr Rva00959410Dispatch;
struct HWND__;
struct IDispatch;
class DX8WebBrowser {
public:
 static HWND__ *hWnd;
 static void CreateBrowser(const char*, const char*, int,int,int,int,int,long,IDispatch*);
};
void DX8WebBrowser::CreateBrowser(const char *browsername,const char *url,int x,int y,int w,int h,int updateticks,long options,IDispatch *gamedispatch) {
 if(Rva00959410Dispatch) {
  BfmeBstrVGP brsname(browsername);
  ((Rva00958C80*)Rva00959410Dispatch.operator->())->invoke(brsname,BfmeBstrVGP(url),(long)hWnd,x,y,w,h,options,gamedispatch);
  Rva00959410Dispatch->invoke(brsname,(void*)updateticks);
 }
}

