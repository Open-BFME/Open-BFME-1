// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/System

#include "game_client_random_variable.h"

class Xfer;

namespace FXParticleSystem
{
class LightningDrawModuleInfoCleanupBase
{
public:
    LightningDrawModuleInfoCleanupBase() {}
    ~LightningDrawModuleInfoCleanupBase();
};

class LightningDrawModuleInfo : public LightningDrawModuleInfoCleanupBase
{
public:
    LightningDrawModuleInfo();
    virtual ~LightningDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    LightningDrawModuleInfo &operator=(const LightningDrawModuleInfo &that);
    GameClientRandomVariable m_gcrv1;
    GameClientRandomVariable m_gcrv2;
    GameClientRandomVariable m_gcrv3;
    int m_field28;
    bool m_flag;
};

// ??0LightningDrawModuleInfo@FXParticleSystem@@QAE@XZ
LightningDrawModuleInfo::LightningDrawModuleInfo()
{
    m_gcrv1.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_gcrv2.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_gcrv3.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_field28 = 0;
    m_flag = false;
}
}
