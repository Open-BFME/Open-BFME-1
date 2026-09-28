// ?d_006ff160@@YAXXZ
// partial score=0.53 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
// Retail 0x006FF160 (3,023 bytes): the last step Rva00700030::initialize runs
// through ILT 0x0003D01E on its own receiver, so the owner is Rva00700030
// (camera +0x70, scene +0x74, three directional lights +0x78..+0x80).
// It creates the world render object named by the settings block embedded at
// g_bfmeGameCW+0x0C and "LM_SunRays", samples a 50x50 height grid through
// 0x006FE600, sets up the three lights and the shadow manager, and reads the
// per-mode tables from "livingworld.txt".  Method name stays address-derived.

#include <stdio.h>
#include <stdlib.h>
#include "rendobj.h"
#include "light.h"
#include "scene.h"
#include "mesh.h"
#include "matrix3d.h"

struct Coord3D
{
	Coord3D(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	float x;
	float y;
	float z;
};

extern char Rva006A16B0Empty[];

class Rva006FF160Name
{
public:
	const char *str() const { return m_data ? m_data + 8 : Rva006A16B0Empty; }
private:
	char *m_data;
};

struct Rva006FF160LightDesc
{
	float m_polar;					// degrees
	float m_azimuth;				// degrees
	Vector3 m_color;
};

struct Rva006FF160Settings
{
	Rva006FF160Name m_worldObjectName;		// +0x00
	unsigned char m_pad004[0x20];
	Vector3 m_ambient;				// +0x24
	Rva006FF160LightDesc m_lights[3];		// +0x30
	unsigned char m_pad06c[0x11c - 0x6c];
	Rva006FF160Name m_subObjectA;			// +0x11C
	Rva006FF160Name m_subObjectB;			// +0x120
	unsigned char m_pad124[0x14c - 0x124];
	Vector3 m_shadowColor;				// +0x14C
	bool m_castShadows;				// +0x158
};

class BfmeGameCW
{
public:
	unsigned char m_pad000[0xc];
	Rva006FF160Settings m_settings;			// +0x0C
};

extern BfmeGameCW *g_bfmeGameCW;

struct Rva006C9270GlobalData
{
	unsigned char m_pad000[0xdb6];
	bool m_xdb6;
	unsigned char m_pad0db7[0xdbc - 0xdb7];
	bool m_xdbc;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;
extern char g_bfmeFlagSGA;

class Rva009EB7A0RefOwner
{
public:
	void Release_Ref();
};

class Gen_0090E810
{
public:
	void bfmeSetFlag(unsigned char value);
protected:
	Rva009EB7A0RefOwner *m_bfmeTarget;
};

class BfmeHandleCX : public Gen_0090E810
{
public:
	~BfmeHandleCX() { if (m_bfmeTarget) m_bfmeTarget->Release_Ref(); }
};

class Rva006FD440
{
public:
	BfmeHandleCX bfmeGet(int pidx, int pass, int stage) const;
};

class BfmeLivingWorldManager
{
public:
	float rva006fe600(Coord3D point);
};

void Rva00739B30(RenderObjClass *object, bool flag);
RenderObjClass *Create_Render_Obj(const char *name);

class Drawable;
class Shadow
{
public:
	struct ShadowTypeInfo;
	virtual void release();
	void enableShadowRender(bool enable) { m_isEnabled = enable; }
private:
	bool m_isEnabled;
};

struct BfmeShadowTypeInfo
{
	char m_shadowNames[128];
	int m_type;
	bool m_allowUpdates;
	bool m_allowWorldAlign;
	unsigned char m_padding86[2];
	float m_sizeX;
	float m_sizeY;
	float m_offsetX;
	float m_offsetY;
	float m_unmodelled98;
	float m_unmodelled9c;
	bool m_unmodelleda0;
};

class W3DShadowManager
{
public:
	Shadow *addShadow(RenderObjClass *renderObject, Shadow::ShadowTypeInfo *info, Drawable *drawable);
	void setLightPosition(int lightIndex, float x, float y, float z);
	void setShadowColor(unsigned int color) { m_shadowColor = color; }
private:
	bool m_isShadowScene;
	unsigned int m_shadowColor;
};

extern W3DShadowManager *TheW3DShadowManager;

extern float g_Va012F8268[3];
extern float g_Va012F825C[3];
extern float g_Va012F8254[2];
extern float g_Va012F824C[2];
extern float g_Va012F8244[2];
extern float g_Va012F823C[2];
extern float g_Va012F8238;
extern float g_bfmeDefaultRateCX;
extern float g_bfmeDeltaAAW;
extern float g_Va012F8274;
extern float g_Va012BAC4C;
extern float g_Va012BAC50;
extern float g_Va012BAC54;

extern void j_0001f744();

#define HALF_PI (WWMATH_PI * 0.5f)
static inline float Sin(float x) { return (float)sin(x); }
static inline float Cos(float x) { return (float)cos(x); }

class Rva00700030
{
public:
	void rva006ff160();

private:
	unsigned char m_pad000[0x74];
	SceneClass *m_scene;				// +0x74
	LightClass *m_lights[3];			// +0x78
	RenderObjClass *m_world;			// +0x84
	float m_x88;					// +0x88
	float m_x8c;					// +0x8C
	Vector3 m_ambient;				// +0x90
	unsigned char m_pad09c[0xec - 0x9c];
	float m_xec;					// +0xEC
	unsigned char m_pad0f0[0x120 - 0xf0];
	Vector3 m_center;				// +0x120
	Vector3 m_extent;				// +0x12C
	RenderObjClass *m_sunRays;			// +0x138
	RenderObjClass *m_subObjectA;			// +0x13C
	RenderObjClass *m_subObjectB;			// +0x140
	unsigned char m_pad144[4];
	Shadow *m_shadow;				// +0x148
	Vector3 m_lightDirection;			// +0x14C
	float m_heights[50 * 50];			// +0x158
};

static void callRva006FE730(Rva00700030 *self)
{
	struct Thunk { void call(); };
	typedef void (Thunk::*Function)();
	union { void (*raw)(); Function member; } function;
	function.raw = j_0001f744;
	(reinterpret_cast<Thunk *>(self)->*function.member)();
}

// ?rva006ff160@Rva00700030@@QAEXXZ
void Rva00700030::rva006ff160()
{
	g_bfmeFlagSGA = 1;
	TheWritableGlobalData->m_xdbc = false;

	const Rva006FF160Settings *settings = &g_bfmeGameCW->m_settings;

	m_world = Create_Render_Obj(settings->m_worldObjectName.str());
	m_sunRays = Create_Render_Obj("LM_SunRays");

	if (m_world)
	{
		m_scene->Add_Render_Object(m_world);
		callRva006FE730(this);

		Vector3 low = m_center - m_extent;
		Vector3 span;
		span = (m_center + m_extent) - low;
		float spanY = span.Y;
		float spanX = span.X;

		for (int i = 0; i < 50; ++i)
		{
			float fx = i * 0.02f;
			for (int j = 0; j < 50; ++j)
			{
				float fy = j * 0.02f;
				m_heights[i * 50 + j] = reinterpret_cast<BfmeLivingWorldManager *>(this)->rva006fe600(
					Coord3D(spanX * fx + low.X, fy * spanY + low.Y, 0.0f));
			}
		}

		float lowest = 99999.9f;
		float highest = -99999.9f;
		int x, y;
		for (x = 0; x < 50; ++x)
		{
			for (y = 0; y < 50; ++y)
			{
				if (lowest > m_heights[x * 50 + y])
					lowest = m_heights[x * 50 + y];
				if (highest < m_heights[x * 50 + y])
					highest = m_heights[x * 50 + y];
			}
		}
		for (x = 0; x < 50; ++x)
			for (y = 0; y < 50; ++y)
				m_heights[x * 50 + y] -= lowest;

		m_subObjectA = m_world->Get_Sub_Object_By_Name(settings->m_subObjectA.str());
		if (m_subObjectA)
		{
			Rva00739B30(m_subObjectA, false);
			m_subObjectA->Release_Ref();
		}

		m_subObjectB = m_world->Get_Sub_Object_By_Name(settings->m_subObjectB.str());
		if (m_subObjectB)
		{
			Rva00739B30(m_subObjectB, false);
			m_subObjectB->Release_Ref();
		}

		MeshModelClass *model = static_cast<MeshClass *>(m_subObjectB)->Get_Model();
		if (model)
		{
			BfmeHandleCX texture = reinterpret_cast<Rva006FD440 *>(model)->bfmeGet(0, 0, 0);
			texture.bfmeSetFlag(1);
			reinterpret_cast<RefCountClass *>(model)->Release_Ref();
		}
	}

	if (m_sunRays)
		m_scene->Add_Render_Object(m_sunRays);

	Vector3 color;
	Vector3 direction;

	color = settings->m_ambient;
	m_ambient = color;

	if (m_lights[0])
	{
		float azimuth = DEG_TO_RADF(settings->m_lights[0].m_azimuth);
		color = settings->m_lights[0].m_color;
		direction.X = settings->m_lights[0].m_polar;
		float polar = DEG_TO_RADF(direction.X) + HALF_PI;
		direction.X = Cos(azimuth) * Sin(polar);
		direction.Y = Sin(azimuth) * Sin(polar);
		direction.Z = Cos(polar);

		m_lightDirection = -direction;
		m_lightDirection.Normalize();
		m_lightDirection *= 10000.0f;

		m_lights[0]->Set_Ambient(Vector3(0.0f, 0.0f, 0.0f));
		m_lights[0]->Set_Specular(Vector3(0.0f, 0.0f, 0.0f));
		m_lights[0]->Set_Diffuse(color);
		Matrix3D transform(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), direction, Vector3(0.0f, 0.0f, 0.0f));
		m_lights[0]->Set_Transform(transform);
		m_scene->Add_Render_Object(m_lights[0]);
	}

