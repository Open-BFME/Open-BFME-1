// ?Thread_Function@PSThreadClass@@UAEXXZ
// partial score=0.987 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native reconstruction derived from EA PersistentStorageThread.cpp (GPL-3.0-or-later).
// This is a banked near miss, not a verified game source. See 0065ca50-storage-worker.md.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#include "ascii_string.h"
#include "PreRTS.h"
#include "Common/UserPreferences.h"
#include "mutex.h"
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef std::map<int,unsigned int> PerGeneralMap;
class PSPlayerStats
{
public:
 PSPlayerStats();PSPlayerStats(const PSPlayerStats&);~PSPlayerStats();
	Int id;                             // +0x000
	PerGeneralMap wins;                 // +0x004
	PerGeneralMap losses;               // +0x010
	PerGeneralMap currentWinStreaks;    // +0x01c
	PerGeneralMap currentLossStreaks;   // +0x028
	PerGeneralMap worstLossStreaks;     // +0x034
	PerGeneralMap bestWinStreaks;       // +0x040
	PerGeneralMap games;                // +0x04c
	PerGeneralMap duration;             // +0x058
	PerGeneralMap unitsKilled;          // +0x064
	PerGeneralMap unitsLost;            // +0x070
	PerGeneralMap unitsBuilt;           // +0x07c
	PerGeneralMap buildingsKilled;      // +0x088
	PerGeneralMap buildingsLost;        // +0x094
	PerGeneralMap buildingsBuilt;       // +0x0a0
	PerGeneralMap earnings;             // +0x0ac
	PerGeneralMap discons;              // +0x0b8
	PerGeneralMap desyncs;              // +0x0c4
	PerGeneralMap surrenders;           // +0x0d0
	PerGeneralMap gamesOf2p;            // +0x0dc
	PerGeneralMap gamesOf3p;            // +0x0e8
	PerGeneralMap gamesOf4p;            // +0x0f4
	PerGeneralMap gamesOf5p;            // +0x100
	PerGeneralMap gamesOf6p;            // +0x10c
	PerGeneralMap gamesOf7p;            // +0x118
	PerGeneralMap gamesOf8p;            // +0x124
	PerGeneralMap customGames;          // +0x130
	PerGeneralMap QMGames;              // +0x13c
	Int locale;                         // +0x148
	std::string dateCreated;            // +0x14c
	Int gamesAsRandom;                  // +0x158
	std::string options;                // +0x15c
	std::string systemSpec;             // +0x168
	Real lastFPS;                       // +0x174
	Int lastSide;                       // +0x178
	Int gamesInRowWithLastSide;         // +0x17c
	Int challengeMedals;                // +0x180
	Int battleHonors;                   // +0x184
	Int winsInARow;                     // +0x188
	Int maxWinsInARow;                  // +0x18c
	Int lossesInARow;                   // +0x190
	Int maxLossesInARow;                // +0x194
	Int gamesOn1_1_Ladder;              // +0x198
	Int gamesOn2_2_Ladder;              // +0x19c
	Int disconsInARow;                  // +0x1a0
	Int maxDisconsInARow;               // +0x1a4
	Int desyncsInARow;                  // +0x1a8
	Int maxDesyncsInARow;               // +0x1ac
	Int best1v1LadderRank;              // +0x1b0
	Int best2v2LadderRank;              // +0x1b4
	std::string lastLadderPlayed;       // +0x1b8
};


