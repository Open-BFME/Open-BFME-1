// ?d_005fb530@@YAXXZ
// partial score=0.4 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/GameEngine/Source/Common/System
// Retail layout: the primary module view is 0x1c bytes and the emission info
// starts at +0x1c with two Coord3D records followed by nine random variables.

#include "coord3d.h"
#include "game_client_random_variable.h"
#include <math.h>

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;
extern const float g_bfmeK1253;

class Rva005FB4D0Host;

class Rva005FB4D0Node
{
public:
	Rva005FB4D0Host *m_host;
	Rva005FB4D0Node *m_next;
	Rva005FB4D0Node *m_prev;
};

class Rva005FB4D0Owner
{
public:
	void link(Rva005FB4D0Node *node);

	int m_bfmePad000;
	Rva005FB4D0Host *m_host;
};

class GenNode_006fa270
{
public:
	void unlink();
};

struct Vec3_005FB530
{
	Vec3_005FB530() {}
	Vec3_005FB530(float xValue, float yValue, float zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}

	float x;
	float y;
	float z;
};

class Matrix3D_005FB530
{
public:
	struct Row
	{
		float x;
		float y;
		float z;
		float w;
	};

	Row m_row[3];

	Vec3_005FB530 getTranslation() const
	{
		return Vec3_005FB530(m_row[0].w, m_row[1].w, m_row[2].w);
	}

	static void inverseTransform(const Matrix3D_005FB530 &matrix,
		const Vec3_005FB530 &input, Vec3_005FB530 *output)
	{
		Vec3_005FB530 temporary;
		const Vec3_005FB530 *value;
		if (output == &input)
		{
			temporary = input;
			value = &temporary;
		}
		else
			value = &input;

		Vec3_005FB530 difference(value->x - matrix.m_row[0].w,
			value->y - matrix.m_row[1].w,
			value->z - matrix.m_row[2].w);
		output->x = matrix.m_row[0].x * difference.x
			+ matrix.m_row[1].x * difference.y
			+ matrix.m_row[2].x * difference.z;
		output->y = matrix.m_row[0].y * difference.x
			+ matrix.m_row[1].y * difference.y
			+ matrix.m_row[2].y * difference.z;
		output->z = matrix.m_row[0].z * difference.x
			+ matrix.m_row[1].z * difference.y
			+ matrix.m_row[2].z * difference.z;
	}
};

class ParticleSystemZA
{
public:
	unsigned char m_beforeTransform[0xc0];
	Matrix3D_005FB530 m_localTransform;
	unsigned char m_betweenFlags[0x18c - 0xf0];
	float m_anchorX;
	float m_anchorY;
	float m_anchorZ;
	unsigned char m_isLocalIdentity;
};

ParticleSystemZA *bfmeNullSystemZA();

namespace FXParticleSystem
{

class T1A1_005DD290
{
public:
	virtual void unusedVirtual();

protected:
	unsigned int m_storage[4];
};

class ParticleModuleCategorySlice
{
public:
	virtual void unusedVirtual();
};

class ParticleModuleSnapshotSlice
{
public:
	virtual void unusedVirtual();
};

template <int Category>
class DefaultParticleModule
	: public T1A1_005DD290,
	  public ParticleModuleCategorySlice,
	  public ParticleModuleSnapshotSlice
{
};

class EmissionVolumeInfo
{
public:
	virtual void unusedVirtual();

protected:
	bool m_isHollow;
	unsigned char m_alignment[3];
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
protected:
	Coord3D m_start;
	Coord3D m_end;
	GameClientRandomVariable m_random[9];
};

class LightningEmissionModule
	: public DefaultParticleModule<5>, public LightningEmissionInfo
{
public:
	virtual Coord3D getPosition(float, float, int index, int count);
};

typedef char DefaultParticleModuleLayout[
	(sizeof(DefaultParticleModule<5>) == 0x1c) ? 1 : -1];
typedef char LightningEmissionInfoLayout[
	(sizeof(LightningEmissionInfo) == 0x8c) ? 1 : -1];

Coord3D LightningEmissionModule::getPosition(float, float, int index,
int count)
{
	LightningEmissionModule *module = this;
	Vec3_005FB530 start;
	Vec3_005FB530 end;
	Vec3_005FB530 delta;
	Rva005FB4D0Node node;

	if (count <= 1 || count >= 30)
	{
		Coord3D result;
		return result;
	}

	static Coord3D points[30];
	int pointIndex = index;

	start.x = module->m_start.x;
	start.y = module->m_start.y;
	start.z = module->m_start.z;
	end.x = module->m_end.x;
	end.y = module->m_end.y;
	end.z = module->m_end.z;

	((Rva005FB4D0Owner *)module)->link(&node);
	ParticleSystemZA *host = (ParticleSystemZA *)node.m_host;
	if (host == 0)
		host = bfmeNullSystemZA();

	if (host->m_isLocalIdentity)
	{
		ParticleSystemZA *system = (ParticleSystemZA *)node.m_host;
		if (system == 0)
			system = bfmeNullSystemZA();

		Vec3_005FB530 origin = system->m_localTransform.getTranslation();
		Matrix3D_005FB530::inverseTransform(system->m_localTransform,
			origin, &start);

		ParticleSystemZA *second = (ParticleSystemZA *)node.m_host;
		if (second == 0)
			second = bfmeNullSystemZA();
		Vec3_005FB530 anchor;
		anchor.x = second->m_anchorX;
		anchor.y = second->m_anchorY;
		anchor.z = second->m_anchorZ;
		Matrix3D_005FB530::inverseTransform(second->m_localTransform,
			anchor, &end);
	}

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	delta.z = end.z - start.z;
	((Coord3D *)&delta)->normalize();

	float lateralX = delta.y;
	float lateralY = delta.x - lateralX;
	float lateralZ = BfmeZeroRange - BfmeZeroRange;
	float step = g_bfmeDefaultBU / (float)(count - 1);
	float fraction = BfmeZeroRange;
	float wave0 = module->m_random[0].getValue();
	float wave1 = module->m_random[1].getValue();
	float wave2 = module->m_random[2].getValue();
	float wave3 = module->m_random[3].getValue();
	float wave4 = module->m_random[4].getValue();
	float wave5 = module->m_random[5].getValue();
	float wave6 = module->m_random[6].getValue();
	float wave7 = module->m_random[7].getValue();
	float wave8 = module->m_random[8].getValue();

	for (int i = count; i > 0; --i)
	{
		float envelope = g_bfmeK1253 - (float)fabs(g_bfmeK1253 - fraction);
		float xWave = (float)sin(fraction * wave1 + wave2) * envelope * wave0;
		float yWave = (float)sin(fraction * wave3 + wave4) * envelope * wave5;
		float zWave = (float)sin(fraction * wave6 + wave7) * envelope * wave8;
		points[count - i].x = start.x + fraction * delta.x + lateralX * xWave + lateralX * yWave + lateralX * zWave;
		points[count - i].y = start.y + fraction * delta.y + lateralY * xWave + lateralY * yWave + lateralY * zWave;
		points[count - i].z = start.z + fraction * delta.z + lateralZ * xWave + lateralZ * yWave + lateralZ * zWave;
		fraction += step;
	}

	((GenNode_006fa270 *)&node)->unlink();
	Coord3D result;
	result.x = fraction;
	result.y = points[pointIndex].x;
	result.z = points[pointIndex].z;
	return result;
}

}
