// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"
#include "game_client_random_variable.h"
#include "snapshot.h"

class Xfer;
class FXList;

namespace FXParticleSystem
{
class TerrainCollisionModuleInfo : public Snapshot
{
public:
    TerrainCollisionModuleInfo();
    virtual ~TerrainCollisionModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    TerrainCollisionModuleInfo &operator=(const TerrainCollisionModuleInfo &that);
    const FXList *getEventFX();

private:
    AsciiString m_eventName;
    GameClientRandomVariable m_eventTime;
    bool m_flag;
    const FXList *m_cached;
};

// ??0TerrainCollisionModuleInfo@FXParticleSystem@@QAE@XZ
TerrainCollisionModuleInfo::TerrainCollisionModuleInfo()
{
    m_cached = 0;
    m_eventTime.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_flag = false;
}
}
