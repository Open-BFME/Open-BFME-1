// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
struct Rva006990E0Kind
{
	unsigned char m_pad0[0x3c];
	unsigned char m_flag;
	unsigned char m_pad3d[0x84 - 0x3d];
	unsigned int m_kind;
};

struct Rva006990E0Request
{
	unsigned char m_pad0[8];
	Rva006990E0Kind *m_kind;
	unsigned char m_pad0c[0x68 - 0xc];
	int m_value;
};

static __declspec(noinline) int streamLoopCount006990E0(Rva006990E0Request *request)
{
	Rva006990E0Kind *kind = request->m_kind;
	if (kind == 0)
		return 1;

	switch (kind->m_kind)
	{
	case 0:
		{
			int value = request->m_value;
			if (value == -1)
				goto full;
			if (value >= 1)
				return value;
			return 1;
		}
	case 1:
	case 4:
		return (kind->m_flag & 1) ? 1000000 : 1;
	case 3:
full:
		return 1000000;
	default:
		return 1;
	}
}

extern "C" {
__declspec(dllimport) void __stdcall AIL_lock_mutex();
__declspec(dllimport) void __stdcall AIL_unlock_mutex();
__declspec(dllimport) void __stdcall AIL_set_stream_loop_count(void*,int);
__declspec(dllimport) void* __stdcall AIL_register_stream_callback(void*,void (__stdcall *)(void*));
__declspec(dllimport) void __stdcall AIL_set_stream_reverb_levels(void*,float,float);
__declspec(dllimport) void __stdcall AIL_stream_ms_position(void*,int*,int*);
__declspec(dllimport) void __stdcall AIL_set_stream_ms_position(void*,int);
__declspec(dllimport) void __stdcall AIL_pause_stream(void*,int);
__declspec(dllimport) long __stdcall InterlockedIncrement(volatile long*);
__declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
}
extern void j_0003429d();
extern void j_000071b7();
extern void j_0000b60e();
int GetGameClientRandomValue(int,int,char*,int);
class Rva006A8210Owner { public: void dispatch(int,int); };
class Gen_006AC5D0 { public: void bfmePush(void*); };
struct Info006AE2C0 { char pad0[0x3c]; unsigned flags_3c; char pad40[0x7c-0x40]; float float_7c,float_80; int type_84; char pad88[4]; void *begin_8c,*end_90; };
struct Event006AE2C0 { char pad0[8]; Info006AE2C0 *info; char padc[0x28-0xc]; int index_28; char pad2c[0x64-0x2c]; int index_64; int int_68; };
class PlayingAudio { public:
    virtual ~PlayingAudio(); long count_4; void *handle_8; char padc[8]; Event006AE2C0 *event_14; char pad18[0x39-0x18]; bool byte_39,byte_3a,byte_3b,byte_3c;
    bool paused() const { return byte_39 || byte_3a || byte_3b || byte_3c; }
};
class Ref006AE2C0 { public:
    PlayingAudio *ptr;
    Ref006AE2C0(const Ref006AE2C0& r):ptr(r.ptr) { if(ptr) InterlockedIncrement(&ptr->count_4); }
    ~Ref006AE2C0() { if(ptr && InterlockedDecrement(&ptr->count_4)<=0) delete ptr; }
};
struct BfmeHashValue { unsigned key; PlayingAudio *value; };
struct BfmeInsertResultE { void *node,*table; bool inserted; };
class Gen_006A0D50 { public: BfmeInsertResultE bfmeInsertUnique(const BfmeHashValue*); };
struct Table006AE2C0 { char data[0x10]; unsigned count;
    void insert(const BfmeHashValue &entry) { resize(count+1); ((Gen_006A0D50*)this)->bfmeInsertUnique(&entry); }
    void resize(unsigned n) {
        typedef void (Table006AE2C0::*Fn)(unsigned);
        union { void (__cdecl *raw)(); Fn member; } call;
        call.raw=j_000071b7; (this->*call.member)(n);
    }
};
class MilesLock006AE2C0 { bool locked; public:
    MilesLock006AE2C0() { AIL_lock_mutex(); locked=true; }
    ~MilesLock006AE2C0() { if(locked) AIL_unlock_mutex(); }
};
class StartAudioStream006AE2C0 { public:
    void start(const Ref006AE2C0&,float);
    char pad0[0x604]; int index_604; char pad608[0x633-0x608]; bool byte_633;
    char pad634[0x9d0-0x634]; _STL::list<Ref006AE2C0> list_9d0;
    char pad9d4[0xac4-0x9d4]; int indices_ac4[3]; Ref006AE2C0 refs_ad0[3];
    char padadc[0xb30-0xadc]; Table006AE2C0 table_b30;
};
void StartAudioStream006AE2C0::start(const Ref006AE2C0 &ref,float fraction) {
    Event006AE2C0 *&event=ref.ptr->event_14;
    void *stream=ref.ptr->handle_8;
    Info006AE2C0 *&info=event->info;
    {
        MilesLock006AE2C0 lock;
        BfmeHashValue entry={(unsigned)stream,ref.ptr};
        table_b30.insert(entry);
    }
    AIL_set_stream_loop_count(stream,streamLoopCount006990E0((Rva006990E0Request*)event));
    AIL_register_stream_callback(stream,(void (__stdcall *)(void*))j_0003429d);
    if(byte_633) AIL_set_stream_reverb_levels(ref.ptr->handle_8,ref.ptr->event_14->info->float_80,ref.ptr->event_14->info->float_7c);
    else AIL_set_stream_reverb_levels(ref.ptr->handle_8,1.0f,0.0f);
    int position;
    if(fraction>=0.0f && fraction<=1.0f) {
        int length=-1; AIL_stream_ms_position(stream,&length,0);
        position=(int)(length*fraction);
        if(length-position<6000) { position=length-6000; if(position<0) position=0; }
        AIL_set_stream_ms_position(stream,position);
    } else if(info->flags_3c&4) {
        int length=-1; AIL_stream_ms_position(stream,&length,0);
        position=GetGameClientRandomValue(0,length-1,"F:\\bfme\\Code\\gameenginedevice\\Source\\MilesAudioDevice\\MilesAudioManager.cpp",0x2a50);
        AIL_set_stream_ms_position(stream,position);
    } else AIL_set_stream_ms_position(stream,0);
    if(ref.ptr->event_14->index_28!=2 && ref.ptr->event_14->index_28!=index_604) ref.ptr->byte_3b=true;
    else ref.ptr->byte_3b=false;
    if(info->type_84==0) {
        int index=event->index_28;
        int sub=event->index_64;
        if(sub==indices_ac4[index]) {
            typedef void (Ref006AE2C0::*Fn)(const Ref006AE2C0&);
            union { void (__cdecl *raw)(); Fn member; } call;
            call.raw=j_0000b60e;
            (refs_ad0[index].*call.member)(ref);
        } else ((Gen_006AC5D0*)((char*)this+0x9d4+(index*2+sub)*40))->bfmePush((void*)&ref);
        return;
    }
    if(info->begin_8c!=info->end_90) ((Rva006A8210Owner*)this)->dispatch((int)&info,event->index_28);
    list_9d0.push_back(ref);
    AIL_pause_stream(stream,ref.ptr->paused());
}

