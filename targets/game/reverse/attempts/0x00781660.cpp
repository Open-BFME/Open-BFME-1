// ?d_00781660@@YAXXZ
// partial score=0.9977431730986234 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWAudio /Igame/Libraries/Source/Compression /Iinputs/reference/shims/sweep
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
// Recovered BFME W3DTruckDraw::doDrawModule, RVA 0x00781660, 4431 bytes.
// Ten x87 operand bytes remain different; this bank is not a source claim.
// Native headers supply strings, coordinates, matrices, and render objects.
// See targets/game/reverse/attempt_support/0x00781660-20260926.md.
// Drawable::getWheelInfo must remain visible: its exact 17-byte body supplies
// alias information that recovers the caller's integer register allocation.
// It currently lives in DrawableFields.cpp; move its ledger/source ownership
// alongside this body only when landing, rather than defining it twice.
// The W3DTankTruckDraw cast below is the existing callee's legacy typed view.
// Its 436-byte createEmitters body and no-argument thiscall ABI were verified
// independently; that legacy name is not evidence for this caller's owner.
#include "basetype.h"
#include "ascii_string.h"
#include "rendobj.h"


class BfmeVec3FC { public: float x,y,z; };
class BfmeHostFC { public: void bfmeGetPosFC(BfmeVec3FC *); };
class Thing { public: float bfmeRelativeAngleTo(const Coord3D *) const; };
class Rva000D3F10 { public: int test(unsigned); };
class BfmeOwnerRW { public: int bfmeCheckRW(); };
class Rva0077B3F0 { public: void method(const Matrix3D *); };
class W3DTankTruckDraw { friend class W3DTruckDraw; protected: void createEmitters(); };
struct Rva00781660Locomotor { char head[0x40]; unsigned field40; bool isMovingBackwards() const { return (field40 >> 7) & 1; } };
struct AIUpdateInterface { char head[0x140]; BfmeHostFC *path; char gap[0x1cc-0x144]; Rva00781660Locomotor *loco; BfmeHostFC *getPath() const { return path; } Rva00781660Locomotor *getCurLocomotor() const { return loco; } };
class Object : public Thing { public: float bfmeGetNonnegativePreferredLocomotorHeight() const; char head[0x204]; AIUpdateInterface *ai; AIUpdateInterface *getAI() const { return ai; } };
struct TWheelInfo { float m_frontLeftHeightOffset, m_frontRightHeightOffset, m_rearLeftHeightOffset, m_rearRightHeightOffset, m_wheelAngle; };
class Drawable { public: const TWheelInfo *getWheelInfo() const; char head[0xfc]; Object *object; char before138[0x38]; void *m_locoInfo; Object *getObject() const { return object; } };
class ParticleSystem { public: void stop(); };
ParticleSystem *Make00001B18();
struct Rva00781660Handle { ParticleSystem *system; void *previous, *next; operator bool() const { return system != 0; } ParticleSystem *operator->() const { if (!system) return Make00001B18(); return system; } };
struct Rva006C9270GlobalData { char head[0xa80]; bool m_showClientPhysics; };
extern Rva006C9270GlobalData *TheWritableGlobalData;
class GameEngine { public: char head[0x34]; int field34; };
extern GameEngine *TheGameEngine;
class ScriptEngine { public: bool isTimeFrozenDebug(); bool _bfme_isClientFrameFrozen(); bool isFrozen() { return isTimeFrozenDebug() || _bfme_isClientFrameFrozen(); } };
extern ScriptEngine *TheScriptEngine;
class BfmeScriptEngineFreezeExtra { public: unsigned char get() const; };
class View { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0c();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1c();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2c();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3c();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4c();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5c();
virtual void slot60();
virtual void slot64();
virtual void slot68();
virtual void slot6c();
virtual void slot70();
virtual bool isCameraMovementFinished();
virtual void slot78();
virtual void slot7c();
virtual void slot80();
virtual void slot84();
virtual void slot88();
virtual void slot8c();
virtual void slot90();
virtual void slot94();
virtual void slot98();
virtual void slot9c();
virtual void slota0();
virtual void slota4();
virtual void slota8();
virtual void slotac();
virtual void slotb0();
virtual void slotb4();
virtual void slotb8();
virtual void slotbc();
virtual void slotc0();
virtual void slotc4();
virtual void slotc8();
virtual void slotcc();
virtual void slotd0();
virtual bool isTimeFrozen();
};
extern View *TheTacticalView;
class W3DTruckDrawModuleData {
public:
    char prefix[0x168];
    AsciiString m_frontLeftTireBoneName;
    AsciiString m_frontRightTireBoneName;
    AsciiString m_rearLeftTireBoneName;
    AsciiString m_rearRightTireBoneName;
    AsciiString m_midFrontLeftTireBoneName;
    AsciiString m_midFrontRightTireBoneName;
    AsciiString m_midRearLeftTireBoneName;
    AsciiString m_midRearRightTireBoneName;
    AsciiString m_midMidLeftTireBoneName;
    AsciiString m_midMidRightTireBoneName;
    AsciiString field190;
    AsciiString field194;
    AsciiString field198;
    AsciiString field19c;
    AsciiString field1a0;
    AsciiString field1a4;
    AsciiString m_cabBoneName, m_trailerBoneName;
    float m_cabRotationFactor, m_trailerRotationFactor, m_rotationDampingFactor, m_rotationSpeedMultiplier, m_powerslideRotationAddition;
};
class W3DTruckDraw {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6c();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7c();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8c();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9c();
    virtual void slota0();
    virtual void slota4();
    virtual void slota8();
    virtual void slotac();
    virtual void slotb0();
    virtual void slotb4();
    virtual RenderObjClass *getRenderObject() const;
    W3DTruckDrawModuleData *data;
    Drawable *drawable;
    char gap00c[0x27c-0xc];
    bool m_effectsInitialized;
    unsigned char m_wasAirborne;
    bool m_isPowersliding;
    char gap27f;
    Rva00781660Handle m_dustEffect,m_dirtEffect,m_powerslideEffect;
    float m_frontWheelRotation,m_rearWheelRotation,m_midFrontWheelRotation,m_midRearWheelRotation;

