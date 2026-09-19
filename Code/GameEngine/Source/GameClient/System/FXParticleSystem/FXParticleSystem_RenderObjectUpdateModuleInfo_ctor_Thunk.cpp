// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Xfer;

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

private:
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
	virtual void DoXfer(Xfer &xfer);
};

class RenderObjectUpdateModuleInfo : public SnapshotInfo
{
public:
	RenderObjectUpdateModuleInfo();
	virtual ~RenderObjectUpdateModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	GameClientRandomVariable m_var3;
	GameClientRandomVariable m_var4;
	GameClientRandomVariable m_var5;
	GameClientRandomVariable m_var6;
	GameClientRandomVariable m_var7;
	GameClientRandomVariable m_var8;
	GameClientRandomVariable m_var9;
	GameClientRandomVariable m_var10;
	GameClientRandomVariable m_var11;
	unsigned int m_mode;
};

// ??0RenderObjectUpdateModuleInfo@FXParticleSystem@@QAE@XZ
RenderObjectUpdateModuleInfo::RenderObjectUpdateModuleInfo()
{
	m_var0.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var3.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var6.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var1.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var4.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var7.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var2.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var5.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var8.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var9.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var10.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_var11.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
	m_mode = 1;
}

}
