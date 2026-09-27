// ?_bfme_updateOnlinePlayerStats@@YAXPAVPlayer@@@Z
// partial score=0.730548 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "PreRTS.h"
#include "Common/GameSpyMiscPreferences.h"
template<> inline bool StringBase<char>::isEmpty()const{return !m_data||m_data->length==0;}
template<> inline const char *StringBase<char>::str()const{return m_data?m_data->data:"";}
template<> inline int StringBase<char>::compareNoCase(const char*s)const {
 int len=s?strlen(s):0;
 int myLen=m_data?m_data->length:0;
 const char*data=m_data?m_data->data:"";
 int r=_memicmp(data,s,myLen<len?myLen:len);return r?r:myLen-len;
}
typedef std::map<int, unsigned int> PerGeneralMap;
class PSPlayerStats {
public:
  PSPlayerStats();
  PSPlayerStats(const PSPlayerStats &);
  ~PSPlayerStats();
  PSPlayerStats &operator=(const PSPlayerStats &);
  Int id;                           // +0x000
  PerGeneralMap wins;               // +0x004
  PerGeneralMap losses;             // +0x010
  PerGeneralMap currentWinStreaks;  // +0x01c
  PerGeneralMap currentLossStreaks; // +0x028
  PerGeneralMap worstLossStreaks;   // +0x034
  PerGeneralMap bestWinStreaks;     // +0x040
  PerGeneralMap games;              // +0x04c
  PerGeneralMap duration;           // +0x058
  PerGeneralMap unitsKilled;        // +0x064
  PerGeneralMap unitsLost;          // +0x070
  PerGeneralMap unitsBuilt;         // +0x07c
  PerGeneralMap buildingsKilled;    // +0x088
  PerGeneralMap buildingsLost;      // +0x094
  PerGeneralMap buildingsBuilt;     // +0x0a0
  PerGeneralMap earnings;           // +0x0ac
  PerGeneralMap discons;            // +0x0b8
  PerGeneralMap desyncs;            // +0x0c4
  PerGeneralMap surrenders;         // +0x0d0
  PerGeneralMap gamesOf2p;          // +0x0dc
  PerGeneralMap gamesOf3p;          // +0x0e8
  PerGeneralMap gamesOf4p;          // +0x0f4
  PerGeneralMap gamesOf5p;          // +0x100
  PerGeneralMap gamesOf6p;          // +0x10c
  PerGeneralMap gamesOf7p;          // +0x118
  PerGeneralMap gamesOf8p;          // +0x124
  PerGeneralMap customGames;        // +0x130
  PerGeneralMap QMGames;            // +0x13c
  Int locale;                       // +0x148
  std::string dateCreated;          // +0x14c
  Int gamesAsRandom;                // +0x158
  std::string options;              // +0x15c
  std::string systemSpec;           // +0x168
  Real lastFPS;                     // +0x174
  Int lastSide;                     // +0x178
  Int gamesInRowWithLastSide;       // +0x17c
  Int challengeMedals;              // +0x180
  Int battleHonors;                 // +0x184
  Int winsInARow;                   // +0x188
  Int maxWinsInARow;                // +0x18c
  Int lossesInARow;                 // +0x190
  Int maxLossesInARow;              // +0x194
  Int gamesOn1_1_Ladder;            // +0x198
  Int gamesOn2_2_Ladder;            // +0x19c
  Int disconsInARow;                // +0x1a0
  Int maxDisconsInARow;             // +0x1a4
  Int desyncsInARow;                // +0x1a8
  Int maxDesyncsInARow;             // +0x1ac
  Int best1v1LadderRank;            // +0x1b0
  Int best2v2LadderRank;            // +0x1b4
  std::string lastLadderPlayed;     // +0x1b8
};


