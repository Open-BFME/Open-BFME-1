// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// GameState::init RVA0x001112D0,1368B.
// Snapshot is a secondary base at+8 for subsystem objects; direct Snapshot
// implementations retain their original pointer. Inline StringBase forwarding
// and /EHsc preserve retail argument-construction cleanup bookkeeping.
// GameState snapshot registration. BFME adds living-world, shroud, collision,
// victory, taint and weather blocks to the original save/deep-CRC registries.
template<class T> class StringBase {
    friend class AsciiString;
    T *m_data;
    StringBase(const T *);
    void releaseBuffer();
protected:
    ~StringBase() { releaseBuffer(); }
};
class AsciiString : private StringBase<char> {
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    ~AsciiString() {}
};
class SubsystemInterface { public: virtual ~SubsystemInterface(); private: int m_subsystemData; };
class Snapshot { public: virtual ~Snapshot(); };
enum SnapshotType { SNAPSHOT_SAVELOAD, SNAPSHOT_DEEPCRC_LOGICONLY };
class GameState : public SubsystemInterface, public Snapshot {
public:
    virtual void init();
private:
    void addSnapshotBlock(AsciiString, Snapshot *, SnapshotType);
    char m_state[0x48];
    bool m_isInLoadGame;
};
class CampaignObject : public SubsystemInterface, public Snapshot {};
class AudioManager : public SubsystemInterface, public Snapshot {};
class CampaignManager : public Snapshot {};
class AptPalantir : public SubsystemInterface, public Snapshot {};
class GameStateMap : public SubsystemInterface, public Snapshot {};
class TerrainLogic : public Snapshot {};
class TeamFactory : public SubsystemInterface, public Snapshot {};
class PlayerList : public SubsystemInterface, public Snapshot {};
class GameLogic : public SubsystemInterface, public Snapshot {};
class Radar : public Snapshot {};
class ScriptEngine : public SubsystemInterface, public Snapshot {};
class SidesList : public SubsystemInterface, public Snapshot {};
class View : public Snapshot {};
class GameClient : public SubsystemInterface, public Snapshot {};
class InGameUI : public SubsystemInterface, public Snapshot {};
class PartitionManager : public SubsystemInterface, public Snapshot {};
class ShroudManager : public SubsystemInterface, public Snapshot {};
class CollisionManager : public SubsystemInterface, public Snapshot {};
class ParticleSystemManager : public SubsystemInterface, public Snapshot {};
class TerrainVisual : public Snapshot {};
class GhostObjectManager : public Snapshot {};
class VictorySystem : public SubsystemInterface, public Snapshot {};
class BfmeTaintManager : public SubsystemInterface, public Snapshot {};
class WeatherSystem : public SubsystemInterface, public Snapshot {};
extern CampaignObject *TheLivingWorldLogic;
extern AudioManager *TheAudio;
extern GameState *TheGameState;
extern CampaignManager *TheCampaignManager;
extern AptPalantir *TheAptPalantir;
extern GameStateMap *TheGameStateMap;
extern TerrainLogic *TheTerrainLogic;
extern TeamFactory *TheTeamFactory;
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
extern Radar *TheRadar;
extern ScriptEngine *TheScriptEngine;
extern SidesList *TheSidesList;
extern View *TheTacticalView;
extern GameClient *TheGameClient;
extern InGameUI *TheInGameUI;
extern PartitionManager *ThePartitionManager;
extern ShroudManager *TheShroudManager;
extern CollisionManager *TheCollisionManager;
extern ParticleSystemManager *TheParticleSystemManager;
extern TerrainVisual *TheTerrainVisual;
extern GhostObjectManager *TheGhostObjectManager;
extern VictorySystem *TheVictorySystem;
extern BfmeTaintManager *TheTaintManager;
extern WeatherSystem *TheWeatherSystem;
void GameState::init()
{
    addSnapshotBlock("CHUNK_LivingWorldLogic", TheLivingWorldLogic, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_Audio", TheAudio, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_GameState", TheGameState, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_Campaign", TheCampaignManager, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_Palantir", TheAptPalantir, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_GameStateMap", TheGameStateMap, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_TerrainLogic", TheTerrainLogic, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_TeamFactory", TheTeamFactory, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_Players", ThePlayerList, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_GameLogic", TheGameLogic, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_Radar", TheRadar, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_ScriptEngine", TheScriptEngine, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_SidesList", TheSidesList, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_TacticalView", TheTacticalView, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_GameClient", TheGameClient, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_InGameUI", TheInGameUI, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_Partition", ThePartitionManager, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_Shroud", TheShroudManager, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_Collision", TheCollisionManager, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_ParticleSystem", TheParticleSystemManager, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_TerrainVisual", TheTerrainVisual, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_GhostObject", TheGhostObjectManager, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_VictorySystem", TheVictorySystem, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_TaintManager", TheTaintManager, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_WeatherSystem", TheWeatherSystem, SNAPSHOT_SAVELOAD);
    addSnapshotBlock("CHUNK_TeamFactory", TheTeamFactory, SNAPSHOT_DEEPCRC_LOGICONLY);
    addSnapshotBlock("CHUNK_Players", ThePlayerList, SNAPSHOT_DEEPCRC_LOGICONLY);
    addSnapshotBlock("CHUNK_GameLogic", TheGameLogic, SNAPSHOT_DEEPCRC_LOGICONLY);
    addSnapshotBlock("CHUNK_ScriptEngine", TheScriptEngine, SNAPSHOT_DEEPCRC_LOGICONLY);
    addSnapshotBlock("CHUNK_SidesList", TheSidesList, SNAPSHOT_DEEPCRC_LOGICONLY);
    addSnapshotBlock("CHUNK_Partition", ThePartitionManager, SNAPSHOT_DEEPCRC_LOGICONLY);
    addSnapshotBlock("CHUNK_Shroud", TheShroudManager, SNAPSHOT_DEEPCRC_LOGICONLY);
    addSnapshotBlock("CHUNK_Collision", TheCollisionManager, SNAPSHOT_DEEPCRC_LOGICONLY);
    m_isInLoadGame = false;
}

