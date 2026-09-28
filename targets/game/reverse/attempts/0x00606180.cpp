// ?d_00606180@@YAXXZ
// partial score=0.9520451339915373 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/iniexception
// AnimationSound INI callback at RVA 00606180; identity remains address-derived.
// All 1417 bytes include five throw tails, normal RET at +0x508.
// BANKED PARTIAL, not an accepted replacement: compiled main stream swaps ESI
// and EDI throughout (67 differing bytes) and carries one trailing INT3.
// memset mask initialization fixes zero-register hoisting; the excluded-loop
// inline boundary preserves retail null-test joins and EBX shrink wrapping.
// ABI evidence: INI separators load +0x41c; audio vslot +0x118 returns a
// one-word owning handle into hidden caller storage; tree insert at ILT aab5
// (body 605f00) consumes one 0x60-byte record by reference and returns a
// one-word iterator through a hidden first stack argument. The opaque tree
// declaration below needs mapping to the existing landed STL symbol before
// any landing. The audio global view also needs its existing VA 012ed668 pin.
// AnimationSoundInfo's constructor signature and offsets come from the
// landed AnimationSoundInfoCtor.cpp (RVA 605270, reached through ILT 8fd5).
// ThingRef's out-of-line destructor is the existing object symbol at 877b0,
// reached via ILT 362ff. The per-record reference destructor is inline.
#include "ascii_string.h"
#include <string.h>
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

extern "C" __declspec(dllimport) int __cdecl _stricmp(const char *, const char *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long *);
class INI {
public:
 const char *getNextSubToken(const char *);
 const char *getNextToken(const char *);
 const char *getNextTokenOrNull(const char *);
 static float scanReal(const char *);
 const char *seps606180() const { return *(const char **)((const char *)this + 0x41c); }
};
#include "Common/INIException.h"
class RefCountedThing {
public:
 virtual ~RefCountedThing();
 long m_refCount;
 void Release_Ref() { if (InterlockedDecrement(&m_refCount) <= 0) delete this; }
};
class ThingRef {
public:
 ~ThingRef();
 RefCountedThing *m_ptr;
};
struct AudioEventInfoRef {
 RefCountedThing *m_referent;
 ~AudioEventInfoRef() { if (m_referent) m_referent->Release_Ref(); }
};
class ModelConditionFlags {
public:
 unsigned int m_words[10];
 ModelConditionFlags() { memset(m_words,0,sizeof(m_words)); }
 void set(unsigned int i) { m_words[i >> 5] |= 1u << (i & 31); }
};
class AnimationSoundInfo {
public:
 AnimationSoundInfo(const AudioEventInfoRef &, const AsciiString &, float,
                    const ModelConditionFlags &, const ModelConditionFlags &);
 AsciiString m_animation;
 AudioEventInfoRef m_sound;
 float m_frame;
 ModelConditionFlags m_required;
 ModelConditionFlags m_excluded;
 unsigned char m_hasModelConditions;
};
struct Rva00606180Audio {
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00c();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01c();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02c();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03c();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04c();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05c();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06c();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07c();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08c();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09c();
 virtual void slot0a0();
 virtual void slot0a4();
 virtual void slot0a8();
 virtual void slot0ac();
 virtual void slot0b0();
 virtual void slot0b4();
 virtual void slot0b8();
 virtual void slot0bc();
 virtual void slot0c0();
 virtual void slot0c4();
 virtual void slot0c8();
 virtual void slot0cc();
 virtual void slot0d0();
 virtual void slot0d4();
 virtual void slot0d8();
 virtual void slot0dc();
 virtual void slot0e0();
 virtual void slot0e4();
 virtual void slot0e8();
 virtual void slot0ec();
 virtual void slot0f0();
 virtual void slot0f4();
 virtual void slot0f8();
 virtual void slot0fc();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10c();
 virtual void slot110();
 virtual void slot114();
 virtual ThingRef findAudioEventInfo(const AsciiString &);
};
extern Rva00606180Audio *TheAudioClientUpdate;
struct Rva00606180Iterator { void *node; };
class Rva00606180Tree {
public:
 Rva00606180Iterator insert(const AnimationSoundInfo &);
};
int bfmeLookup_001c62b0(void *);

__forceinline const char *parseExcludedConditions00606180(INI *ini, const char *token, ModelConditionFlags &excluded, const char *excludedKey, const char *animationKey, const char *framesKey)
{
 if (token && !_stricmp(token,excludedKey)) {
  token=ini->getNextToken(ini->seps606180());
  do {
   int bit=bfmeLookup_001c62b0((void *)token);
   if (bit<0) throw INIException(3,"AnimationSound line: unknown model condition '%s' in %s list",token,excludedKey);
   excluded.set(bit);
   token=ini->getNextTokenOrNull(ini->seps606180());
   if (token && !_stricmp(token,excludedKey)) token=ini->getNextTokenOrNull(ini->seps606180());
  } while (token && _stricmp(token,animationKey) && _stricmp(token,framesKey));
 }
 return token;
}

void parseAnimationSound00606180(INI *ini, void *instance, void *, const void *)
{
 if (!instance) return;
 char soundKey[]="Sound";
 char requiredKey[]="RequiredMC";
 char excludedKey[]="ExcludedMC";
 char animationKey[]="Animation";
 char framesKey[]="Frames";
 AsciiString sound(ini->getNextSubToken(soundKey));
 if (sound.isEmpty())
  throw INIException(3,"AnimationSound line: sound name cannot empty");
 ThingRef info=TheAudioClientUpdate->findAudioEventInfo(sound);
 if (!info.m_ptr)
  throw INIException(3,"AnimationSound line: unknown sound '%s'",sound.str());
 const char *token=ini->getNextTokenOrNull(ini->seps606180());
 ModelConditionFlags required;
 ModelConditionFlags excluded;
 if (token && !_stricmp(token,requiredKey)) {
  token=ini->getNextToken(ini->seps606180());
  do {
   int bit=bfmeLookup_001c62b0((void *)token);
   if (bit<0) throw INIException(3,"AnimationSound line: unknown model condition '%s' in %s list",token,requiredKey);
   required.set(bit);
   token=ini->getNextTokenOrNull(ini->seps606180());
   if (token && !_stricmp(token,requiredKey)) token=ini->getNextTokenOrNull(ini->seps606180());
  } while (token && _stricmp(token,excludedKey) && _stricmp(token,animationKey) && _stricmp(token,framesKey));
 }
 token=parseExcludedConditions00606180(ini,token,excluded,excludedKey,animationKey,framesKey);
 do {
  if (!token || _stricmp(token,animationKey)) {
   if (!token) token="<End of line>";
   throw INIException(3,"AnimationSound line: expected '%s' next, got '%s'",animationKey,token);
  }
  AsciiString animation(ini->getNextToken(ini->seps606180()));
  token=ini->getNextSubToken(framesKey);
  do {
   float frame=INI::scanReal(token);
   AnimationSoundInfo item(*(const AudioEventInfoRef *)&info,animation,frame,required,excluded);
   ((Rva00606180Tree *)((char *)instance+8))->insert(item);
   token=ini->getNextTokenOrNull(ini->seps606180());
  } while (token && _stricmp(token,animationKey));
 } while (token);
}
