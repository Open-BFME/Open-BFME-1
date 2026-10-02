// ?mangle@Rva00417330Drawable@@QBEXVRva00417330Holder@@@Z
// partial score=1.0 date=2026-10-02
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib
#include "Common/AsciiString.h"
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->StringBase<char>::~StringBase(); }
template<class T> inline void StringBase<T>::concat(const StringBase<T>& other) { concat(other.str(),other.getLength()); }
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);
extern void j_0001d002();
class Rva00417330AudioInfo {
public:
 virtual ~Rva00417330AudioInfo();
 long refs;
 AsciiString name;
 void override_00417330(const AsciiString& name) {
  union { void (*raw)(); void (Rva00417330AudioInfo::*member)(const AsciiString&); } target;
  target.raw = j_0001d002;
  (this->*target.member)(name);
 }
 void release() { if(InterlockedDecrement(&refs)<=0) delete this; }
};
class Rva00417330Holder {
public:
 Rva00417330AudioInfo *p;
 ~Rva00417330Holder() { if(p) p->release(); }
};
class Rva00417330Drawable {
public:
 char pad[0x100]; unsigned id;
 unsigned getID() const { return id; }
 void mangle(Rva00417330Holder audio) const;
};
void Rva00417330Drawable::mangle(Rva00417330Holder audio) const {
 AsciiString name;
 name.format(AsciiString(" CUSTOM %d "),(int)getID());
 name.concat(audio.p->name);
 audio.p->override_00417330(name);
}
