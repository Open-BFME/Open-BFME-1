// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// RecorderClass command-history dump (RVA 0x0009A580): the sole caller 0x00388C10 loads TheRecorder into ecx.
// Globals by VA: CommandsAt012ED5F4 list head at +8, ClientAt012F1464 lookup at vslot +0x2C, RelationshipsAt012A9FC8 name table.
#include "ascii_string.h"
#include "unicode_string.h"
// Retail inlines every string access and scope exit in this body.
template<class T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template<class T> inline const T* StringBase<T>::str() const { return m_data ? m_data->data : (const T*)""; }
template<class T> inline int StringBase<T>::getLength() const { return m_data ? m_data->length : 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }

class PlayerTemplate { public: AsciiString getName() const; };
class Team;
enum Relationship { REL_INVALID = -1 };
class Player { public: UnicodeString getPlayerDisplayName(); Relationship getRelationship(const Team*) const; };
class PlayerList { public: Player* getNthPlayer(int); };
class ThingTemplate { char rva0009A580_pad[32]; public: AsciiString rva0009A580_at20; const AsciiString& getName() const { return rva0009A580_at20; } };
class Thing { public: const ThingTemplate* getTemplate() const; };
class Object : public Thing { public: Player* getControllingPlayer() const; };
class GameLogic { public: Object* findObjectByID(int); };
class ThingFactory { public: const ThingTemplate* findByTemplateID(unsigned short); };
class SpecialPowerTemplate { public: AsciiString getName() const; };
class SpecialPowerStore { public: const SpecialPowerTemplate* findSpecialPowerTemplateByID(unsigned); };
enum ScienceType { SCIENCE_INVALID = -1 };
class ScienceStore { public: AsciiString getInternalNameForScience(ScienceType) const; };
struct Coord0009A580 { float x,y,z; };
union GameMessageArgumentType { int integer; unsigned timestamp; float real; bool boolean; unsigned short character; Coord0009A580 coord; struct { int x,y; } pixel; struct { int x1,y1,x2,y2; } region; };
enum GameMessageArgumentDataType { ARG_INT, ARG_REAL, ARG_BOOL, ARG_OBJECT, ARG_DRAWABLE, ARG_TEAM, ARG_LW, ARG_COORD, ARG_PIXEL, ARG_REGION, ARG_TIME, ARG_CHAR };
class GameMessage { public:
 const GameMessageArgumentType* getArgument(int) const;
 GameMessageArgumentDataType getArgumentDataType(int);
 AsciiString getCommandAsAsciiString();
};
// Address-derived interface: only observed slot +0x10 is modeled.
class CommandDumpFile0009A580 { public:
 virtual void slot0(); virtual void slot4(); virtual void slot8(); virtual void slotC();
 virtual int write(const void*,int);
};
class Drawable0009A580 : public Thing {};
class Client0009A580 { public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
 virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
 virtual void s8(); virtual void s9(); virtual void s10();
 virtual Drawable0009A580* find(int);
};
extern PlayerList* ThePlayerList;
extern GameLogic* TheGameLogic;
extern ThingFactory* TheThingFactory;
extern ScienceStore* TheScienceStore;
extern SpecialPowerStore* TheSpecialPowerStore;
extern Client0009A580* ClientAt012F1464;
extern char* CommandsAt012ED5F4;
extern bool FlagAt012ED4E5, FlagAt012ED4E6;
extern int OpenBFME5_netCRCInterval;
extern const char* RelationshipsAt012A9FC8[];

