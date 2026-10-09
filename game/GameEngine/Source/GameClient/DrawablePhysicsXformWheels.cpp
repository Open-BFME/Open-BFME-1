// cl: /DNDEBUG /DWIN32 /MD
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Identity: the landed Drawable::calcPhysicsXform caller reaches this body twice.
// Ported from the ZH Drawable.cpp wheel suspension routine. BFME delegates terrain
// tilt to RVA 00413A40, uses one pitch limit and damps the wheel angle toward zero.
// Drawable +FC/+138 and LocomotorTemplate offsets are witnessed by name_oracle.
// DrawableLocoInfo offsets agree with its landed constructor and the ZH fields.
// Object +204 is independently used by ObjectHeightAndLayer.cpp; +208 remains opaque.
// The constructor has no unwind cleanup at the retail allocation site.
#include <math.h>
typedef int Int;
#define NULL 0
typedef float Real; typedef bool Bool;
#define PI 3.14159265358979323846f
#include "../../../Libraries/Include/Lib/Coord3D.h"
class Overridable { public: void *vtable; const Overridable *m_nextOverride; const Overridable *getFinalOverride() const; };
class LocomotorTemplate: public Overridable { public: char pad8[0x84-8]; float m_accelPitchLimit,m_bounceKick,m_pitchStiffness,m_rollStiffness,m_pitchDamping,m_rollDamping; char pad9c[0xb4-0x9c]; float m_uniformAxialDamping; char padb8[0xd8-0xb8]; bool m_hasSuspension; char padd9[3]; float m_maximumWheelExtension; };
class Locomotor { public: void *vtable; const LocomotorTemplate *m_template;
 const LocomotorTemplate *getTemplate() const { const LocomotorTemplate *p=m_template; if(p && p->m_nextOverride) p=(const LocomotorTemplate*)p->m_nextOverride->getFinalOverride(); return p; }
};
struct TWheelInfo
{
	Real m_frontLeftHeightOffset;
	Real m_frontRightHeightOffset;
	Real m_rearLeftHeightOffset;
	Real m_rearRightHeightOffset;
	Real m_wheelAngle;
	Int	 m_framesAirborneCounter;
	Int	 m_framesAirborne;
};

class DrawableLocoInfo { public: void *vtable;
	Real m_pitch;
	Real m_pitchRate;
	Real m_roll;
	Real m_rollRate;
	Real m_yaw;
	Real m_accelerationPitch;
	Real m_accelerationPitchRate;
	Real m_accelerationRoll;
	Real m_accelerationRollRate;
	Real m_overlapZVel;
	Real m_overlapZ;
	Real m_wobble;
  Real m_yawModulator;
  Real m_pitchModulator;
	TWheelInfo m_wheelInfo;

