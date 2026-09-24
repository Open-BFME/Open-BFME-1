// ?xfer@GameLogic@@MAEXPAVXfer@@@Z
// partial score=0.9948342660352992 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/GameEngine/Source/Common/System
// stlport
// GameLogic secondary Snapshot transfer, RVA00391C40,2323B.
// Secondary receiver is complete-object+8. See IDENTITY.md and LAYOUTS.md.
#define _STLP_NO_EXCEPTIONS 1
#include <stddef.h>
#include <hash_map>
#include <list>
#include <vector>
#include <bitset>
typedef _STL::bitset<86> Rva00391C40StatusBits;
#include "ascii_string.h"
template<> __declspec(nothrow) int StringBase<wchar_t>::compare(const StringBase<wchar_t>&) const;
#include "Common/UnicodeString.h"
#include "coord3d.h"
#include "xfer.h"
#include "snapshot.h"
typedef bool Bool;
#include "subsystem_interface.h"
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->releaseBuffer(); }
template<> inline const char *StringBase<char>::str() const {const char *text=&m_data->data[0];if(!m_data)text="";return text;}
template<> inline bool StringBase<char>::isEmpty() const {return !m_data || m_data->length==0;}
inline Coord3D::Coord3D() { }
inline Coord3D::~Coord3D() { }
inline Coord3D::Coord3D(int a,int b,int c) {x=(float)a;y=(float)b;z=(float)c;}
inline Coord3D::Coord3D(const Coord3D &p) { x=p.x; y=p.y; z=p.z; }
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &p) {
    struct Words {unsigned x,y,z;}; *(Words*)this=*(const Words*)&p; return *this;
}
class XferException {
public:
    XferException(int tag,const char *format,...);
    XferException(const XferException&);
    ~XferException();
    char *text; int tagValue;
};
extern void j_000022bb(); extern void j_00004c41(); extern void j_00008170();
extern void j_0000c702(); extern void j_0000c9b4(); extern void j_00010898();
extern void j_00015d7a(); extern void j_00017a12(); extern void j_0001e0c9();
extern void j_0001e759(); extern void j_000226ec(); extern void j_00028560();
extern void j_0002e523(); extern void j_0002fb80(); extern void j_00030bb1();
extern void j_00033a96(); extern void j_0003b59d(); extern void j_0003e81f();
extern void j_000424b0(); extern void j_0004494a(); extern void j_00045935();
extern void j_00046b82(); extern void j_00047767();
extern void Rva009EBAC0(int);
extern void setFPMode();
class SkirmishPreferences {
public:
    SkirmishPreferences();
    virtual ~SkirmishPreferences();
    char data[20];
    UnicodeString getUserName();
    void writeRoute() {
        typedef void(SkirmishPreferences::*P)(); union {void(*raw)();P member;}r={j_0002e523}; (this->*r.member)();
    }
};
class Rva00391C40BlockView {
public:
    virtual void slot000(); virtual void slot004(); virtual void slot008();
    virtual void slot00c(); virtual void slot010();
    virtual int begin(const char*); virtual void end(); virtual void skip(const char*);
};
inline void transferId(Xfer *xfer,unsigned *p) { typedef void(__cdecl*P)(Xfer*,unsigned*); ((P)j_0000c9b4)(xfer,p); }
enum BuildableStatus {}; // Label independently witnessed in helper0010BFC0.
inline void transferBuildable(Xfer *xfer,BuildableStatus *p) { typedef void(__cdecl*P)(Xfer*,BuildableStatus*); ((P)j_0001e0c9)(xfer,p); }
inline void transferDifficulty(Xfer *xfer,int *p) { typedef void(__cdecl*P)(Xfer*,int*); ((P)j_0003e81f)(xfer,p); }
struct Rva00391C40Hash {
    unsigned operator()(AsciiString value) const {return (unsigned)_STL::__stl_hash_string(value.str());}
};
struct Rva00391C40Equal { bool operator()(const AsciiString&a,const AsciiString&b)const; };
struct Rva00391C40Button { char pad000[12]; AsciiString at00c; };
template<class T> struct Rva00391C40Map {
    typedef _STL::hash_map<AsciiString,T,Rva00391C40Hash,Rva00391C40Equal> Native;
    typedef typename Native::const_iterator const_iterator;
    Native table;
    const_iterator first(void(*target)()) const {
        typedef const_iterator(Rva00391C40Map::*P)()const;
        union {void(*raw)();P member;}r={target}; return (this->*r.member)();
    }
    T& index(const AsciiString &key,void(*target)()) {
        typedef T&(Rva00391C40Map::*P)(const AsciiString&);
        union {void(*raw)();P member;}r={target}; return (this->*r.member)(key);
    }
};
struct Rva00391C40Entry { AsciiString at000; unsigned short at004; };
typedef Xfer *(__fastcall *Rva00391C40UnsignedShortSlot)(Xfer *, void *, unsigned short *);
struct Rva00391C40XferVtable
{
    void *slots[31];
    Rva00391C40UnsignedShortSlot transferUnsignedShort;
};
__forceinline void Rva00391C40TransferUnsignedShort(Xfer *xfer, unsigned short *value)
{
    Rva00391C40XferVtable *vtable = *(Rva00391C40XferVtable **)xfer;
    vtable->transferUnsignedShort(xfer, vtable, value);
}

