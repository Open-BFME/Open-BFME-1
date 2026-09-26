// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME5: ParticleSystemFXNugget destructor at 0x0042A1A0 (127B).
// Member offsets match the landed ctor thunk: four AsciiString tails at
// +0xB4, +0xFC, +0x104, +0x108, then the FXNugget base.
// BFME FieldParse table 0x00CF2F80 names the extended tail fields.

typedef float Real;
typedef bool Bool;

#include "ascii_string.h"

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

class __declspec(novtable) ParticleSystemFXNugget : public FXNugget
{
public:
	ParticleSystemFXNugget();
	virtual ~ParticleSystemFXNugget();

private:
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
	AsciiString m_attachToBone;
	Bool m_createAtGroundHeight;
	Bool m_ricochet;
	unsigned char m_pad102[2];
	AsciiString m_createBoneOverride;
	AsciiString m_targetBoneOverride;
	Bool m_createBoneAtTarget;
	unsigned char m_pad10D[3];
	Real m_targetCoeff;
	int m_systemLife;
	Bool m_useTargetOffset;
	Bool m_setTargetMatrix;
	Bool m_onlyIfOnLand;
	Bool m_onlyIfOnWater;
	Coord3D m_targetOffset;
};

// ??1ParticleSystemFXNugget@@UAE@XZ
ParticleSystemFXNugget::~ParticleSystemFXNugget()
{
}
