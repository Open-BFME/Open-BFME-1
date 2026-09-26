// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x00615FE0, 156 bytes.  The body walks the AsciiString hash_map at
// manager+0x224, the same table the matched siblings rva00615cb0, rva00616110,
// rva00616240 and rva00616410 walk, so BfmeLivingWorldManager owns it.  For
// every entry it resolves the override chain hanging off the mapped object at
// +4 and returns the object whose resolved head carries the argument at +0xC.
// The chain walker is the matched ?getFinalOverride@Overridable@@QBEPBV1@XZ at
// 0x00087A80, which the body reaches through ILT 0x000022BB.  No caller names
// the method, so the name keeps the address.
//
// Reading m_override three times through the accessor is what makes VC7.1
// materialize the sub-object address with add eax,4 before one CSE-d load.
// Caching it in a local folds the load into [eax+4] and shifts the body by
// two bytes.

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
	char m_unmodelled08[4];
	void *m_field0c;
};

struct Rva00615FE0Slot
{
	Overridable *getFinal() const
	{
		if (m_override != 0 && m_override->m_nextOverride != 0)
			return (Overridable *)m_override->m_nextOverride->getFinalOverride();
		return m_override;
	}

	Overridable *m_override;
};

struct Rva00615D50Object
{
	char m_unmodelled00[4];
	Rva00615FE0Slot m_slot;
};

typedef _STL::hash_map<AsciiString, Rva00615D50Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00615FE0Map;

class BfmeLivingWorldManager
{
public:
	Rva00615D50Object *rva00615fe0(void *key);

private:
	unsigned char m_prefix[0x224];
	Rva00615FE0Map m_objects;
};

Rva00615D50Object *BfmeLivingWorldManager::rva00615fe0(void *key)
{
	for (Rva00615FE0Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		if (it->second->m_slot.getFinal()->m_field0c == key)
			return it->second;
	}
	return 0;
}
