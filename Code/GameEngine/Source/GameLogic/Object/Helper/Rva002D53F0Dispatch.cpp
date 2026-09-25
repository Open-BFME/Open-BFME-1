// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
class ModelConditionFlags {
public:
 bool test(int bit) const { return m_bits._Unchecked_test(bit); }
 void set(int bit) { m_bits._Unchecked_set(bit); }
private:
 _STL::bitset<320> m_bits;
};
#define BFME_HAVE_MODELCONDITIONFLAGS
// Retail 0x002D53F0..0x002D5475 (133 bytes), no stack arguments.
// Model-condition word +0x12C is bit 252 of the canonical 40-byte field.
// The unchecked STLport pattern follows ObjectSMCHelperSetModelConditionState.cpp.
// ILT 0x2191D -> notifyModelConditionChanged 0x1BE1C0;
// ILT 0xDE9F -> getProjectileUpdateInterface 0x1BF630.
// Address-derived owner view for retail RVA 0x002D53F0. Retail enters through
// a receiver storing its Object pointer at this-8; no semantic owner is claimed.
class ProjectileUpdateInterface;
#define OBJECT_TU_MEMBERS \
	void notifyModelConditionChanged(); \
	ProjectileUpdateInterface *getProjectileUpdateInterface() const;
#include "../object.h"

class Rva002D53F0ModuleInterface {
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void *slot02() = 0; // observed +0x08 dispatch
};
class Rva002D53F0InterfaceA {
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual bool slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot0A() = 0;
	virtual void slot0B() = 0;
	virtual void slot0C() = 0;
	virtual void slot0D() = 0;
	virtual void slot0E() = 0;
	virtual void slot0F() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot1A() = 0;
	virtual void slot1B() = 0;
	virtual void slot1C() = 0;
	virtual void slot1D() = 0;
	virtual void slot1E() = 0;
	virtual void slot1F() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot2A() = 0;
	virtual void slot2B() = 0;
	virtual void slot2C() = 0;
	virtual void slot2D() = 0;
	virtual void slot2E() = 0;
	virtual void slot2F() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot3A(int) = 0;
};

class Rva002D53F0InterfaceB {
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual int slot02(unsigned int) = 0;
};

class Rva002D53F0 {
public:
	void dispatch();
};

void Rva002D53F0::dispatch()
{
 Object *owner = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
 BehaviorModule **module = owner->m_behaviors;
 while (*module != 0) {
  Rva002D53F0ModuleInterface *moduleInterface = reinterpret_cast<Rva002D53F0ModuleInterface *>(reinterpret_cast<char *>(*module) + 0x0C);
  Rva002D53F0InterfaceA *interfaceA = reinterpret_cast<Rva002D53F0InterfaceA *>(moduleInterface->slot02());
  if (interfaceA != 0 && interfaceA->slot02()) {
   if (!owner->m_modelConditionFlags.test(252)) {
    owner->m_modelConditionFlags.set(252);
    owner->notifyModelConditionChanged();
   }
   interfaceA->slot3A(1);
  }
  ++module;
 }
 if (*reinterpret_cast<void **>(reinterpret_cast<char *>(owner) + 0x204) != 0) {
  ProjectileUpdateInterface *projectile = owner->getProjectileUpdateInterface();
  if (projectile != 0) {
   unsigned int id = *reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(owner) + 0x74);
   reinterpret_cast<Rva002D53F0InterfaceB *>(projectile)->slot02(id);
  }
 }
}
