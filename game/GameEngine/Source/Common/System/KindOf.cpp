// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Data-only TU: it owns KINDOFMASK_NONE, the one empty KindOf mask the linked
// build references and nothing in game/ defines.
//
// Upstream: Zero Hour GameEngine/Source/Common/System/KindOf.cpp:164
//     KindOfMaskType KINDOFMASK_NONE;	// inits to all zeroes
// BFME widened KindOfMaskType past Zero Hour's 126-bit KINDOF_COUNT (the
// reference shim inputs/reference/shims/bfmekindof/Common/KindOf.h still
// enumerates 126), so the mask is six dwords, not one.
// Size is proven from retail bytes, not from the width pin:
// game/GameEngine/Source/Common/KindOfMaskCountThunk.cpp pins the width only,
// and game/GameEngine/Source/GameLogic/System/CrateSystem.cpp proves it falls
// in (160,192]. The extent is fixed by the TransportContain module-data
// constructor at RVA 0x0021FC80 (matched row ??0TransportContainModuleData@@QAE@XZ),
// which loads six dwords, 0x012ED8B8 through 0x012ED8CC inclusive, and passes
// them by value to the filter setter at 0x0039FF30 -- 24 bytes, so
// BitFlags<192>, not a guess.
// The type here is spelled `const BitFlags<192>` because that is what the
// referencing objects ask for. Of the 69 game/ TUs that name KINDOFMASK_NONE,
// 50 carry an extern declaration; the spellings that mangle to
// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B, the one
// targets/game/reverse/dir32_addresses.csv records at 0x012ED8B8, are:
//     extern const KindOfMaskType KINDOFMASK_NONE;  24 TUs whose TU-local
//         typedef BitFlags<192> KindOfMaskType; resolves to BitFlags<192>
//     extern const BitFlags<192> KINDOFMASK_NONE;     9 TUs
//     extern const KindOfMask KINDOFMASK_NONE;        4 TUs whose TU-local
//         typedef BitFlags<192> KindOfMask; likewise resolves to BitFlags<192>
// ($0MA is MSVC's encoding of the non-type argument 192: hex digits shifted
// into A..P, so $0HE is 116, $0HO is 126 and $0N is 13.)
// The TU-local BitFlags below is the upstream Common/BitFlags.h layout
// (std::bitset<NUMBITS> rounds to whole 32-bit words). It is declared locally
// because ObjectStatusBits.h's BitFlags has a user-provided constructor, which
// would give this global a dynamic initializer retail does not have.
// Still to be respelled, deliberately out of scope for this data-only TU:
//   - 5 TUs that declare `extern const KindOfMaskType` but typedef it
//     BitFlags<116>, which mangles to ?$BitFlags@$0HE@@ and will not link:
//     OpenContainGetPassengerBoneName.cpp, ThingTemplateInitForLTA.cpp,
//     ScoreKeeperCounters.cpp (and 2 more spelling BitFlags<116> directly).
//   - 7 TUs declaring a TU-local non-template class (KindOfMask126,
//     KindOfBlock, VptrZeroBlock24, ...), which mangles to a different name.
//   - 4 TUs that take the symbol from the shared shim
//     inputs/reference/shims/bfmekindof/Common/KindOf.h, which declares it
//     non-const BitFlags<126>; a shim header edit is out of scope here.

template<int NUMBITS>
class BitFlags
{
public:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;

// upstream Common/KindOf.h declares it before the definition; MSVC 7.1 only
// mangles the global when it sees that declaration first.
extern const KindOfMaskType KINDOFMASK_NONE;

// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B -- retail VA 0x012ED8B8, 24 zero bytes
const KindOfMaskType KINDOFMASK_NONE;