	DrawableLocoInfo() throw();
};
class BfmeGeometryInfo { public: float boxMajorRadius() const; float boxMinorRadius() const; };
class AIUpdateInterface { public: float getCurLocomotorSpeed(); };
class Object { public: char pad[0x204]; AIUpdateInterface *m_ai; void *dword_208; int getLayer() const; float bfmeGetNonnegativePreferredLocomotorHeight() const;
 BfmeGeometryInfo &getGeometryInfo() { return *(BfmeGeometryInfo*)((char*)this+0xac); }
};
// ILT 00019FF1 reaches the matched int-returning predicate at 00131B20.
class BfmeOwnerRW { public: int bfmeCheckRW(); };
class TerrainLogic { public: virtual void s0();virtual void s4();virtual void s8();virtual void sc();virtual void s10();virtual void s14();virtual void s18(); virtual float getLayerHeight(float,float,int,Coord3D*,bool); };
extern TerrainLogic *TheTerrainLogic;
class BfmeUnitRC; class BfmeHolderRC;
class BfmeOwnerRC { public: char bfmeSendRC(BfmeUnitRC*,BfmeHolderRC*,void*,void*,void*,void*); };
class BFMERopeDrawable { public: const Coord3D *getPosition() const; };
class Thing { public: const Coord3D *getUnitDirectionVector2D() const; };
float Sin(float);
int GetGameClientRandomValue(int,int,char*,int);
class Drawable { public:
 struct PhysicsXformInfo { float m_totalPitch,m_totalRoll,m_totalYaw,m_totalZ; };
 char pad[0xfc]; Object *m_object; char pad100[0x38]; DrawableLocoInfo *m_locoInfo;
 protected: void calcPhysicsXformWheels(const Locomotor*,PhysicsXformInfo&);
};
void Drawable::calcPhysicsXformWheels(const Locomotor *locomotor, PhysicsXformInfo& info) {

	if (m_locoInfo == NULL)
		m_locoInfo = new DrawableLocoInfo;

	const Real ACCEL_PITCH_LIMIT = locomotor->getTemplate()->m_accelPitchLimit;

	const Real BOUNCE_ANGLE_KICK = locomotor->getTemplate()->m_bounceKick;
	const Real PITCH_STIFFNESS = locomotor->getTemplate()->m_pitchStiffness;
	const Real ROLL_STIFFNESS =  locomotor->getTemplate()->m_rollStiffness;
	const Real PITCH_DAMPING = locomotor->getTemplate()->m_pitchDamping;
	const Real ROLL_DAMPING = locomotor->getTemplate()->m_rollDamping;

	const Real UNIFORM_AXIAL_DAMPING = locomotor->getTemplate()->m_uniformAxialDamping;

	const Real MAX_SUSPENSION_EXTENSION = locomotor->getTemplate()->m_maximumWheelExtension;

	const Bool DO_WHEELS = locomotor->getTemplate()->m_hasSuspension;

	Object *obj = m_object;
	if (obj == NULL)
		return;

	AIUpdateInterface *ai = obj->m_ai;
	if (ai == NULL)
		return ;

	void *physics = obj->dword_208;
	if (physics == NULL)
		return ;

	const Coord3D *pos = ((const BFMERopeDrawable*)this)->getPosition();
	const Coord3D *dir = ((const Thing*)this)->getUnitDirectionVector2D();
float groundPitch=0,groundRoll=0;
 ((BfmeOwnerRC*)this)->bfmeSendRC((BfmeUnitRC*)obj,(BfmeHolderRC*)locomotor,(void*)pos,(void*)dir,&groundPitch,&groundRoll);
 float hheight=TheTerrainLogic->getLayerHeight(pos->x,pos->y,obj->getLayer(),0,true);

	const unsigned char airborne = (unsigned char)((BfmeOwnerRW *)obj)->bfmeCheckRW();

	if (airborne)
	{
		if (DO_WHEELS)
		{

			m_locoInfo->m_wheelInfo.m_framesAirborne = 0;
			m_locoInfo->m_wheelInfo.m_framesAirborneCounter++;
			if (pos->z - hheight > -MAX_SUSPENSION_EXTENSION)
			{
				m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset += (MAX_SUSPENSION_EXTENSION - m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset)/2.0f;
				m_locoInfo->m_wheelInfo.m_rearRightHeightOffset += (MAX_SUSPENSION_EXTENSION - m_locoInfo->m_wheelInfo.m_rearRightHeightOffset)/2.0f;
			}
			else
			{
				m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset += (0 - m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset)/2.0f;
				m_locoInfo->m_wheelInfo.m_rearRightHeightOffset += (0 - m_locoInfo->m_wheelInfo.m_rearRightHeightOffset)/2.0f;
			}
		}

		Real length = obj->getGeometryInfo().boxMajorRadius();
		Real width = obj->getGeometryInfo().boxMinorRadius();
		Real pitchHeight = length*Sin(m_locoInfo->m_pitch + m_locoInfo->m_accelerationPitch - groundPitch);
		Real rollHeight = width*Sin(m_locoInfo->m_roll + m_locoInfo->m_accelerationRoll - groundRoll);
		info.m_totalZ = (fabs(pitchHeight) + fabs(rollHeight))/4;
		return;
	}

	Real curSpeed = obj->bfmeGetNonnegativePreferredLocomotorHeight();

	Real maxSpeed = ai->getCurLocomotorSpeed();
	if (!airborne && curSpeed > maxSpeed/10)
	{
		Real factor = curSpeed/maxSpeed;
		if (fabs(m_locoInfo->m_pitchRate)<factor*BOUNCE_ANGLE_KICK/4 && fabs(m_locoInfo->m_rollRate)<factor*BOUNCE_ANGLE_KICK/8)
		{

			switch (GetGameClientRandomValue(0,3,"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\Drawable.cpp",3219))
			{
			case 0:
				m_locoInfo->m_pitchRate -= BOUNCE_ANGLE_KICK*factor;
				m_locoInfo->m_rollRate -= BOUNCE_ANGLE_KICK*factor/2;
				break;
			case 1:
				m_locoInfo->m_pitchRate += BOUNCE_ANGLE_KICK*factor;
				m_locoInfo->m_rollRate -= BOUNCE_ANGLE_KICK*factor/2;
				break;
			case 2:
				m_locoInfo->m_pitchRate -= BOUNCE_ANGLE_KICK*factor;
				m_locoInfo->m_rollRate += BOUNCE_ANGLE_KICK*factor/2;
				break;
			case 3:
				m_locoInfo->m_pitchRate += BOUNCE_ANGLE_KICK*factor;
				m_locoInfo->m_rollRate += BOUNCE_ANGLE_KICK*factor/2;
				break;
			}
		}
	}

	if (!airborne)
	{
		m_locoInfo->m_pitchRate += ((-PITCH_STIFFNESS * (m_locoInfo->m_pitch - groundPitch)) + (-PITCH_DAMPING * m_locoInfo->m_pitchRate));
		if (m_locoInfo->m_pitchRate > 0.0f)
			m_locoInfo->m_pitchRate *= 0.5f;

		m_locoInfo->m_rollRate += ((-ROLL_STIFFNESS * (m_locoInfo->m_roll - groundRoll)) + (-ROLL_DAMPING * m_locoInfo->m_rollRate));
	}

	m_locoInfo->m_pitch += m_locoInfo->m_pitchRate * UNIFORM_AXIAL_DAMPING;
	m_locoInfo->m_roll += m_locoInfo->m_rollRate   * UNIFORM_AXIAL_DAMPING;

	m_locoInfo->m_accelerationPitchRate += ((-PITCH_STIFFNESS * (m_locoInfo->m_accelerationPitch)) + (-PITCH_DAMPING * m_locoInfo->m_accelerationPitchRate));
	m_locoInfo->m_accelerationPitch += m_locoInfo->m_accelerationPitchRate;

	m_locoInfo->m_accelerationRollRate += ((-ROLL_STIFFNESS * m_locoInfo->m_accelerationRoll) + (-ROLL_DAMPING * m_locoInfo->m_accelerationRollRate));
	m_locoInfo->m_accelerationRoll += m_locoInfo->m_accelerationRollRate;

	info.m_totalPitch = m_locoInfo->m_pitch + m_locoInfo->m_accelerationPitch;
	info.m_totalRoll = m_locoInfo->m_roll + m_locoInfo->m_accelerationRoll;

	if (m_locoInfo->m_accelerationPitch > ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationPitch = ACCEL_PITCH_LIMIT;
	else if (m_locoInfo->m_accelerationPitch < -ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationPitch = -ACCEL_PITCH_LIMIT;

	if (m_locoInfo->m_accelerationRoll > ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationRoll = ACCEL_PITCH_LIMIT;
	else if (m_locoInfo->m_accelerationRoll < -ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationRoll = -ACCEL_PITCH_LIMIT;

	info.m_totalYaw = 0;
	info.m_totalZ = 0;

	Real length = obj->getGeometryInfo().boxMajorRadius();
	Real width = obj->getGeometryInfo().boxMinorRadius();
	Real pitchHeight = length*Sin(info.m_totalPitch-groundPitch);
	Real rollHeight = width*Sin(info.m_totalRoll-groundRoll);
	if (DO_WHEELS)
	{

		m_locoInfo->m_wheelInfo.m_framesAirborne = m_locoInfo->m_wheelInfo.m_framesAirborneCounter;
		m_locoInfo->m_wheelInfo.m_framesAirborneCounter = 0;
		TWheelInfo newInfo = m_locoInfo->m_wheelInfo;
		newInfo.m_wheelAngle=0;

		#define WHEEL_SMOOTHNESS 10.0f
		m_locoInfo->m_wheelInfo.m_wheelAngle += (newInfo.m_wheelAngle - m_locoInfo->m_wheelInfo.m_wheelAngle)/WHEEL_SMOOTHNESS;

		const Real SPRING_FACTOR = 0.9f;
		if (pitchHeight<0) {
			newInfo.m_frontLeftHeightOffset = SPRING_FACTOR*(pitchHeight*(1.0f/3+1.0f/2));
			newInfo.m_frontRightHeightOffset = SPRING_FACTOR*(pitchHeight*(1.0f/3+1.0f/2));
			newInfo.m_rearLeftHeightOffset = pitchHeight*(-1.0f/2+1.0f/4);
			newInfo.m_rearRightHeightOffset = pitchHeight*(-1.0f/2+1.0f/4);
		}	else {
			newInfo.m_frontLeftHeightOffset = (pitchHeight*(-1.0f/4+1.0f/2));
			newInfo.m_frontRightHeightOffset = (pitchHeight*(-1.0f/4+1.0f/2));
			newInfo.m_rearLeftHeightOffset = SPRING_FACTOR*(pitchHeight*(-1.0f/2-1.0f/3));
			newInfo.m_rearRightHeightOffset = SPRING_FACTOR*(pitchHeight*(-1.0f/2-1.0f/3));
		}
		if (rollHeight>0) {
			newInfo.m_frontRightHeightOffset += -SPRING_FACTOR*(rollHeight*(1.0f/3+1.0f/2));
			newInfo.m_rearRightHeightOffset += -SPRING_FACTOR*(rollHeight*(1.0f/3+1.0f/2));
			newInfo.m_rearLeftHeightOffset += rollHeight/2 - rollHeight/4;
			newInfo.m_frontLeftHeightOffset += rollHeight/2 - rollHeight/4;
		}	else {
			newInfo.m_frontRightHeightOffset += -rollHeight*(1.0f/2-1.0f/4);
			newInfo.m_rearRightHeightOffset += -rollHeight*(1.0f/2-1.0f/4);
			newInfo.m_rearLeftHeightOffset += SPRING_FACTOR*(rollHeight*(1.0f/3+1.0f/2));
			newInfo.m_frontLeftHeightOffset += SPRING_FACTOR*(rollHeight*(1.0f/3+1.0f/2));
		}
		if (newInfo.m_frontLeftHeightOffset < m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset) {

			m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset += (newInfo.m_frontLeftHeightOffset - m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset)/2.0f;
		}	else {
			m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset = newInfo.m_frontLeftHeightOffset;
		}
		if (newInfo.m_frontRightHeightOffset < m_locoInfo->m_wheelInfo.m_frontRightHeightOffset) {

			m_locoInfo->m_wheelInfo.m_frontRightHeightOffset += (newInfo.m_frontRightHeightOffset - m_locoInfo->m_wheelInfo.m_frontRightHeightOffset)/2.0f;
		}	else {
			m_locoInfo->m_wheelInfo.m_frontRightHeightOffset = newInfo.m_frontRightHeightOffset;
		}
		if (newInfo.m_rearLeftHeightOffset < m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset) {

			m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset += (newInfo.m_rearLeftHeightOffset - m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset)/2.0f;
		}	else {
			m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset = newInfo.m_rearLeftHeightOffset;
		}
		if (newInfo.m_rearRightHeightOffset < m_locoInfo->m_wheelInfo.m_rearRightHeightOffset) {

			m_locoInfo->m_wheelInfo.m_rearRightHeightOffset += (newInfo.m_rearRightHeightOffset - m_locoInfo->m_wheelInfo.m_rearRightHeightOffset)/2.0f;
		}	else {
			m_locoInfo->m_wheelInfo.m_rearRightHeightOffset = newInfo.m_rearRightHeightOffset;
		}

		if (m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset<MAX_SUSPENSION_EXTENSION) {
			m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset=MAX_SUSPENSION_EXTENSION;
		}
		if (m_locoInfo->m_wheelInfo.m_frontRightHeightOffset<MAX_SUSPENSION_EXTENSION) {
			m_locoInfo->m_wheelInfo.m_frontRightHeightOffset=MAX_SUSPENSION_EXTENSION;
		}
		if (m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset<MAX_SUSPENSION_EXTENSION) {
			m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset=MAX_SUSPENSION_EXTENSION;
		}
		if (m_locoInfo->m_wheelInfo.m_rearRightHeightOffset<MAX_SUSPENSION_EXTENSION) {
			m_locoInfo->m_wheelInfo.m_rearRightHeightOffset=MAX_SUSPENSION_EXTENSION;
		}

	}

	Real divisor = 4;
	Real pitch = fabs(info.m_totalPitch-groundPitch);

	if (pitch>PI/8) {
		divisor = ((4*PI/8) + (1*(pitch-PI/8)))/pitch;
	}
	info.m_totalZ += fabs(pitchHeight)/divisor;
	info.m_totalZ += fabs(rollHeight)/divisor;
}