class PSRequest {public:
 PSRequest();~PSRequest();
 enum RequestType {PSREQUEST_READPLAYERSTATS,PSREQUEST_UPDATEPLAYERSTATS,PSREQUEST_UPDATEPLAYERLOCALE,PSREQUEST_READCDKEYSTATS};
 RequestType requestType;PSPlayerStats player;std::string cdkey,nick,password,email;bool addDiscon,addDesync;int lastHouse,rva200;std::string results;
};
typedef char RequestExtent[sizeof(PSRequest)==0x210?1:-1];
class GameSpyPSMessageQueue {public:
 virtual void slot0();virtual void slot4();virtual void slot8();virtual void slotC();virtual void slot10();virtual bool getRequest(PSRequest&);virtual void slot18();virtual void slot1C();virtual void trackPlayerStats(PSPlayerStats);
 char prefix[0x64];int localID;
 int getLocalPlayerID(){return localID;}void setLocalPlayerID(int id){localID=id;}
 void setEmail(std::string);void setNick(std::string);void setPassword(std::string);
};
class GameSpyPSMessageQueueInterface {public:static std::string formatPlayerKVPairs(PSPlayerStats);};
class BfmeQueueEUG;extern BfmeQueueEUG *g_bfmeQueueEUG;
#define TheGameSpyPSMessageQueue ((GameSpyPSMessageQueue*)g_bfmeQueueEUG)
#define MESSAGE_QUEUE TheGameSpyPSMessageQueue
struct statsgame_s;typedef statsgame_s *statsgame_t;
class GameSpyStagingRoom {public:char prefix[0x464];statsgame_t statsGame;};extern GameSpyStagingRoom *TheGameSpyGame;
struct Rva0065CA50HttpRecord;
class PSThreadClass {public:
 virtual void slot0();virtual void slot4();virtual void Thread_Function();
 char prefix[0x4c];bool m_loginOK,m_doneTryingToLogin;int m_opCount;bool m_sawLocalData;
 std::map<int,Rva0065CA50HttpRecord*> m_requests;MutexClass *m_ownerLock;
 void incrOpCount(){++m_opCount;}void decrOpCount(){--m_opCount;}
private:bool tryConnect();bool tryLogin(int,std::string,std::string,std::string);
};
class BFMENetworkBackend {public:void requestLadderPlayerCount(int);void _bfme_requestLadderRank(int);};
class BfmeHostXK {public:void bfmeStartXK();};
extern "C" {int IsStatsConnected();int InitStatsConnection(int);statsgame_t NewGame(int);int SendGameSnapShotA(statsgame_t,const char*,int);void FreeGame(statsgame_t);void CloseStatsConnection();int PersistThink();
void GenerateAuthA(char*,char*,char*);char* GetChallenge(statsgame_t);
typedef void (__cdecl *GetDataCallback)(int,int,int,int,int,long,char*,int,void*);
typedef void (__cdecl *SetDataCallback)(int,int,int,int,int,long,void*);
void GetPersistDataValuesA(int,int,int,int,char*,GetDataCallback,void*);
void SetPersistDataValuesA(int,int,int,int,char*,SetDataCallback,void*);
void PreAuthenticatePlayerCDA(int,char*,char*,char*,void(__cdecl*)(int,int,int,char*,void*),void*);
void BFMENetworkRegisteredCallback(int,int,int,int,int,long,char*,int,void*);
int ghttpRequestThink(int);
}
void setPersistentDataLocaleCallback(int,int,int,int,int,long,void*);
void setPersistentDataCallback(int,int,int,int,int,long,void*);
void getPreorderCallback(int,int,int,int,int,long,char*,int,void*);
void preAuthCDCallback(int,int,int,char*,void*);
char *BFMEDuplicateString(const char*) throw();
struct CDAuthInfo {bool success,done;int id;};
#define pd_public_rw 3
#define pd_public_ro 2
#define GetPersistDataValues GetPersistDataValuesA
#define SetPersistDataValues SetPersistDataValuesA
#define getPersistentDataCallback BFMENetworkRegisteredCallback
#define GenerateAuth GenerateAuthA
#define PreAuthenticatePlayerCD PreAuthenticatePlayerCDA
#define strdup BFMEDuplicateString
#define DEBUG_LOG(x)
#define DEBUG_ASSERTCRASH(x,y)
bool PSThreadClass::tryConnect(){if(IsStatsConnected())return true;int result=InitStatsConnection(0);if(result!=0)return false;return true;}
void PSThreadClass::Thread_Function(){try {
 PSRequest req;
 while(1) {
  MutexClass::LockClass lock(*m_ownerLock,1);
  bool hasRequest=TheGameSpyPSMessageQueue->getRequest(req);
  if(!lock.Failed() && !hasRequest) break;
  if(hasRequest) switch(req.requestType) {
  case 5:
   if(tryConnect() && TheGameSpyGame){incrOpCount();TheGameSpyGame->statsGame=NewGame(0);}break;
  case 6:
   if(!IsStatsConnected()) {
    if(TheGameSpyGame && TheGameSpyGame->statsGame){FreeGame(TheGameSpyGame->statsGame);TheGameSpyGame->statsGame=0;}
   }else if(TheGameSpyGame){
    const char *p=req.results.c_str();int len=req.results.size();int offset=0;
    while(len>0){offset+=(std::min)(511,len);len-=(std::min)(511,len);}
    SendGameSnapShotA(0,p,1);
    if(TheGameSpyGame->statsGame){FreeGame(TheGameSpyGame->statsGame);TheGameSpyGame->statsGame=0;}
    decrOpCount();
   }
   break;
  case 7:
   if(!IsStatsConnected()){
    if(TheGameSpyGame && TheGameSpyGame->statsGame){FreeGame(TheGameSpyGame->statsGame);TheGameSpyGame->statsGame=0;}
   }else if(TheGameSpyGame){if(TheGameSpyGame->statsGame){SendGameSnapShotA(0,"",1);FreeGame(TheGameSpyGame->statsGame);TheGameSpyGame->statsGame=0;}decrOpCount();}
   break;
			case PSRequest::PSREQUEST_READPLAYERSTATS:
				{
					if (!MESSAGE_QUEUE->getLocalPlayerID())
					{
						MESSAGE_QUEUE->setLocalPlayerID(req.player.id); // first request is for ourselves
						MESSAGE_QUEUE->setEmail(req.email);
						MESSAGE_QUEUE->setNick(req.nick);
						MESSAGE_QUEUE->setPassword(req.password);
						DEBUG_LOG(("Setting email/nick/password = %s/%s/%s\n", req.email.c_str(), req.nick.c_str(), req.password.c_str()));
					}
					DEBUG_LOG(("Processing PSRequest::PSREQUEST_READPLAYERSTATS\n"));
					if (tryConnect())
					{
						incrOpCount();
						GetPersistDataValues(0, req.player.id, pd_public_rw, 0, "", getPersistentDataCallback, this);
					}
					((BFMENetworkBackend*)this)->_bfme_requestLadderRank(req.player.id);
					if(MESSAGE_QUEUE->getLocalPlayerID()==req.player.id){((BFMENetworkBackend*)this)->requestLadderPlayerCount(1);((BFMENetworkBackend*)this)->requestLadderPlayerCount(2);}
				}
				break;
			case PSRequest::PSREQUEST_UPDATEPLAYERLOCALE:
				{
					DEBUG_LOG(("Processing PSRequest::PSREQUEST_UPDATEPLAYERLOCALE\n"));
					if (tryConnect() && tryLogin(req.player.id, req.nick, req.password, req.email))
					{
						char kvbuf[256];
						sprintf(kvbuf, "\\locale\\%d", req.player.locale);
						incrOpCount();
						SetPersistDataValues(0, req.player.id, pd_public_rw, 0, kvbuf, setPersistentDataLocaleCallback, this);
					}
				}
				break;
			case PSRequest::PSREQUEST_UPDATEPLAYERSTATS:
				{
					/*
					** NOTE THAT THIS IS HIGHLY DEPENDENT ON INI ORDERING FOR THE PLAYERTEMPLATES!!!
					*/
					DEBUG_LOG(("Processing PSRequest::PSREQUEST_UPDATEPLAYERSTATS\n"));
					UserPreferences pref;
					AsciiString userPrefFilename;
					userPrefFilename.format("LoTRB4MEOnline\\MiscPref%d.ini", MESSAGE_QUEUE->getLocalPlayerID());
					DEBUG_LOG(("using the file %s\n", userPrefFilename.str()));
					pref.load(userPrefFilename);
					Int addedInDesyncs2 = pref.getInt("0", 0);
					DEBUG_LOG(("addedInDesyncs2 = %d\n", addedInDesyncs2));
					if (addedInDesyncs2 < 0)
						addedInDesyncs2 = 10;
					Int addedInDesyncs3 = pref.getInt("1", 0);
					DEBUG_LOG(("addedInDesyncs3 = %d\n", addedInDesyncs3));
					if (addedInDesyncs3 < 0)
						addedInDesyncs3 = 10;
					Int addedInDesyncs4 = pref.getInt("2", 0);
					DEBUG_LOG(("addedInDesyncs4 = %d\n", addedInDesyncs4));
					if (addedInDesyncs4 < 0)
						addedInDesyncs4 = 10;
					Int addedInDiscons2 = pref.getInt("3", 0);
					DEBUG_LOG(("addedInDiscons2 = %d\n", addedInDiscons2));
					if (addedInDiscons2 < 0)
						addedInDiscons2 = 10;
					Int addedInDiscons3 = pref.getInt("4", 0);
					DEBUG_LOG(("addedInDiscons3 = %d\n", addedInDiscons3));
					if (addedInDiscons3 < 0)
						addedInDiscons3 = 10;
					Int addedInDiscons4 = pref.getInt("5", 0);
					DEBUG_LOG(("addedInDiscons4 = %d\n", addedInDiscons4));
					if (addedInDiscons4 < 0)
						addedInDiscons4 = 10;

					DEBUG_LOG(("req.addDesync=%d, req.addDiscon=%d, addedInDesync=%d,%d,%d, addedInDiscon=%d,%d,%d\n",
						req.addDesync, req.addDiscon, addedInDesyncs2, addedInDesyncs3, addedInDesyncs4,
						addedInDiscons2, addedInDiscons3, addedInDiscons4));

					if (req.addDesync || req.addDiscon)
					{
						AsciiString val;
						if (req.lastHouse == 2)
						{
							val.format("%d", addedInDesyncs2 + req.addDesync);
							pref["0"] = val;
							val.format("%d", addedInDiscons2 + req.addDiscon);
							pref["3"] = val;
							DEBUG_LOG(("house 2 req.addDesync || req.addDiscon: %d %d\n",
								addedInDesyncs2 + req.addDesync, addedInDiscons2 + req.addDiscon));
						}
						else if (req.lastHouse == 3)
						{
							val.format("%d", addedInDesyncs3 + req.addDesync);
							pref["1"] = val;
							val.format("%d", addedInDiscons3 + req.addDiscon);
							pref["4"] = val;
							DEBUG_LOG(("house 3 req.addDesync || req.addDiscon: %d %d\n",
								addedInDesyncs3 + req.addDesync, addedInDiscons3 + req.addDiscon));
						}
						else
						{
							val.format("%d", addedInDesyncs4 + req.addDesync);
							pref["2"] = val;
							val.format("%d", addedInDiscons4 + req.addDiscon);
							pref["5"] = val;
							DEBUG_LOG(("house 4 req.addDesync || req.addDiscon: %d %d\n",
								addedInDesyncs4 + req.addDesync, addedInDiscons4 + req.addDiscon));
						}
						pref.write();
						if (req.password.size() == 0)
							return;
					}
					if (!req.player.id)
					{
						DEBUG_LOG(("Bailing because ID is NULL!\n"));
						return;
					}
					req.player.desyncs[2] += addedInDesyncs2;
					req.player.games[2] += addedInDesyncs2;
					req.player.discons[2] += addedInDiscons2;
					req.player.games[2] += addedInDiscons2;
					req.player.desyncs[3] += addedInDesyncs3;
					req.player.games[3] += addedInDesyncs3;
					req.player.discons[3] += addedInDiscons3;
					req.player.games[3] += addedInDiscons3;
					req.player.desyncs[4] += addedInDesyncs4;
					req.player.games[4] += addedInDesyncs4;
					req.player.discons[4] += addedInDiscons4;
					req.player.games[4] += addedInDiscons4;
					DEBUG_LOG(("House2: %d/%d/%d, House3: %d/%d/%d, House4: %d/%d/%d\n",
						req.player.desyncs[2], req.player.discons[2], req.player.games[2],
						req.player.desyncs[3], req.player.discons[3], req.player.games[3],
						req.player.desyncs[4], req.player.discons[4], req.player.games[4]
						));
					if (tryConnect() && tryLogin(req.player.id, req.nick, req.password, req.email))
					{
						DEBUG_LOG(("Logged in!\n"));
						if (TheGameSpyPSMessageQueue)
							TheGameSpyPSMessageQueue->trackPlayerStats(req.player);

						char *munkeeHack = strdup(GameSpyPSMessageQueueInterface::formatPlayerKVPairs(req.player).c_str()); // GS takes a char* for some reason
						incrOpCount();
						DEBUG_LOG(("Setting values %s\n", munkeeHack));
						SetPersistDataValues(0, req.player.id, pd_public_rw, 0, munkeeHack, setPersistentDataCallback, this);
						free(munkeeHack);
					}
					else
					{
						DEBUG_LOG(("Cannot connect!\n"));
						//if (IsStatsConnected())
							//CloseStatsConnection();
					}
				}
				break;

 case 11: {
  if(tryConnect() && tryLogin(req.player.id,req.nick,req.password,req.email)){
   incrOpCount();char kvbuf[128];
   if(req.player.best1v1LadderRank>0) sprintf(kvbuf,"\\best1v1LadderRank\\%d",req.player.best1v1LadderRank);
   if(req.player.best2v2LadderRank>0) sprintf(kvbuf+strlen(kvbuf),"\\best2v2LadderRank\\%d",req.player.best2v2LadderRank);
   SetPersistDataValues(0,req.player.id,3,0,kvbuf,setPersistentDataCallback,this);
  }
 }break;
			case PSRequest::PSREQUEST_READCDKEYSTATS:
				{
					DEBUG_LOG(("Processing PSRequest::PSREQUEST_READCDKEYSTATS\n"));
					if (tryConnect())
					{
						incrOpCount();
						CDAuthInfo cdAuthInfo;
						cdAuthInfo.done = FALSE;
						cdAuthInfo.success = FALSE;
						cdAuthInfo.id = 0;
						char cdkeyHash[33] = "";
						char validationToken[33] = "";
						char *munkeeHack = strdup(req.cdkey.c_str()); // GenerateAuth takes a char*, not a const char* :P

						GenerateAuth(GetChallenge(NULL), munkeeHack, validationToken); // validation token
						GenerateAuth("", munkeeHack, cdkeyHash); // cdkey hash

						free (munkeeHack);

						PreAuthenticatePlayerCD( 0, "preorder", cdkeyHash, validationToken, preAuthCDCallback , &cdAuthInfo);

						while(1) {MutexClass::LockClass cdLock(*m_ownerLock,1);if(!cdLock.Failed() || !IsStatsConnected() || cdAuthInfo.done)break;PersistThink();}

						DEBUG_LOG(("Looking for preorder status for %d (success=%d, done=%d) from CDKey %s with hash %s\n",
							cdAuthInfo.id, cdAuthInfo.success, cdAuthInfo.done, req.cdkey.c_str(), cdkeyHash));
						if (cdAuthInfo.done && cdAuthInfo.success)
							GetPersistDataValues(0, cdAuthInfo.id, pd_public_ro, 0, "\\preorder", getPreorderCallback, this);
						else
							decrOpCount();
					}
				}
				break;
 case 10:((BfmeHostXK*)this)->bfmeStartXK();break;
 }
 if(IsStatsConnected()){PersistThink();if(m_opCount<=0){CloseStatsConnection();m_opCount=0;}}
 std::map<int,Rva0065CA50HttpRecord*>::iterator it=m_requests.begin();
 while(it!=m_requests.end()){std::map<int,Rva0065CA50HttpRecord*>::iterator next=it;++next;ghttpRequestThink(it->first);it=next;}
 }
 if(IsStatsConnected())CloseStatsConnection();
 }catch(...){}
}
