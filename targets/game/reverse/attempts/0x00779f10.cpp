// ?recalcBonesForClientParticleSystems@W3DModelDraw@@IAEXXZ
// partial score=0.9 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims
// stlport
//
// Retail 0x00779F10 (2480 bytes): BFME's
// W3DModelDraw::recalcBonesForClientParticleSystems, the Zero Hour method
// grown into a list-driven attachment pass.  It merges the current state's
// bone particle list (+0x50) with the second list at +0x10's +0x9C, reuses or
// retires tracked systems by key, creates each new system through the
// handle-returning ParticleSystemManager factory, places it by pristine bone,
// bone transform or scaled bone translation, and records a tracker at the
// front or back of the list at +0x48.  Flag, state and render-object offsets
// follow the W3DModelDraw layout witness.

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "rendobj.h"
#include <list>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int Color;

template <class T> struct StringData
{
	int refs;
	unsigned short length, capacity;
	T text[1];
};

template <class T> class StringBase
{
	friend class AsciiString;

protected:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	StringData<T> *m_data;

private:
	StringBase(const StringBase &s);
	void releaseBuffer();

public:
	void set(const StringBase &s);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &s) : StringBase<char>(s) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &s)
	{
		StringBase<char>::set(s);
		return *this;
	}
	const char *str() const { return m_data ? m_data->text : ""; }
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class Drawable;
class ParticleSystemTemplate;

class Object
{
public:
	Color getIndicatorColor() const;
};

// The per-system colour sink at ParticleSystem+0x1B0; only its slot 4 is used.
class Rva00779F10ColorSink
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void setColor(Color color);
};

class ParticleSystem
{
public:
	void destroy();
	void setPosition(const Coord3D *pos);
	void rotateLocalTransformZ(Real rotation);
	void setLocalTransform(const Matrix3D *transform);
	void attachToDrawable(const Drawable *drawable);
	void setSaveable(Bool saveable);
	void stop();

	ParticleSystemID getSystemID() const { return m_systemID; }
	void applyIndicatorColor(Color color)
	{
		if (m_colorSink)
			m_colorSink->setColor(color);
	}

	char m_pad000[0x98];
	void *m_handleHead;
	void *m_handleTail;
	char m_pad0a0[0xac - 0xa0];
	ParticleSystemID m_systemID;
	char m_pad0b0[0x1ab - 0xb0];
	Bool m_localTransformMode;
	char m_pad1ac[0x1b0 - 0x1ac];
	Rva00779F10ColorSink *m_colorSink;
};

ParticleSystem *Make00001B18(void);

// The intrusive handle the BFME particle-system manager hands out: the handle
// links itself into the system's handle list at +0x98/+0x9C.
class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle()
	{
		if (m_system)
		{
			if (m_previous)
				m_previous->m_next = m_next;
			else
				m_system->m_handleHead = m_next;
			if (m_next)
				m_next->m_previous = m_previous;
			else
				m_system->m_handleTail = m_previous;
			m_previous = 0;
			m_next = 0;
		}
	}

	operator Bool() const { return m_system != 0; }

	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make00001B18();
		return m_system;
	}

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class W3DModelDraw;

class ParticleSystemManager
{
	friend class W3DModelDraw;

public:
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate,
		Bool createSlaves);

private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class Drawable
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions,
		Matrix3D *transforms, Int maxBones) const;
	Real getScale() const;
	Bool isDrawableEffectivelyHidden() const;
	Object *getObject() const { return m_object; }

	char m_pad000[0xfc];
	Object *m_object;
	char m_pad100[0x110 - 0x100];
	unsigned int m_status;
	char m_pad114[0x2ec - 0x114];
	Int m_int2ec;
};

enum
{
	DRAWABLE_STATUS_NO_STATE_PARTICLES = 0x08
};

typedef void (*Rva00779F10Callback)(Int userData, ParticleSystemID id);

// One bone particle entry; the element type keeps the name its out-of-line
// _Construct is pinned under.
struct Rva0076A930Element
{
	AsciiString boneName;
	Bool localTransform;
	Int drawableFilter;
	Int key;
	Int mode;
	Int userData;
	Rva00779F10Callback callback;
	const ParticleSystemTemplate *particleSystemTemplate;
	Bool useIndicatorColor;
};

// One tracked system; likewise named by its pinned _Construct.
struct Rva0076AA30Element
{
	ParticleSystemID id;
	Int boneIndex;
	AsciiString boneName;
	Int key;
	Bool retired;
};

// Zero Hour's name for the tracker record.
typedef Rva0076AA30Element ParticleSysTrackerType;

struct ModelConditionInfo
{
	char m_pad00[0x50];
	std::list<Rva0076A930Element> m_particleSysBones;
};

struct Rva00779F10Extra
{
	char m_pad00[0x9c];
	std::list<Rva0076A930Element> m_particleSysBones;
};

struct W3DModelDrawModuleData
{
	char m_pad00[0xfe];
	Bool m_usePristineBones;
};

class W3DModelDrawPrimaryBase
{
public:
	virtual void sharedSlot();
	W3DModelDrawModuleData *m_moduleData;
	Drawable *m_drawable;
};

class W3DModelDrawSecondaryBase
{
public:
#define MD_SLOT(n) virtual void v##n();
	MD_SLOT(00) MD_SLOT(01) MD_SLOT(02) MD_SLOT(03) MD_SLOT(04) MD_SLOT(05) MD_SLOT(06) MD_SLOT(07)
	MD_SLOT(08) MD_SLOT(09) MD_SLOT(10) MD_SLOT(11) MD_SLOT(12) MD_SLOT(13) MD_SLOT(14) MD_SLOT(15)
	MD_SLOT(16) MD_SLOT(17) MD_SLOT(18) MD_SLOT(19) MD_SLOT(20) MD_SLOT(21) MD_SLOT(22) MD_SLOT(23)
	MD_SLOT(24) MD_SLOT(25)
#undef MD_SLOT
	virtual void slot068(Bool value);
};

