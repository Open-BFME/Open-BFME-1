// ?recalcBonesForClientParticleSystems@W3DModelDraw@@IAEXXZ
// partial score=0.31 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/w3dmodeldraw /Ireference/shims/asciistring8 /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"
#include "GameClient/Drawable.h"
#include "GameClient/ParticleSys.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"

// Zero Hour twin of the BFME client-particle bone rebuild at 0x00779F10.
void W3DModelDraw::recalcBonesForClientParticleSystems()
{
	if (m_needRecalcBoneParticleSystems) {
		const Drawable *drawable = getDrawable();
		if (drawable != NULL) {
			if (m_curState != NULL &&
				drawable->testDrawableStatus(DRAWABLE_STATUS_NO_STATE_PARTICLES) == FALSE) {
				for (std::vector<ParticleSysBoneInfo>::const_iterator it =
						m_curState->m_particleSysBones.begin();
					 it != m_curState->m_particleSysBones.end(); ++it) {
					ParticleSystem *sys = TheParticleSystemManager->createParticleSystem(
						it->particleSystemTemplate);
					if (sys != NULL) {
						Coord3D pos;
						pos.zero();
						Real rotation = 0.0f;
						Int boneIndex = m_renderObject
							? m_renderObject->Get_Bone_Index(it->boneName.str()) : 0;
						if (boneIndex != 0) {
							Matrix3D originalTransform = m_renderObject->Get_Transform();
							Matrix3D tmp(true);
							tmp.Scale(getDrawable()->getScale());
							m_renderObject->Set_Transform(tmp);
							const Matrix3D boneTransform =
								m_renderObject->Get_Bone_Transform(boneIndex);
							Vector3 vpos = boneTransform.Get_Translation();
							rotation = boneTransform.Get_Z_Rotation();
							m_renderObject->Set_Transform(originalTransform);
							pos.x = vpos.X;
							pos.y = vpos.Y;
							pos.z = vpos.Z;
						}

						sys->setPosition(&pos);
						sys->rotateLocalTransformZ(rotation);
						sys->attachToDrawable(drawable);
						sys->setSaveable(FALSE);
						if (drawable->isDrawableEffectivelyHidden() || m_fullyObscuredByShroud)
							sys->stop();

						ParticleSysTrackerType tracker;
						tracker.id = sys->getSystemID();
						tracker.boneIndex = boneIndex;
						m_particleSystemIDs.push_back(tracker);
					}
				}
			}
		}
		m_needRecalcBoneParticleSystems = false;
	}
}
