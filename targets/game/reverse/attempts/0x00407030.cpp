// ?process@Rva00407030@@QAEXPAPAVPathfindCell@@ABUIRegion2D@@1PAVPathfindZoneManager@@@Z
// partial score=0.0 date=2026-10-03
// cl: /DNDEBUG /MD /O2 /Iinputs/reference/shims/pathfind
// stlport
// Complete candidate, NOT byte-exact and not production. Extent 00407030
// through RET16 at 00407F9A, INT3 starts 00407F9D (3949 bytes).
// Native k=0..11 selects threshold k%3 and flags (k/3)&1, (k/6)&1.
// Each row holds five equivalency arrays. Slots 1,2,0 normalize type zero
// to 1,3,2 respectively and require equal layer; slot3 compares type==2;
// slot4 requires equal raw type and layer. Each merge replaces the larger
// representative with the smaller across the whole array.
// Global VA 012B4D2C chooses pair-map lookup versus two adjacent-cell scans.
// Pair writer 00406EC0 proves the 32-byte map payload at manager+235FC.
// No speculative semantic names or new pins accompany this bank.
// Register allocation, loop scheduling, and helper boundaries remain open.
// Six source variants: 3901..4109 bytes; native-helper visibility did not
// improve the instruction shape. The bank retains the complete typed body.
// Opaque block identity is
// independently named by matched incremental-step caller 00408480.
#include "GameLogic/AIPathfind.h"
#include <map>
void __cdecl operator delete[](void *);
void *__cdecl operator new[](unsigned int);
class PathfindZoneManager;
typedef unsigned short U16;
struct Cell00406EC0 {
 char pad00[10]; U16 zone;
 unsigned type:3, pad03:3, layer:6, connect:6, pad18:2, bit20:1, bit21:1, bits22:2;
 U16 getZone() const { return zone; }
};
struct Rva00407030Record {
 U16 type; int layer; int connect; bool bit20, bit21; U16 bits22;
};
struct Rva00407030Pair { Rva00407030Record a,b; };
class PairMerge00406EC0 {
public:
 // Existing matched PairMerge00406EC0::merge, RVA 00406EC0, ret8.
 // Cell00406EC0 layout matches that independently verified TU.
 void merge(const Cell00406EC0 *, const Cell00406EC0 *);
 char pad00[0x235FC];
 std::map<unsigned,Rva00407030Pair> pairs;
 const Rva00407030Pair *lookup(U16 za,U16 zb) {
  if(za==zb)return 0;
  if(za>zb){U16 t=za;za=zb;zb=t;}
  unsigned key=(unsigned(za)<<16)|zb;
  std::map<unsigned,Rva00407030Pair>::iterator it=pairs.find(key);
  return it==pairs.end()?0:&it->second;
 }
};
extern bool Rva00407030Flag012B4D2C;
class Rva00407030 {
public:
 void process(PathfindCell **map,const IRegion2D &bounds,const IRegion2D &globalBounds,PathfindZoneManager *owner);
 char pad00[0x130]; U16 first, count; U16 *tables[12][5]; char tail[4];
};
static __forceinline void merge(int src,int dst,U16 *table,int count) {
 if(dst<src) { for(int i=0;i<count;++i) if(table[i]==src) table[i]=dst; }
 else { for(int i=0;i<count;++i) if(table[i]==dst) table[i]=src; }
}
static __forceinline void apply(U16 dst,U16 src,U16 *table,int first,int count) {
 U16 s=table[src-first],t=table[dst-first];
 if(t==s)return;
 merge(s,t,table,count);
}
static __forceinline bool compatible(const Cell00406EC0 &a,const Cell00406EC0 &b,int n,bool p,bool q) {
 bool ok=true;
 if(n>0 && ((int)a.bits22>n)!=((int)b.bits22>n))ok=false;
 if(p && a.bit20!=b.bit20)ok=false;
 if(q && a.bit21!=b.bit21)ok=false;
 return ok;
}
static __forceinline bool compatible(const Rva00407030Record &a,const Rva00407030Record &b,int n,bool p,bool q) {
 if(n>0 && ((int)a.bits22>n)!=((int)b.bits22>n))return false;
 if(p && a.bit20!=b.bit20)return false;
 if(q && a.bit21!=b.bit21)return false;
 return true;
}
template<class T> static __forceinline bool same(const T &a,const T &b,int fallback) {
 int x=a.type==0?fallback:a.type;
 int y=b.type==0?fallback:b.type;
 return x==y && a.layer==b.layer;
}
static __forceinline Cell00406EC0 &cellAt(PathfindCell **map,int i,int j) {
 return *(Cell00406EC0 *)&map[i][j];
}
void Rva00407030::process(PathfindCell **map,const IRegion2D &bounds,const IRegion2D &globalBounds,PathfindZoneManager *owner) {

 PairMerge00406EC0 *manager=(PairMerge00406EC0 *)owner;
 int i,j;
 unsigned minZone=cellAt(map,bounds.lo.x,bounds.lo.y).getZone(),maxZone=minZone;
 for(j=bounds.lo.y;j<=bounds.hi.y;++j)for(i=bounds.lo.x;i<=bounds.hi.x;++i) {
  Cell00406EC0 *cell=&cellAt(map,i,j); U16 zone=cell->getZone();
  if(minZone>zone)minZone=zone;
  if(maxZone<zone)maxZone=zone;
  if(Rva00407030Flag012B4D2C) {
   if(i>globalBounds.lo.x)manager->merge(cell,&cellAt(map,i-1,j));
   if(j>globalBounds.lo.y)manager->merge(cell,&cellAt(map,i,j-1));
  }
 }
 first=minZone; count=1+maxZone-minZone;
 for(i=0;i<5;++i)for(j=0;j<12;++j) {
  delete [] tables[j][i];
  tables[j][i]=count>1?new U16[count]:0;
 }
 if(count==1)return;
 for(int k=0;k<12;++k) {
  int n=k%3; bool p=(k/3)&1,q=((k/3)>>1)&1;
  for(i=0;i<count;++i) {
   tables[k][0][i]=i+first; tables[k][1][i]=i+first;
   tables[k][2][i]=i+first; tables[k][3][i]=i+first;
   tables[k][4][i]=i+first;
  }
  if(Rva00407030Flag012B4D2C) {
   for(int a=1;a<count;++a)for(int b=0;b<a;++b) {
    const Rva00407030Pair *pair=manager->lookup(b+first,a+first);
    if(pair && compatible(pair->a,pair->b,n,p,q)) {
     if(same(pair->a,pair->b,1))apply(b+first,a+first,tables[k][1],first,count);
     if(same(pair->a,pair->b,3))apply(b+first,a+first,tables[k][2],first,count);
     if(same(pair->a,pair->b,2))apply(b+first,a+first,tables[k][0],first,count);
     if((pair->a.type==2)==(pair->b.type==2))apply(b+first,a+first,tables[k][3],first,count);
     if(same(pair->a,pair->b,0))apply(b+first,a+first,tables[k][4],first,count);
    }
   }
  } else {
   for(j=bounds.lo.y;j<=bounds.hi.y;++j)for(i=bounds.lo.x;i<=bounds.hi.x;++i) {
    if(i>bounds.lo.x && cellAt(map,i,j).getZone()!=cellAt(map,i-1,j).getZone() && compatible(cellAt(map,i,j),cellAt(map,i-1,j),n,p,q)) {
     if(same(cellAt(map,i,j),cellAt(map,i-1,j),1))apply(cellAt(map,i,j).getZone(),cellAt(map,i-1,j).getZone(),tables[k][1],first,count);
     if(same(cellAt(map,i,j),cellAt(map,i-1,j),3))apply(cellAt(map,i,j).getZone(),cellAt(map,i-1,j).getZone(),tables[k][2],first,count);
     if(same(cellAt(map,i,j),cellAt(map,i-1,j),2))apply(cellAt(map,i,j).getZone(),cellAt(map,i-1,j).getZone(),tables[k][0],first,count);
     if((cellAt(map,i,j).type==2)==(cellAt(map,i-1,j).type==2))apply(cellAt(map,i,j).getZone(),cellAt(map,i-1,j).getZone(),tables[k][3],first,count);
     if(same(cellAt(map,i,j),cellAt(map,i-1,j),0))apply(cellAt(map,i,j).getZone(),cellAt(map,i-1,j).getZone(),tables[k][4],first,count);
    }
    if(j>bounds.lo.y && cellAt(map,i,j).getZone()!=cellAt(map,i,j-1).getZone() && compatible(cellAt(map,i,j),cellAt(map,i,j-1),n,p,q)) {
     if(same(cellAt(map,i,j),cellAt(map,i,j-1),1))apply(cellAt(map,i,j).getZone(),cellAt(map,i,j-1).getZone(),tables[k][1],first,count);
     if(same(cellAt(map,i,j),cellAt(map,i,j-1),3))apply(cellAt(map,i,j).getZone(),cellAt(map,i,j-1).getZone(),tables[k][2],first,count);
     if(same(cellAt(map,i,j),cellAt(map,i,j-1),2))apply(cellAt(map,i,j).getZone(),cellAt(map,i,j-1).getZone(),tables[k][0],first,count);
     if((cellAt(map,i,j).type==2)==(cellAt(map,i,j-1).type==2))apply(cellAt(map,i,j).getZone(),cellAt(map,i,j-1).getZone(),tables[k][3],first,count);
     if(same(cellAt(map,i,j),cellAt(map,i,j-1),0))apply(cellAt(map,i,j).getZone(),cellAt(map,i,j-1).getZone(),tables[k][4],first,count);
    }
   }
  }
 }
}
