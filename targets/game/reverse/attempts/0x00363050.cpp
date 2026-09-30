// ?update@Rva00363050Owner@@QAEXABVBfmeSharedString@@HABURva00363050Pair@@_N@Z
// partial score=0.0977 date=2026-09-30
// cl: /DNDEBUG /MD /O2 /EHsc /I.
#include "game/GameEngine/Source/GameNetwork/NetworkStringGetterIdentities.cpp"
#include <string.h>
struct Rva00363050Text { int refs; unsigned short length,capacity; char text[1]; };
static int compare(const BfmeSharedString &left, const BfmeSharedString &right) {
    Rva00363050Text *a,*b;
    memcpy(&a,&left,4);memcpy(&b,&right,4);
    int na=a?a->length:0,nb=b?b->length:0;
    int cmp=memcmp(a?a->text:"",b?b->text:"",na<nb?na:nb);
    return cmp?cmp:na-nb;
}
struct Rva00363050Pair { int x,y; };
struct Rva00363050Entry : Rva00361960 {
    char pad14[0xC]; int field20,field24; char pad28[0x14]; Rva00363050Pair field3C; char pad44[8];bool field4C;char pad4D[0xB];
};
class Rva00363050Owner {
public:void update(const BfmeSharedString &name,int duration,const Rva00363050Pair &pair,bool flag);
private:char pad00[0x18];Rva00363050Entry *begin,*end;
};
void Rva00363050Owner::update(const BfmeSharedString &name,int duration,const Rva00363050Pair &pair,bool flag) {
    for(unsigned i=0;i<(unsigned)(end-begin);++i) {
        int cmp;
        { BfmeSharedString temp=begin[i].copyString();cmp=compare(temp,name); }
        if(cmp==0) { begin[i].field20=0;begin[i].field24=(int)(duration*5.0f);begin[i].field3C=pair;begin[i].field4C=flag; }
    }
}
