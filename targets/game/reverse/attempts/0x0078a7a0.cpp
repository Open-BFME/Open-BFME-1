// ?renderSetup@Rva00789900Init@@UAEXABVAsciiString@@00@Z
// partial score=0.4473 date=2026-10-09
// ?renderSetup@Rva00789900Init@@UAEXABVAsciiString@@00@Z
// cl: /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
// canonical set layout from matched bindHAnim sibling
#include <set>
#include <stdlib.h>
#include <string.h>
#include <WW3D2/light.h>
#include <WW3D2/scene.h>
#include "vector3.h"

#include "ascii_string.h"

struct Gen_t_00140950_k4 { unsigned int m_value; };
typedef _STL::_Rb_tree<Gen_t_00140950_k4, Gen_t_00140950_k4,
	_STL::_Identity<Gen_t_00140950_k4>, _STL::less<Gen_t_00140950_k4>,
	_STL::allocator<Gen_t_00140950_k4> > ImageAssetTree;

class BfmeList950B
{
public:
	BfmeList950B(void);
	~BfmeList950B(void) { ((ImageAssetTree *)this)->~ImageAssetTree(); }
	char m_storage[0x14];
};

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &name);
};

class Rva007896C0
{
public:
	bool bindHAnim(const AsciiString &name, class Rva0078A5D0Owner *obj, int value);
	class Rva0078A5D0Owner *m_owner;
	class HAnimClass *m_animation;
	int m_second;
	int m_first;
};

class Rva0078A5D0Owner
{
public:
	virtual void release(void);
	int m_refCount;
};

class Rva00789900Init
{
public:
	virtual ~Rva00789900Init();
	virtual void rva00789980();
	virtual void renderViewport00789BF0(int x, int y, int width, int height);
	virtual void renderSetup(const AsciiString &name, const AsciiString &unused, const AsciiString &registrationName);
	unsigned char m_gap0000[0x08];
	SceneClass *m_ownerView;
	unsigned char m_gap0010[8];
	RenderObjClass *m_renderObject;
	int m_childIndex;
	Rva007896C0 m_hAnimHolder;
};

extern int __cdecl bfmeComputeQW(void *item);
extern void Rva009EBAC0(int value);
extern const float g_bfmeDefaultBR;
#define Rva0078A7A0DebugCounter (*(int *)0x013069cc)
#define Rva0078A7A0Scale (*(const double *)0x010aebd0)
#define FirstUpdateSubsystem (*(void **)0x0134faa0)
extern RenderObjClass *__cdecl Create_Render_Obj(const char *name);
void *operator new(unsigned int size);

void Rva00789900Init::renderSetup(const AsciiString &name, const AsciiString &, const AsciiString &registrationName)
{
	SceneClass *ownerView = m_ownerView;
	++Rva0078A7A0DebugCounter;
	if (ownerView == 0)
		return;

	if (FirstUpdateSubsystem)
	{
		BfmeList950B assets;
		(*(AssetList *)&assets) << name;
		Rva009EBAC0((int)&assets);
	}

	const char *renderName = name.str();
	RenderObjClass *renderObject = Create_Render_Obj(renderName);
	if (renderObject == 0)
		return;

	RenderObjClass *view = renderObject;
	int childCount = view->Get_Num_Bones();
	if (childCount <= 0)
		goto no_children;

	for (int i = 0; i < childCount; ++i)
	{
		const char *childName = view->Get_Bone_Name(i);
		if (childName == 0 || *childName == 0)
			continue;

		if (m_renderObject == 0 && _strcmpi(childName, "CAMERA") == 0)
		{
			renderObject->Add_Ref();
			if (m_renderObject) m_renderObject->Release_Ref();
			m_renderObject = renderObject;
			m_childIndex = i;
			continue;
		}

		if (strstr(childName, "LIGHT") == 0)
			continue;
		char *separator = strchr((char *)childName, '_');
		if (separator == 0 || separator[0] == 0)
			continue;
		int number = atoi(separator + 1);
		if (!((double)number * Rva0078A7A0Scale > g_bfmeDefaultBR))
			continue;

		LightClass *light = new LightClass(LightClass::POINT);
		light->Set_Diffuse(Vector3(0.5f, 0.5f, 0.5f));
		light->Set_Ambient(Vector3(0.5f, 0.5f, 0.5f));
		light->Set_Specular(Vector3(0.5f, 0.5f, 0.5f));
		light->Enable_Shadows(true);
		const SphereClass &bounds = view->Get_Bounding_Sphere();
		light->Set_Far_Attenuation_Range(bounds.Radius, bounds.Radius * 2.0f);
		m_ownerView->Register(light, SceneClass::LIGHT);
		view->Add_Sub_Object_To_Bone(light, i, 0);
		light->Release_Ref();
	}

no_children:
	Matrix3D matrix(true);
	view->Set_Transform(matrix);
	view->Set_LOD_Level(0);
	m_ownerView->Add_Render_Object(renderObject);
	int value = bfmeComputeQW((void *)&registrationName);
	m_hAnimHolder.bindHAnim(registrationName, (Rva0078A5D0Owner *)renderObject, value);
	renderObject->Release_Ref();
}
