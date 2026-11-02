// ?updateBonesForClientParticleSystems@W3DModelDraw@@UAE_NXZ
// partial score=0.1051 date=2026-11-03
// cl: /DNDEBUG /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA 0x00762F40, 590 bytes (ret 4): slot 0 of the W3DModelDraw
// draw-interface vtable (VA 0x01122408, ILT 0x0003D974; slot 1 is the matched
// W3DModelDraw::setPauseAnimation), shared by seven draw classes. The body is
// Zero Hour's W3DModelDraw::updateBonesForClientParticleSystems loop (move each
// tracked client particle system to its bone) reshaped by BFME: the trackers
// sit in a STLport list at +0x3C of the interface, systems come back as
// by-value handles from ParticleSystemManager::findParticleSystemByID, a
// module-data flag (+0xFE) switches to the drawable's named-bone lookup, and
// a bool argument stops the walk at the first system whose +0x1AB byte is
// clear. The ILT contradicts the Zero Hour decoration (with or without the
// argument), so the method keeps an address-derived name.
// `this` is the draw-interface subobject: the module data and drawable sit
// just before it (-8/-4); the view models that with the primary base.

#define _STLP_USE_NEWALLOC 1
#include <list>

typedef bool Bool;

enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

class Matrix3D
{
public:
	float Row[3][4];
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : Rva006A16B0Empty;
	}

private:
	void releaseBuffer();

	void *m_data;
	static char Rva006A16B0Empty[];
};
#define Rva006A16B0Empty __identifier("?Rva006A16B0Empty@@3PADA")
extern "C" char Rva006A16B0Empty[];
#undef Rva006A16B0Empty

// The list element (copy constructor at 0x00762E80): system id, bone index,
// bone name and two scalars.
class Rva00762E80
{
public:
	Rva00762E80(const Rva00762E80 &other);

	ParticleSystemID m_id;
	int m_boneIndex;
	BFMERetailAsciiString m_boneName;
	int m_0c;
	char m_10;
};

class Drawable
{
public:
	Bool getCurrentWorldspaceClientBonePositions(const char *boneName, Matrix3D &transform) const;
};

class ParticleSystem
{
public:
	void start(void);
	void stop(void);
	void setLocalTransform(const Matrix3D *transform);
	void setSkipParentXfrm(Bool enable);

	unsigned char m_pad[0x1AB];
	Bool m_1ab;
};

class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA(void);

class GenNode_006fa270
{
public:
	void unlink(void);
};

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() { ((GenNode_006fa270 *)this)->unlink(); }

	ParticleSystem *operator->() const
	{
		return m_system ? m_system : (ParticleSystem *)bfmeNullSystemZA();
	}

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystemManager
{
	friend class W3DModelDraw;
private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class RenderObjClass
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0; virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0;
	virtual const Matrix3D &Get_Bone_Transform(int boneIndex) = 0;		// +0xC8
	virtual void slot51() = 0;
	virtual Bool slot52(int boneIndex) = 0;							// +0xD0
};

class W3DModelDrawModuleData
{
public:
	unsigned char m_pad[0xFE];
	Bool m_useNamedBones;
};

class W3DModelDrawModuleView
{
public:
	virtual void slot00();

protected:
	const W3DModelDrawModuleData *m_moduleData;		// interface -8
	Drawable *m_drawable;								// interface -4
};

class W3DModelDrawInterfaceView
{
public:
	virtual Bool rva00762F40(Bool stopAtInactive) = 0;
};

class W3DModelDraw : public W3DModelDrawModuleView, public W3DModelDrawInterfaceView
{
public:
	virtual Bool rva00762F40(Bool stopAtInactive);

private:
	void *m_curState;									// interface +0x04
	unsigned char m_pad08[0x28 - 0x08];
	RenderObjClass *m_renderObject;					// interface +0x28
	unsigned char m_pad2c[0x3C - 0x2C];
	_STL::list<Rva00762E80> m_particleSystemIDs;		// interface +0x3C
};

// ?rva00762F40@W3DModelDraw@@UAE_N_N@Z
Bool W3DModelDraw::rva00762F40(Bool stopAtInactive)
{
	if (m_curState == 0 || m_renderObject == 0 || m_drawable == 0)
		return true;
	{
		for (_STL::list<Rva00762E80>::iterator it = m_particleSystemIDs.begin();
			it != m_particleSystemIDs.end(); ++it)
		{
			BfmeParticleSystemHandle sys = TheParticleSystemManager->findParticleSystemByID((*it).m_id);
			if (sys.m_system == 0)
				continue;
			if (!sys.m_system->m_1ab && stopAtInactive)
				return true;

			int boneIndex = (*it).m_boneIndex;
			if (m_moduleData->m_useNamedBones)
			{
				Rva00762E80 tracker(*it);
				Matrix3D transform;
				if (m_drawable->getCurrentWorldspaceClientBonePositions(tracker.m_boneName.str(), transform))
				{
					sys->setLocalTransform(&transform);
					sys->setSkipParentXfrm(true);
				}
			}
			else if (boneIndex != 0)
			{
				if (m_renderObject->slot52(boneIndex))
					sys->start();
				else
					sys->stop();
				Matrix3D originalTransform = m_renderObject->Get_Bone_Transform(boneIndex);
				sys->setLocalTransform(&originalTransform);
				sys->setSkipParentXfrm(true);
			}
		}
	}
	return true;
}
