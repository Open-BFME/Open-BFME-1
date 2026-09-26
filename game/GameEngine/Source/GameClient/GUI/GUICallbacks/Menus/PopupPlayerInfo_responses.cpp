// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Opaque identity retained: RVA 0x004DD2B0, 2116 bytes including the six-case
// switch table (2089 instruction bytes + 3 alignment bytes + 24 table bytes).
// Strong source-family identity is HandlePersistentStorageResponses from the
// PopupPlayerInfo.cpp TU sandwich, PopupPlayerInfo.wnd literal, and call family.
// Native BFME adds cases 3/4/5; their unproved payload names retain offsets.
// PSPlayerStats layout is independently witnessed by formatPlayerKVPairs
// (0x00655360); full instruction evidence is in astra_P/LAYOUTS.md.
#include <map>
#include <string>
#include <vector>
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
typedef int Int;
typedef bool Bool;
typedef float Real;
typedef std::map<int,unsigned int> PerGeneralMap;
class PSPlayerStats { public:
    PSPlayerStats(); PSPlayerStats(const PSPlayerStats&); ~PSPlayerStats();
    PSPlayerStats& operator=(const PSPlayerStats&);
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
class PlayerInfo { public:
    PlayerInfo(); PlayerInfo(const PlayerInfo&); ~PlayerInfo();
    AsciiString m_name, m_baseName, m_locale;
    int m_wins, m_losses, m_profileID, m_flags, m_rankPoints;
    int field_20, field_24, field_28, m_side, m_preorder;
};
struct AsciiComparator { bool operator()(AsciiString,AsciiString) const; };
typedef std::map<AsciiString,PlayerInfo,AsciiComparator> PlayerInfoMap;
class PSResponse { public:
    enum { PSRESPONSE_PLAYERSTATS, PSRESPONSE_COULDNOTCONNECT, PSRESPONSE_PREORDER,
        Rva004DD2B0Case3, Rva004DD2B0Case4, Rva004DD2B0Case5 } responseType;
    PSPlayerStats player;
    int field_1c8, field_1cc, field_1d0, field_1d4, field_1d8;
    unsigned int *field_1dc,*field_1e0,*field_1e4,*field_1e8;
    bool preorder;
};
class PeerRequest { public:
    PeerRequest(); ~PeerRequest();
    enum {PEERREQUEST_PUSHSTATS=19,Rva004DD2B0Request25=25} peerRequestType;
    std::string nick; std::wstring text; std::string password,email,id,options,ladderIP,hostPingStr,gameOptsMapName;
    std::string gameOptsPlayerNames[8]; std::vector<bool> qmMaps;
    union {
        struct { int locale,wins,losses,rankPoints,side; bool preorder; } statsToPush;
        struct { int field_e4,field_e8; } ranks;
        unsigned char field_e4[0xb0];
    };
};
class PeerResponse { public:
    PeerResponse(); ~PeerResponse();
    enum {PEERRESPONSE_PLAYERINFO=13} peerResponseType;
    std::string groupRoomName,nick,oldNick;
    std::wstring text;
    std::string locale,stagingServerGameOptions;
    std::wstring stagingServerName;
    std::string stagingServerPingString,stagingServerLadderIP,stagingRoomMapName;
    std::string stagingRoomPlayerNames[8],command,commandOptions;
    struct {
        int profileID,wins,losses,roomType,flags;
        unsigned int IP;
        int rankPoints,side,preorder;
        unsigned int internalIP,externalIP;
        unsigned char field_120[0x204];
        int field_324,field_328,field_32c;
    } player;
};
class GameSpyMiscPreferences { public:
    GameSpyMiscPreferences(); virtual ~GameSpyMiscPreferences();
    int getLocale();
    unsigned char field_04[0x10];
};
class GameTextInterface { public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual UnicodeString fetch(const char *,bool * = 0)=0;
};
class GameSpyInfoInterface { public:
    virtual void slot00()=0;
    virtual void slot04()=0;
    virtual void slot08()=0;
    virtual void slot0c()=0;
    virtual void slot10()=0;
    virtual void slot14()=0;
    virtual void slot18()=0;
    virtual void slot1c()=0;
    virtual void slot20()=0;
    virtual void slot24()=0;
    virtual void slot28()=0;
    virtual void slot2c()=0;
    virtual void slot30()=0;
    virtual void slot34()=0;
    virtual void slot38()=0;
    virtual void slot3c()=0;
    virtual void slot40()=0;
    virtual void slot44()=0;
    virtual PlayerInfoMap *getPlayerInfoMap()=0;
    virtual void slot4c()=0;
    virtual void slot50()=0;
    virtual void slot54()=0;
    virtual void slot58()=0;
    virtual void slot5c()=0;
    virtual void slot60()=0;
    virtual void slot64()=0;
    virtual void slot68()=0;
    virtual void slot6c()=0;
    virtual int getLocalProfileID()=0;
    virtual void slot74()=0;
    virtual void slot78()=0;
    virtual void slot7c()=0;
    virtual void slot80()=0;
    virtual void slot84()=0;
    virtual void slot88()=0;
    virtual void setCachedLocalPlayerStats(PSPlayerStats)=0;
    virtual void slot90()=0;
    virtual void slot94()=0;
    virtual void slot98()=0;
    virtual void slot9c()=0;
    virtual void slota0()=0;
    virtual void slota4()=0;
    virtual void slota8()=0;
    virtual void slotac()=0;
    virtual void slotb0()=0;
    virtual void slotb4()=0;
    virtual void slotb8()=0;
    virtual void slotbc()=0;
    virtual void slotc0()=0;
    virtual void slotc4()=0;
    virtual void slotc8()=0;
    virtual void slotcc()=0;
    virtual void slotd0()=0;
    virtual void slotd4()=0;
    virtual void slotd8()=0;
    virtual void slotdc()=0;
    virtual void slote0()=0;
    virtual void slote4()=0;
    virtual void slote8()=0;
    virtual void slotec()=0;
    virtual void slotf0()=0;
    virtual void slotf4()=0;
    virtual void slotf8()=0;
    virtual void slotfc()=0;
    virtual void slot100()=0;
    virtual void slot104()=0;
    virtual void slot108()=0;
    virtual void slot10c()=0;
    virtual void slot110()=0;
    virtual void slot114()=0;
    virtual void slot118()=0;
    virtual void slot11c()=0;
    virtual void slot120()=0;
    virtual void slot124()=0;
    virtual void slot128()=0;
    virtual void slot12c()=0;
    virtual void slot130()=0;
    virtual void slot134()=0;
    virtual void slot138()=0;
    virtual void slot13c()=0;
    virtual void slot140()=0;
    virtual void slot144()=0;
    virtual void slot148()=0;
    virtual void slot14c()=0;
    virtual void slot150()=0;
    virtual void slot154()=0;
    virtual void slot158()=0;
    virtual void slot15c()=0;
    virtual bool didPlayerPreorder(int) const=0;
    virtual void markPlayerAsPreorder(int)=0;
};
class GameSpyPSMessageQueueInterface { public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void addResponse(const PSResponse&)=0;
    virtual bool getResponse(PSResponse&)=0;
    virtual void trackPlayerStats(PSPlayerStats)=0;
    virtual PSPlayerStats findPlayerStatsByID(int)=0;
};
class GameSpyPeerMessageQueueInterface { public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void addRequest(const PeerRequest&)=0;
    virtual void slot1c();
    virtual void addResponse(const PeerResponse&)=0;
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameTextInterface *TheGameText;
extern int g_bfmePeerReqE4, g_bfmePeerReqE8;
extern int g_Rva012F73D0, g_Rva012F73D4;
enum GSOverlayType {GSOVERLAY_PLAYERINFO=0};
void GSMessageBoxOk(UnicodeString,UnicodeString,void (*)());
void GameSpyCloseOverlay(GSOverlayType);
bool SetUnsignedIntInRegistry(std::string,std::string,unsigned int);
int CalculateRank(const PSPlayerStats&);
void UpdateLocalPlayerStats();
void UpdateBestLadderRanks004DBBF0(PSPlayerStats*);
void rva00545d00CopyBlocks(const unsigned int*,const unsigned int*,const unsigned int*,const unsigned int*);
void PopulatePlayerInfoWindows(AsciiString);
typedef char CheckPS[sizeof(PSPlayerStats)==0x1c4?1:-1];
typedef char CheckResponse[sizeof(PSResponse)==0x1f0?1:-1];
typedef char CheckRequest[sizeof(PeerRequest)==0x194?1:-1];
typedef char CheckPeer[sizeof(PeerResponse)==0x330?1:-1];
void d_004dd2b0( void )
{
	if (TheGameSpyPSMessageQueue)
	{
		PSResponse resp;
		if (TheGameSpyPSMessageQueue->getResponse( resp ))
		{
			switch (resp.responseType)
			{
			case PSResponse::PSRESPONSE_COULDNOTCONNECT:
				{
					// message box & hide the window
					GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:PSCannotConnect"), NULL);
					GameSpyCloseOverlay(GSOVERLAY_PLAYERINFO);
				}
				break;
			case PSResponse::PSRESPONSE_PREORDER:
				{
					if (resp.preorder)
					{
						SetUnsignedIntInRegistry("", "Preorder", 1);
						TheGameSpyInfo->markPlayerAsPreorder( TheGameSpyInfo->getLocalProfileID() );

						// force an update of our shtuff
						PSResponse newResp;
						newResp.responseType = PSResponse::PSRESPONSE_PLAYERSTATS;
						newResp.player = TheGameSpyPSMessageQueue->findPlayerStatsByID(TheGameSpyInfo->getLocalProfileID());
						TheGameSpyPSMessageQueue->addResponse(newResp);
					}
				}
				break;
			case PSResponse::Rva004DD2B0Case3:
                {
                    PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(resp.player.id);
                    if (resp.field_1c8 == TheGameSpyInfo->getLocalProfileID()) {
                        g_bfmePeerReqE4 = resp.field_1cc;
                        g_bfmePeerReqE8 = resp.field_1d0;
                        if (stats.id) UpdateBestLadderRanks004DBBF0(&stats);
                        PeerRequest req;
                        req.peerRequestType = PeerRequest::Rva004DD2B0Request25;
                        req.ranks.field_e4 = g_bfmePeerReqE4;
                        req.ranks.field_e8 = g_bfmePeerReqE8;
                        TheGameSpyPeerMessageQueue->addRequest(req);
                    }
                    PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->begin();
                    while (it != TheGameSpyInfo->getPlayerInfoMap()->end()) {
                        PlayerInfo *info = &it->second;
                        if (info && info->m_profileID == resp.player.id) {
                            info->field_20 = g_bfmePeerReqE4;
                            info->field_24 = g_bfmePeerReqE8;
                            break;
                        }
                        ++it;
                    }
                }
                break;
            case PSResponse::Rva004DD2B0Case4:
                if (resp.field_1d8 == 1) g_Rva012F73D0 = resp.field_1d4;
                else if (resp.field_1d8 == 2) g_Rva012F73D4 = resp.field_1d4;
                break;
            case PSResponse::Rva004DD2B0Case5:
                rva00545d00CopyBlocks(resp.field_1dc,resp.field_1e0,resp.field_1e4,resp.field_1e8);
                delete [] resp.field_1e4; resp.field_1e4=0;
                delete [] resp.field_1dc; resp.field_1dc=0;
                delete [] resp.field_1e0; resp.field_1e0=0;
                delete [] resp.field_1e8; resp.field_1e8=0;
                break;
            case PSResponse::PSRESPONSE_PLAYERSTATS:
				{
					
					if (resp.player.id == TheGameSpyInfo->getLocalProfileID())
					{
						PeerRequest req;
						req.peerRequestType = PeerRequest::PEERREQUEST_PUSHSTATS;
						GameSpyMiscPreferences cPref;
						req.statsToPush.locale = cPref.getLocale();
						Int wins = 0, losses = 0;
						PerGeneralMap::const_iterator it;
						for (it = resp.player.wins.begin(); it != resp.player.wins.end(); ++it)
						{
							wins += it->second;
						}
						for (it = resp.player.losses.begin(); it != resp.player.losses.end(); ++it)
						{
							losses += it->second;
						}
						req.statsToPush.wins = wins;
						req.statsToPush.losses = losses;
						req.statsToPush.rankPoints = CalculateRank( resp.player );

						Int numGames = 0;
						Int favorite = 0;
						for(it =resp.player.games.begin(); it != resp.player.games.end(); ++it)
						{
							if(it->second >= numGames)
							{
								numGames = it->second;
								favorite = it->first;
							}
						}
						if(numGames == 0)
							req.statsToPush.side = 0;
						else if( resp.player.gamesAsRandom >= numGames )
							req.statsToPush.side = 0;
						else
							req.statsToPush.side = favorite;

						Bool isPreorder = TheGameSpyInfo->didPlayerPreorder( TheGameSpyInfo->getLocalProfileID() );
						req.statsToPush.preorder = isPreorder;
						TheGameSpyPeerMessageQueue->addRequest(req);
                        UpdateBestLadderRanks004DBBF0(&resp.player);
					}
					TheGameSpyPSMessageQueue->trackPlayerStats(resp.player);
					if (resp.player.id == TheGameSpyInfo->getLocalProfileID())
					{
						UpdateLocalPlayerStats();
                        TheGameSpyInfo->setCachedLocalPlayerStats(resp.player);
					}
					PopulatePlayerInfoWindows("PopupPlayerInfo.wnd");
					//GadgetListBoxAddEntryText(listboxInfo, UnicodeString(L"Got info!"), GameSpyColor[GSCOLOR_DEFAULT], -1);
					
					// also update info for player list in lobby
					PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->begin();
					while (it != TheGameSpyInfo->getPlayerInfoMap()->end())
					{
						PlayerInfo *info = &(it->second);
						if (info && info->m_profileID == resp.player.id)
						{
							// update m_wins, m_losses, m_rankPoints
							Int wins = 0, losses = 0;
							PerGeneralMap::const_iterator it;
							for (it = resp.player.wins.begin(); it != resp.player.wins.end(); ++it)
							{
								wins += it->second;
							}
							for (it = resp.player.losses.begin(); it != resp.player.losses.end(); ++it)
							{
								losses += it->second;
							}
							info->m_wins = wins;
							info->m_losses = losses;
							info->m_rankPoints = CalculateRank( resp.player );
							Int numGames = 0;
							Int favorite = 0;
							for(it = resp.player.games.begin(); it != resp.player.games.end(); ++it)
							{
								if(it->second >= numGames)
								{
									numGames = it->second;
									favorite = it->first;
								}
							}
							if(numGames == 0)
								info->m_side = 0;
							else if( resp.player.gamesAsRandom >= numGames )
								info->m_side = 0;
							else
								info->m_side = favorite;

							info->m_preorder = TheGameSpyInfo->didPlayerPreorder(info->m_profileID);

                            PeerResponse r;
							r.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERINFO;
							r.nick = info->m_name.str();
							r.player.profileID = info->m_profileID;
							r.player.flags = info->m_flags;
							r.player.wins = info->m_wins;
							r.player.losses = info->m_losses;
							r.locale = info->m_locale.str();
							r.player.rankPoints = info->m_rankPoints;
							r.player.side = info->m_side;
							r.player.preorder = info->m_preorder;
							r.player.field_324 = info->field_20;
                            r.player.field_328 = info->field_24;
                            r.player.field_32c = info->field_28;
                            TheGameSpyPeerMessageQueue->addResponse(r);
							break;
						}
						++it;
					}

				}
				break;
			}
		}
	}
}

