// cl: /O2 /Ob0

struct Rva00903470Device;
struct Rva00903470Vtable
{
	void *m_prior[77];
	long (__stdcall *m_slot77)(Rva00903470Device *, unsigned);
};
struct Rva00903470Device
{
	Rva00903470Vtable *m_vtable;
};
extern Rva00903470Device *Rva01340534Device;
extern unsigned int Rva01340594DX8Calls;

void rva00903470DeviceSlot77(unsigned char value)
{
	Rva01340534Device->m_vtable->m_slot77(Rva01340534Device, value);
	++Rva01340594DX8Calls;
}
