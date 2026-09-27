// cl: /DNDEBUG /MD /EHsc
// Retail 0x002EFB20: the cdecl helper both team-member script walks call per
// object (ScriptActions::d_002f5100 and the 0x002EFBE0 lookup shim).
//
// The lifted name on this address (?getModuleNameKey@FlammableUpdate) is
// refuted four ways, so the body takes the address-keyed name the house
// convention uses for a free function of unknown owner (namespace Rva002EFB20):
//   * vtable_lookup --target 0x2EFB20 finds no vtable slot, so this is not the
//     virtual Module::getModuleNameKey that name claims;
//   * both callers push two explicit stack args and clean them themselves, and
//     the body reads its object pointer from [entry+4] and its flag from
//     [entry+8] -- not a thiscall, and not a zero-argument method;
//   * no exit path ever loads the function-local static into eax, so the return
//     type is void, not NameKeyType;
//   * the 104-byte getModuleNameKey bodies (ModuleNameKeys_*.cpp) stop at the
//     static's "return nk"; these 42 extra bytes call findModule and then one
//     of two void members on its result, which a NameKeyType getter cannot do.
// The two callers keep reaching the address through the
// ?bfmeHelperB20@@YAXPAX0@Z pin (BfmeConv827.cpp), whose second argument they
// spell void*; the body itself takes that slot as a by-value flag, because
// retail reads its low byte and never dereferences it.
//
// What the body does: NAMEKEY("FlammableUpdate") once into a function-local
// static, find that module on the object, and on a hit call tryToIgnite (flag
// set) or the flame-cleanup apply (flag clear). Both are void members reached
// on the same pointer, so they are spelled as two casts.

enum NameKeyType { };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
};

class Object
{
public:
	Module *findModule( NameKeyType key ) const;
};

class FlammableUpdate
{
public:
	void tryToIgnite();
};

class FlameCleanup00293E50
{
public:
	void apply();
};

namespace Rva002EFB20
{

// ?helper@Rva002EFB20@@YAXPAX_N@Z
void __cdecl helper( void *obj, bool flag )
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("FlammableUpdate");
	Module *module = ( (Object *)obj )->findModule( nk );
	if ( module )
	{
		if ( flag )
		{
			( (FlammableUpdate *)module )->tryToIgnite();
		}
		else
		{
			( (FlameCleanup00293E50 *)module )->apply();
		}
	}
}

}
