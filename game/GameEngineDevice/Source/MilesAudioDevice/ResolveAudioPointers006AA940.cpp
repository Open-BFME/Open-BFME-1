// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <map>
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void*,unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void*);
class Guard006AA940 { void *handle; char owned; public:
    Guard006AA940(void *h) { owned=0; handle=h; if(WaitForSingleObject(h,~0u)!=0x102) owned=1; }
    ~Guard006AA940() { if(owned) { ReleaseMutex(handle); owned=0; } }
};
class BfmeEntryCN;
BfmeEntryCN *__cdecl bfmeLookup(void*);
struct XferException { char *text; int tag; };
extern "C" XferException *__cdecl bfmeFormatText(XferException*,int,const char*,...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void*,void*);
extern int g_guardTargetTypeThrowInfo;
struct Pair006AA940 : _STL::pair<void*,float> {};
struct Word006AA940 { int value; };
class ResolveAudioPointers006AA940 {
public:
    void resolve();
    char pad0[0x62f]; bool byte_62f;
    char pad630[0x954-0x630]; void *mutex_954;
    char pad958[0xad4-0x958];
    _STL::vector<Pair006AA940> vector_ad4,vector_ae0;
    _STL::map<int,Word006AA940> tree_aec;
};
void ResolveAudioPointers006AA940::resolve() {
    void *handle=mutex_954; Guard006AA940 guard(handle);
    byte_62f=false;
    vector_ad4.clear();
    vector_ad4.reserve(vector_ae0.size());
    for(Pair006AA940 *p=vector_ae0.begin();p!=vector_ae0.end();++p) {
        Pair006AA940 value; value.second=p->second; value.first=bfmeLookup(p->first);
        if(!value.first) {
            XferException error; bfmeFormatText(&error,5,0);
            _CxxThrowException(&error,&g_guardTargetTypeThrowInfo);
        }
        vector_ad4.push_back(value);
    }
    vector_ae0.clear();
    tree_aec.clear();
}