	if (m_lights[1])
	{
		float azimuth = DEG_TO_RADF(settings->m_lights[1].m_azimuth);
		color = settings->m_lights[1].m_color;
		direction.X = settings->m_lights[1].m_polar;
		float polar = DEG_TO_RADF(direction.X) + HALF_PI;
		m_lights[1]->Set_Ambient(Vector3(0.0f, 0.0f, 0.0f));
		m_lights[1]->Set_Specular(Vector3(0.0f, 0.0f, 0.0f));
		m_lights[1]->Set_Diffuse(color);
		direction.X = Cos(azimuth) * Sin(polar);
		direction.Y = Sin(azimuth) * Sin(polar);
		direction.Z = Cos(polar);
		Matrix3D transform(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), direction, Vector3(0.0f, 0.0f, 0.0f));
		m_lights[1]->Set_Transform(transform);
		m_scene->Add_Render_Object(m_lights[1]);
	}

	if (m_lights[2])
	{
		float azimuth = DEG_TO_RADF(settings->m_lights[2].m_azimuth);
		color = settings->m_lights[2].m_color;
		direction.X = settings->m_lights[2].m_polar;
		float polar = DEG_TO_RADF(direction.X) + HALF_PI;
		m_lights[2]->Set_Ambient(Vector3(0.0f, 0.0f, 0.0f));
		m_lights[2]->Set_Specular(Vector3(0.0f, 0.0f, 0.0f));
		m_lights[2]->Set_Diffuse(color);
		direction.X = Cos(azimuth) * Sin(polar);
		direction.Y = Sin(azimuth) * Sin(polar);
		direction.Z = Cos(polar);
		Matrix3D transform(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), direction, Vector3(0.0f, 0.0f, 0.0f));
		m_lights[2]->Set_Transform(transform);
		m_scene->Add_Render_Object(m_lights[2]);
	}

	if (settings->m_castShadows)
	{
		BfmeShadowTypeInfo shadowInfo;
		shadowInfo.m_unmodelled9c = 20.0f;
		shadowInfo.m_unmodelleda0 = false;
		shadowInfo.m_type = 2;
		shadowInfo.m_sizeX = 0;
		shadowInfo.m_sizeY = 0;
		shadowInfo.m_offsetX = 0;
		shadowInfo.m_offsetY = 0;
		shadowInfo.m_unmodelled98 = 0.0f;
		m_shadow = TheW3DShadowManager->addShadow(m_world, (Shadow::ShadowTypeInfo *)&shadowInfo, 0);
		m_shadow->enableShadowRender(true);

		unsigned int color = (int)(settings->m_shadowColor.X * 255.0);
		color = (color << 8) | (int)(settings->m_shadowColor.Y * 255.0);
		color = (color << 8) | (int)(settings->m_shadowColor.Z * 255.0);
		TheW3DShadowManager->setShadowColor(color);
		TheW3DShadowManager->setLightPosition(0, m_lightDirection.X, m_lightDirection.Y, m_lightDirection.Z);
	}

	FILE *file = fopen("livingworld.txt", "rt");
	if (file)
	{
		char line[100];
		for (int i = 0; i < 3; ++i)
		{
			fgets(line, 100, file);
			g_Va012F8268[i] = (float)DEG_TO_RAD(atof(line));
			fgets(line, 100, file);
			g_Va012F825C[i] = (float)(atof(line) * m_x8c);
			if (i == 2)
				break;
			fgets(line, 100, file);
			g_Va012F8254[i] = (float)atof(line);
			fgets(line, 100, file);
			g_Va012F824C[i] = (float)atof(line);
			fgets(line, 100, file);
			g_Va012F8244[i] = (float)atof(line);
			fgets(line, 100, file);
			g_Va012F823C[i] = (float)atof(line);
		}
		fgets(line, 100, file);
		g_Va012F8238 = (float)atof(line);
		fgets(line, 100, file);
		g_bfmeDefaultRateCX = (float)atof(line);
		fgets(line, 100, file);
		g_bfmeDeltaAAW = (float)atof(line);
		fclose(file);
	}

	int index = 0;
	if (TheWritableGlobalData && TheWritableGlobalData->m_xdb6)
		index = 1;
	m_xec = g_Va012F8268[index];
	m_x88 = g_Va012F825C[index];
	g_Va012F8274 = g_Va012F8254[index];
	g_Va012BAC4C = g_Va012F824C[index];
	g_Va012BAC50 = g_Va012F8244[index];
	g_Va012BAC54 = g_Va012F823C[index];
}
