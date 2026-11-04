// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source
// stlport
//
// AttributeModifierPoolUpdate::xfer, retail RVA 0x0036AA80, 582 bytes (ret 4).
// Identity: slot 3 (+0x0C) of vtable 0x010E92DC, which the matched
// AttributeModifierPoolUpdate constructor (0x00369FD0) installs, holds the ILT
// 0x00049B98 -> 0x0036AA80. The body is a Snapshot xfer: version {1,3} through
// Xfer::operator==(Version &), then a tail call to the pinned
// UpdateModule::xfer ILT 0x000044C1 with the same Xfer. Layout follows the
// matched siblings (applyAttributeModifier 0x0036A570, update): the entry vector
// at +0x20, next-expiration +0x2C, activation frames +0x30 and counts +0x4C.
//
// Shape notes (measured):
// - AttributeModifierEntry takes its name BY VALUE, as in applyAttributeModifier:
//   retail's EH states are 0 (name temporary) -> -1 (temporary released inside
//   the inlined constructor) -> 1 (entry live). A const reference keeps the
//   temporary alive beside the entry and changes the frame and states.
// - push_back is spelled out: _Construct and _M_insert_overflow are the pinned
//   out-of-line AttributeModifierEntry instantiations (ILTs 0x0000E3BD and
//   0x00048356). Retail passes the empty __false_type tag at the load count's
//   address (the dead xfer argument home) and never stores to it; a real
//   _IsPODType() temporary takes that home itself and grows the frame from
//   0x2C to 0x30, so the tag aliases the count.
// - The clear goes through the out-of-line 16-byte erase at 0x001D2940 (ILT
//   0x00007A45), whose ledger name is the gen-tgrid instantiation.
// - Built against stand-in vector declarations (no <vector>) the same source
//   leaves 12 bytes in three lea/push register choices (+0x59, +0x8E, +0xBD);
//   with real STLport included they match retail.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "Common/System/xfer.h"
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();
	void *m_f04;
	Object *m_object;
};

class PB_BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class PB_UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class UpdateModule : public PB_DeepBase,
	public PB_BehaviorModuleInterface,
	public PB_UpdateModuleInterface
{
protected:
	virtual void xfer(Xfer *xfer);

	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

struct AttributeModifierEntry
{
	Int m_index;
	AsciiString m_unused04;
	UnsignedInt m_expirationFrame;
	UnsignedInt m_unused0c;

	__forceinline AttributeModifierEntry(Int index, AsciiString name)
		: m_index(index), m_unused04(name), m_expirationFrame(0), m_unused0c(0)
	{
	}
};

struct Gen_t_001d2940_p16cd
{
	int a[4];
};

namespace _STL
{
// Retail clears the pool through the out-of-line 16-byte erase at 0x001D2940.
template <>
Gen_t_001d2940_p16cd *vector<Gen_t_001d2940_p16cd, allocator<Gen_t_001d2940_p16cd> >::erase(
	Gen_t_001d2940_p16cd *first, Gen_t_001d2940_p16cd *last);

template <typename T, typename Allocator>
class public_vector : public vector<T, Allocator>
{
public:
	using vector<T, Allocator>::_M_finish;
	using vector<T, Allocator>::_M_end_of_storage;
	using vector<T, Allocator>::_M_insert_overflow;
};
}

typedef _STL::public_vector<AttributeModifierEntry, _STL::allocator<AttributeModifierEntry> > AttributeModifierVector;
typedef _STL::vector<Gen_t_001d2940_p16cd, _STL::allocator<Gen_t_001d2940_p16cd> > ErasedModifierVector;

class AttributeModifierPoolUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	AttributeModifierVector m_modifiers;
	UnsignedInt m_nextExpiration;
	UnsignedInt m_activationFrames[7];
	Int m_counts[7];
};

void AttributeModifierPoolUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 3;
	*xfer == version;

	if (xfer->IsLoading())
	{
		ErasedModifierVector *erased = (ErasedModifierVector *)&m_modifiers;
		erased->erase(erased->begin(), erased->end());

		Int count = 0;
		*xfer == count;
		for (Int index = 0; index < count; ++index)
		{
			AttributeModifierEntry entry(0, AsciiString(""));

			*xfer == entry.m_index;
			if (version.data[1] >= 3)
				*xfer == entry.m_unused04;
			*xfer == entry.m_expirationFrame;
			*xfer == entry.m_unused0c;
			AttributeModifierVector *modifiers = &m_modifiers;
			if (modifiers->_M_finish != modifiers->_M_end_of_storage._M_data)
			{
				_STL::_Construct(modifiers->_M_finish, entry);
				++modifiers->_M_finish;
			}
			else
			{
				// The empty POD tag shares the count's slot, as in retail.
				modifiers->_M_insert_overflow(modifiers->_M_finish, entry,
					reinterpret_cast<const _STL::__false_type &>(count), 1, true);
			}
		}
	}
	else
	{
		Int count = (Int)m_modifiers.size();
		*xfer == count;
		for (AttributeModifierEntry *it = m_modifiers.begin(); it != m_modifiers.end(); ++it)
		{
			AttributeModifierEntry entry = *it;

			*xfer == entry.m_index;
			if (version.data[1] >= 3)
				*xfer == entry.m_unused04;
			*xfer == entry.m_expirationFrame;
			*xfer == entry.m_unused0c;
		}
	}

	if (version.data[1] >= 2)
	{
		for (Int index = 0; index < 7; ++index)
		{
			*xfer == m_activationFrames[index];
			*xfer == m_counts[index];
		}
	}

	UpdateModule::xfer(xfer);
}
