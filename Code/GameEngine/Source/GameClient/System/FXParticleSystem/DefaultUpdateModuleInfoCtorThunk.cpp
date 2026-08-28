// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

namespace FXParticleSystem {

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ClientRandomValue.h
class GameClientRandomVariable
{
public:
    enum DistributionType
    {
        CONSTANT,
        UNIFORM
    };

    GameClientRandomVariable()
        : m_distribution(CONSTANT), m_minimum(0.0f), m_maximum(0.0f)
    {
    }

    void setRange(float minimum, float maximum, DistributionType distribution);

    DistributionType m_distribution;
    float m_minimum;
    float m_maximum;
};

class SnapshotInfo
{
public:
    virtual ~SnapshotInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(void *);
};

class DefaultUpdateModuleInfo : public SnapshotInfo
{
public:
    DefaultUpdateModuleInfo();
    virtual ~DefaultUpdateModuleInfo();

private:
    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
    GameClientRandomVariable m_var2;
    GameClientRandomVariable m_var3;
    GameClientRandomVariable m_var4;
    int m_extra;
};

// ??0DefaultUpdateModuleInfo@FXParticleSystem@@QAE@XZ
DefaultUpdateModuleInfo::DefaultUpdateModuleInfo()
{
    m_var0.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_var1.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_var2.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_var3.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_var4.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_extra = 1;
}

}
