// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>
#define _OPERATOR_NEW_DEFINED_
#include "always.h"
#include "ref_ptr.h"
extern "C" {
__declspec(dllimport) void __stdcall AIL_set_stream_reverb_levels(void*,float,float);
__declspec(dllimport) void __stdcall AIL_stream_volume_pan(void*,float*,float*);
__declspec(dllimport) void __stdcall AIL_set_stream_volume_pan(void*,float,float);
__declspec(dllimport) void __stdcall AIL_pause_stream(void*,int);
__declspec(dllimport) long __stdcall InterlockedIncrement(volatile long*);
__declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
}
// The element payload is unused here; the native container supplies the
// independently witnessed begin/end representation for empty().
struct Rva006B2D80Entry { unsigned words[2]; };
struct Rva006B2D80Info { char pad00[0x7c]; float wet,dry; char pad84[8]; _STL::vector<Rva006B2D80Entry> entries; bool empty() const {return entries.empty();} };
struct Rva006B2D80Event { char pad00[8]; Rva006B2D80Info *info; char pad0c[0x1c]; int index; };
class Rva006B2D80Playing {
public:
    virtual ~Rva006B2D80Playing();
    volatile long refs;
    void *stream;
    char pad0c[8];
    Rva006B2D80Event *event;
    char pad18[0x10];
    float fade;
    char pad2c[0xd];
    bool flag39,flag3a,flag3b,flag3c;
    void Add_Ref() { InterlockedIncrement(&refs); }
    void Release_Ref() { if(InterlockedDecrement(&refs)<=0) delete this; }
    bool paused() const {return flag39 || flag3a || flag3b || flag3c;}
};
typedef RefCountPtr<Rva006B2D80Playing> Rva006B2D80Ref;
void gen_00698020(void **,void **);
namespace _STL {
template<> inline void _Construct<Rva006B2D80Ref,Rva006B2D80Ref>(Rva006B2D80Ref *dest,const Rva006B2D80Ref &src) { gen_00698020((void **)dest,(void **)&src); }
}
class Rva006A8210Owner { public: void dispatch(int,int); };
class Rva006AE150Argument;
class Rva006AE150Owner { public: float compute(Rva006AE150Argument *,int); };
struct Rva006B2D80Settings {char pad00[0x3c]; int fadeFrames;};
class Rva006B2D80 {
public:
    void method();
    char pad00[0xc]; Rva006B2D80Settings *settings;
    char pad10[0x623]; bool enabled;
    char pad634[0x39c]; _STL::list<Rva006B2D80Ref> active;
    char pad9d4[0xfc]; Rva006B2D80Ref saved[3];
};
// Full retail extent is 455 bytes through RET at 006B2F46.
// See identity_evidence/006b2d80-stream-restore.md.
void Rva006B2D80::method()
{
    for(int i=0;i<3;++i) {
        if(saved[i]) {
            bool found=false;
            for(_STL::list<Rva006B2D80Ref>::iterator it=active.begin();it!=active.end() && !found;++it) {
                if(it->Peek()==saved[i].Peek()) found=true;
            }
            if(!found) {
                Rva006B2D80Event *event=saved[i]->event;
                if(!event->info->empty()) ((Rva006A8210Owner *)this)->dispatch((int)&event->info,event->index);
                if(enabled) AIL_set_stream_reverb_levels(saved[i]->stream,saved[i]->event->info->dry,saved[i]->event->info->wet);
                else AIL_set_stream_reverb_levels(saved[i]->stream,1.0f,0.0f);
                float pan;
                AIL_stream_volume_pan(saved[i]->stream,0,&pan);
                Rva006B2D80Event *volumeEvent=saved[i]->event;
                float volume=((Rva006AE150Owner *)this)->compute((Rva006AE150Argument *)volumeEvent,1);
                float fade=1.0f-saved[i]->fade/(float)settings->fadeFrames;
                if(fade<0.0f)fade=0.0f;else if(fade>1.0f)fade=1.0f;
                AIL_set_stream_volume_pan(saved[i]->stream,volume*fade,pan);
                active.push_back(saved[i]);
                AIL_pause_stream(saved[i]->stream,saved[i]->paused());
            }
            saved[i].Clear();
        }
    }
}
