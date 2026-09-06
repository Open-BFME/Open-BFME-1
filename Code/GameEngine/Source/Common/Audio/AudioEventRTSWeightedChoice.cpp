// Address-derived static helper; retail debug file identifies AudioEventRTS.cpp.
// count is total weight, not vector length. Entries are 8B (name pointer, weight).
// MSVC chooses EAX=count, EDX=range, CL=logical when the body is visible.
// The write barrier emits no bytes; it preserves retail separate zero-return tails.
// cl: /DNDEBUG /MD /EHsc
extern int GetGameLogicRandomValue(int,int,char*,int);
extern int GetGameAudioRandomValue(int,int,char*,int);
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
struct WeightedSoundB2430 { void *name; unsigned weight; };
struct WeightedSoundRangeB2430 { WeightedSoundB2430 *begin,*end,*capacity; };
static __declspec(noinline) int bfmeWeightedChoiceB2430(unsigned count,const WeightedSoundRangeB2430*range,bool logical) {
 if (!(count>0)) return -1;
 unsigned value;
 if(logical) value=GetGameLogicRandomValue(0,count-1,"F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",55);
 else value=GetGameAudioRandomValue(0,count-1,"F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",59);
 WeightedSoundB2430 *it=range->begin;
 if(it!=range->end) { do {
  if(value<it->weight) goto found;
  value-=it->weight; ++it;
 } while(it!=range->end);
 return 0; }
found: if(it==range->end){_WriteBarrier();return 0;}
 return it-range->begin;
}
// ?forceWeightedChoiceB2430@@YAHIPBUWeightedSoundRangeB2430@@_N@Z absent-from-retail
// Absent-from-retail callsite to expose the static helper to MSVC optimization.
int forceWeightedChoiceB2430(unsigned count, const WeightedSoundRangeB2430*range,bool logical) { return bfmeWeightedChoiceB2430(count,range,logical); }
