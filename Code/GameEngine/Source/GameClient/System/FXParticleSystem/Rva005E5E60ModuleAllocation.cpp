// cl: /EHsc /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// COUNT lane near-twin of ?createModule@?$ConcreteModuleTemplate@...LightningDrawModule...
// @ 0x005E8A50 (fx_particle_system_bulk.cpp). Same "new Allocation(sys, this)"
// shape: an inline ctor shim forwards to an out-of-line construct(), then
// stamps three vtables. This target's object is 0xB0 bytes (not 0x8E4), its
// three sub-object vtables sit at +0x00/+0x08/+0x0C (not +0x00/+0x14/+0x18,
// so only three polymorphic bases, packed with no gap -- no fourth base and
// no inline-constructed extra base), and its ctor shim forwards to the ILT
// thunk at 0x000151FE (retail FUN_009efb10) instead of 0x0002A76B. Vtables
// 0x01111F6C/0x01111F68/0x01111F54 verified via tools/vtable_lookup.py: each
// slot table matches a distinct interface, but the owning class name is not
// recovered -- address-derived naming, per the near-twin lane's IDENTITY
// POLICY.

struct Rva005E5E60Sys;

class Rva005E5E60CtorShim
{
public:
	void construct(Rva005E5E60Sys &sys, const void *source);
};

class Rva005E5E60Allocation
{
public:
	__forceinline Rva005E5E60Allocation(Rva005E5E60Sys &sys, const void *source)
	{
		((Rva005E5E60CtorShim *)this)->construct(sys, source);
		*(volatile unsigned int *)this = 0x01111f6c;
		*(volatile unsigned int *)((unsigned char *)this + 0x08) = 0x01111f68;
		*(volatile unsigned int *)((unsigned char *)this + 0x0c) = 0x01111f54;
	}

private:
	unsigned char m_storage[0xb0];
};

class Rva005E5E60Owner
{
public:
	void *createModule(Rva005E5E60Sys &sys);
};

void *Rva005E5E60Owner::createModule(Rva005E5E60Sys &sys)
{
	return (void *)new Rva005E5E60Allocation(sys, this);
}
