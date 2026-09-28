// ?createBridgeObjectsRva003916F0@GameLogic@@QAEX_N@Z
// partial score=0.6935 date=2026-09-28
// cl: /Igame/Libraries/Source/WWVegas/WWMath /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// RVA003916F0: BFME bridge-object creation phase, extracted from the ZH startNewGame flow.
// Exact method name is not established; retain the address in its identity.
// Exact only when 0x0038F7B0's body is in the same TU (VC7.1 then proves `created` does not escape).
#include <vector>
#include <bitset>
extern void j_000017a8(); extern void j_00012814();
extern void j_0001325a(); extern void j_00015d7a(); extern void j_00017a12();
extern void j_0002fb80(); extern void j_000399A5();
extern void j_0003a1a7(); extern void j_000441b1();
extern void j_0004494a();
extern void Rva0090F050();
float normalizeAngle(float angle);
extern void Rva009EBAC0(int);
#include "coord3d.h"
inline Coord3D::Coord3D(const Coord3D &p) {x=p.x;y=p.y;z=p.z;}
inline Coord3D::~Coord3D() {}
typedef Coord3D BridgePosition003916F0;
struct BridgeExtra003916F0 {
    unsigned data[5];
    BridgeExtra003916F0() {typedef void(BridgeExtra003916F0::*P)(); union{void(*raw)();P member;}r={j_0002fb80};(this->*r.member)();}
    ~BridgeExtra003916F0() {typedef void(BridgeExtra003916F0::*P)(); union{void(*raw)();P member;}r={j_00015d7a};(this->*r.member)();}
};
struct BridgeTemplate003916F0 {
    char at000[0x485]; bool m_isBridge;
    void read(BridgeExtra003916F0*e,bool*b) const {typedef void(BridgeTemplate003916F0::*P)(BridgeExtra003916F0*,bool*)const;union{void(*raw)();P member;}r={j_00017a12};(this->*r.member)(e,b);}
};
struct BridgeMapObject003916F0 {
    void *at000; BridgeMapObject003916F0 *at004; char at008[0x14]; float at01c; unsigned at020; char at024[20];
    BridgeTemplate003916F0 *getTemplate() {typedef BridgeTemplate003916F0*(BridgeMapObject003916F0::*P)();union{void(*raw)();P member;}r={j_00012814};return (this->*r.member)();}
    const BridgePosition003916F0* getLocation() {typedef const BridgePosition003916F0*(BridgeMapObject003916F0::*P)();union{void(*raw)();P member;}r={j_0001325a};return (this->*r.member)();}
};
class BfmeMapObjectListHolder {public:BridgeMapObject003916F0 *first;};
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;
class BridgeObject003916F0 {
public:
    void setOrientation(float angle) {typedef void(BridgeObject003916F0::*P)(float);union{void(*raw)();P member;}r={j_000399A5};(this->*r.member)(angle);}
    void setPosition(const BridgePosition003916F0 *p) {typedef void(BridgeObject003916F0::*P)(const BridgePosition003916F0*);union{void(*raw)();P member;}r={j_0003a1a7};(this->*r.member)(p);}
    void updateProperties(void *p) {typedef void(BridgeObject003916F0::*P)(void*);union{void(*raw)();P member;}r={j_000441b1};(this->*r.member)(p);}
    void levelStart(void *p) {typedef void(BridgeObject003916F0::*P)(void*);union{void(*raw)();P member;}r={j_000017a8};(this->*r.member)(p);}
};
typedef std::pair<BridgeObject003916F0*,BridgeMapObject003916F0*> BridgePair003916F0;
typedef std::vector<BridgePair003916F0> BridgeVector003916F0;
struct BridgePlayer003916F0 { char at000[0x230]; void *at230; void *getDefaultTeam() const { return at230; } };
struct Players005999B0 {char at000[0x14];BridgePlayer003916F0*at014; BridgePlayer003916F0 *getNeutralPlayer() const { return at014; }};
extern Players005999B0 *PlayerList005999B0;
class Object; class Team; class ThingTemplate;
template<int N> class BitFlags { std::bitset<N> m_bits; public: BitFlags() {} };
class ThingFactory {public:Object *newObject(const ThingTemplate*,Team*,const BitFlags<86>&,unsigned);};
extern ThingFactory *Factory0040A260;
extern void *AssetSubsystem0059A3D0;
struct BridgeRefresh003916F0 { virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();virtual void refresh();};
struct BridgeTerrain003916F0 {
    virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();virtual void s14();
    virtual float groundHeight(float,float,void*);
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void s90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sa0();
    virtual void sa4();
    virtual void sa8();
    virtual void sac();
    virtual void addBridge(BridgeObject003916F0*);
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class GameLogic {
public:
    void createBridgeObjectsRva003916F0(bool loadingSaveGame);
    void createMapObjectsRva0038F7B0(BridgeVector003916F0 *v,bool flag,int *progress,bool loading);
};
void GameLogic::createBridgeObjectsRva003916F0(bool loadingSaveGame) {
    BridgeVector003916F0 created;
    for(BridgeMapObject003916F0 *map=BfmeTheMapObjectListHolder->first;map;map=map->at004) {
        ((BridgeRefresh003916F0*)AssetSubsystem0059A3D0)->refresh(); Rva0090F050();
        if(map->at020 & 0x36) continue;
        BridgeTemplate003916F0 *thing=map->getTemplate();
        if(!thing || !thing->m_isBridge) continue;
        struct Context003916F0 { bool value; Context003916F0():value(false) {} } flag;
        BridgeExtra003916F0 extra;
        thing->read(&extra,&flag.value);
        Rva009EBAC0((int)&extra);
        if(!loadingSaveGame) {
            void *team=PlayerList005999B0->getNeutralPlayer()->getDefaultTeam();
            BridgeObject003916F0 *obj=(BridgeObject003916F0*)Factory0040A260->newObject((ThingTemplate*)thing,(Team*)team,BitFlags<86>(),0);
            if(obj) {
                BridgePosition003916F0 pos=*map->getLocation();
                pos.z+=((BridgeTerrain003916F0*)TheTerrainLogic)->groundHeight(pos.x,pos.y,0);
                float angle=map->at01c;
                float normalized=normalizeAngle(angle);
                obj->setOrientation(normalized);
                obj->setPosition(&pos);
                if(thing->m_isBridge) ((BridgeTerrain003916F0*)TheTerrainLogic)->addBridge(obj);
                BridgePair003916F0 pair;
                pair.first=obj; pair.second=map;
                created.push_back(pair);
                obj->updateProperties(map->at024);
            }
        }
    }
    { int progress=59;
    createMapObjectsRva0038F7B0(&created,false,&progress,loadingSaveGame); }
    BridgeVector003916F0::iterator last=created.end();
    for(BridgeVector003916F0::iterator it=created.begin();it!=last;++it) {
        ((BridgeRefresh003916F0*)AssetSubsystem0059A3D0)->refresh(); Rva0090F050();
        it->first->levelStart(it->second->at024);
    }
}




