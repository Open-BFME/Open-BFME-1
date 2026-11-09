// cl: /O2 /Ob1 /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
// Complete BFME LocomotorTemplate constructor at RVA 0x001B52C0.  The old
// generated row covered only 41 bytes and ended two bytes into the instruction
// at +0x27; the real function returns at +0x207 and is 520 bytes long.
//
// Identity is fixed by two named callers.  LocomotorStore::newOverride allocates
// 0x140 bytes and calls this constructor through ILT 0x0000D049, while
// LocomotorStore::parseLocomotorTemplateDefinition uses the same ILT for a new
// definition.  The constructor installs vtable 0x0109DE9C; its one slot reaches
// the deleting destructor immediately before the proven Locomotor constructor.
//
// The 0x140-byte scalar layout is shared with the already matched copy assignment
// at 0x001B4250.  Fields whose BFME semantic names are not independently known
// retain offset-based names; float and byte types are used only where the
// constructor values and surrounding source establish those ABI widths.
// The retail LocomotorTemplate FieldParse table at 0x00C9D860 maps
// Acceleration/Lift/LiftDamaged to +0x40/+0x44/+0x48. The matched getter at
// 0x001B5A30 appears to conflict; its identity remains unresolved (see
// docs/naming_evidence.md). Matched getMaxTurnRate at 0x001B5860 reads
// +0x28/+0x2c as normal/damaged turn periods.

class Overridable
{
public:
	Overridable() : m_nextOverride(0), m_isAllocatedOverride(0) {}

protected:
	virtual ~Overridable();

private:
	Overridable *m_nextOverride;
	unsigned char m_isAllocatedOverride;
};

#include "ascii_string.h"

class LocomotorTemplate : public Overridable
{
public:
	LocomotorTemplate();

protected:
	virtual ~LocomotorTemplate();

private:
	AsciiString m_name;
	unsigned int m_surfaces;
	float m_lookAheadMult;
	unsigned char m_nonDirtyTransform;
	unsigned int m_maxSpeed;
	float m_maxSpeedDamaged;
	unsigned int m_minSpeed;
	unsigned int m_turnPeriod;
	unsigned int m_damagedTurnPeriod;
	unsigned int m_slowTurnRadius;
	float m_fastTurnRadius;
	float m_turnThreshold;
	float m_turnThresholdHS;
	unsigned int m_acceleration;
	unsigned int m_lift;
	float m_liftDamaged;
	unsigned int m_braking;
	float m_minTurnSpeed;
	unsigned int m_preferredHeight;
	unsigned int m_preferredAttackHeight;
	float m_preferredHeightDamping;
	unsigned int m_circlingRadius;
	float m_speedLimitZ;
	unsigned int m_maxThrustAngle;
	unsigned int m_behaviorZ;
	unsigned int m_appearance;
	unsigned int m_formationPriority;
	float m_accDecTrigger;
	unsigned int m_walkDistance;
	float m_maxTurnWithoutReform;
	unsigned int m_accelPitchLimit;
	unsigned int m_bounceKick;
	float m_pitchStiffness;
	float m_rollStiffness;
	float m_pitchDamping;
	float m_rollDamping;
	unsigned int m_pitchByZVelCoef;
	float m_maxOverlappedHeight;
	unsigned int m_forwardVelCoef;
	unsigned int m_lateralVelCoef;
	unsigned int m_dac;
	unsigned int m_lateralAccelCoef;
	float m_uniformAxialDamping;
	unsigned int m_turnPivotOffset;
	unsigned int m_dbc;
	float m_closeEnoughDist;
	unsigned char m_isCloseEnoughDist3D;
	unsigned int m_ultraAccurateSlideIntoPlaceFactor;
	unsigned char m_cc;
	unsigned char m_cd;
	unsigned char m_ce;
	unsigned char m_cf;
	unsigned char m_stickToGround;
	unsigned int m_canMoveBackward;
	unsigned char m_hasSuspension;
	unsigned int m_ddc;
	unsigned int m_maximumWheelCompression;
	unsigned int m_wheelTurnAngle;
	unsigned char m_crewPowered;
	unsigned char m_useTerrainSmoothing;
	unsigned int m_dec;
	float m_wanderLengthFactor;
	unsigned int m_wanderAboutPointRadius;
	unsigned int m_chargeSpeed;
	unsigned char m_dfc;
	unsigned char m_dfd;
	unsigned char m_dfe;
	unsigned int m_rudderCorrectionDegree;
	unsigned int m_rudderCorrectionRate;
	unsigned int m_elevatorCorrectionDegree;
	unsigned int m_elevatorCorrectionRate;
	unsigned int m_aeleronCorrectionDegree;
	unsigned int m_e14;
	float m_swoopStandoffRadius;
	float m_swoopStandoffHeight;
	float m_swoopTerminalVelocity;
	float m_e24;
	float m_e28;
	float m_e2c;
	unsigned char m_e30;
	unsigned int m_e34;
	unsigned int m_e38;
	float m_e3c;
};

