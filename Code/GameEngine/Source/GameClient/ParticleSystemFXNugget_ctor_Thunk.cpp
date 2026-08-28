// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of the BFME particle-system FX nugget.

typedef float Real;
typedef bool Bool;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
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
	void setRange(Real min, Real max, DistributionType type);

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

class ParticleSystemFXNugget : public FXNugget
{
public:
	ParticleSystemFXNugget();
	virtual ~ParticleSystemFXNugget();

private:
	// Retail proves these BFME-only tail offsets; neutral names avoid inventing semantics.
	AsciiString m_name;
	int m_count;
	Coord3D m_offset;
	GameClientRandomVariable m_radius;
	GameClientRandomVariable m_height;
	GameClientRandomVariable m_delay;
	Real m_rotateX;
	Real m_rotateY;
	Real m_rotateZ;
	Bool m_orientToObject;
	Bool m_attachToObject;
	unsigned char m_padFA[2];
	AsciiString m_bfmeNameFC;
	Bool m_createAtGroundHeight;
	Bool m_ricochet;
	unsigned char m_pad102[2];
	AsciiString m_bfmeName104;
	AsciiString m_bfmeName108;
	Bool m_useCallersRadius;
	unsigned char m_pad10D[3];
	Real m_bfmeScale;
	int m_bfmeIndex;
	Bool m_bfmeFlag118;
	Bool m_bfmeFlag119;
	Bool m_bfmeFlag11A;
	Bool m_bfmeFlag11B;
	Coord3D m_bfmeOffset;
};

ParticleSystemFXNugget::ParticleSystemFXNugget()
{
	m_name.clear();
	m_count = 1;
	m_radius.setRange(0.0f, 0.0f, GameClientRandomVariable::CONSTANT);
	m_height.setRange(0.0f, 0.0f, GameClientRandomVariable::CONSTANT);
	m_delay.setRange(-1.0f, -1.0f, GameClientRandomVariable::CONSTANT);
	m_offset.x = m_offset.y = m_offset.z = 0.0f;
	m_orientToObject = false;
	m_attachToObject = false;
	m_createAtGroundHeight = false;
	m_rotateX = m_rotateY = m_rotateZ = 0.0f;
	m_useCallersRadius = false;
	m_bfmeFlag118 = false;
	m_bfmeOffset.x = m_bfmeOffset.y = m_bfmeOffset.z = 0.0f;
	m_bfmeFlag119 = false;
	m_bfmeFlag11A = false;
	m_bfmeFlag11B = false;
	m_ricochet = false;
	m_nuggetType = 8;
	m_bfmeScale = 1.0f;
	m_bfmeIndex = -1;
}
