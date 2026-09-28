// cl: /O2 /Ob1 /DNDEBUG /MD
// Retail0056E600: SUB ECX 218h; tail JMP ILT0001C391 ->0056E830.
// ILT000322B3 proves start. Old0056E606 row was the interior JMP.
// Opaque ABI carrier: target0056E830 consumes one unsigned flags argument,
// calls destructor0056E7D0, optionally deletes, and returns the original this.
// C++ multiple inheritance emits the witnessed secondary-base adjustment.
class Rva0056E600Lead { public: virtual void *invoke(unsigned); char pad[0x214]; };
class Rva0056E600Secondary { public: virtual void *invoke(unsigned); };
class Rva0056E600 : public Rva0056E600Lead, public Rva0056E600Secondary {
public: Rva0056E600(); virtual void *invoke(unsigned);
};
// Emission anchor for the adjustor thunk; not a claimed retail constructor.
// ??0Rva0056E600@@QAE@XZ absent-from-retail
Rva0056E600::Rva0056E600() {}
