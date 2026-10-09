// cl: /O2 /Ob1 /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
// BFME retail LocomotorTemplate::operator= (RVA 0x001B4250).
// The retail LocomotorTemplate FieldParse table at 0x00C9D860 maps
// Acceleration/Lift/LiftDamaged to +0x40/+0x44/+0x48. The matched getter at
// 0x001B5A30 appears to conflict; its identity remains unresolved (see
// docs/naming_evidence.md). Matched getMaxTurnRate at 0x001B5860 reads
// +0x28/+0x2c as normal/damaged turn periods.

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other);

private:
	char m_head[0x0c];
};

#include "ascii_string.h"

class LocomotorTemplate : public ScienceInfoBase
{
public:
	LocomotorTemplate &operator=(const LocomotorTemplate &other);

private:
	AsciiString m_name;
	unsigned int m_surfaces;
	unsigned int m_d14;
	unsigned char m_c18;
	unsigned int m_maxSpeed;
	unsigned int m_maxSpeedDamaged;
	unsigned int m_minSpeed;
	unsigned int m_turnPeriod;
	unsigned int m_damagedTurnPeriod;
	unsigned int m_d30;
	unsigned int m_d34;
	unsigned int m_d38;
	unsigned int m_d3c;
	unsigned int m_acceleration;
	unsigned int m_lift;
	unsigned int m_liftDamaged;
	unsigned int m_braking;
	unsigned int m_minTurnSpeed;
	unsigned int m_preferredHeight;
	unsigned int m_d58;
	unsigned int m_preferredHeightDamping;
	unsigned int m_circlingRadius;
	unsigned int m_speedLimitZ;
	unsigned int m_maxThrustAngle;
	unsigned int m_behaviorZ;
	unsigned int m_appearance;
	unsigned int m_d74;
	unsigned int m_d78;
	unsigned int m_d7c;
	unsigned int m_d80;
	unsigned int m_accelPitchLimit;
	unsigned int m_bounceKick;
	unsigned int m_pitchStiffness;
	unsigned int m_rollStiffness;
	unsigned int m_pitchDamping;
	unsigned int m_rollDamping;
	unsigned int m_pitchByZVelCoef;
	unsigned int m_da0;
	unsigned int m_forwardVelCoef;
	unsigned int m_lateralVelCoef;
	unsigned int m_dac;
	unsigned int m_lateralAccelCoef;
	unsigned int m_uniformAxialDamping;
	unsigned int m_turnPivotOffset;
	unsigned int m_dbc;
	unsigned int m_closeEnoughDist;
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
	unsigned char m_de8;
	unsigned char m_de9;
	unsigned int m_dec;
	unsigned int m_wanderLengthFactor;
	unsigned int m_wanderAboutPointRadius;
	unsigned int m_df8;
	unsigned char m_dfc;
	unsigned char m_dfd;
	unsigned char m_dfe;
	unsigned int m_rudderCorrectionDegree;
	unsigned int m_rudderCorrectionRate;
	unsigned int m_elevatorCorrectionDegree;
	unsigned int m_elevatorCorrectionRate;
	unsigned int m_e10;
	unsigned int m_e14;
	unsigned int m_e18;
	unsigned int m_e1c;
	unsigned int m_e20;
	unsigned int m_e24;
	unsigned int m_e28;
	unsigned int m_e2c;
	unsigned char m_e30;
	unsigned int m_e34;
	unsigned int m_e38;
	unsigned int m_e3c;
};