typedef char LocomotorTemplateSizeMustBe140[
	(sizeof(LocomotorTemplate) == 0x140) ? 1 : -1
];

LocomotorTemplate::LocomotorTemplate()
{
	m_maxSpeedDamaged = 1.0f;
	m_turnPeriod = 5;
	m_acceleration = 5;
	m_braking = 5;
	m_pitchStiffness = 0.1f;
	m_rollStiffness = 0.1f;
	m_damagedTurnPeriod = 0;
	m_liftDamaged = -1.0f;
	m_surfaces = 0;
	m_maxSpeed = 0;
	m_lookAheadMult = 1.0f;
	m_nonDirtyTransform = 0;
	m_slowTurnRadius = 0;
	m_fastTurnRadius = 20.0f;
	m_turnThreshold = 0.2617994f;
	m_turnThresholdHS = 3.1415927f;
	m_lift = 0;
	m_minSpeed = 0;
	m_minTurnSpeed = 99999.0f;
	m_behaviorZ = 0;
	m_appearance = 1;
	m_formationPriority = 7;
	m_preferredHeight = 0;
	m_preferredAttackHeight = 0;
	m_preferredHeightDamping = 1.0f;
	m_circlingRadius = 0;
	m_accDecTrigger = 0.5f;
	m_walkDistance = 0;
	m_maxThrustAngle = 0;
	m_speedLimitZ = 999999.0f;
	m_maxTurnWithoutReform = 6.2831855f;
	m_accelPitchLimit = 0;
	m_bounceKick = 0;
	m_pitchDamping = 0.9f;
	m_rollDamping = 0.9f;
	m_forwardVelCoef = 0;
	m_pitchByZVelCoef = 0;
	m_maxOverlappedHeight = 3.402823466e38f;
	m_lateralVelCoef = 0;
	m_dac = 0;
	m_lateralAccelCoef = 0;
	m_uniformAxialDamping = 1.0f;
	m_turnPivotOffset = 0;
	m_ce = 0;
	m_cf = 0;
	m_cd = 0;
	m_cc = 0;
	m_dbc = 0x7fffffff;
	m_stickToGround = 0;
	m_canMoveBackward = 0;
	m_hasSuspension = 0;
	m_wheelTurnAngle = 0;
	m_ddc = 0;
	m_maximumWheelCompression = 0;
	m_closeEnoughDist = 1.0f;
	m_isCloseEnoughDist3D = 0;
	m_ultraAccurateSlideIntoPlaceFactor = 0;
	m_crewPowered = 0;
	m_useTerrainSmoothing = 0;
	m_dec = 0;
	m_wanderLengthFactor = 1.0f;
	m_wanderAboutPointRadius = 0;
	m_chargeSpeed = 0;
	m_dfc = 0;
	m_dfd = 1;
	m_dfe = 0;
	m_rudderCorrectionDegree = 0;
	m_rudderCorrectionRate = 0;
	m_elevatorCorrectionDegree = 0;
	m_elevatorCorrectionRate = 0;
	m_swoopStandoffRadius = 200.0f;
	m_swoopStandoffHeight = 200.0f;
	m_aeleronCorrectionDegree = 0;
	m_e14 = 0;
	m_swoopTerminalVelocity = 0.07f;
	m_e24 = 0.003f;
	m_e28 = 1.0f;
	m_e2c = 0.75f;
	m_e30 = 0;
	m_e34 = 0;
	m_e38 = 0;
	m_e3c = 0.5f;
}
