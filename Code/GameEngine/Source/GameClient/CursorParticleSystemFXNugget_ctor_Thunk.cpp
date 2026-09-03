// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of the BFME CursorParticleSystem FX constructor.
// FieldParse at 0x010F31B0 names Anim2DTemplateName, BurstCount, ParticleLife,
// SystemLife, DriftVelX and DriftVelY.

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	~AsciiString();
	void clear();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ClientRandomValue.h
class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT
	};

	GameClientRandomVariable() : m_min(0.0f), m_max(0.0f), m_type(CONSTANT) {}

private:
	Real m_min;
	Real m_max;
	DistributionType m_type;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

protected:
	int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class CursorParticleSystemFXNugget : public FXNugget
{
public:
	CursorParticleSystemFXNugget();
	virtual ~CursorParticleSystemFXNugget();

private:
	AsciiString m_name;
	int m_burstCount;
	GameClientRandomVariable m_particleLife;
	GameClientRandomVariable m_systemLife;
	GameClientRandomVariable m_driftVelX;
	GameClientRandomVariable m_driftVelY;
};

CursorParticleSystemFXNugget::CursorParticleSystemFXNugget()
{
	m_nuggetType = 12;
	m_burstCount = 10;
	m_name.clear();
}