class PSRequest {public:PSRequest();~PSRequest();
 int requestType;PSPlayerStats player;std::string cdkey,nick,password,email;
 bool addDiscon,addDesync;int lastHouse,rva200;std::string results;
};
class PSResponse {public:int responseType;PSPlayerStats player;bool preorder;char rva1C9[0x27];};
typedef char ResponseSize[sizeof(PSResponse)==0x1f0?1:-1];
typedef char RequestSize[sizeof(PSRequest)==0x210?1:-1];
class GameSpyInfoInterface {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual int getLocalProfileID();
virtual AsciiString getLocalEmail();
virtual void slot30();
virtual AsciiString getLocalPassword();
virtual void slot32();
virtual void slot33();
virtual AsciiString getLocalBaseName();
virtual void setCachedLocalPlayerStats(PSPlayerStats);
};extern GameSpyInfoInterface *TheGameSpyInfo;
class GameSpyPSMessageQueueInterface {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual void addRequest(const PSRequest&);virtual void slot5();virtual void addResponse(const PSResponse&);
 virtual void slot7();virtual void trackPlayerStats(PSPlayerStats);virtual PSPlayerStats findPlayerStatsByID(int);
 static std::string formatPlayerKVPairs(PSPlayerStats);
};extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
class GameSlot {public:
 virtual void slot0();char gap4[0x10];int playerTemplate;char gap18[0xc];int originalPlayerTemplate;
 char gap28[4];AsciiString internalName;char gap30[0xc];unsigned lastFrame;bool wasDisconnected;
 bool isOccupied()const;bool isHuman()const;bool isAI()const;
 bool disconnected()const{return isHuman()&&wasDisconnected;}
 unsigned lastFrameInGame()const{return lastFrame;}
 int getOriginalPlayerTemplate()const{return originalPlayerTemplate;}
 int getPlayerTemplate()const{return playerTemplate;}
};
class GameSpyGameSlot:public GameSlot{};
class GameInfo {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual int getLocalSlotNum();
 GameSlot*getSlot(int);const GameSlot*getConstSlot(int)const;
 char gap4[0xa];bool surrendered;
 bool haveWeSurrendered()const{return surrendered;}
};
class GameSpyStagingRoom:public GameInfo {public:
 AsciiString generateGameSpyGameResultsPacket(bool);
 char gapF[0x43c-sizeof(GameInfo)];bool isQM;char padding[3];int qmType;
 bool isQMGame()const{return isQM;}
 int getQuickMatchType()const{return qmType;}
};
extern GameInfo*TheGameInfo;extern GameSpyStagingRoom*TheGameSpyGame;
class Player;
class PlayerTemplate {public:char prefix[8];AsciiString side;char tail[0x124-12];AsciiString getSide()const{return side;}};
class PlayerTemplateStore {public:
 int prefix[2];PlayerTemplate*begin,*end,*capacity;
 const PlayerTemplate*getNthPlayerTemplate(int)const;
 int getPlayerTemplateCount()const{return end-begin;}
};extern PlayerTemplateStore*ThePlayerTemplateStore;
class ScoreKeeper {public:
 int getTotalUnitsDestroyed();int getTotalBuildingsDestroyed();
 int getTotalMoneyEarned(){return m_totalMoneyEarned;}
int getTotalUnitsBuilt(){return m_totalUnitsBuilt;}
int getTotalUnitsLost(){return m_totalUnitsLost;}
int getTotalBuildingsBuilt(){return m_totalBuildingsBuilt;}
int getTotalBuildingsLost(){return m_totalBuildingsLost;}
void*vptr;int m_totalMoneyEarned,m_totalMoneySpent,m_totalUnitsDestroyed[32];
 int m_totalUnitsBuilt,m_totalUnitsLost,m_totalBuildingsDestroyed[32],m_totalBuildingsBuilt,m_totalBuildingsLost;
};
class Player {public:char prefix[4];PlayerTemplate*playerTemplate;char gap8[0x340];ScoreKeeper score;
 const PlayerTemplate*getPlayerTemplate()const{return playerTemplate;}
 ScoreKeeper*getScoreKeeper(){return &score;}
};
class PlayerList {public:Player*findPlayerWithNameKey(NameKeyType);};extern PlayerList*ThePlayerList;
class VictoryConditionsInterface {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual bool hasAchievedVictory(const Player*);
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual bool isLocalAlliedVictory();
virtual bool isLocalAlliedDefeat();
virtual bool isLocalDefeat();
virtual bool amIObserver();
virtual int getEndFrame();
virtual void slot18();
virtual void slot19();
virtual bool isPlayerDefeated(int);
};extern VictoryConditionsInterface*TheVictoryConditions;
struct GameLogic {char prefix[0x3c];unsigned frame;char gap40[0x2c];bool sawCRCMismatch;char gap6D[0x290-0x6d];int rva290;};
extern GameLogic*TheGameLogic;
class Display {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual float getAverageFPS();};extern Display*TheDisplay;
class GameLODManager {public:int rva0007E0F0();};extern GameLODManager*TheGameLODManager;
extern int best1v1LadderRank,best2v2LadderRank;
extern void j_000061d6();
typedef GameSpyGameSlot*(GameSpyStagingRoom::*GameSlotMethod)(int);
inline GameSlotMethod slotMethod(){union{void(*raw)();GameSlotMethod method;}f;f.raw=j_000061d6;return f.method;}
template<class T>inline const T&bfmeMax(const T&a,const T&b){return a>b?a:b;}
void _bfme_updateOnlinePlayerStats(Player *player) {
 int localID=TheGameSpyInfo->getLocalProfileID();
 if(!localID)return;
 int localSlotNum=TheGameSpyGame->getLocalSlotNum();
 GameSpyGameSlot*localSlot=(TheGameSpyGame->*slotMethod())(localSlotNum);
 if(!localSlot)return;
 if(TheVictoryConditions->amIObserver())return;
 PSPlayerStats stats=TheGameSpyPSMessageQueue->findPlayerStatsByID(localID);
 unsigned latestHumanInGame=0,lastFrameOfGame=0;
 bool gameEndedInDisconnect=false,anyNonAI=false;
 int i;
 for(i=0;i<8;++i){const GameSlot*slot=TheGameInfo->getConstSlot(i);
 if(slot->isOccupied()&&i!=localSlotNum){if(!slot->isAI())anyNonAI=true;}
 if(slot->isOccupied())lastFrameOfGame=bfmeMax(lastFrameOfGame,slot->lastFrameInGame());
 if(slot->isHuman()&&i!=localSlotNum)latestHumanInGame=bfmeMax(latestHumanInGame,slot->lastFrameInGame());
 }
 for(i=0;i<8;++i){const GameSlot*slot=TheGameInfo->getConstSlot(i);
 if(slot->isOccupied()&&slot->disconnected()&&TheGameLogic->rva290==0){gameEndedInDisconnect=true;break;}}
 if(!anyNonAI)return;
 bool sawEndOfGame=false;
 if(TheVictoryConditions->isLocalAlliedDefeat()||TheVictoryConditions->isLocalAlliedVictory())sawEndOfGame=true;
 if(TheVictoryConditions->isLocalDefeat())sawEndOfGame=true;
 if(TheGameLogic->sawCRCMismatch||gameEndedInDisconnect)sawEndOfGame=true;
 if(!TheVictoryConditions->isPlayerDefeated(localSlotNum)&&!sawEndOfGame)return;
 bool sendResults=false;
 if(TheVictoryConditions->isLocalAlliedVictory()){
 for(i=0;i<8;++i){AsciiString playerName;playerName=TheGameInfo->getSlot(i)->internalName;
 if(playerName.isEmpty())continue;
 Player*p=ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName.str()));
 if(p){GameSlot*slot=TheGameSpyGame->getSlot(i);
 if(TheVictoryConditions->hasAchievedVictory(p)&&!slot->disconnected()){
 if(TheGameSpyGame->getLocalSlotNum()==i)sendResults=true;
 break;}}
 }}
 if(sendResults){AsciiString result=TheGameSpyGame->generateGameSpyGameResultsPacket(gameEndedInDisconnect);
 PSRequest req;req.requestType=6;req.results=result.str();TheGameSpyPSMessageQueue->addRequest(req);}
 else{PSRequest req;req.requestType=7;TheGameSpyPSMessageQueue->addRequest(req);}
 if(gameEndedInDisconnect)return;
 const PlayerTemplate*myTemplate=player->getPlayerTemplate();
 int ptIdx;for(ptIdx=0;ptIdx<ThePlayerTemplateStore->getPlayerTemplateCount();++ptIdx)
 if(ThePlayerTemplateStore->getNthPlayerTemplate(ptIdx)==myTemplate)break;
 if(!stats.id){if(TheGameLogic->sawCRCMismatch){PSRequest req;req.requestType=1;
 req.email=TheGameSpyInfo->getLocalEmail().str();req.nick=TheGameSpyInfo->getLocalBaseName().str();req.password="";
 req.player=stats;req.addDesync=TheGameLogic->sawCRCMismatch;req.addDiscon=false;req.lastHouse=ptIdx;
 TheGameSpyPSMessageQueue->addRequest(req);}return;}
 int side=0;AsciiString sideStr=myTemplate->side;
 if(sideStr.compareNoCase("gondor")==0)side=1;
 else if(sideStr.compareNoCase("rohan")==0)side=0;
 else if(sideStr.compareNoCase("isengard")==0)side=3;
 else if(sideStr.compareNoCase("mordor")==0)side=2;
 if(TheGameLogic->sawCRCMismatch)++stats.desyncs[side];
 else if(TheVictoryConditions->isLocalAlliedDefeat()||!TheVictoryConditions->getEndFrame()||TheVictoryConditions->isPlayerDefeated(localSlotNum))++stats.losses[side];
 else ++stats.wins[side];
 ScoreKeeper*s=player->getScoreKeeper();
 stats.buildingsBuilt[ptIdx]+=s->getTotalBuildingsBuilt();
 stats.buildingsKilled[ptIdx]+=s->getTotalBuildingsDestroyed();
 stats.buildingsLost[ptIdx]+=s->getTotalBuildingsLost();
 if(TheGameSpyGame->isQMGame())stats.QMGames[side]++;else stats.customGames[side]++;
 if(TheGameLogic->sawCRCMismatch){++stats.desyncsInARow;stats.maxDesyncsInARow=bfmeMax(stats.desyncsInARow,stats.maxDesyncsInARow);}
 else if(TheVictoryConditions->isLocalAlliedVictory()&&!TheVictoryConditions->isPlayerDefeated(localSlotNum)){
 stats.lossesInARow=0;stats.currentLossStreaks[side]=0;stats.winsInARow++;
 stats.desyncsInARow=0;stats.disconsInARow=0;stats.currentWinStreaks[side]++;
 stats.maxWinsInARow=bfmeMax(stats.winsInARow,stats.maxWinsInARow);
 stats.bestWinStreaks[side]=bfmeMax(stats.currentWinStreaks[side],stats.bestWinStreaks[side]);
 }else{stats.lossesInARow++;stats.currentLossStreaks[side]++;stats.desyncsInARow=0;stats.disconsInARow=0;
 stats.winsInARow=0;stats.currentWinStreaks[side]=0;
 stats.maxLossesInARow=bfmeMax(stats.lossesInARow,stats.maxLossesInARow);
 stats.worstLossStreaks[side]=bfmeMax(stats.currentLossStreaks[side],stats.worstLossStreaks[side]);}
 if(TheGameSpyGame){if(TheGameSpyGame->getQuickMatchType()==1){stats.gamesOn1_1_Ladder++;stats.lastLadderPlayed="1v1";
 if(best1v1LadderRank>0){if(stats.best1v1LadderRank>0)stats.best1v1LadderRank=std::min(stats.best1v1LadderRank,best1v1LadderRank);else stats.best1v1LadderRank=best1v1LadderRank;}}
 else if(TheGameSpyGame->getQuickMatchType()==2){stats.gamesOn2_2_Ladder++;stats.lastLadderPlayed="2v2";
 if(best2v2LadderRank>0){if(stats.best2v2LadderRank>0)stats.best2v2LadderRank=std::min(stats.best2v2LadderRank,best2v2LadderRank);else stats.best2v2LadderRank=best2v2LadderRank;}}}
 stats.earnings[ptIdx]+=s->getTotalMoneyEarned();
 stats.duration[ptIdx]+=TheGameLogic->frame/5/60;
 stats.games[side]++;
 stats.gamesAsRandom+=(localSlot->getOriginalPlayerTemplate()==-1);
 if(stats.lastSide!=side)stats.gamesInRowWithLastSide=0;
 ++stats.gamesInRowWithLastSide;stats.lastSide=side;
 int gameSize=0;for(i=0;i<8;++i)if(TheGameSpyGame->getConstSlot(i)->isOccupied()&&TheGameSpyGame->getConstSlot(i)->getPlayerTemplate()!=-2)++gameSize;
 switch(gameSize){case 2:++stats.gamesOf2p[ptIdx];break;case 3:++stats.gamesOf3p[ptIdx];break;case 4:++stats.gamesOf4p[ptIdx];break;
 case 5:++stats.gamesOf5p[ptIdx];break;case 6:++stats.gamesOf6p[ptIdx];break;case 7:++stats.gamesOf7p[ptIdx];break;case 8:++stats.gamesOf8p[ptIdx];break;default:return;}
 stats.lastFPS=TheDisplay->getAverageFPS();
 stats.surrenders[ptIdx]+=TheGameInfo->haveWeSurrendered()||!TheVictoryConditions->getEndFrame();
 AsciiString systemSpec;systemSpec.format("LOD%d",TheGameLODManager->rva0007E0F0());stats.systemSpec=systemSpec.str();
 stats.unitsBuilt[ptIdx]+=s->getTotalUnitsBuilt();stats.unitsKilled[ptIdx]+=s->getTotalUnitsDestroyed();stats.unitsLost[ptIdx]+=s->getTotalUnitsLost();
 if(!TheGameLogic->sawCRCMismatch&&!TheVictoryConditions->isLocalAlliedDefeat())TheVictoryConditions->getEndFrame();
 PSRequest req;req.requestType=1;req.email=TheGameSpyInfo->getLocalEmail().str();req.nick=TheGameSpyInfo->getLocalBaseName().str();
 req.password=TheGameSpyInfo->getLocalPassword().str();req.player=stats;req.addDesync=TheGameLogic->sawCRCMismatch;req.addDiscon=false;req.lastHouse=ptIdx;
 TheGameSpyPSMessageQueue->addRequest(req);TheGameSpyPSMessageQueue->trackPlayerStats(stats);
 PSResponse newResp;newResp.responseType=0;newResp.player=stats;TheGameSpyPSMessageQueue->addResponse(newResp);
 GameSpyMiscPreferences mPref;mPref.setCachedStats(GameSpyPSMessageQueueInterface::formatPlayerKVPairs(stats).c_str());mPref.write();
 TheGameSpyInfo->setCachedLocalPlayerStats(stats);
}
