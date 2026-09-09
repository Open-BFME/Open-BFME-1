// ?Rva00699F30ShroudCheck@@YG_NPAVAudioEventRTS@@@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Coord3D
{
    float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventInfo.h
struct AudioEventInfoSlice
{
    char m_pad[0x38];
    unsigned char m_type;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
    void resolveOwnerPosition(Coord3D *pos, bool *valid);

    char m_pad0[8];
    const AudioEventInfoSlice *m_eventInfo;
    char m_pad1[0x1c];
    unsigned int m_unmodelled028;
};

enum CellShroudStatus
{
    CELLSHROUD_CLEAR,
    CELLSHROUD_FOGGED,
    CELLSHROUD_SHROUDED,
    CELLSHROUD_COUNT
};

class PartitionManager
{
public:
    CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
};
extern PartitionManager *TheShroudManager;

struct Rva002EE330Player
{
    char m_pad[0x24];
    int m_playerIndex;
};

struct Rva002EE330PlayerList
{
    char m_pad[0xc];
    Rva002EE330Player *m_localPlayer;
};
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

bool __stdcall Rva00699F30ShroudCheck(AudioEventRTS *event)
{
    if (event->m_unmodelled028 == 0)
    {
        if ((event->m_eventInfo->m_type & 4) != 0)
        {
            Coord3D pos;
            bool valid;
            event->resolveOwnerPosition(&pos, &valid);
            if (valid)
            {
                Rva002EE330PlayerList *players = Rva002EE330ThePlayers;
                if (players)
                {
                    PartitionManager *shroud = TheShroudManager;
                    if (shroud)
                    {
                        int playerIndex = players->m_localPlayer->m_playerIndex;
                        if (shroud->getShroudStatusForPlayer(playerIndex, &pos) != CELLSHROUD_CLEAR)
                            return true;
                    }
                }
            }
        }
    }
    return false;
}
