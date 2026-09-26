// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// RVA 007647D0: thiscall(), ret0; seven .rdata tables reference its ILT 00033776.
// Offsets agree with the W3DModelDraw witness (+0x34 m_renderObject, +0x3c m_shadow).
#include "matrix3d.h"

class BfmeCalc919G { public: int bfmeCalc919G(); }; // Landed 0041CEC0 via ILT 00017512.

class Rva007647D0ModuleData { public: char unknown00[0x69]; bool flag69; };

struct Rva007647D0Drawable
{
	char unknown00[0xfc];
	void *object;
	const Matrix3D *getTransformMatrix() { return (const Matrix3D *)reinterpret_cast<BfmeCalc919G *>(this)->bfmeCalc919G(); }
};

// Only slot 21 (+0x54, one Matrix3D reference, callee cleanup) is exercised here.
class Rva007647D0RenderObject
{
public:
	virtual void _pad00(); virtual void _pad04(); virtual void _pad08();
	virtual void _pad0c(); virtual void _pad10(); virtual void _pad14();
	virtual void _pad18(); virtual void _pad1c(); virtual void _pad20();
	virtual void _pad24(); virtual void _pad28(); virtual void _pad2c();
	virtual void _pad30(); virtual void _pad34(); virtual void _pad38();
	virtual void _pad3c(); virtual void _pad40(); virtual void _pad44();
	virtual void _pad48(); virtual void _pad4c(); virtual void _pad50();
	virtual void Set_Transform(const Matrix3D &m);
};

// Only slot 1 (+4, no arguments) is exercised here.
class Rva007647D0SecondaryTarget
{
public:
	virtual void _pad00();
	virtual void notify();
};

// Landed 007629F0 (thiscall, Matrix3D&, ret4) on this same object, called through ILT 00026350.
class AttachmentTransform007629F0 { public: void adjust(Matrix3D &); };

class Rva007647D0
{
public:
	void update();

	void *m_vtbl;
	const Rva007647D0ModuleData *m_moduleData;
	Rva007647D0Drawable *m_drawable;
	char unknown0C[0x34 - 0x0C];
	Rva007647D0RenderObject *m_renderObject;
	char unknown38[0x3c - 0x38];
	Rva007647D0SecondaryTarget *m_shadow;
};

// ?update@Rva007647D0@@QAEXXZ
void Rva007647D0::update()
{
	if (m_shadow && m_renderObject && m_drawable->object)
	{
		const Rva007647D0ModuleData *data = m_moduleData;
		Matrix3D mtx(true);
		if (data->flag69)
			mtx.Set_Translation(m_drawable->getTransformMatrix()->Get_Translation());
		else
			mtx = *m_drawable->getTransformMatrix();
		reinterpret_cast<AttachmentTransform007629F0 *>(this)->adjust(mtx);
		m_renderObject->Set_Transform(mtx);
		m_shadow->notify();
	}
}
