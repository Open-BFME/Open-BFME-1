// ?d_0078a7a0@@YAXXZ
// partial score=0.23284 date=2026-09-24
// ?renderSetup@Rva0078A7A0Owner@@QAEXABVAsciiString@@H0@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WW3D2
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
// canonical set layout from matched bindHAnim sibling
#include <set>
#include <stdlib.h>
#include <string.h>
#include <light.h>
#include "vector3.h"

#include "ascii_string.h"

struct Gen_t_00140950_k4 { int m_value; };
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

class Rva0078A7A0OwnerRef
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(RenderObjClass *obj) = 0;
};

class Rva0078A7A0OpaqueRenderView
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2C(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot38(LightClass *light, int enabled) = 0;
	virtual void slot3C(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot4C(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot54(const float *matrix) = 0;
	virtual void slot58(void) = 0;
	virtual void slot5C(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot64(void) = 0;
	virtual void slot68(void) = 0;
	virtual void slot6C(void) = 0;
	virtual void slot70(void) = 0;
	virtual void slot74(void) = 0;
	virtual void slot78(void) = 0;
	virtual void slot7C(void) = 0;
	virtual void slot80(void) = 0;
	virtual void slot84(void) = 0;
	virtual void slot88(void) = 0;
	virtual void slot8C(void) = 0;
	virtual void slot90(void) = 0;
	virtual void slot94(LightClass *light, int a, int b) = 0;
	virtual void slot98(void) = 0;
	virtual void slot9C(void) = 0;
	virtual void slotA0(void) = 0;
	virtual void slotA4(void) = 0;
	virtual void slotA8(void) = 0;
	virtual void slotAC(void) = 0;
	virtual void slotB0(void) = 0;
	virtual void slotB4(void) = 0;
	virtual void slotB8(void) = 0;
	virtual int slotBC(void) const = 0;
	virtual const char *slotC0(int index) const = 0;
	virtual void slotC4(void) = 0;
	virtual void slotC8(void) = 0;
	virtual void slotCC(void) = 0;
	virtual void slotD0(void) = 0;
	virtual void slotD4(void) = 0;
	virtual void slotD8(void) = 0;
	virtual void slotDC(void) = 0;
	virtual void slotE0(void) = 0;
	virtual void slotE4(void) = 0;
	virtual void slotE8(void) = 0;
	virtual void slotEC(void) = 0;
	virtual void slotF0(void) = 0;
	virtual void slotF4(void) = 0;
	virtual void slotF8(void) = 0;
	virtual void slotFC(void) = 0;
	virtual const float *boundsView(void) const = 0;
	virtual void slot104(void) = 0;
	virtual void slot108(void) = 0;
	virtual void slot10C(void) = 0;
	virtual void slot110(void) = 0;
	virtual void slot114(void) = 0;
	virtual void slot118(void) = 0;
	virtual void slot11C(void) = 0;
	virtual void slot120(void) = 0;
	virtual void slot124(void) = 0;
	virtual void slot128(void) = 0;
	virtual void slot12C(void) = 0;
	virtual void slot130(void) = 0;
	virtual void slot134(void) = 0;
	virtual void slot138(int value) = 0;
};

class Rva007896C0
{
public:
	bool bindHAnim(const AsciiString &name, class Rva0078A5D0Owner *obj, int value);
};

class Rva0078A5D0Owner
{
public:
	virtual void release(void);
	int m_refCount;
};

class Rva0078A7A0Owner
{
public:
	void renderSetup(const AsciiString &name, int unused, const AsciiString &registrationName);
	unsigned char m_gap0000[0x0c];
	Rva0078A7A0OwnerRef *m_ownerView;
	unsigned char m_gap0010[8];
	RenderObjClass *m_renderObject;
	int m_childIndex;
	Rva007896C0 m_hAnimHolder;
};

extern int __cdecl bfmeComputeQW(void *item);
extern void Rva009EBAC0(int value);
extern const float BfmeZeroRange;
#define Rva0078A7A0DebugCounter (*(int *)0x013069cc)
#define Rva0078A7A0Scale (*(const double *)0x010aebd0)
#define FirstUpdateSubsystem (*(void **)0x0134faa0)
extern RenderObjClass *__cdecl Create_Render_Obj(const char *name);
void *operator new(unsigned int size);

void Rva0078A7A0Owner::renderSetup(const AsciiString &name, int, const AsciiString &registrationName)
{
	Rva0078A7A0OwnerRef *ownerView = m_ownerView;
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

	Rva0078A7A0OpaqueRenderView *view = (Rva0078A7A0OpaqueRenderView *)renderObject;
	int childCount = view->slotBC();
	if (childCount <= 0)
		goto no_children;

	for (int i = 0; i < childCount; ++i)
	{
		const char *childName = view->slotC0(i);
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
		if (!((double)number * Rva0078A7A0Scale > BfmeZeroRange))
			continue;

		LightClass *light = new LightClass(LightClass::POINT);
		Vector3 first(0.5f, 0.5f, 0.5f);
		Vector3 second(0.5f, 0.5f, 0.5f);
		Vector3 third(0.5f, 0.5f, 0.5f);
		light->Set_Ambient(first);
		light->Set_Diffuse(second);
		light->Set_Specular(third);
		light->Enable_Shadows(true);
		const float *bounds = view->boundsView();
		float radius = bounds[3];
		light->Set_Far_Attenuation_Range(radius, radius * 2.0f);
		((Rva0078A7A0OpaqueRenderView *)m_ownerView)->slot38(light, 1);
		view->slot94(light, i, 0);
		light->Release_Ref();
	}

no_children:
	float matrix[12] = { 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	view->slot54(matrix);
	view->slot138(0);
	m_ownerView->slot08(renderObject);
	int value = bfmeComputeQW((void *)&registrationName);
	m_hAnimHolder.bindHAnim(registrationName, (Rva0078A5D0Owner *)renderObject, value);
	renderObject->Release_Ref();
}
