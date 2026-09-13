// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// GameSpyStagingRoom::generateLadderGameResultsPacket, RVA 0x00639190.
// Complete retail extent 1583: RET 4 at +0x62c, then INT3 at +0x62f. The old
// 1580-byte naked claim omitted the return instruction.
// Identity: score-screen caller and ILT routes documented in symbols.csv;
// BFME slot stride 0x78, GameInfo 0x58 and PSPlayerStats 0x1c4 are byte-derived.

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
 void concat(const char*s){StringBase<char>::concat(s,strlen(s));}
 int compare(const char *s)const {int n=strlen(s),m;const char*p;if(m_data){m=m_data->length;p=m_data->text;}else{m=0;p="";}int result=memcmp(p,s,m<n?m:n);return result?result:m-n;}
 void __cdecl format(AsciiString,...);
};
// Existing matched +0x48 string getter, reached through retail ILT 0x28565.
class Rva00505D10StringOwner {public:AsciiString value();};
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
 AsciiString generateLadderGameResultsPacket();
 AsciiString getLadderIP()const;
 unsigned int getSeed()const{return seed;}
 unsigned short getLadderPort()const{return ladderPort;}
 bool isQuickMatch()const{return isQM;}
 GameSpyGameSlot slots[8];char extra[0x24];bool isQM;char qmGap[3];int qmType;char ladderGap[12];unsigned short ladderPort;
};
struct PlayerTemplate {char prefix[8];AsciiString side;const AsciiString&getSide()const{return side;}};
class ScoreKeeper{public:
 char prefix[4];int earnings;char gap[0x84];int unitsBuilt,unitsLost;char gap2[0x80];int buildingsBuilt,buildingsLost;
 int getTotalUnitsDestroyed();int getTotalBuildingsDestroyed();
 int getTotalUnitsLost()const{return unitsLost;}
 int getTotalUnitsBuilt()const{return unitsBuilt;}
 int getTotalBuildingsLost()const{return buildingsLost;}
 int getTotalBuildingsBuilt()const{return buildingsBuilt;}
 int getTotalMoneyEarned()const{return earnings;}

};
class Player {public:char prefix[4];PlayerTemplate*playerTemplate;char gap[0x340];ScoreKeeper keeper;ScoreKeeper*getScoreKeeper(){return &keeper;}const PlayerTemplate*getPlayerTemplate()const{return playerTemplate;}};
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

class GameState{public:AsciiString realMapPathToPortableMapPath(const AsciiString&)const;};
class PSPlayerStats{public:char prefix[0x148];int locale;char tail[0x78];~PSPlayerStats();};
class GameSpyPSMessageQueue{public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();
 virtual PSPlayerStats findPlayerStatsByID(int);
};
extern GameState*TheGameState;
extern GameSpyPSMessageQueue*TheGameSpyPSMessageQueue;
AsciiString GameSpyStagingRoom::generateLadderGameResultsPacket()
{
 int i;
 int endFrame=TheVictoryConditions->getEndFrame();
 int localSlotNum=getLocalSlotNum();
 bool sawGameEnd=endFrame>0;
 int winningTeam=-1,numPlayers=0,numTeamsAtGameEnd=0,lastTeamAtGameEnd=-1;
 Player*p[8];
 for(i=0;i<8;++i){
  AsciiString playerName;
  playerName=TheGameInfo->getSlot(i)->internalName;
  p[i]=ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName.str()));
  if(p[i]){
   ++numPlayers;
   if(TheVictoryConditions->hasAchievedVictory(p[i]))winningTeam=getSlot(i)->getTeamNumber();
   GameSlot*slot=getSlot(i);
   if(!slot->disconnected()){
    if(slot->getTeamNumber()!=lastTeamAtGameEnd||numTeamsAtGameEnd==0){lastTeamAtGameEnd=slot->getTeamNumber();++numTeamsAtGameEnd;}
   }
  }
 }
 AsciiString results;
 results.format("seed=%d,slotNum=%d,sawDesync=%d,sawGameEnd=%d,winningTeam=%d,disconEnd=%d,duration=%d,numPlayers=%d,isQM=%d,map=%s",getSeed(),localSlotNum,TheGameLogic->sawMismatch,sawGameEnd,winningTeam,numTeamsAtGameEnd<2,endFrame,numPlayers,isQuickMatch(),TheGameState->realMapPathToPortableMapPath(getMap()).str());
 AsciiString tempStr;
 tempStr.format(",ladderIP=%s,ladderPort=%d",getLadderIP().str(),getLadderPort());
 results.concat(tempStr);
 int playerID=0;
 for(i=0;i<8;++i){
  AsciiString playerName;
  playerName=TheGameInfo->getSlot(i)->internalName;
  if(p[i]){
   GameSpyGameSlot*slot=&slots[i];
   ScoreKeeper*keeper=p[i]->getScoreKeeper();
   AsciiString playerName=((Rva00505D10StringOwner*)slot)->value();
   int gsPlayerID=slot->profileID;
   PSPlayerStats stats=TheGameSpyPSMessageQueue->findPlayerStatsByID(gsPlayerID);
   int unitsKilled=keeper->getTotalUnitsDestroyed();
   int unitsLost=keeper->getTotalUnitsLost();
   int unitsBuilt=keeper->getTotalUnitsBuilt();
   int buildingsKilled=keeper->getTotalBuildingsDestroyed();
   int buildingsLost=keeper->getTotalBuildingsLost();
   int buildingsBuilt=keeper->getTotalBuildingsBuilt();
   int earnings=keeper->getTotalMoneyEarned();
   bool disconnected=slot->disconnected();
   AsciiString playerStr;
   playerStr.format(",player%d=%s,playerID%d=%d,locale%d=%d",playerID,playerName.str(),playerID,gsPlayerID,playerID,stats.locale);
   results.concat(playerStr);
   playerStr.format(",unitsKilled%d=%d,unitsLost%d=%d,unitsBuilt%d=%d",playerID,unitsKilled,playerID,unitsLost,playerID,unitsBuilt);
   results.concat(playerStr);
   playerStr.format(",buildingsKilled%d=%d,buildingsLost%d=%d,buildingsBuilt%d=%d",playerID,buildingsKilled,playerID,buildingsLost,playerID,buildingsBuilt);
   results.concat(playerStr);
   // Retail +0x4AB passes an extra LEADING playerID. This malformed call shifts
   // all six conversions: %s consumes playerID as a pointer, and the actual
   // side string is the unused seventh argument. Preserve the retail bug for
   // byte matching; deleting the argument would change both bytes and behavior.
   playerStr.format(",cash%d=%d,discon%d=%d,side%d=%s",playerID,playerID,earnings,playerID,disconnected,playerID,p[i]->getPlayerTemplate()->getSide().str());
   results.concat(playerStr);
   ++playerID;
  }
 }
 results.concat(",size=");
 int resultsLen=results.getLength()+10;
 AsciiString tail;
 tail.format("%10.10d",resultsLen);
 results.concat(tail);
 return results;
}