class Rva00391C40Thing;
struct Rva00391C40Redirect {
    Rva00391C40Thing* get() {
        typedef Rva00391C40Thing*(Rva00391C40Redirect::*P)();
        union {void(*raw)();P member;}r={j_000022bb}; return (this->*r.member)();
    }
};
struct Rva00391C40Extra {
    char data[20];
    Rva00391C40Extra() {typedef void(Rva00391C40Extra::*P)();union{void(*raw)();P member;}r={j_0002fb80};(this->*r.member)();}
    ~Rva00391C40Extra() {typedef void(Rva00391C40Extra::*P)();union{void(*raw)();P member;}r={j_00015d7a};(this->*r.member)();}
};
class Rva00391C40Thing {
public:
    char pad000[4]; Rva00391C40Redirect *at004; char pad008[24]; AsciiString at020;
    void read(Rva00391C40Extra *extra,bool *flag) {
        typedef void(Rva00391C40Thing::*P)(Rva00391C40Extra*,bool*);
        union {void(*raw)();P member;}r={j_00017a12}; (this->*r.member)(extra,flag);
    }
};
struct Rva00391C40ObjectPrefix {
    virtual ~Rva00391C40ObjectPrefix();
    Rva00391C40Thing *at004; char pad008[0x30]; Coord3D at038; char pad044[0x1c];
};
struct Rva00391C40Object : Rva00391C40ObjectPrefix,Snapshot {
    char pad064[0x10]; unsigned at074;
    char pad078[0x10]; Rva00391C40Object *at088;
    const Rva00391C40Thing *get()const {Rva00391C40Thing*p=at004;if(p&&p->at004)p=p->at004->get();return p;}
};
struct Rva00391C40Team {};
struct Rva00391C40Player {char pad000[0x230];Rva00391C40Team *at230;};
struct Rva00391C40PlayerList {char pad000[20];Rva00391C40Player *at014;};
struct Rva00391C40Factory {
    Rva00391C40Thing *find(const AsciiString &name) {
        typedef Rva00391C40Thing*(Rva00391C40Factory::*P)(const AsciiString&);
        union {void(*raw)();P member;}r={j_00028560};return (this->*r.member)(name);
    }
    Rva00391C40Object *create(Rva00391C40Thing *t,Rva00391C40Team *team,const Rva00391C40StatusBits &status,unsigned id) {
        typedef Rva00391C40Object*(Rva00391C40Factory::*P)(Rva00391C40Thing*,Rva00391C40Team*,const Rva00391C40StatusBits&,unsigned);
        union {void(*raw)();P member;}r={j_0004494a};return (this->*r.member)(t,team,status,id);
    }
};
struct Rva00391C40Control {
    Rva00391C40Button *find(const AsciiString &name) {
        typedef Rva00391C40Button*(Rva00391C40Control::*P)(const AsciiString&);
        union{void(*raw)();P member;}r={j_0003b59d};return (this->*r.member)(name);
    }
};
struct Rva00391C40Secondary : SubsystemInterface,Snapshot {};
extern Rva00391C40PlayerList *g_Rva00391C40PlayerList;
extern Rva00391C40Factory *g_Rva00391C40Factory;
extern Rva00391C40Control *g_Rva00391C40Control;
extern Snapshot *g_Rva00391C40Snapshot012F4CB0;
extern Rva00391C40Secondary *g_Rva00391C40Snapshot012F086C;
extern Rva00391C40Secondary *g_Rva00391C40Snapshot012F1044;
extern const AsciiString g_Rva00391C40Empty;
struct Rva00391C40Complete {
    void enter() {if(at1a0==0)setFPMode();++at1a0;}
    void leave() {--at1a0;}
    char pad000[0x1a0]; int at1a0;char pad1a4[8];_STL::list<Rva00391C40Entry> at1ac;
    Rva00391C40Entry *findId(unsigned short number) {
        const _STL::list<Rva00391C40Entry>::iterator last=at1ac.end();
        for(_STL::list<Rva00391C40Entry>::iterator it=at1ac.begin();it!=last;++it)
            if(it->at004==number)return &*it;
        return 0;
    }
    void toc(Xfer*xfer) {typedef void(Rva00391C40Complete::*P)(Xfer*);union{void(*raw)();P member;}r={j_0001e759};(this->*r.member)(xfer);}
    void prepare() {typedef void(Rva00391C40Complete::*P)();union{void(*raw)();P member;}r={j_000424b0};(this->*r.member)();}
};
// TU ABI view: preserve the witnessed secondary slot with the source xfer(Xfer*)
// signature; the shared Snapshot header spells it DoXfer(Xfer&) instead.
class Rva00391C40SnapshotInterface {
public:
    virtual ~Rva00391C40SnapshotInterface();
    virtual const char *slot004()=0;
    virtual void slot008()=0;
protected:
    virtual void xfer(Xfer*)=0;
};
class GameLogic : public SubsystemInterface, public Rva00391C40SnapshotInterface {
public:
    Rva00391C40Map<BuildableStatus> at00c;
    Rva00391C40Map<Rva00391C40Button*> at020;
    char pad034[8]; unsigned at03c;
    char pad040[0x4c]; int at08c;
    bool at090,at091,at092,at093,at094,at095,at096; char pad097;
    int at098,at09c; char pad0a0[8]; Rva00391C40Object *at0a8;
    char pad0ac[0x60]; int at10c,at110;bool at114;char pad115[0x47];
    _STL::vector<unsigned> at15c;
    int at168;unsigned at16c;char pad170[0x30];int at1a0;
    char pad1a4[8];_STL::list<Rva00391C40Entry> at1ac;
    unsigned getCount()const {unsigned n=0;for(Rva00391C40Object *obj=at0a8;obj;obj=obj->at088)++n;return n;}
    void toc(Xfer*xfer) {typedef void(GameLogic::*P)(Xfer*);union{void(*raw)();P member;}r={j_0001e759};(this->*r.member)(xfer);}
    void prepare() {typedef void(GameLogic::*P)();union{void(*raw)();P member;}r={j_000424b0};(this->*r.member)();}
    Rva00391C40Entry *find(AsciiString name) {typedef Rva00391C40Entry*(GameLogic::*P)(AsciiString);union{void(*raw)();P member;}r={j_00030bb1};return (this->*r.member)(name);}
protected:
    virtual void xfer(Xfer *xfer);
};
void GameLogic::xfer(Xfer *xfer) {
    unsigned id;
    union { Xfer::Version version; unsigned versionWord; };version.data[0]=1;version.data[1]=4;
    *xfer==version;
    if(version.data[1]>=4 && at10c==2) {
        SkirmishPreferences prefs;
        UnicodeString name=prefs.getUserName();
        *xfer==name;
        if(xfer->IsLoading() && prefs.getUserName().compare(name)!=0) {
            typedef void(SkirmishPreferences::*P)(UnicodeString);
            union {void(*raw)();P member;}r={j_00045935};(prefs.*r.member)(name);
            prefs.writeRoute();
        }
    }
    *xfer==at03c;
    *xfer==at168;
    *xfer==at114;
    if(xfer->IsLightCRC()) {
        for(Rva00391C40Object *obj=at0a8;obj;obj=obj->at088) {
            Coord3D pos=obj->at038;*xfer==(Coord3DBase&)pos;
        }
        return;
    }
    Rva00391C40Complete *owner=(Rva00391C40Complete*)this;
    owner->enter();
    owner->toc(xfer);
    if(xfer->IsLoading())owner->prepare();
    unsigned count=getCount();
    *xfer==count;
    if(xfer->IsStoring()) {
        for(Rva00391C40Object *obj=at0a8;obj;obj=obj->at088) {
            typedef Rva00391C40Entry*(Rva00391C40Complete::*P)(AsciiString);
            union{void(*raw)();P member;}r={j_00030bb1};
            Rva00391C40Entry *entry=(owner->*r.member)(obj->get()->at020);
            if(!entry)throw XferException(5,0);
            *xfer==entry->at004;
            id=obj->at074;transferId(xfer,&id);
            ((Rva00391C40BlockView*)xfer)->begin("Object");
            *xfer==*(Snapshot*)obj;
            ((Rva00391C40BlockView*)xfer)->end();
        }
    } else {
        Rva00391C40Team *team=g_Rva00391C40PlayerList->at014->at230;
        unsigned short number;
        for(unsigned i=0;i<count;++i) {
            Rva00391C40TransferUnsignedShort(xfer, &number);
            Rva00391C40Entry *entry=owner->findId(number);
            if(!entry)throw XferException(5,0);
            transferId(xfer,&id);
            Rva00391C40Thing *thing=g_Rva00391C40Factory->find(entry->at000);
            if(!thing) {((Rva00391C40BlockView*)xfer)->skip("Object");continue;}
            union { bool flag; unsigned flagWord; };flag=false;
            Rva00391C40Extra extra;
            thing->read(&extra,&flag);
            Rva009EBAC0((int)&extra);
            // The callee's third argument is the 86-bit ObjectStatus mask,
            // not a position: canonical ThingFactory::newObject pin + forwarder.
            Rva00391C40Object *obj=g_Rva00391C40Factory->create(thing,team,Rva00391C40StatusBits(),id);
            ((Rva00391C40BlockView*)xfer)->begin("Object");
            *xfer==*(Snapshot*)obj;
            ((Rva00391C40BlockView*)xfer)->end();
        }
    }
    *xfer==*g_Rva00391C40Snapshot012F4CB0;
    *xfer==*(Snapshot*)g_Rva00391C40Snapshot012F086C;
    *xfer==*(Snapshot*)g_Rva00391C40Snapshot012F1044;
    *xfer==at090;*xfer==at110;
    if(xfer->IsStoring()) {
        for(Rva00391C40Map<BuildableStatus>::const_iterator it=((const Rva00391C40Map<BuildableStatus>::Native&)at00c.table).begin();it!=at00c.table.end();++it) {
            AsciiString name=it->first;BuildableStatus value=it->second;
            *xfer==name;transferBuildable(xfer,&value);
        }
        AsciiString empty;*xfer==empty;
    } else {
        if(!at00c.table.empty())throw XferException(5,0);
        for(;;) {
            AsciiString name;*xfer==name;if(name.isEmpty())break;
            BuildableStatus value;transferBuildable(xfer,&value);
            at00c.index(name,j_00033a96)=value;
        }
    }
    *xfer==at091;*xfer==at092;*xfer==at093;*xfer==at098;
    if(version.data[1]>=3)transferDifficulty(xfer,&at09c);
    *xfer==at16c;
    if(xfer->IsStoring()) {
        for(Rva00391C40Map<Rva00391C40Button*>::const_iterator it=at020.table.begin();it!=at020.table.end();++it) {
            AsciiString name=it->first;
            AsciiString value=it->second?it->second->at00c:g_Rva00391C40Empty;
            *xfer==name;*xfer==value;
        }
        AsciiString empty;*xfer==empty;
    } else {
        if(!at020.table.empty())throw XferException(5,0);
        for(;;) {
            AsciiString name;*xfer==name;if(name.isEmpty())break;
            AsciiString value;*xfer==value;
            Rva00391C40Button *button=0;
            if(!value.isEmpty())button=g_Rva00391C40Control->find(value);
            at020.index(name,j_00008170)=button;
        }
    }
    *xfer==at08c;
    if(version.data[1]>=2)*xfer==at096;
    at15c.clear();
    owner->leave();
}
