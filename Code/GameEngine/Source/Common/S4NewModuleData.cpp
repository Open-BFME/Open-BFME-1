// Five bodies -- three of 110 bytes and two of 107 -- of SAGE's module-data
// factory, the one shape that reaches `INI::initFromINIMultiProc`:
//
//     ModuleData *friend_newModuleData( INI *ini )
//     {
//         XModuleData *data = new XModuleData;
//         if ( ini ) ini->initFromINIMultiProc( data, XModuleData::buildFieldParse );
//         return data;
//     }
//
// WHAT THE BYTES SHOW, AND WHY THE CALLEE IS NAMED.  The second call is
// 0x00852130 in all five, and that address is already a matched row:
// `?initFromINIMultiProc@INI@@QAEXPAXP6AXAAVMultiIniFieldParse@@@Z@Z`.  It is
// __thiscall -- ecx is loaded with the incoming pointer, TESTED, and still live
// across the call -- and it pops its own two dwords.  So the guarded call is a
// member call on the function's own argument, and the argument is an `INI *`.
// That callee's signature also fixes the two pushed dwords: an untyped `void *`
// and a pointer to a `void (MultiIniFieldParse &)` procedure.  This is the only
// name in this family that is RECOVERED rather than derived.
//
// The second pushed dword is a DIR32 to a low-RVA incremental-link thunk, not to
// a body -- following the five through their thunks reaches 0x0021A280,
// 0x0024E6C0, 0x00202F20, 0x00116500 and 0x007594E0.  Read as raw RVAs instead
// of virtual addresses those five land in the thunk table and disassemble into
// nonsense; the image base has to come off first.
//
// The `new` is the plain MSVC sequence with a DEFAULT constructor -- nothing is
// pushed before `call` and `this` is the only input -- wrapped in an EH state
// that goes to 0 for the allocation and back to -1 before the guarded call.
// The null-allocation arm is `xor esi,esi` and joins the main path, so a failed
// allocation still runs the `if` and still returns; the source has one `return`.
//
// THE AXES ARE THE ALLOCATION SIZE, THE CONSTRUCTOR AND THE PROCEDURE.  Retail's
// five sizes are 428, 428, 36, 364 and 12 bytes; the two that fit an imm8 are
// the two 107-byte bodies.  Two rows share a size but have different
// constructors and different procedures, so they stay separate types.
//
// IDENTITY IS NOT RECOVERED for the module-data classes themselves.  Each is
// named after the factory that allocates it, sized only to the byte count the
// `push` shows, and given a DECLARED constructor pinned to the address its REL32
// resolves to.  `buildFieldParse` is declared and never defined; its address is
// a DIR32 the patcher copies, so nothing here asserts which parse table it is.
// WHICH MODULE each of the five is remains open -- the size and the two
// addresses are the whole evidence, and nothing in these bytes names a class.

class MultiIniFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc( void *what, void ( *proc )( MultiIniFieldParse & ) );
};

#define S4_NEW_MODULE_DATA( NAME, DWORDS )                                     \
	struct S4ModuleData##NAME                                                  \
	{                                                                          \
		int m_storage[ DWORDS ];                                               \
		S4ModuleData##NAME();                                                  \
		static void buildFieldParse( MultiIniFieldParse &p );                  \
	};                                                                         \
	S4ModuleData##NAME *s4newModuleData##NAME( INI *ini )                      \
	{                                                                          \
		S4ModuleData##NAME *data = new S4ModuleData##NAME;                     \
		if ( ini )                                                             \
			ini->initFromINIMultiProc( data,                                   \
				S4ModuleData##NAME::buildFieldParse );                         \
		return data;                                                           \
	}

S4_NEW_MODULE_DATA( 00116640, 107 )
S4_NEW_MODULE_DATA( 00116D80, 107 )
S4_NEW_MODULE_DATA( 00116E90, 9 )
S4_NEW_MODULE_DATA( 0012A070, 91 )
S4_NEW_MODULE_DATA( 006BF930, 3 )