LocomotorTemplate &LocomotorTemplate::operator=(const LocomotorTemplate &other)
{
	ScienceInfoBase::operator=(other);
	m_name = other.m_name;
	m_surfaces = other.m_surfaces;
	m_d14 = other.m_d14;
	m_c18 = other.m_c18;
	m_maxSpeed = other.m_maxSpeed;
	m_maxSpeedDamaged = other.m_maxSpeedDamaged;
	m_minSpeed = other.m_minSpeed;
	m_turnPeriod = other.m_turnPeriod;
	m_damagedTurnPeriod = other.m_damagedTurnPeriod;
	m_d30 = other.m_d30;
	m_d34 = other.m_d34;
	m_d38 = other.m_d38;
	m_d3c = other.m_d3c;
	m_acceleration = other.m_acceleration;
	m_lift = other.m_lift;
	m_liftDamaged = other.m_liftDamaged;
	m_braking = other.m_braking;
	m_minTurnSpeed = other.m_minTurnSpeed;
	m_preferredHeight = other.m_preferredHeight;
	m_d58 = other.m_d58;
	m_preferredHeightDamping = other.m_preferredHeightDamping;
	m_circlingRadius = other.m_circlingRadius;
	m_speedLimitZ = other.m_speedLimitZ;
	m_maxThrustAngle = other.m_maxThrustAngle;
	m_behaviorZ = other.m_behaviorZ;
	m_appearance = other.m_appearance;
	m_d74 = other.m_d74;
	m_d78 = other.m_d78;
	m_d7c = other.m_d7c;
	m_d80 = other.m_d80;
	m_accelPitchLimit = other.m_accelPitchLimit;
	m_bounceKick = other.m_bounceKick;
	m_pitchStiffness = other.m_pitchStiffness;
	m_rollStiffness = other.m_rollStiffness;
	m_pitchDamping = other.m_pitchDamping;
	m_rollDamping = other.m_rollDamping;
	m_pitchByZVelCoef = other.m_pitchByZVelCoef;
	m_da0 = other.m_da0;
	m_forwardVelCoef = other.m_forwardVelCoef;
	m_lateralVelCoef = other.m_lateralVelCoef;
	m_dac = other.m_dac;
	m_lateralAccelCoef = other.m_lateralAccelCoef;
	m_uniformAxialDamping = other.m_uniformAxialDamping;
	m_turnPivotOffset = other.m_turnPivotOffset;
	m_dbc = other.m_dbc;
	m_closeEnoughDist = other.m_closeEnoughDist;
	m_isCloseEnoughDist3D = other.m_isCloseEnoughDist3D;
	m_ultraAccurateSlideIntoPlaceFactor = other.m_ultraAccurateSlideIntoPlaceFactor;
	m_cc = other.m_cc;
	m_cd = other.m_cd;
	m_ce = other.m_ce;
	m_cf = other.m_cf;
	m_stickToGround = other.m_stickToGround;
	m_canMoveBackward = other.m_canMoveBackward;
	m_hasSuspension = other.m_hasSuspension;
	m_ddc = other.m_ddc;
	m_maximumWheelCompression = other.m_maximumWheelCompression;
	m_wheelTurnAngle = other.m_wheelTurnAngle;
	m_de8 = other.m_de8;
	m_de9 = other.m_de9;
	m_dec = other.m_dec;
	m_wanderLengthFactor = other.m_wanderLengthFactor;
	m_wanderAboutPointRadius = other.m_wanderAboutPointRadius;
	m_df8 = other.m_df8;
	m_dfc = other.m_dfc;
	m_dfd = other.m_dfd;
	m_dfe = other.m_dfe;
	m_rudderCorrectionDegree = other.m_rudderCorrectionDegree;
	m_rudderCorrectionRate = other.m_rudderCorrectionRate;
	m_elevatorCorrectionDegree = other.m_elevatorCorrectionDegree;
	m_elevatorCorrectionRate = other.m_elevatorCorrectionRate;
	m_e10 = other.m_e10;
	m_e14 = other.m_e14;
	m_e18 = other.m_e18;
	m_e1c = other.m_e1c;
	m_e20 = other.m_e20;
	m_e24 = other.m_e24;
	m_e28 = other.m_e28;
	m_e2c = other.m_e2c;
	m_e30 = other.m_e30;
	m_e34 = other.m_e34;
	m_e38 = other.m_e38;
	m_e3c = other.m_e3c;
	return *this;
}
