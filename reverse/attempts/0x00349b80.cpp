// ?xfer@ScriptEngine@@MAEXPAVXfer@@@Z
// partial score=0.35624895711663607 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common
// stlport
// Natural reconstruction of 00349B80..0034B2E8 (5993 bytes, ret 4 then INT3).
// This entry receives the Snapshot-adjusted this pointer (full ScriptEngine +8).
// Field offsets below are relative to THAT pointer. No ZH array layout is used.
#include "ascii_string.h"
#include "System/xfer.h"
#include "System/snapshot.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <vector>
#include <list>
#include <utility>
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
struct XferException { void *text; int tag; };
extern "C" XferException *__cdecl bfmeFormatText(XferException*,int,const char*,...);
void __declspec(noreturn) __stdcall _CxxThrowException(void*,void*);
extern int g_guardTargetTypeThrowInfo;
static __forceinline void invalid_data() {
    XferException e; bfmeFormatText(&e,5,0); _CxxThrowException(&e,&g_guardTargetTypeThrowInfo);
}
class SequentialScript : public Snapshot {
public:
    SequentialScript() : team(0), object(0), script(0), instruction(-1), loops(0), frames(-1), paused(false), field28(0) {}
    virtual const char *GetSnapshotName(); virtual void LoadPostProcess(); virtual void DoXfer(Xfer &);
    void *team; unsigned object; AsciiString name0c,name10; void *script;
    int instruction,loops,frames; bool paused; void *field28;
};
class ObjectTypes {
public: ObjectTypes(); virtual ~ObjectTypes(); unsigned fields[4];
};
struct Rva00349B80Object { char pad[0x74]; unsigned id; };
struct Rva00349B80Node { Rva00349B80Node *next; unsigned id; Rva00349B80Object *object; };
struct Rva00349B80Logic {
    char pad[0xb4]; Rva00349B80Node **begin, **end;
    Rva00349B80Object *find(unsigned id) {
        if (!id) return 0;
        Rva00349B80Node *n=begin[id % (end-begin)];
        while(n && n->id!=id) n=n->next;
        return n ? n->object : 0;
    }
};
extern Rva00349B80Logic *TheGameLogic;
class MidVirtualSlot90Receiver;
void Rva0010C3C0(MidVirtualSlot90Receiver *,void *);
void Rva0010BDE0(MidVirtualSlot90Receiver *,void *);
typedef std::pair<AsciiString,AsciiString> ScriptKey;
namespace _STL {
template<> struct less<ScriptKey> {
    bool operator()(const ScriptKey &a,const ScriptKey &b) const {
        return a.first.compare(b.first)<0 || (!(b.first.compare(a.first)<0) && a.second.compare(b.second)<0);
    }
};
}
struct ScriptCounter { int value; bool countdown,milliseconds; };
typedef std::map<ScriptKey,ScriptCounter> CounterMap;
typedef std::map<ScriptKey,bool> FlagMap;
typedef std::map<ScriptKey,unsigned> ReferenceMap;
enum ObjectID;
typedef std::map<ScriptKey,ObjectID> UnitReferenceMap;
typedef std::map<AsciiString,bool> NameFlagMap;
typedef std::pair<AsciiString,Rva00349B80Object*> NamedRequest;
typedef std::vector<NamedRequest> NamedRequests;
struct Rva00349B80Reveal { AsciiString field00,field04; float field08; AsciiString field0c; };
struct AsciiStringCoord3DPair { AsciiString first; float x,y,z; };
typedef std::list<AsciiString> StringList;
typedef std::list<std::pair<AsciiString,unsigned> > StringUnsignedList;
typedef std::list<AsciiStringCoord3DPair> StringCoordList;
Xfer *xferListAsciiString(Xfer *,StringList *);
Xfer *xferListAsciiStringUINT(Xfer *,StringUnsignedList *);
Xfer *xferListAsciiStringCoord3D(Xfer *,StringCoordList *);
struct XferTriple32 { int a,b,c; };
extern "C" Xfer &xferRva00347BB0(Xfer &,int (&)[32]);
extern "C" Xfer &xferRva00347C40(Xfer &,XferTriple32 (&)[32]);
class ScriptEngine {
    template<class T> __forceinline T &at(unsigned off) { return *reinterpret_cast<T*>(reinterpret_cast<char*>(this)+off); }
protected: virtual void xfer(Xfer *);
    std::vector<SequentialScript*> sequential;
    char gap10[0x16038-0x10];
    CounterMap counters; FlagMap flags; UnitReferenceMap units; ReferenceMap teams; NameFlagMap map;
    char attackInfo[0x1000]; int attackCountField;
    char gap17078[0x17094-0x17078]; NamedRequests named;
    char gap170a0[0x175f0-0x170a0]; std::vector<Rva00349B80Reveal> reveals;
    char gap175fc[0x17620-0x175fc]; std::vector<ObjectTypes*> types;
};
void ScriptEngine::xfer(Xfer *xfer)
{
    if (xfer->IsCRC()) return;
    Xfer::Version version; version.data[0]=1; version.data[1]=3;
    *xfer == version;
    *xfer == at<bool>(0x1762e);
    *xfer == at<AsciiString>(0x17080);
    unsigned short sequentialCount=sequential.size();
    *xfer == sequentialCount;
    SequentialScript *script;
    if (xfer->IsStoring()) {
        for(std::vector<SequentialScript*>::iterator i=sequential.begin();i!=sequential.end();++i) {
            script=*i; *xfer == *script;
        }
    } else {
        if(sequential.size()!=0) invalid_data();
        for(unsigned short i=0;i<(unsigned short)sequentialCount;++i) {
            script=new SequentialScript;
            sequential.push_back(script); *xfer == *script;
        }
    }
    unsigned short counterCount=counters.size();
    *xfer == counterCount;
    if(xfer->IsStoring()) {
        for(CounterMap::iterator i=counters.begin(),end=counters.end();i!=end;++i) {
            *xfer == const_cast<AsciiString&>(i->first.first);
            *xfer == const_cast<AsciiString&>(i->first.second);
            *xfer == i->second.value; *xfer == i->second.countdown;
        }
    } else {
        counters.clear();
        for(int i=0;i<(unsigned short)counterCount;++i) {
            ScriptKey key;
            *xfer == key.first; *xfer == key.second;
            ScriptCounter value={0,false,false};
            *xfer == value.value; *xfer == value.countdown;
            counters.insert(std::make_pair(key,value));
        }
    }
    unsigned short flagCount=flags.size();
    *xfer == flagCount;
    if(xfer->IsStoring()) {
        for(FlagMap::iterator i=flags.begin(),end=flags.end();i!=end;++i) {
            *xfer == const_cast<AsciiString&>(i->first.first);
            *xfer == const_cast<AsciiString&>(i->first.second); *xfer == i->second;
        }
    } else {
        flags.clear();
        for(int i=0;i<(unsigned short)flagCount;++i) {
            ScriptKey key; *xfer == key.first; *xfer == key.second;
            bool value=false; *xfer == value;
            flags.insert(std::make_pair(key,value));
        }
    }
    unsigned short attackCount=(unsigned short)at<int>(0x17074);
    *xfer == attackCount;
    if((unsigned short)attackCount>256) invalid_data();
    for(int i=0;i<(unsigned short)attackCount;++i) *xfer == at<Snapshot>(0x16074+i*16);
    *xfer == at<int>(0x17074); *xfer == at<int>(0x17078); *xfer == at<int>(0x1707c);
    unsigned short namedCount=named.size(); *xfer == namedCount;
    AsciiString namedName;
    unsigned objectID;
    if(xfer->IsStoring()) {
        for(NamedRequests::iterator i=named.begin();i!=named.end();++i) {
            namedName=i->first; *xfer == namedName;
            objectID=i->second ? i->second->id : 0;
            Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&objectID);
        }
    } else {
        NamedRequest req;
        named.clear();
        for(unsigned short i=0;i<(unsigned short)namedCount;++i) {
            *xfer == namedName; Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&objectID);
            Rva00349B80Object *obj=TheGameLogic->find(objectID);
            if(!obj && objectID!=0) invalid_data();
            req.first=namedName; req.second=obj; named.push_back(req);
        }
    }
    *xfer == at<bool>(0x170a0);
    xfer->XferRawBytes(&at<int>(0x170ac),4);
    *xfer == at<float>(0x170b4); *xfer == at<float>(0x170b8); *xfer == at<float>(0x170bc);
    *xfer == at<int>(0x170c0); *xfer == at<int>(0x170c4); *xfer == at<int>(0x170c8); *xfer == at<int>(0x170cc);
    xferListAsciiString(xfer,&at<StringList>(0x17258));
    xferListAsciiString(xfer,&at<StringList>(0x17264));
    xferListAsciiStringUINT(xfer,&at<StringUnsignedList>(0x1725c));
    xferListAsciiStringUINT(xfer,&at<StringUnsignedList>(0x17260));
    xferListAsciiString(xfer,&at<StringList>(0x17268));
    xferRva00347BB0(*xfer,at<int[32]>(0x1726c));
    xferRva00347BB0(*xfer,at<int[32]>(0x172ec));
    xferRva00347BB0(*xfer,at<int[32]>(0x1736c));
    xferRva00347BB0(*xfer,at<int[32]>(0x173ec));
    xferRva00347C40(*xfer,at<XferTriple32[32]>(0x1746c));
    xferListAsciiStringCoord3D(xfer,&at<StringCoordList>(0x175ec));
    *xfer == at<float>(0x175fc); *xfer == at<float>(0x17600); *xfer == at<float>(0x17604);
    *xfer == at<float>(0x17608); *xfer == at<float>(0x1760c); *xfer == at<float>(0x17610);
    *xfer == at<short>(0x17614); *xfer == at<short>(0x17616);
    Rva0010BDE0((MidVirtualSlot90Receiver*)xfer,&at<int>(0x17618));
    *xfer == at<bool>(0x1761c);
    unsigned short revealCount=reveals.size(); *xfer == revealCount;
    *xfer == at<unsigned>(0x170d0); *xfer == at<unsigned>(0x170d4);
    if(xfer->IsStoring()) {
        for(std::vector<Rva00349B80Reveal>::iterator i=reveals.begin();i!=reveals.end();++i) {
            *xfer == i->field00; *xfer == i->field04; *xfer == i->field08; *xfer == i->field0c;
        }
    } else {
        if(!reveals.empty()) invalid_data();
        Rva00349B80Reveal r;
        for(unsigned short i=0;i<(unsigned short)revealCount;++i) {
            *xfer == r.field00; *xfer == r.field04; *xfer == r.field08; *xfer == r.field0c;
            reveals.push_back(r);
        }
    }
    unsigned short typesCount=types.size(); *xfer == typesCount;
    if(xfer->IsStoring()) {
        for(std::vector<ObjectTypes*>::iterator i=types.begin();i!=types.end();++i)
            *xfer == *(Snapshot*)*i;
    } else {
        if(!types.empty()) invalid_data();
        for(unsigned short i=0;i<(unsigned short)typesCount;++i) {
            ObjectTypes *t=new ObjectTypes; *xfer == *(Snapshot*)t; types.push_back(t);
        }
    }
    *xfer == at<bool>(0x1762c); *xfer == at<bool>(0x1762d);
    if(xfer->IsLoading() && at<int>(0x170ac)==0) {
        at<int>(0x170ac)=4; at<int>(0x170c0)=0; at<float>(0x170b4)=1.0f;
        at<float>(0x170b8)=0; at<int>(0x170c4)=0; at<int>(0x170c8)=0;
        at<int>(0x170cc)=0; at<float>(0x170bc)=0;
    }
    if(version.data[1]>1) {
        if(xfer->IsLoading()) {
            units.clear(); unsigned count=0; *xfer == count;
            for(unsigned i=0;i<count;++i) {
                AsciiString a,b; unsigned id; *xfer == a; *xfer == b;
                Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&id);
                ScriptKey key(a,b); unsigned zero=0;
                std::pair<UnitReferenceMap::iterator,bool> result=units.insert(std::make_pair(key,(ObjectID)zero));
                result.first->second=(ObjectID)id;
            }
            teams.clear(); unsigned count2=0; *xfer == count2;
            for(unsigned i=0;i<count2;++i) {
                AsciiString a,b; unsigned id; *xfer == a; *xfer == b; *xfer == id;
                ScriptKey key(a,b); unsigned zero=0;
                std::pair<ReferenceMap::iterator,bool> result=teams.insert(std::make_pair(key,zero));
                result.first->second=id;
            }
        } else if(xfer->IsStoring()) {
            unsigned count=units.size(); *xfer == count;
            for(UnitReferenceMap::iterator i=units.begin();i!=units.end();++i) {
                std::pair<ScriptKey,ObjectID> value=*i;
                *xfer == value.first.first; *xfer == value.first.second;
                Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&value.second);
            }
            unsigned count2=teams.size(); *xfer == count2;
            for(ReferenceMap::iterator i=teams.begin();i!=teams.end();++i) {
                std::pair<ScriptKey,unsigned> value=*i;
                *xfer == value.first.first; *xfer == value.first.second; *xfer == value.second;
            }
        }
    }
    if(version.data[1]>2) {
        if(xfer->IsStoring()) {
            unsigned count=map.size(); *xfer == count;
            for(NameFlagMap::iterator i=map.begin();i!=map.end();++i) {
                std::pair<AsciiString,bool> value=*i;
                *xfer == value.first; *xfer == value.second;
            }
        } else if(xfer->IsLoading()) {
            map.clear(); unsigned count=0; *xfer == count;
            while(count) {
                AsciiString key; bool value=false; *xfer == key; *xfer == value;
                map.insert(std::make_pair(key,value)); --count;
            }
        }
    }
}