    int m_frontLeftTireBone, m_frontRightTireBone;
    int m_rearLeftTireBone, m_rearRightTireBone;
    int m_midFrontLeftTireBone, m_midFrontRightTireBone;
    int m_midRearLeftTireBone, m_midRearRightTireBone;
    int m_midMidLeftTireBone, m_midMidRightTireBone;
    int m_secondaryFrontLeftTireBone, m_secondaryFrontRightTireBone;
    int m_secondaryRearLeftTireBone, m_secondaryRearRightTireBone;
    int m_secondaryMidMidLeftTireBone, m_secondaryMidMidRightTireBone;
    int m_cabBone; float m_curCabRotation; int m_trailerBone; float m_curTrailerRotation; int m_prevNumBones;
    char gap308[0x3e8-0x308];
    RenderObjClass *m_prevRenderObj;
    const W3DTruckDrawModuleData *getW3DTruckDrawModuleData() const { return data; }
protected:
    void updateBones();
public:
    Drawable *getDrawable() const { return drawable; }
    virtual void doDrawModule(const Matrix3D *);
};
void W3DTruckDraw::doDrawModule(const Matrix3D* transformMtx)
{

	((Rva0077B3F0 *)this)->method(transformMtx);

	if (!TheWritableGlobalData->m_showClientPhysics)
		return;
	const W3DTruckDrawModuleData *moduleData = getW3DTruckDrawModuleData();
	if (moduleData==0) return; // shouldn't ever happen.

    if(TheTacticalView->isTimeFrozen() && !TheTacticalView->isCameraMovementFinished()) return;
    if(TheScriptEngine->isFrozen()) return;
    if(((BfmeScriptEngineFreezeExtra *)TheScriptEngine)->get()) return;



	// get object from logic
	Object *obj = getDrawable()->getObject();
	if (obj == 0)
		return;

	if (getRenderObject()==0) return;
	if (getRenderObject() != m_prevRenderObj) {
		updateBones();
	}
	
    float speed=obj->bfmeGetNonnegativePreferredLocomotorHeight();
    if(!(unsigned char)((Rva000D3F10 *)obj)->test(60)) speed=0;

	const TWheelInfo *wheelInfo = getDrawable()->getWheelInfo();	// note, can return null!
	AIUpdateInterface *ai = obj->getAI();
	if (m_cabBone && wheelInfo) {
		Matrix3D cabXfrm(1);
		cabXfrm.Make_Identity();		 
		float desiredAngle = wheelInfo->m_wheelAngle*moduleData->m_cabRotationFactor;

		// Check goal angle.
		if (ai && ai->getPath())
		{
			Coord3D pointOnPath;
			ai->getPath()->bfmeGetPosFC((BfmeVec3FC *)&pointOnPath);
			float angleToGoal = obj->bfmeRelativeAngleTo(&pointOnPath);
			//DEBUG_LOG(("To goal %f, desired %f ", 180*angleToGoal/PI, 180*desiredAngle/PI));
			if (angleToGoal<0) {
				if (desiredAngle<angleToGoal) desiredAngle=angleToGoal;
				if (desiredAngle>0) desiredAngle = 0;
			} else {
				if (desiredAngle>angleToGoal) desiredAngle = angleToGoal;
				if (desiredAngle<0) desiredAngle = 0;
			}
			//DEBUG_LOG(("final desired %f ", 180*desiredAngle/PI));
		}	

		float deltaAngle = desiredAngle - m_curCabRotation;
		deltaAngle *= moduleData->m_rotationDampingFactor;
		m_curCabRotation += deltaAngle;
		cabXfrm.Rotate_Z(m_curCabRotation);
		getRenderObject()->Capture_Bone( m_cabBone );
		getRenderObject()->Control_Bone( m_cabBone, cabXfrm );
		if (m_trailerBone && wheelInfo) {
			desiredAngle = -wheelInfo->m_wheelAngle*moduleData->m_trailerRotationFactor;
			float deltaAngle = desiredAngle - m_curTrailerRotation;
			deltaAngle *= moduleData->m_rotationDampingFactor;
			m_curTrailerRotation += deltaAngle;
			cabXfrm.Make_Identity();
			cabXfrm.Rotate_Z(m_curTrailerRotation);
			getRenderObject()->Capture_Bone( m_trailerBone );
			getRenderObject()->Control_Bone( m_trailerBone, cabXfrm );
		}
	}

	if (m_frontLeftTireBone || m_rearLeftTireBone) 
	{
		float powerslideRotationAddition = moduleData->m_powerslideRotationAddition;
		if (ai) {
			Rva00781660Locomotor *loco = ai->getCurLocomotor();
			if (loco) {
				if (loco->isMovingBackwards()) {
					speed = -speed; // rotate wheels backwards.  jba.
					powerslideRotationAddition = -powerslideRotationAddition;
				}
			}
		}
		const float rotationFactor = moduleData->m_rotationSpeedMultiplier / TheGameEngine->field34;
		m_frontWheelRotation += rotationFactor*speed;
		if (m_isPowersliding) 
		{
			m_rearWheelRotation += rotationFactor*(speed + powerslideRotationAddition);
		} 
		else 
		{
			m_rearWheelRotation += rotationFactor*speed;
		}

		// For now, just use the same values for mid wheels -- may want to do independent calcs later...
		m_midFrontWheelRotation = m_frontWheelRotation;
		m_midRearWheelRotation = m_rearWheelRotation;

		Matrix3D wheelXfrm(1);



		if (m_frontLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_frontLeftHeightOffset);		 
			wheelXfrm.Rotate_Z(wheelInfo->m_wheelAngle);
			wheelXfrm.Rotate_Y(m_frontWheelRotation);
			getRenderObject()->Capture_Bone( m_frontLeftTireBone );
			getRenderObject()->Control_Bone( m_frontLeftTireBone, wheelXfrm );
            if(m_secondaryFrontLeftTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryFrontLeftTireBone);
                getRenderObject()->Control_Bone(m_secondaryFrontLeftTireBone,wheelXfrm);
            }


			wheelXfrm.Make_Identity();
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_frontRightHeightOffset);
			wheelXfrm.Rotate_Z(wheelInfo->m_wheelAngle);
			wheelXfrm.Rotate_Y(m_frontWheelRotation);
			getRenderObject()->Capture_Bone( m_frontRightTireBone );
			getRenderObject()->Control_Bone( m_frontRightTireBone, wheelXfrm );
            if(m_secondaryFrontRightTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryFrontRightTireBone);
                getRenderObject()->Control_Bone(m_secondaryFrontRightTireBone,wheelXfrm);
            }	
		}
		if (m_rearLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_rearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearLeftHeightOffset);
			getRenderObject()->Capture_Bone( m_rearLeftTireBone );
			getRenderObject()->Control_Bone( m_rearLeftTireBone, wheelXfrm );
            if(m_secondaryRearLeftTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryRearLeftTireBone);
                getRenderObject()->Control_Bone(m_secondaryRearLeftTireBone,wheelXfrm);
            }	

			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_rearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearRightHeightOffset);

			//@todo TROUBLE HERE, THE BONE INDICES DO NOT MATCH THE RENDEROBJECTS BONES, SOMETIMES

			getRenderObject()->Capture_Bone( m_rearRightTireBone );
			getRenderObject()->Control_Bone( m_rearRightTireBone, wheelXfrm );
            if(m_secondaryRearRightTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryRearRightTireBone);
                getRenderObject()->Control_Bone(m_secondaryRearRightTireBone,wheelXfrm);
            }	
		}
		if (m_midFrontLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_frontLeftHeightOffset);		 
			wheelXfrm.Rotate_Z(wheelInfo->m_wheelAngle);
			wheelXfrm.Rotate_Y(m_midFrontWheelRotation);
			getRenderObject()->Capture_Bone( m_midFrontLeftTireBone );
			getRenderObject()->Control_Bone( m_midFrontLeftTireBone, wheelXfrm );

			wheelXfrm.Make_Identity();
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_frontRightHeightOffset);
			wheelXfrm.Rotate_Z(wheelInfo->m_wheelAngle);
			wheelXfrm.Rotate_Y(m_midFrontWheelRotation);
			getRenderObject()->Capture_Bone( m_midFrontRightTireBone );
			getRenderObject()->Control_Bone( m_midFrontRightTireBone, wheelXfrm );	
		}
		if (m_midRearLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_midRearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearLeftHeightOffset);
			getRenderObject()->Capture_Bone( m_midRearLeftTireBone );
			getRenderObject()->Control_Bone( m_midRearLeftTireBone, wheelXfrm );	

			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_midRearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearRightHeightOffset);
			getRenderObject()->Capture_Bone( m_midRearRightTireBone );
			getRenderObject()->Control_Bone( m_midRearRightTireBone, wheelXfrm );	
		}
		if (m_midMidLeftTireBone && wheelInfo) 
		{
			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_midRearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearLeftHeightOffset);
			getRenderObject()->Capture_Bone( m_midMidLeftTireBone );
			getRenderObject()->Control_Bone( m_midMidLeftTireBone, wheelXfrm );
            if(m_secondaryMidMidLeftTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryMidMidLeftTireBone);
                getRenderObject()->Control_Bone(m_secondaryMidMidLeftTireBone,wheelXfrm);
            }	

			wheelXfrm.Make_Identity();
			wheelXfrm.Rotate_Y(m_midRearWheelRotation);
			wheelXfrm.Adjust_Z_Translation(wheelInfo->m_rearRightHeightOffset);
			getRenderObject()->Capture_Bone( m_midMidRightTireBone );
			getRenderObject()->Control_Bone( m_midMidRightTireBone, wheelXfrm );
            if(m_secondaryMidMidRightTireBone) {
                getRenderObject()->Capture_Bone(m_secondaryMidMidRightTireBone);
                getRenderObject()->Control_Bone(m_secondaryMidMidRightTireBone,wheelXfrm);
            }	
		}
	}


    ((W3DTankTruckDraw *)this)->createEmitters();
    m_effectsInitialized=true;
    if(m_dustEffect) m_dustEffect->stop();
    if(m_dirtEffect) m_dirtEffect->stop();
    if(m_powerslideEffect) m_powerslideEffect->stop();
    m_wasAirborne=(unsigned char)((BfmeOwnerRW *)obj)->bfmeCheckRW();
}

const TWheelInfo *Drawable::getWheelInfo() const { return m_locoInfo ? reinterpret_cast<const TWheelInfo *>(reinterpret_cast<const unsigned char *>(m_locoInfo)+0x3c) : 0; }
