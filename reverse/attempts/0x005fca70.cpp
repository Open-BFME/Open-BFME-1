// ?d_005fca70@@YAXXZ
// partial score=0.5 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem {

class FXList;

class BfmeVal1027 {
public:
	float bfmeVal1027() const;
};

class TerrainCollisionEventFXLookupShim {
public:
	const FXList *lookup(const char *name) const;
};

extern "C" TerrainCollisionEventFXLookupShim *g_terrainCollisionEventFXListStore;

template <int Category>
struct DefaultModuleName {
	static const char VALUE[1];
};

struct OwnerY005FCA70;

// Retail layout: address-derived, same family as 0x005FD6A0 (see
// reverse/re_attempts.log for that banked partial). BaseY005E6290 spans
// outer+0x0..+0x18: its leading dword (+0x0, the eventual own-vtable slot)
// is left untouched by the base ctor, which installs two interim
// "CategoryModuleTemplate<8>"-family vtables at +0x4/+0xc and zeroes the
// trailing two dwords; its declared-only destructor gives retail's SEH frame
// and construction-state byte. The derived ctor then finalizes all three
// vtable slots (+0, +4, +0xc), truncates a BfmeVal1027 member of the owner
// at +0x28 to int via __ftol2 into +0x10 (unlike 0x005FD6A0's float store --
// this sibling truncates), and copies the owner's lazily-cached
// TerrainCollisionEventFX lookup (owner+0x34, keyed by the name pointer at
// owner+0x24 with the same name->m_text ? name->m_text+8 :
// DefaultModuleName<8>::VALUE idiom landed for LifeEventModuleInfo::
// getEventFX / TerrainCollisionModuleInfo::getEventFX in
// fx_particle_system_bulk.cpp) into +0x14, plus one owner byte (+0x1d ->
// +0x8).
class BaseY005E6290
{
public:
	BaseY005E6290(OwnerY005FCA70 *owner);
	~BaseY005E6290();

private:
	unsigned int m_vtbl0;      // +0x00, left uninitialized here
	unsigned int m_vtbl1;      // +0x04
	unsigned char m_flag1;     // +0x08
	unsigned char m_pad[3];
	unsigned int m_vtbl2;      // +0x0c
	unsigned int m_zero1;      // +0x10
	unsigned int m_zero2;      // +0x14
};

BaseY005E6290::BaseY005E6290(OwnerY005FCA70 *)
	: m_vtbl1(0x0107375c), m_flag1(1), m_vtbl2(0x01112a4c),
	  m_zero1(0), m_zero2(0)
{
}

class Rva005FCA70 : public BaseY005E6290
{
public:
	Rva005FCA70(OwnerY005FCA70 *owner);
};

Rva005FCA70::Rva005FCA70(OwnerY005FCA70 *owner)
	: BaseY005E6290(owner)
{
	unsigned char *self = (unsigned char *)this;
	unsigned char *ownerBytes = (unsigned char *)owner;
	BfmeVal1027 *val = (BfmeVal1027 *)(ownerBytes + 0x28);

	*(unsigned int *)(self + 0) = 0x01112a3c;
	*(unsigned int *)(self + 4) = 0x01112810;
	*(unsigned int *)(self + 0xc) = 0x011127fc;

	*(int *)(self + 0x10) = (int)val->bfmeVal1027();

	const FXList **cached = (const FXList **)(ownerBytes + 0x34);
	if (!*cached) {
		const char *name = *(const char **)(ownerBytes + 0x24);
		*cached = g_terrainCollisionEventFXListStore->lookup(
			name ? name + 8 : DefaultModuleName<8>::VALUE);
	}

	*(unsigned int *)(self + 0x14) = (unsigned int)*cached;
	*(unsigned char *)(self + 8) = *(ownerBytes + 0x1d);
}

}
