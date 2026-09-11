// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ
// partial score=0.89 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

namespace FXParticleSystem
{

class GameClientRandomVariable
{
public:
	enum DistributionType { CONSTANT, UNIFORM };
	GameClientRandomVariable()
		: m_distribution(CONSTANT), m_minimum(0.0f), m_maximum(0.0f) {}
	void setRange(float minimum, float maximum, DistributionType distribution);

private:
	DistributionType m_distribution;
	float m_minimum;
	float m_maximum;
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class DefaultPhysicsModuleInfo : public Snapshot
{
public:
	DefaultPhysicsModuleInfo();
	virtual ~DefaultPhysicsModuleInfo();

private:
	float m_field0;
	float m_field1;
	float m_field2;
	int m_field3;
	GameClientRandomVariable m_var1;
};

// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ
DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo()
{
	m_field3 = 0;
	m_field0 = 0.0f;
	m_field1 = 0.0f;
	m_field2 = 0.0f;
	m_var1.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
}

}
