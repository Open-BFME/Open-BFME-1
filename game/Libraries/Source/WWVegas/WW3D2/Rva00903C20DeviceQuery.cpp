// cl: /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug
#include "dx8wrapper.h"

struct Rva00903C20Device;
struct Rva00903C20Vtable
{
	void *m_prior[70];
	long (__stdcall *m_slot70)(Rva00903C20Device *, unsigned *);
};
struct Rva00903C20Device
{
	Rva00903C20Vtable *m_vtable;
};
bool rva00903C20DeviceQuery()
{
	unsigned result = 0;
	Rva00903C20Device *device = reinterpret_cast<Rva00903C20Device *>(DX8Wrapper::_Get_D3D_Device8());
	return device->m_vtable->m_slot70(device, &result) == 0;
}
