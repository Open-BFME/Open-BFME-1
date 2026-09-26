// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"
#include "game_client_random_variable.h"
#include "snapshot.h"

class Xfer;
class FXList;

namespace FXParticleSystem
{
class LifeEventModuleInfo : public Snapshot
{
public:
    LifeEventModuleInfo();
    virtual ~LifeEventModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    LifeEventModuleInfo &operator=(const LifeEventModuleInfo &that);
    const FXList *getEventFX();

private:
    AsciiString m_eventName;
    GameClientRandomVariable m_eventTime;
    const FXList *m_cached;
};

// ??0LifeEventModuleInfo@FXParticleSystem@@QAE@XZ
LifeEventModuleInfo::LifeEventModuleInfo()
{
    m_cached = 0;
    m_eventTime.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
}
}
