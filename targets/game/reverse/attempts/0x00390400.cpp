// ?xferObjectTOC@GameLogic@@AAEXPAVXfer@@@Z
// partial score=0.29772727272727273 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// GameLogic::xferObjectTOC: Zero Hour GameLogic.cpp twin, retail RVA 00390400.
// BFME moves object list to +a8 and TOC list to +1ac; Xfer uses typed operators.
#include <list>
#include "ascii_string.h"
#include "xfer.h"
template<> inline StringBase<char>::~StringBase() { releaseBuffer(); }
extern void j_000496e8();
extern void j_000022bb();
extern void j_00030bb1();
extern void j_0004b4f2();
struct Rva00390400Template {
    char pad000[4]; Rva00390400Template *at004; char pad008[24]; AsciiString at020;
    const Rva00390400Template *finalOverride() const {
        typedef const Rva00390400Template *(Rva00390400Template::*P)() const;
        union {void (*raw)();P member;} r={j_000022bb}; return (this->*r.member)();
    }
};
struct Rva00390400Object {
    char pad000[4]; Rva00390400Template *at004; char pad008[0x80]; Rva00390400Object *m_next;
    const Rva00390400Template *getTemplate() const {
        const Rva00390400Template *p=at004;
        if (!p) return 0;
        if (p->at004) p=p->at004->finalOverride();
        return p;
    }
};
inline void transferTOCVersion(Xfer *xfer, unsigned char number) { Xfer::Version v; v.data[0]=number; v.data[1]=number; *xfer==v; }
class GameLogic {
public:
    struct ObjectTOCEntry {AsciiString name; unsigned short id;};
private:
    char pad000[0xa8]; Rva00390400Object *m_objectList; char pad0ac[0x100];
    std::list<ObjectTOCEntry> m_objectTOC;
    void clearTOC() {
        typedef void(std::list<ObjectTOCEntry>::*P)();
        union {void(*raw)();P member;}r={j_000496e8};(m_objectTOC.*r.member)();
    }
    ObjectTOCEntry *findTOCEntryByName(AsciiString name);
    void addTOCEntry(AsciiString name,unsigned short id);
    void xferObjectTOC(Xfer *xfer);
};
void GameLogic::xferObjectTOC(Xfer *xfer) {
    { Xfer::Version version; version.data[0]=1;version.data[1]=1; *xfer==version; }
    m_objectTOC.clear();
    unsigned tocCount=0;
    unsigned i=0;
    if(xfer->IsStoring()) {
        AsciiString templateName;
        for(Rva00390400Object *obj=m_objectList;obj;obj=obj->m_next) {
            templateName=obj->getTemplate()->at020;
            if(findTOCEntryByName(templateName)!=0) continue;
            addTOCEntry(obj->getTemplate()->at020,++tocCount);
        }
        *xfer==tocCount;
        for(std::list<ObjectTOCEntry>::iterator it=m_objectTOC.begin();it!=m_objectTOC.end();++it) {
            ObjectTOCEntry *entry=&*it;
            *xfer==entry->name; *xfer==entry->id;
        }
    } else {
        AsciiString templateName; unsigned short id;
        *xfer==tocCount;
        for(;i<tocCount;++i) {
            *xfer==templateName; *xfer==id;
            addTOCEntry(templateName,id);
        }
    }
}





