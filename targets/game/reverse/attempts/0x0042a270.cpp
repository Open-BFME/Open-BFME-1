// ?reallyDoFX@ParticleSystemFXNugget@@IBEXPBUCoord3D@@PBVMatrix3D@@PBVObject@@2@Z
// partial score=0.25 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
// ?reallyDoFX@ParticleSystemFXNugget@@IBEXPBUCoord3D@@PBVMatrix3D@@PBVObject@@2@Z  retail 0x0042A270 3002 B
// First full-flow BFME body (no earlier bank existed). Field names from the BFME FieldParse table as
// used by the matched ctor (ParticleSystemFXNuggetConstructor.cpp). Flow decoded from retail:
// createParticleSystem returns a BfmeParticleSystemHandle (EH state 0; dtor = if (m_system) U1Sub::_bfme_detach);
// every sys-> goes through the handle operator-> (Make00001B18 null system); CreateBoneOverride /
// CreateBoneAtTarget pick the bone matrix translation instead of the radius spread (the random angle is
// still drawn and popped); OrientToObject copies *mtx and, with SetTargetMatrix, post-multiplies by a
// Rotate_Y(PI - atan2(dz + 10, horizontal)) pitch toward the secondary; OnlyIfOnLand/OnlyIfOnWater use
// TerrainLogic slot 0x4C (isUnderwater) + TheAI->pathfinder()->getLayer and destroy the system;
// AttachToBone -> 0x005BE1A0 (sets the AsciiString at sys+0xBC); TargetBoneOverride / UseTargetOffset
// store a target at sys+0x18C with flag sys+0x198; SystemLife -> sys+0x12C; InitialDelay -> ceil import.
// KNOWN GAP (the main lever still open): retail builds every Matrix3D through ??_H(ptr,0x10,3,Vector4 ctor)
// (ILT 0x0000AE5C / 0x00045561). This standalone TU gets an inline 3-call loop instead (Vector4() declared
// only; a defined empty ctor folds away and lets VC7.1 constant-fold the identity pitch matrix, which
// retail cannot because &matrix escapes into ??_H). Measured: the matched in-class doFXObj in
// game/GameEngine/Source/GameClient/FXList.cpp DOES emit ??_H for Matrix3D(1), but the same code as a free
// function, an out-of-class member, or an in-class virtual of another class in that same TU does not.
// Compiled 2870 vs 3002, 2326 non-reloc diffs, shape 0.754, frame 0x124 vs 0x120, this in EBP (retail EDI).

#include <math.h>

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define PI 3.14159265359f
#define LOGICFRAMES_PER_MSEC_REAL 0.005f

extern "C" __declspec(dllimport) double __cdecl ceil(double);

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_CEIL(x) (fast_float2long_round((Real)ceil((double)(x))))

struct Coord3D
{
	Real x, y, z;
};

class Vector4
{
public:
	Vector4();
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	float X, Y, Z, W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline explicit Matrix3D(bool init) { if (init) Make_Identity(); }
	__forceinline Matrix3D(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
	}
	Vector4 &operator[](int i) { return Row[i]; }
	const Vector4 &operator[](int i) const { return Row[i]; }
	__forceinline void Make_Identity(void)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
	__forceinline void Rotate_Y(float theta)
	{
		float tmp1, tmp2;
		float s, c;
		s = sinf(theta);
		c = cosf(theta);
		tmp1 = Row[0][0]; tmp2 = Row[0][2];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[0][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][0]; tmp2 = Row[1][2];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[2][0]; tmp2 = Row[2][2];
		Row[2][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
	}
	// In-place post-multiply, one row at a time.
	__forceinline void postMulRow(int r, const Matrix3D &b)
	{
		float a0 = Row[r][0], a1 = Row[r][1], a2 = Row[r][2];
		float t3 = a0*b[0][3] + a1*b[1][3] + a2*b[2][3];
		Row[r][0] = a0*b[0][0] + a1*b[1][0] + a2*b[2][0];
		Row[r][1] = a0*b[0][1] + a1*b[1][1] + a2*b[2][1];
		Row[r][2] = a0*b[0][2] + a1*b[1][2] + a2*b[2][2];
		Row[r][3] += t3;
	}
	__forceinline void postMul(const Matrix3D &b)
	{
		postMulRow(0, b);
		postMulRow(1, b);
		postMulRow(2, b);
	}
	Vector4 Row[3];
};

void adjustVector(Coord3D *vec, const Matrix3D *mtx);

class AsciiString
{
public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
	};
	const char *str() const { return m_data ? (const char *)(m_data + 1) : ""; }
	Bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	Header *m_data;
};

