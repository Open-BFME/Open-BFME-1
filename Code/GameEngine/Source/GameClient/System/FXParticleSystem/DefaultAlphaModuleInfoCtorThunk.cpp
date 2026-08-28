// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ClientRandomValue.h
class GameClientRandomVariable
{
public:
	enum DistributionType { CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS };

	GameClientRandomVariable() : m_type(CONSTANT), m_low(0.0f), m_high(0.0f) {}
	void setRange(float low, float high, DistributionType type = UNIFORM);

private:
	DistributionType m_type;
	float m_low;
	float m_high;
};

namespace FXParticleSystem {

struct RandomAlphaKeyframe
{
	RandomAlphaKeyframe()
	{
		var.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
		frame = 0.0f;
	}

	GameClientRandomVariable var;
	float frame;
};

class Xfer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
protected:
	~Snapshot();
};

class DefaultAlphaModuleInfo : public Snapshot
{
public:
	DefaultAlphaModuleInfo();
	virtual ~DefaultAlphaModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &);

private:
	RandomAlphaKeyframe m_alphaKey[8];
};

// ??0DefaultAlphaModuleInfo@FXParticleSystem@@QAE@XZ
DefaultAlphaModuleInfo::DefaultAlphaModuleInfo()
{
}

}