class W3DModelDraw : public W3DModelDrawPrimaryBase, public W3DModelDrawSecondaryBase
{
public:
	void rva00779910();

protected:
	const W3DModelDrawModuleData *getW3DModelDrawModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }

	void recalcBonesForClientParticleSystems();

	Rva00779F10Extra *m_extra010;
	const ModelConditionInfo *m_curState;
	char m_pad018[0x2c - 0x18];
	Bool m_needRecalcBoneParticleSystems;
	Bool m_fullyObscuredByShroud;
	char m_pad02e[0x34 - 0x2e];
	RenderObjClass *m_renderObject;
	char m_pad038[0x48 - 0x38];
	std::list<ParticleSysTrackerType> m_particleSystemIDs;
};

void W3DModelDraw::recalcBonesForClientParticleSystems()
{
	if (m_needRecalcBoneParticleSystems)
	{
		const Drawable *drawable = getDrawable();
		if (drawable == 0)
			return;

		if (m_curState != 0 && (drawable->m_status & DRAWABLE_STATUS_NO_STATE_PARTICLES) == 0)
		{
			std::list<Rva0076A930Element> bones;
			std::list<Rva0076A930Element>::const_iterator src;
			for (src = m_curState->m_particleSysBones.begin();
				src != m_curState->m_particleSysBones.end(); ++src)
				bones.push_back(*src);
			for (src = m_extra010->m_particleSysBones.begin();
				src != m_extra010->m_particleSysBones.end(); ++src)
				bones.push_back(*src);

			for (std::list<Rva0076A930Element>::iterator it = bones.begin(); it != bones.end(); ++it)
			{
				Rva0076A930Element info = *it;

				if (info.key != 0)
				{
					for (std::list<ParticleSysTrackerType>::iterator t = m_particleSystemIDs.begin();
						t != m_particleSystemIDs.end(); ++t)
					{
						if (t->key != info.key)
							continue;

						Int mode = info.mode;
						if (mode == 3 || t->retired)
							goto next;

						if (mode == 2 || mode == 1)
						{
							BfmeParticleSystemHandle existing =
								TheParticleSystemManager->findParticleSystemByID(t->id);
							if (existing)
								existing->destroy();
							if (mode == 1)
								m_particleSystemIDs.erase(t);
							else if (mode == 2)
								t->retired = true;
							goto next;
						}
					}
				}

				if (info.particleSystemTemplate == 0)
					goto next;

				{
					BfmeParticleSystemHandle handle = TheParticleSystemManager->createParticleSystem(
						info.particleSystemTemplate, true);
					if (!handle)
						goto next;

					if (info.drawableFilter != 0 && drawable->m_int2ec != info.drawableFilter)
						goto next;

					Coord3D pos;
					pos.zero();
					Real rotation = 0.0f;
					Int boneIndex = m_renderObject ? m_renderObject->Get_Bone_Index(info.boneName.str()) : 0;

					if (getW3DModelDrawModuleData()->m_usePristineBones)
					{
						Matrix3D transform;
						if (getDrawable()->getPristineBonePositions(info.boneName.str(), 0, 0, &transform, 1))
							handle->setLocalTransform(&transform);
					}
					else if (info.localTransform && boneIndex != 0 && m_renderObject)
					{
						Matrix3D transform = m_renderObject->Get_Bone_Transform(boneIndex);
						handle->setLocalTransform(&transform);
					}
					else
					{
						if (!info.localTransform && boneIndex != 0 && m_renderObject)
						{
							Matrix3D originalTransform = m_renderObject->Get_Transform();
							Matrix3D tmp(true);
							tmp.Scale(getDrawable()->getScale());
							m_renderObject->Set_Transform(tmp);
							const Matrix3D boneTransform = m_renderObject->Get_Bone_Transform(boneIndex);
							Vector3 vpos = boneTransform.Get_Translation();
							rotation = boneTransform.Get_Z_Rotation();
							m_renderObject->Set_Transform(originalTransform);
							pos.x = vpos.X;
							pos.y = vpos.Y;
							pos.z = vpos.Z;
						}
						handle->setPosition(&pos);
						handle->rotateLocalTransformZ(rotation);
					}

					handle->attachToDrawable(drawable);
					handle->setSaveable(false);
					handle->m_localTransformMode = info.localTransform;

					Object *obj = drawable->getObject();
					if (obj && info.useIndicatorColor)
						handle->applyIndicatorColor(obj->getIndicatorColor());

					if (drawable->isDrawableEffectivelyHidden() || m_fullyObscuredByShroud)
						handle->stop();

					ParticleSysTrackerType tracker;
					tracker.id = handle->getSystemID();
					tracker.boneIndex = boneIndex;
					tracker.boneName = info.boneName;
					tracker.key = info.key;
					tracker.retired = false;

					if (info.callback)
						info.callback(info.userData, handle->getSystemID());

					if (handle->m_localTransformMode)
						m_particleSystemIDs.push_front(tracker);
					else
						m_particleSystemIDs.push_back(tracker);
				}
			next:
				;
			}
			bones.clear();
		}
		m_needRecalcBoneParticleSystems = false;
	}
	else
	{
		slot068(true);
		rva00779910();
	}
}
