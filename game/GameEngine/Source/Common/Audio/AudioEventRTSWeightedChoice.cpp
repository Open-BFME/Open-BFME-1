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
static __declspec(noinline) int bfmeWeightedChoiceB2430(unsigned totalWeight,const WeightedSoundRangeB2430*range,bool useLogicRandom) {
 if (!(totalWeight>0)) return -1;
 unsigned remainingWeight;
 if(useLogicRandom) remainingWeight=GetGameLogicRandomValue(0,totalWeight-1,"F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",55);
 else remainingWeight=GetGameAudioRandomValue(0,totalWeight-1,"F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",59);
 WeightedSoundB2430 *soundEntry=range->begin;
 if(soundEntry!=range->end) { do {
  if(remainingWeight<soundEntry->weight) goto found;
  remainingWeight-=soundEntry->weight; ++soundEntry;
 } while(soundEntry!=range->end);
 return 0; }
found: if(soundEntry==range->end){_WriteBarrier();return 0;}
 return soundEntry-range->begin;
}
// ?forceWeightedChoiceB2430@@YAHIPBUWeightedSoundRangeB2430@@_N@Z absent-from-retail
// Absent-from-retail callsite to expose the static helper to MSVC optimization.
int forceWeightedChoiceB2430(unsigned count, const WeightedSoundRangeB2430*range,bool logical) { return bfmeWeightedChoiceB2430(count,range,logical); }
