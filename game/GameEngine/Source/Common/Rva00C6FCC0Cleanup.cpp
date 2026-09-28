// cl: /O2 /Ob0
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Nine independently int3-bounded startup callbacks, retaining opaque names.
// 00C6FCC0 writes the witnessed address 0107C7DC to global 012A7A48.
extern unsigned int RvaData0107C7DC[];
extern unsigned int *RvaGlobal012A7A48;
void rva00C6FCC0() { RvaGlobal012A7A48 = RvaData0107C7DC; }

// Existing address-derived callee names; ABI independently checked from
// the retail bodies: ECX receiver, no stack arguments, plain ret.
// 14475->681C0 (Dict release);26F35->B31F0 (AudioEventRTS destructor).
struct Gen00014475 { void handle(); };
struct Gen00026F35 { void handle(); };
extern Gen00014475 RvaObject012ED5E0;
extern Gen00026F35 RvaObject012EF0E8;
void rva00C6FCD0() { RvaObject012ED5E0.handle(); }
void rva00C6FD10() { RvaObject012EF0E8.handle(); }

// 0D828->5EE90->887940 is the AsciiString/StringBase release path.
// Calling the inline destructor explicitly under MSVC 7.1 /Ob0 inserts a
// scalar-deleting wrapper. Use the existing address-derived direct route;
// its ECX receiver and zero stack arguments are witnessed at 00887940.
struct Gen0000D828 { void handle(); };
extern AsciiString RvaObject012ED60C;
extern AsciiString RvaObject012ED828;
extern AsciiString RvaObject012ED82C;
extern AsciiString RvaObject012EF180;
extern AsciiString RvaObject012EF1E4;
extern AsciiString RvaObject012EF1F0;
void rva00C6FCE0() { reinterpret_cast<Gen0000D828 *>(&RvaObject012ED60C)->handle(); }
void rva00C6FCF0() { reinterpret_cast<Gen0000D828 *>(&RvaObject012ED828)->handle(); }
void rva00C6FD00() { reinterpret_cast<Gen0000D828 *>(&RvaObject012ED82C)->handle(); }
void rva00C6FD20() { reinterpret_cast<Gen0000D828 *>(&RvaObject012EF180)->handle(); }
void rva00C6FD30() { reinterpret_cast<Gen0000D828 *>(&RvaObject012EF1E4)->handle(); }
void rva00C6FD40() { reinterpret_cast<Gen0000D828 *>(&RvaObject012EF1F0)->handle(); }