class GameClientRandomVariable
{
public:
	Real getValue(void) const;
private:
	Real m_min, m_max;
	Int m_type;
};

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, int line);

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

class Drawable
{
public:
	Bool getCurrentWorldspaceClientBonePositions(const char *boneName, Matrix3D &transform) const;
};

class Object
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual Drawable *getDrawable() const;
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}
	Int getLayer() const;
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true) const;
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = 0, Real *terrainZ = 0);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Int getLayer(const Coord3D *pos);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad[0xc];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

class ParticleSystemTemplate;

class ParticleSystem
{
public:
	void setLocalTransform(const Matrix3D *matrix);
	void rotateLocalTransformX(Real x);
	void rotateLocalTransformY(Real y);
	void rotateLocalTransformZ(Real z);
	void attachToObject(const Object *obj);
	void setPosition(const Coord3D *pos);
	void destroy();
	void rva005BE1A0(const AsciiString &boneName);
	void setInitialDelay(UnsignedInt delay) { m_delayLeft = delay; }
	void setSystemLifetime(Int frames) { m_systemLifetime = frames; }
	void setTargetPosition(const Coord3D &pos) { m_targetPos = pos; m_hasTarget = true; }
private:
	unsigned char m_pad000[0x124];
	UnsignedInt m_delayLeft;
	unsigned char m_pad128[0x12c - 0x128];
	Int m_systemLifetime;
	unsigned char m_pad130[0x18c - 0x130];
	Coord3D m_targetPos;
	Bool m_hasTarget;
};

ParticleSystem *Make00001B18(void);

class U1Sub
{
public:
	void _bfme_detach(void);

	ParticleSystem *m_system;
	U1Sub *m_previous;
	U1Sub *m_next;
};

class BfmeParticleSystemHandle : public U1Sub
{
public:
	~BfmeParticleSystemHandle()
	{
		if (m_system)
			_bfme_detach();
	}
	operator Bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make00001B18();
		return m_system;
	}
};

class ParticleSystemManager
{
public:
	const ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
};
extern ParticleSystemManager *TheParticleSystemManager;

class FXNugget
{
public:
	virtual ~FXNugget();
protected:
	int m_nuggetType;
private:
	unsigned char m_bfmeBaseData[0xAC];
};

class ParticleSystemFXNugget : public FXNugget
{
protected:
	void reallyDoFX(const Coord3D *primary, const Matrix3D *mtx, const Object *thingToAttachTo, const Object *secondary) const;

