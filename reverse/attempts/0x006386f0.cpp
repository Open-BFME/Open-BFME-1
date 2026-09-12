// ?generateGameSpyGameResultsPacket@GameSpyStagingRoom@@QAE?AVAsciiString@@_N@Z
// partial score=0.65 date=2026-09-12
// Retail boundary: RVA 0x006386F0, 1684 bytes, ret 8 (hidden AsciiString result plus bool).
// Fresh BFME reconstruction replaces old no-argument ZH bank and its wrong slot layout.
// GameInfo size 0x58; eight GameSpyGameSlot size0x78; isQM0x43c, qmType0x440.
// Slots have internalName0x2c, disconnected0x40, profileID0x44, login0x48,
// authentication name0x70 and token0x74. Existing ILT bindings preserve honest identity.
// Recovered BFME ladder/authentication/disconnect fields and internal-name player lookup.
// Current 1694 vs1684, frame0x50 vs0x4c, 90 relocs. First-loop instruction extents match;
// differing stack homes and second-loop playerID spill cause broad byte drift (783 raw masked).
// Target playerID EBP, this EDI, loop index/pointer on stack; ours playerID stack,this EBP,
// loop index EDI, pointer EBX. Do not claim a 10-byte-only diff: 52 reloc sites drift.
// Combined StringBase compare length/pointer fetch fixed 4 bytes from1698.
// Tested authentic string forwarding/composition/compare/concat layers, declarations,
// isHuman/isAI/getMap noinline visibility, existing-ILT PMF vs direct helper declarations:
// no further gain. getSlot visibility incorrectly allows deletion of unused winning call.
// Bank score is author estimate of reconstruction, not byte-match proof. t=20min root Astra.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
extern "C" unsigned int __cdecl strlen(const char *);
extern "C" int __cdecl memcmp(const void *,const void *,unsigned int);
#pragma intrinsic(strlen,memcmp)
template<class T> struct StringData {int refs; unsigned short length,capacity; T text[1];};
template<class T> class StringBase {
 friend class AsciiString;
protected:
 StringBase():m_data(0){}
 StringBase(const StringBase&);
 ~StringBase(){releaseBuffer();}
 StringData<T>*m_data;
private:
 StringBase(const T*);
 void releaseBuffer();
 void set(const StringBase&);
public:
 void set(const T*,int);
 void concat(const T*,int);
};
class AsciiString:private StringBase<char>{
public:
 AsciiString():StringBase<char>(){}
 AsciiString(const AsciiString &s):StringBase<char>(s){}
 AsciiString(const char*s):StringBase<char>(s){}
 ~AsciiString(){}
 const char *str()const{return m_data?m_data->text:"";}
 int getLength()const{return m_data?m_data->length:0;}
 bool isEmpty()const{return !m_data||m_data->length==0;}
 char getCharAt(int i)const{return m_data?m_data->text[i]:0;}
 AsciiString&operator=(const AsciiString&s){StringBase<char>::set(s);return *this;}
 AsciiString&operator=(const char*s){StringBase<char>::set(s,s?strlen(s):0);return *this;}
 void concat(char c){StringBase<char>::concat(&c,1);}
 void concat(const AsciiString&s){StringBase<char>::concat(s.str(),s.getLength());}
 int compare(const char *s)const {int n=strlen(s),m;const char*p;if(m_data){m=m_data->length;p=m_data->text;}else{m=0;p="";}int result=memcmp(p,s,m<n?m:n);return result?result:m-n;}
 void __cdecl format(AsciiString,...);
};
class GameSlot {
public:
 virtual void slot0();
 char prefix[0x14]; int team;
 char gap[0x10]; AsciiString internalName;
 char gap2[0x10];bool didDisconnect;char gap3[3];
 bool isHuman()const;
 bool isAI()const;
 bool disconnected()const{return isHuman()&&didDisconnect;}
 int getTeamNumber()const{return team;}
};
extern void j_00016dd8();
extern void j_0000692e();
extern void j_00028565();
class GameSpyGameSlot:public GameSlot {
public:
 int profileID;
 AsciiString login;
 char opaque[0x24];
 AsciiString authName,authToken;
 AsciiString copyAuthName()const {typedef AsciiString(GameSpyGameSlot::*F)()const;union{void(*entry)();F method;}call;call.entry=j_00016dd8;return(this->*call.method)();}
 AsciiString copyAuthToken()const {typedef AsciiString(GameSpyGameSlot::*F)()const;union{void(*entry)();F method;}call;call.entry=j_0000692e;return(this->*call.method)();}
 AsciiString copyLogin()const {typedef AsciiString(GameSpyGameSlot::*F)()const;union{void(*entry)();F method;}call;call.entry=j_00028565;return(this->*call.method)();}
};
class GameInfo {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();
 virtual int getLocalSlotNum();
 GameSlot *getSlot(int);
 AsciiString getMap()const;
 char fields[0x48];unsigned int seed;char suffix[8];
};
class GameSpyStagingRoom:public GameInfo {
public:
 AsciiString generateGameSpyGameResultsPacket(bool forceDisconnect);
 GameSpyGameSlot slots[8];char extra[0x24];bool isQM;char qmGap[3];int qmType;
};
struct PlayerTemplate {char prefix[8];AsciiString side;};
struct Player {char prefix[4];PlayerTemplate*playerTemplate;};
enum NameKeyType {NAMEKEY_INVALID=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
class PlayerList {public:Player*findPlayerWithNameKey(NameKeyType);};
class VictoryConditionsInterface {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();
 virtual bool hasAchievedVictory(const Player*);
 virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();virtual void slot16();
 virtual int getEndFrame();
};
class GameLogic {public:char prefix[0x6c];bool sawMismatch;};
extern VictoryConditionsInterface*TheVictoryConditions;
extern NameKeyGenerator*TheNameKeyGenerator;
extern PlayerList*ThePlayerList;
extern GameInfo*TheGameInfo;
extern GameLogic*TheGameLogic;
AsciiString GameSpyStagingRoom::generateGameSpyGameResultsPacket(bool forceDisconnect)
{
 int endFrame=TheVictoryConditions->getEndFrame();
 int localSlotNum=getLocalSlotNum();
 int winningTeam=-1,numHumans=0,numPlayers=0,numAIs=0,numTeamsAtGameEnd=0,lastTeamAtGameEnd=-1;
 int i;
 for(i=0;i<8;++i){
  AsciiString playerName;
  playerName=TheGameInfo->getSlot(i)->internalName;
  Player*p=playerName.isEmpty()?0:ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName.str()));
  if(p){
   ++numHumans;
   if(TheVictoryConditions->hasAchievedVictory(p))winningTeam=getSlot(i)->getTeamNumber();
   GameSlot*slot=getSlot(i);
   if(!slot->disconnected()){
    if(slot->getTeamNumber()!=lastTeamAtGameEnd||numTeamsAtGameEnd==0){lastTeamAtGameEnd=slot->getTeamNumber();++numTeamsAtGameEnd;}
   }
  }else if(slots[i].isAI())++numAIs;
 }
 numPlayers=numHumans+numAIs;
 AsciiString mapName;
 for(i=0;i<getMap().getLength();++i){char c=getMap().getCharAt(i);if(c=='\\')c='/';mapName.concat(c);}
 AsciiString ladder;
 if(isQM){if(qmType==1)ladder="1v1";else if(qmType==2)ladder="2v2";else ladder="none";}else ladder="none";
 AsciiString results;
 results.format("\\seed\\%d\\hostname\\%s\\mapname\\%s\\numplayers\\%d\\duration\\%d\\gamemode\\exiting\\localplayer\\%d\\ladder\\%s",seed,slots[0].copyLogin().str(),mapName.str(),numPlayers,endFrame,localSlotNum,ladder.str());
 int playerID=0;
 for(i=0;i<8;++i){
  AsciiString playerName;
  playerName=TheGameInfo->getSlot(i)->internalName;
  Player*p=playerName.isEmpty()?0:ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName.str()));
  if(p){
   GameSpyGameSlot*slot=&slots[i];
   AsciiString authName=slot->copyAuthName();
   AsciiString authToken=slot->copyAuthToken();
   AsciiString playerName=slot->isHuman()?slot->copyLogin():"AIPlayer";
   int gsPlayerID=slot->profileID;
   bool disconnected=slot->disconnected();
   AsciiString result="loss";
   AsciiString side="USA";
   if(forceDisconnect)result="discon";
   else if(TheGameLogic->sawMismatch)result="desync";
   else if(disconnected&&isQM&&qmType==1)result="loss";
   else if(TheVictoryConditions->hasAchievedVictory(p))result="win";
   side=p->playerTemplate->side;
   if(side.compare("America")==0)side="USA";
   AsciiString playerStr;
   playerStr.format("\\player_%d\\%s\\pid_%d\\%d\\team_%d\\%d\\result_%d\\%s\\side_%d\\%s\\auth_%d\\%s\\authtoken_%d\\%s",playerID,playerName.str(),playerID,gsPlayerID,playerID,slot->getTeamNumber(),playerID,result.str(),playerID,side.str(),playerID,authName.str(),playerID,authToken.str());
   results.concat(playerStr);
   ++playerID;
  }
 }
 return results;
}
