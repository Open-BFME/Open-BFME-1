// cl: /O2 /Ob0
// Separate int3-bounded entries; no semantic class identity is asserted.
// ret 4 witnesses one opaque stack slot; mov eax,ecx returns the receiver.
void rva009ECE80() {}
struct Rva009ECE90 { Rva009ECE90 *value(unsigned int); };
Rva009ECE90 *Rva009ECE90::value(unsigned int) { return this; }
struct Rva009ECEA0 { Rva009ECEA0 *value(unsigned int); };
Rva009ECEA0 *Rva009ECEA0::value(unsigned int) { return this; }
struct Rva009ECEB0 { Rva009ECEB0 *value(unsigned int); };
Rva009ECEB0 *Rva009ECEB0::value(unsigned int) { return this; }
struct Rva009ECEC0 { Rva009ECEC0 *value(unsigned int); };
Rva009ECEC0 *Rva009ECEC0::value(unsigned int) { return this; }
struct Rva009ECED0 { Rva009ECED0 *value(unsigned int); };
Rva009ECED0 *Rva009ECED0::value(unsigned int) { return this; }
void rva009ECEE0() {}
struct Rva009ECEF0 { Rva009ECEF0 *value(unsigned int); };
Rva009ECEF0 *Rva009ECEF0::value(unsigned int) { return this; }
