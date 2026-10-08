// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Data-only TU: it owns DISABLEDMASK_NONE, the one empty Disabled mask the
// linked build references and nothing in game/ defines.
//
// Upstream: Zero Hour GameEngine/Source/Common/System/DisabledTypes.cpp:54
//     DisabledMaskType DISABLEDMASK_NONE;	// inits to all zeroes
// Size is 4, proven twice over from retail bytes rather than assumed:
//   - the only .text reference to this address is the 15-byte thunk at
//     RVA 0x0011A130 (`mov eax,[esp+4]; mov ecx,[0x12ed858];
//     mov [eax],ecx; ret 4`), already matched as
//     ?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0N@@@XZ
//     (functions.csv); it copies one dword and nothing wider;
//   - retail's next global ?g_Va012ED85C@@3IA starts exactly at 0x012ED85C
//     (targets/game/reverse/dir32_addresses.csv), so the extent is
//     0x012ED858..0x012ED85C = 4 bytes.
// The 13-bit width is not inferred from that size: it comes from the already
// matched row ?getDisabledTypesToProcess@PoisonedBehavior@@UBE?AV?$BitFlags@$0N@@@XZ
// (functions.csv), whose retail body at 0x001B2D50 likewise copies the single
// dword at 0x012ED85C, and whose game/ source
// game/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehaviorGetDisabledTypesThunk.cpp
// declares `extern BitFlags<13> DISABLEDMASK_ALL;` for the sibling symbol.
// $0N is that 13: MSVC encodes a non-type argument by shifting each hex digit
// into A..P, so 13 is 'N', 116 is $0HE, 126 is $0HO and 192 is $0MA.
//
// The canonical spelling is ?DISABLEDMASK_NONE@@3V?$BitFlags@$0N@@@A: the
// trailing @A is the mutable global, which is what ZH's own non-const
// declaration produces and what the referencing objects ask for (only one
// spelling is recorded at 0x012ED858 in dir32_addresses.csv).
//
// BitFlags is declared locally on purpose. ObjectStatusBits.h's BitFlags wraps a
// std::bitset and has a user-provided constructor, so defining the global with it
// would emit a dynamic initializer retail does not have; retail holds plain zero
// words here, and this POD has the same size and mangles to the same name.

template<int NUMBITS>
class BitFlags
{
public:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<13> DisabledMaskType;

// ?DISABLEDMASK_NONE@@3V?$BitFlags@$0N@@@A -- retail VA 0x012ED858, 4 zero bytes
DisabledMaskType DISABLEDMASK_NONE;
// ?DISABLEDMASK_ALL@@3V?$BitFlags@$0N@@@A -- retail VA 0x012ED85C, 4 zero bytes in
// .data; read by the matched PoisonedBehavior::getDisabledTypesToProcess
// (0x001B2D50) and set to all bits at startup by the 0x00104750 store.
DisabledMaskType DISABLEDMASK_ALL;
