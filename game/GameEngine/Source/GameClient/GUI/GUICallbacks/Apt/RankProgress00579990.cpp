// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include <stdlib.h>
#include <string.h>
class SkirmishBattleHonors {
public:
 int getRank(AsciiString) const;
 int getRankWidth(AsciiString,int) const;
 int getPointsToNextRank(AsciiString,int) const;
};
template<class T> inline const T &clamp00579990(const T &low,const T &value,const T &high)
{ const T &bounded = value<low ? low:value; return bounded<high ? bounded:high; }
class RankProgress00579990 { public: void write(int,char*,bool); private: char pad00[0x3c4]; SkirmishBattleHonors honors; };
void RankProgress00579990::write(int side,char *output,bool skip)
{
 AsciiString name;
 char buffer[256];
 if(!skip) *output=0;
 switch(side) {
 case 0:
  if(!skip) { _itoa(0,buffer,10); strcpy(output,buffer); }
  return;
 case 1: if(skip) return; name="Gondor"; break;
 case 2: if(skip) return; name="Rohan"; break;
 case 3: if(skip) return; name="Isengard"; break;
 case 4: if(skip) return; name="Mordor"; break;
 }
 int rank=honors.getRank(name);
 int width=honors.getRankWidth(name,rank);
 int remaining=honors.getPointsToNextRank(name,rank);
 int percentage=(int)((float)(width-remaining)/honors.getRankWidth(name,rank)*100.0f);
 int bounded=clamp00579990(0,percentage,100);
 _itoa(bounded,buffer,10);
 strcpy(output,buffer);
}

