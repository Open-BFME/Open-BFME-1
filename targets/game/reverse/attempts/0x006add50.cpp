// ?advance@AudioStreamAdvance006ADD50@@QAEXPAVRva006ABFD0Slot@@@Z
// partial score=0.86 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
extern "C" __declspec(dllimport) void __stdcall AIL_set_stream_loop_count(void *,int);
extern "C" __declspec(dllimport) void __stdcall AIL_start_stream(void *);
struct Rva006990E0Request;
int __fastcall rva006990E0(int,Rva006990E0Request*);
struct Info006ADD50 { char pad0[0x3c]; unsigned char flags_3c; char pad3d[0x47]; int kind_84; };
struct Tail006ADD50 { int dword0; short word4; };
enum PortionToPlay { Portion006ADD50_1=1 };
class AudioEventRTS { public:
    void setNextPlayPortion(PortionToPlay);
    void advanceNextPlayPortion();
    void bfmeGenerateFilename();
    char pad0[8]; Info006ADD50 *info8; char padc[0x1c]; int category28;
    char pad2c[0x19]; bool flag45; char pad46[0x1a]; int portion60;
    int dword64, loops68; Tail006ADD50 *tail6c;
};
struct Playing006ADD50 { char pad0[8]; void *stream8; int kindc, state10; AudioEventRTS *event14; char pad18[0x25]; bool flag3d; };
class Rva006ABFD0Slot { public: Playing006ADD50 *ptr; };
class Rva006ABFD0 { public: bool go(Rva006ABFD0Slot*); void add(Rva006ABFD0Slot*); };
class AudioStreamAdvance006ADD50 { public:
    void advance(Rva006ABFD0Slot*);
    char pad0[0x624]; unsigned flags624;
};
void AudioStreamAdvance006ADD50::advance(Rva006ABFD0Slot *slot) {
    if (!slot->ptr) return;
    AudioEventRTS *event=slot->ptr->event14;
    unsigned mask=1<<event->category28;
    if ((flags624&mask) && event->info8->kind_84==1) flags624 &= ~mask;
    if (slot->ptr->event14->info8->flags_3c&1) {
        if (slot->ptr->event14->portion60==0) slot->ptr->event14->setNextPlayPortion(Portion006ADD50_1);
        if (slot->ptr->event14->portion60==1 && ((Rva006ABFD0*)this)->go(slot)) return;
    }
    slot->ptr->event14->advanceNextPlayPortion();
    Playing006ADD50 *playing=slot->ptr;
    AudioEventRTS *current=playing->event14;
    if (current->portion60!=3) {
        if (playing->kindc!=3) {
            current->bfmeGenerateFilename();
            ((Rva006ABFD0*)this)->add(slot); return;
        }
    } else if (playing->kindc!=3) goto finish;
    {
        if (!current->flag45) {
            bool loop=false;
            switch(current->info8->kind_84) {
            case 0: loop=current->loops68==-1; break;
            case 1: case 4: loop=(current->info8->flags_3c&1)!=0; break;
            case 3: loop=true; break;
            }
            if (loop) {
                AIL_set_stream_loop_count(playing->stream8,rva006990E0((int)current,(Rva006990E0Request*)current));
                AIL_start_stream(slot->ptr->stream8); return;
            }
        }
    }
finish:
    if (!current->flag45 && current->tail6c && current->tail6c->word4) playing->flag3d=true;
    slot->ptr->state10=1;
}
