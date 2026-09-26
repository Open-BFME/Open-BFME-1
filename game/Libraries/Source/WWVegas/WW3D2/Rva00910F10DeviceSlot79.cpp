// cl: /O2 /Ob0

struct Rva00910F10Device;
struct Rva00910F10Vtable
{
	void *m_prior[79];
	long (__stdcall *m_slot79)(Rva00910F10Device *, unsigned);
};
struct Rva00910F10Device
{
	Rva00910F10Vtable *m_vtable;
};
extern Rva00910F10Device *Rva01340534Device;
extern unsigned int Rva01340594DX8Calls;

void rva00910F10DeviceSlot79(unsigned value)
{
	Rva01340534Device->m_vtable->m_slot79(Rva01340534Device, value);
	++Rva01340594DX8Calls;
}
