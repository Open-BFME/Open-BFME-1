// cl: /DNDEBUG /MD /EHsc /Iinputs/vendor/stlport /D_STLP_USE_STATIC_LIB
// Open-BFME5: UpgradeSoundSelectorClientBehaviorModuleData::parseSoundUpgrade.
// The field parser constructs one SoundUpgrade record and appends it to the
// module-data vector at +0x08.

#include <stl/_config.h>
#include <vector>

class INI;

// Retail reaches every Rva00608FE0Element operation through an
// incremental-link thunk; parseSoundUpgrade calls its own thunk directly.
extern void j_0002a48c();
extern void j_00042339();
extern void j_00034158();
extern void j_00044210();

struct Rva00608FE0Element
{
	// Declared only, never defined here: the inlined vector::push_back below
	// drives these three out of STLport's own templates, so no call site in
	// this file can name a thunk in their place.
	Rva00608FE0Element();
	Rva00608FE0Element(const Rva00608FE0Element &);
	~Rva00608FE0Element();

	unsigned char m_body[528];
};

#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@XZ=?j_0002a48c@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@ABU0@@Z=?j_00042339@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00608FE0Element@@QAE@XZ=?j_00034158@@YAXXZ")

// The matched 00608DE0 overflow body is owned by
// RvaVectorInsertOverflowOutOfLineCopy.cpp.  Preserve the caller's empty tag
// without instantiating a competing overflow implementation here.
namespace _STL {
template <>
void vector<Rva00608FE0Element>::_M_insert_overflow(Rva00608FE0Element *,
	const Rva00608FE0Element &, const __false_type &, size_t, bool);

template <>
__forceinline void vector<Rva00608FE0Element>::push_back(
	const Rva00608FE0Element &value)
{
	if (_M_finish != _M_end_of_storage._M_data) {
		_Construct(_M_finish, value);
		++_M_finish;
	} else {
		__false_type tag;
		_M_insert_overflow(_M_finish, value, tag, 1, true);
	}
}
}

class UpgradeSoundSelectorClientBehaviorModuleData
{
public:
	static void __cdecl parseSoundUpgrade(INI *ini, void *instance,
		void *, const void *);

private:
	unsigned char m_pad[8];
	_STL::vector<Rva00608FE0Element,
		_STL::allocator<Rva00608FE0Element> > m_soundUpgrades;
};

// ?parseSoundUpgrade@UpgradeSoundSelectorClientBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void __cdecl UpgradeSoundSelectorClientBehaviorModuleData::parseSoundUpgrade(
	INI *ini, void *instance, void *, const void *)
{
	UpgradeSoundSelectorClientBehaviorModuleData *self =
		(UpgradeSoundSelectorClientBehaviorModuleData *)instance;
	if (self == 0)
		return;

	Rva00608FE0Element value;
	// Retail's parse reaches the record through ILT thunk 0x00044210.
	union { void (*fn)(); void (Rva00608FE0Element::*call)(INI *); } parse =
		{ j_00044210 };
	(&value->*parse.call)(ini);
	_STL::vector<Rva00608FE0Element,
		_STL::allocator<Rva00608FE0Element> > *items =
		&self->m_soundUpgrades;
	items->push_back(value);
}
