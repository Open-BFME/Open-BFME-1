// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// GameSpyStagingRoom::generateGameSpyGameResultsPacket, RVA 0x006386F0, 1684B.
// Score-screen callers use ILT 0x22A34 and the BFME bool parameter (ret8).
// Native seed/quick-match accessors fix the compiler register allocation that
// made the previous bank ten bytes too long. String getter owners retain
// address-derived names; actual fields +0x70/+0x74 supply auth/auth-token.

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
class Rva00638030StringOwner{public:AsciiString value();};
class Rva006380C0StringOwner{public:AsciiString value();};
class Rva00505D10StringOwner{public:AsciiString value();};
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
 int getProfileID()const{return profileID;}
 int profileID;
 AsciiString login;
 char opaque[0x24];
 AsciiString authName,authToken;

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
 unsigned int getSeed()const{return seed;}
 GameSpyGameSlot*getGameSpySlot(int i){return &slots[i];}
 bool isQuickMatch()const{return isQM;}
 int getQuickMatchType()const{return qmType;}
 GameSpyGameSlot slots[8];char extra[0x24];bool isQM;char qmGap[3];int qmType;
};
struct PlayerTemplate {char prefix[8];AsciiString side;const AsciiString&getSide()const{return side;}};
class Player {public:char prefix[4];PlayerTemplate*playerTemplate;const PlayerTemplate*getPlayerTemplate()const{return playerTemplate;}};
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
 if(isQuickMatch()){if(getQuickMatchType()==1)ladder="1v1";else if(getQuickMatchType()==2)ladder="2v2";else ladder="none";}else ladder="none";
 AsciiString results;
 results.format("\\seed\\%d\\hostname\\%s\\mapname\\%s\\numplayers\\%d\\duration\\%d\\gamemode\\exiting\\localplayer\\%d\\ladder\\%s",getSeed(),((Rva00505D10StringOwner*)&slots[0])->value().str(),mapName.str(),numPlayers,endFrame,localSlotNum,ladder.str());
 int playerID=0;
 for(i=0;i<8;++i){
  AsciiString playerName;
  playerName=TheGameInfo->getSlot(i)->internalName;
  Player*p=playerName.isEmpty()?0:ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName.str()));
  if(p){
   GameSpyGameSlot*slot=getGameSpySlot(i);
   AsciiString authName=((Rva00638030StringOwner*)slot)->value();
   AsciiString authToken=((Rva006380C0StringOwner*)slot)->value();
   AsciiString playerName=slot->isHuman()?((Rva00505D10StringOwner*)slot)->value():"AIPlayer";
   int gsPlayerID=slot->getProfileID();
   bool disconnected=slot->disconnected();
   AsciiString result="loss";
   AsciiString side="USA";
   if(forceDisconnect)result="discon";
   else if(TheGameLogic->sawMismatch)result="desync";
   else if(disconnected&&isQM&&qmType==1)result="loss";
   else if(TheVictoryConditions->hasAchievedVictory(p))result="win";
   side=p->getPlayerTemplate()->getSide();
   if(side.compare("America")==0)side="USA";
   AsciiString playerStr;
   playerStr.format("\\player_%d\\%s\\pid_%d\\%d\\team_%d\\%d\\result_%d\\%s\\side_%d\\%s\\auth_%d\\%s\\authtoken_%d\\%s",playerID,playerName.str(),playerID,gsPlayerID,playerID,slot->getTeamNumber(),playerID,result.str(),playerID,side.str(),playerID,authName.str(),playerID,authToken.str());
   results.concat(playerStr);
   ++playerID;
  }
 }
 return results;
}
