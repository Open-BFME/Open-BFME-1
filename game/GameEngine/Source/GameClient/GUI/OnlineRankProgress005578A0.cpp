// stlport
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/shims/psplayerstats
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
class GameTextInterface;
class GameSpyInfo;
extern GameTextInterface *TheGameText;
extern GameSpyInfo *TheGameSpyInfo;
extern "C" int *g_bfmeLimitsDF;
class TextSlots005578A0 { public:
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
#undef S
 virtual UnicodeString fetch(const char*,bool*);
};
class StatsSlots005578A0 { public:
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
 S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
 S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
 S(30) S(31) S(32) S(33) S(34) S(35)
#undef S
 virtual PSPlayerStats stats();
};
extern void j_00022976();
extern void j_0000132f();
template<class T> inline const T &clamp005578A0(const T &low,const T &value,const T &high)
{ const T &bounded = value<low ? low:value; return bounded<high ? bounded:high; }
class OnlineRankProgress005578A0 { public: void write(int,char*,bool); };
void OnlineRankProgress005578A0::write(int side,char *output,bool skip)
{
 AsciiString name;
 char buffer[256];
 int category=1;
 if(!skip) *output=0;
 switch(side) {
 case 0: if(skip) return; name.translate(((TextSlots005578A0*)TheGameText)->fetch("Apt:Gondor",0)); category=1; break;
 case 1: if(skip) return; name.translate(((TextSlots005578A0*)TheGameText)->fetch("Apt:Rohan",0)); category=0; break;
 case 2: if(skip) return; category=3; name.translate(((TextSlots005578A0*)TheGameText)->fetch("Apt:Isengard",0)); break;
 case 3: if(skip) return; name.translate(((TextSlots005578A0*)TheGameText)->fetch("Apt:Mordor",0)); category=2; break;
 }
 PSPlayerStats stats=((StatsSlots005578A0*)TheGameSpyInfo)->stats();
 typedef int (__cdecl *RankPoints)(PSPlayerStats*,int);
 int points=((RankPoints)j_00022976)(&stats,category);
 int rank=1;
 while(rank<10 && points>=g_bfmeLimitsDF[rank]) ++rank;
 typedef int (__cdecl *NextPoints)(PSPlayerStats,int);
 int remaining=((NextPoints)j_0000132f)(stats,category);
 int percentage;
 if(remaining==0) percentage=100;
 else {
  int width=g_bfmeLimitsDF[rank]-g_bfmeLimitsDF[rank-1];
  percentage=(width-remaining)*100/width;
 }
 int bounded=clamp005578A0(0,percentage,100);
 _itoa(bounded,buffer,10);
 strcpy(output,buffer);
}

