// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/buildlistinfo /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00198A10 BuildLists writer; receiver layout shared with 0x0019DB40.
#include "PreRTS.h"
#include "Common/DataChunk.h"
#include "GameLogic/SidesList.h"
#include "Common/PlayerTemplate.h"
#include "Common/NameKeyGenerator.h"
class ThingTemplate;
class BfmeThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
extern BfmeThingFactory *TheThingFactory;
extern const StaticNameKey TheKey_playerFaction;
struct SideEntry00198A10 {
 BuildListInfo *field00; Dict field04; char field08[16];
 Dict* getDict() {return &field04;} BuildListInfo* getBuildList() {return field00;}
};
class BuildListsWriter00198A10 {
 char field00[0x28]; int field28;
public:
 int getNumSides() {return field28;}
 SideEntry00198A10 *getSide(int i) {if (i>=0 && i<field28) return ((SideEntry00198A10*)((char*)this+0x2c))+i; return 0;}
 void write(DataChunkOutput &chunkWriter);
};
void BuildListsWriter00198A10::write(DataChunkOutput &chunkWriter) {
 chunkWriter.openDataChunk("BuildLists",1);
 chunkWriter.writeInt(getNumSides());
 for(int i=0;i<getNumSides();++i) {
  Dict *dict=getSide(i)->getDict();
  AsciiString faction = dict->getAsciiString(TheKey_playerFaction);
  const PlayerTemplate *player = ThePlayerTemplateStore->findPlayerTemplate(NAMEKEY(faction));
  if(player) {AsciiString side=*(const AsciiString*)((const char*)player+8); chunkWriter.writeNameKey(NAMEKEY(side));}
  else chunkWriter.writeNameKey(NAMEKEY("UNKNOWN"));
  BuildListInfo *pBuildList=getSide(i)->getBuildList();
  int count=0;
  while(pBuildList) {++count; pBuildList=pBuildList->getNext();}
  chunkWriter.writeInt(count);
  if(count>0) {
   Coord3D center; center.x=0;center.y=0;center.z=0;
   pBuildList=getSide(i)->getBuildList();
   while(pBuildList) {
    const ThingTemplate *thing=TheThingFactory->findTemplate(pBuildList->getTemplateName());
    // name_oracle witnesses ThingTemplate+0xC8 as m_kindof. Retail tests bit18.
    if(thing && (*(const unsigned*)((const char*)thing+0xc8)&0x40000)) {center=*pBuildList->getLocation(); break;}
    center.x+=pBuildList->getLocation()->x; center.y+=pBuildList->getLocation()->y; center.z+=pBuildList->getLocation()->z;
    pBuildList=pBuildList->getNext();
   }
   if(!pBuildList) {float scale=1.0f/count;center.x*=scale;center.y*=scale;center.z*=scale;}
   pBuildList=getSide(i)->getBuildList();
   while(pBuildList) {
    chunkWriter.writeAsciiString(pBuildList->getBuildingName());
    chunkWriter.writeAsciiString(pBuildList->getTemplateName());
    Coord3D loc;loc.set(pBuildList->getLocation());
    loc.x-=center.x;loc.y-=center.y;loc.z-=center.z;
    chunkWriter.writeReal(loc.x);chunkWriter.writeReal(loc.y);chunkWriter.writeReal(loc.z);
    chunkWriter.writeReal(pBuildList->getAngle());
    chunkWriter.writeByte(pBuildList->isInitiallyBuilt());chunkWriter.writeInt(pBuildList->getNumRebuilds());
    chunkWriter.writeAsciiString(pBuildList->getScript());chunkWriter.writeInt(pBuildList->getHealth());
    chunkWriter.writeByte(pBuildList->getWhiner());chunkWriter.writeByte(pBuildList->getUnsellable());chunkWriter.writeByte(pBuildList->getRepairable());
    pBuildList=pBuildList->getNext();
   }
  }
 }
 chunkWriter.closeDataChunk();
}


