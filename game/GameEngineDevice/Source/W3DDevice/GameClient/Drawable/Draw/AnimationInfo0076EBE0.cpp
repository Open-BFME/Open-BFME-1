// Retail 0x0076EBE0, secondary interface this = primary owner +0xc.
// ret 12 and three caller stack slots; vtable +8 name, +0x10 frames, +0x18 duration.
// Format literals and 0x1c-stride track accesses establish behavior; owner identity stays address-qualified.
// cl: /O2 /Ob2 /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
class Animation0076EBE0 { public:
 virtual void slot00(); virtual void slot04(); virtual const char* name(); virtual void slot0c();
 virtual int frames(); virtual void slot14(); virtual float duration();
};
struct Track0076EBE0 { Animation0076EBE0* anim; float frame; float at08; float blend; int mode; int at14; bool at18,at19; };
extern unsigned int g_rva0075b2e0_value;
class Rva0076C080 { public: void advanceAnimation(); };
class Rva0076CAF0ConditionalDispatch { public: char pad00[0x9c]; int stamp; void synchronize() { if(g_rva0075b2e0_value!=(unsigned int)stamp) ((Rva0076C080 *)this)->advanceAnimation(); } };

// Retail .data 0x012BB5BC, 32 bytes: seven animation-mode names and a NULL.
const char* AnimModeNames012BB5BC[] =
{
	"MANUAL",
	"LOOP",
	"ONCE",
	"LOOP_PINGPONG",
	"PLAY_TO_FRAME",
	"LOOP_BACKWARDS",
	"ONCE_BACKWARDS",
	0
};
class AnimationInfo0076EBE0 { public:
 char pad00[0x90]; int stamp; char pad94[0x3c]; Track0076EBE0 tracks[3];
 void describe(int,AsciiString*,AsciiString*);
};
void AnimationInfo0076EBE0::describe(int index,AsciiString* info,AsciiString* state) {
 ((Rva0076CAF0ConditionalDispatch*)((char*)this-0xc))->synchronize();
 if(index>=0 && (unsigned int)index<3 && tracks[index].anim) {
  if(info) {
   float duration=tracks[index].anim->duration();
   int frames=tracks[index].anim->frames();
   int frame=(int)tracks[index].frame;
   int blend=(int)tracks[index].blend;
   int modeIndex=tracks[index].mode;
   AsciiString mode(AnimModeNames012BB5BC[modeIndex]);
   info->format("%s %d/%d frames(%.1fs), AnimMode:%s, BlendTime:%d",tracks[index].anim->name(),frame+1,frames,duration,mode.str(),blend);
  }
  if(state) state->format("(ModelState and AnimState info not available in release)");
 }
}
