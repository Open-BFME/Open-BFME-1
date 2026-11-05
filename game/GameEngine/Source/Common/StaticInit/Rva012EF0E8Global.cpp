// cl: /O2 /MD
// ?RvaObject012EF0E8@@3UGen00026F35@@A at retail VA 0x012EF0E8: opaque object
// cookie used only by address from Rva00C6FCC0Cleanup.cpp (rva00C6FD10 calls
// RvaObject012EF0E8.handle()). Retail .data holds 0 at the VA, and the empty
// struct has a trivial constructor, so this emits zero-filled storage with
// no dynamic initializer. Home is this data-only TU (not the consumer: that
// TU carries an unrelated pre-existing unowned reference at 0x012ED5E0 with
// no baseline exemption, so it cannot go green in the same scoped build).
struct Gen00026F35 { void handle(); };
Gen00026F35 RvaObject012EF0E8;