	__forceinline Bool isOverWater(const Coord3D *pos) const
	{
		Bool underwater = TheTerrainLogic->isUnderwater(pos->x, pos->y);
		if (underwater && TheAI && TheAI->pathfinder() && TheAI->pathfinder()->getLayer(pos) != LAYER_GROUND)
			underwater = false;
		return underwater;
	}

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

void ParticleSystemFXNugget::reallyDoFX(const Coord3D *primary, const Matrix3D *mtx,
	const Object *thingToAttachTo, const Object *secondary) const
{
	Coord3D offset = m_offset;
	if (mtx)
	{
		adjustVector(&offset, mtx);
	}

	const ParticleSystemTemplate *tmp = TheParticleSystemManager->findTemplate(m_name);
	if (tmp)
	{
		for (Int i = 0; i < m_count; i++)
		{
			BfmeParticleSystemHandle sys = TheParticleSystemManager->createParticleSystem(tmp, true);
			if (sys)
			{
				Coord3D newPos;
				Real radius = m_radius.getValue();
				Real angle = GetGameClientRandomValueReal(0.0f, 2.0f * PI, "F:\\bfme\\Code\\gameengine\\Source\\GameClient\\FXList.cpp", 0x681);
				Bool useSpread = true;

				if (!m_createBoneOverride.isEmpty() && thingToAttachTo)
				{
					Matrix3D boneMtx(true);
					if (m_createBoneAtTarget && secondary)
						secondary->getDrawable()->getCurrentWorldspaceClientBonePositions(m_createBoneOverride.str(), boneMtx);
					else
						thingToAttachTo->getDrawable()->getCurrentWorldspaceClientBonePositions(m_createBoneOverride.str(), boneMtx);
					newPos.x = boneMtx[0][3];
					newPos.y = boneMtx[1][3];
					newPos.z = boneMtx[2][3];
					useSpread = false;
				}
				else
				{
					newPos.x = radius * cos(angle) + primary->x + offset.x;
					newPos.y = radius * sin(angle) + primary->y + offset.y;
				}

				if (m_createAtGroundHeight && TheTerrainLogic)
				{
					if (useSpread)
					{
						PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, &newPos);
						newPos.z = TheTerrainLogic->getLayerHeight(newPos.x, newPos.y, layer);
					}
				}
				else if (useSpread)
				{
					newPos.z = m_height.getValue() + primary->z + offset.z;
				}

				if (m_orientToObject && mtx)
				{
					Matrix3D orient(*mtx);
					if (m_setTargetMatrix && secondary)
					{
						Coord3D dir;
						const Coord3D *targetPos = secondary->getPosition();
						dir.x = targetPos->x - newPos.x;
						dir.y = targetPos->y - newPos.y;
						dir.z = targetPos->z - newPos.z;
						Matrix3D pitch(true);
						Real horizontal = (Real)sqrt(dir.x * dir.x + dir.y * dir.y);
						pitch.Rotate_Y(PI - (Real)atan2(dir.z + 10.0f, horizontal));
						orient.postMul(pitch);
					}
					sys->setLocalTransform(&orient);
				}

				if (m_rotateX != 0.0f)
					sys->rotateLocalTransformX(m_rotateX);
				if (m_rotateY != 0.0f)
					sys->rotateLocalTransformY(m_rotateY);
				if (m_rotateZ != 0.0f)
					sys->rotateLocalTransformZ(m_rotateZ);

				if (m_onlyIfOnLand)
				{
					Bool overWater = isOverWater(&newPos);
					if ((thingToAttachTo == 0 || thingToAttachTo->getLayer() == LAYER_GROUND) && overWater)
					{
						sys->destroy();
						continue;
					}
				}
				else if (m_onlyIfOnWater)
				{
					Bool overWater = isOverWater(&newPos);
					if (!((thingToAttachTo == 0 || thingToAttachTo->getLayer() == LAYER_GROUND) && overWater))
					{
						sys->destroy();
						continue;
					}
				}

				if (m_attachToObject && thingToAttachTo)
					sys->attachToObject(thingToAttachTo);
				else
					sys->setPosition(&newPos);

				if (!m_attachToBone.isEmpty())
					sys->rva005BE1A0(m_attachToBone);

				if (!m_targetBoneOverride.isEmpty() && secondary)
				{
					Matrix3D targetMtx(true);
					Coord3D targetPos;
					if (secondary->getDrawable()->getCurrentWorldspaceClientBonePositions(m_targetBoneOverride.str(), targetMtx))
					{
						targetPos.x = targetMtx[0][3];
						targetPos.y = targetMtx[1][3];
						targetPos.z = targetMtx[2][3];
					}
					else
					{
						targetPos = *secondary->getPosition();
					}
					sys->setTargetPosition(targetPos);
				}

				if (m_useTargetOffset)
				{
					Coord3D targetPos;
					targetPos.x = newPos.x + m_targetOffset.x;
					targetPos.y = newPos.y + m_targetOffset.y;
					targetPos.z = newPos.z + m_targetOffset.z;
					sys->setTargetPosition(targetPos);
				}

				if (m_systemLife >= 0)
					sys->setSystemLifetime(m_systemLife);

				Real delayInMsec = m_delay.getValue();
				if (delayInMsec >= 0.0f)
				{
					UnsignedInt delayInFrames = REAL_TO_INT_CEIL(delayInMsec * LOGICFRAMES_PER_MSEC_REAL);
					sys->setInitialDelay(delayInFrames);
				}
			}
		}
	}
}
