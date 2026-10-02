// cl: /DNDEBUG /MD /EHsc /Iinputs/vendor/stlport /D_STLP_USE_STATIC_LIB
// Open-BFME5: UpgradeSoundSelectorClientBehaviorModuleData::parseSoundUpgrade.
// The field parser constructs one SoundUpgrade record and appends it to the
// module-data vector at +0x08.

#include <stl/_config.h>
#include <vector>

class INI;

struct Rva00608FE0Element
{
	Rva00608FE0Element();
	Rva00608FE0Element(const Rva00608FE0Element &);
	~Rva00608FE0Element();

	void parse(INI *ini);

	unsigned char m_body[528];
};

#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@XZ=?j_0002a48c@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@ABU0@@Z=?j_00042339@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00608FE0Element@@QAE@XZ=?j_00034158@@YAXXZ")
#pragma comment(linker, "/alternatename:?parse@Rva00608FE0Element@@QAEXPAVINI@@@Z=?j_00044210@@YAXXZ")

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
	value.parse(ini);
	_STL::vector<Rva00608FE0Element,
		_STL::allocator<Rva00608FE0Element> > *items =
		&self->m_soundUpgrades;
	items->push_back(value);
}
