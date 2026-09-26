// cl: /O2 /Ob0

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
extern Rva00903C20Device *Rva01340534Device;

bool rva00903C20DeviceQuery()
{
	unsigned result = 0;
	return Rva01340534Device->m_vtable->m_slot70(Rva01340534Device, &result) == 0;
}