template<class T> __forceinline T& field0009A580(const void* p,int offset) { return *(T*)((char*)p+offset); }
template<class T> __forceinline T read0009A580(const void* p,int offset) { return *(const T*)((const char*)p+offset); }
__forceinline void write0009A580(CommandDumpFile0009A580* file,const AsciiString& text) { file->write(text.str(),text.getLength()); }
// Receiver unused; the caller passes the file and the last frame to dump (ret 8).
class RecorderClass { public: void dumpCommandHistory0009A580(CommandDumpFile0009A580*,unsigned); };
void RecorderClass::dumpCommandHistory0009A580(CommandDumpFile0009A580* file,unsigned maxFrame)
{
 if (!file) return;
 AsciiString text;
 for (unsigned playerIndex=1;playerIndex<32;++playerIndex) {
  bool first=true;
  for (GameMessage* message=read0009A580<GameMessage*>(CommandsAt012ED5F4,8);message;message=read0009A580<GameMessage*>(message,4)) {
   if (read0009A580<unsigned>(message,0x14)!=playerIndex) continue;
   Player* player=ThePlayerList->getNthPlayer(playerIndex);
   if (first) {
    first=false;
    if (!player) text.format("\n\n========================================================\nPlayer Index: %d NOT FOUND! This could be bad...\n=========================================================\n",playerIndex);
    else text.format("\n\n========================================================\nPlayer Index: %d, Name: %S(%s), Template: %s \n=========================================================\n",playerIndex,player->getPlayerDisplayName().str(),field0009A580<AsciiString>(player,0x1c).str(),read0009A580<PlayerTemplate*>(player,4)?read0009A580<PlayerTemplate*>(player,4)->getName().str():"NULL");
    write0009A580(file,text);
   }
   if ((read0009A580<int>(message,0x10)!=0x449 || (!FlagAt012ED4E5 && !FlagAt012ED4E6 && OpenBFME5_netCRCInterval!=1)) && read0009A580<int>(message,0x10)!=0x446 && read0009A580<int>(message,0x10)>1000 && read0009A580<int>(message,0x10)<1999) {
   unsigned frame=message->getArgument(read0009A580<unsigned char>(message,0x18)-1)->timestamp;
   if (frame>maxFrame) break;
   AsciiString name=message->getCommandAsAsciiString();
   text.format("\nFrame:%d, %s(%d):\n",frame,name.str(),read0009A580<int>(message,0x10));
   write0009A580(file,text);
   bool string=false;
   for (int i=0;i<read0009A580<unsigned char>(message,0x18)-1;++i) {
    if (string && message->getArgumentDataType(i)!=ARG_CHAR) {
     text.format("\n"); write0009A580(file,text); string=false;
    }
    switch(message->getArgumentDataType(i)) {
    case ARG_INT:
     if (read0009A580<int>(message,0x10)==0x413) {
      if (i==0) text.format("    %02d: Integer:%d (PlayerIndex)",i,message->getArgument(i)->integer);
      else if (i==1) text.format("    %02d: Integer:%d (Science:%s)",i,message->getArgument(i)->integer,TheScienceStore->getInternalNameForScience((ScienceType)message->getArgument(i)->integer).str());
     } else if (i==0 && read0009A580<int>(message,0x10)==0x418) {
      const ThingTemplate* thing=TheThingFactory->findByTemplateID((unsigned short)message->getArgument(i)->integer);
      text.format("    %02d: Integer:%d (ThingTemplate:%s)",i,message->getArgument(i)->integer,thing?thing->getName().str():"UNKNOWN");
     } else if (i==0 && (read0009A580<int>(message,0x10)==0x410 || read0009A580<int>(message,0x10)==0x411 || read0009A580<int>(message,0x10)==0x40f || read0009A580<int>(message,0x10)==0x455 || read0009A580<int>(message,0x10)==0x457)) {
      unsigned id=message->getArgument(0)->integer;
      const SpecialPowerTemplate* power=TheSpecialPowerStore->findSpecialPowerTemplateByID(id);
      if (power) text.format("    %02d: Integer:%d (SpecialPower=%s)",i,id,power->getName().str());
     } else text.format("    %02d: Integer:%d",i,message->getArgument(i)->integer);
     break;
    case ARG_REAL: text.format("    %02d: Real:%f, %%g(%g), %%x(%08x)",i,message->getArgument(i)->real,message->getArgument(i)->real,message->getArgument(i)->real); break;
    case ARG_BOOL: text.format("    %02d: Bool:%s",i,message->getArgument(i)->boolean?"TRUE":"FALSE"); break;
    case ARG_OBJECT: {
     int id=message->getArgument(i)->integer;
     Object* object=TheGameLogic->findObjectByID(id);
     if (object) {
      int rel=player?player->getRelationship(read0009A580<Team*>(object->getControllingPlayer(),0x230)):-1;
      text.format("    %02d: Object:%s(%d) Relationship:%s",i,object->getTemplate()->rva0009A580_at20.str(),id,rel>=0?RelationshipsAt012A9FC8[rel]:"N/A");
     } else text.format("    %02d: Object:INVALID(%d)",i,id);
     break;
    }
    case ARG_DRAWABLE: {
     int id=message->getArgument(i)->integer;
     Drawable0009A580* drawable=ClientAt012F1464->find(id);
     if (drawable) text.format("    %02d: Drawable:%s(%d)",i,drawable->getTemplate()->rva0009A580_at20.str(),id);
     else text.format("    %02d: Drawable:INVALID",i);
     break;
    }
    case ARG_TEAM: text.format("    %02d: TeamID:%d",i,message->getArgument(i)->integer); break;
    case ARG_LW: text.format("    %02d: LivingWorldUniqueID:%d",i,message->getArgument(i)->integer); break;
    case ARG_COORD: {
     const GameMessageArgumentType* a=message->getArgument(i);
     float x=a->coord.x; float y=a->coord.y; float z=a->coord.z;
     text.format("    %02d: Coord3D: (x:%f,y:%f,z:%f), %%g(%g,%g,%g), %%x(%08x,%08x,%08x)",i,x,y,z,x,y,z,x,y,z); break;
    }
    case ARG_PIXEL: text.format("    %02d: Pixel: (x:%d,y:%d)",i,message->getArgument(i)->pixel.x,message->getArgument(i)->pixel.y); break;
    case ARG_REGION: { const GameMessageArgumentType* a=message->getArgument(i); int x1=a->region.x1; int y1=a->region.y1; int x2=a->region.x2; int y2=a->region.y2; text.format("    %02d: Pixel Region: (x:%d,y:%d) to (x:%d,y:%d)",i,x1,y1,x2,y2); break; }
    case ARG_TIME: text.format("    %02d: TimeStamp:%d",i,message->getArgument(i)->timestamp); break;
    case ARG_CHAR: {
     if (!string) text.format("    %02d: String:%C",i,message->getArgument(i)->character);
     else text.format("%C",message->getArgument(i)->character);
     string=true; break; }
    default: text.format("    %02d: UNKNOWN ARGUMENT TYPE:%d",i,message->getArgumentDataType(i)); break;
    }
    if (!string) text.StringBase<char>::concat("\n",1);
    write0009A580(file,text);
   }
   }
  }
 }
}
