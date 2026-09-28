// cl: /O2
// Address-derived niladic thiscall routes. Each target was independently
// decoded through its complete RET and reads no incoming stack argument.
// Keep identical vptr-store bodies distinct: retail has no ICF.
// ILT 000301D9 -> body 00080340; evidence build/astra_seat/callee-000301D9.asm.
class Gen_uwm_000301d9 { public: ~Gen_uwm_000301d9(); };
extern Gen_uwm_000301d9 Rva00EF4C18Object;
void Rva00C703B0Shutdown() { Rva00EF4C18Object.~Gen_uwm_000301d9(); }
// ILT 00007CBB -> body 005CE090; evidence build/astra_seat/callee-00007CBB.asm.
class Rva005CE090 { public: void invoke(); };
extern Rva005CE090 Rva00EF6510Object;
void Rva00C70410Shutdown() { Rva00EF6510Object.invoke(); }
// ILT 0002083D -> body 005CE4D0; evidence build/astra_seat/callee-0002083D.asm.
class Rva005CE4D0 { public: void invoke(); };
extern Rva005CE4D0 Rva00EF6750Object;
void Rva00C70420Shutdown() { Rva00EF6750Object.invoke(); }
// ILT 00011BE9 -> body 005D8DF0; evidence build/astra_seat/callee-00011BE9.asm.
class Rva005D8DF0 { public: void invoke(); };
extern Rva005D8DF0 Rva00EF6D8CObject;
void Rva00C70820Shutdown() { Rva00EF6D8CObject.invoke(); }
// ILT 00013DEA -> body 005D58A0; evidence build/astra_seat/callee-00013DEA.asm.
class Rva005D58A0 { public: void invoke(); };
extern Rva005D58A0 Rva00EF6DA8Object;
void Rva00C70830Shutdown() { Rva00EF6DA8Object.invoke(); }
// ILT 000305C6 -> body 005F3910; evidence build/astra_seat/callee-000305C6.asm.
class Rva005F3910 { public: void invoke(); };
extern Rva005F3910 Rva00EF6DDBObject;
void Rva00C70840Shutdown() { Rva00EF6DDBObject.invoke(); }
// ILT 00014146 -> body 005D92A0; evidence build/astra_seat/callee-00014146.asm.
class Rva005D92A0 { public: void invoke(); };
extern Rva005D92A0 Rva00EF6DE4Object;
void Rva00C70850Shutdown() { Rva00EF6DE4Object.invoke(); }
// ILT 000382B2 -> body 005D8B40; evidence build/astra_seat/callee-000382B2.asm.
class Rva005D8B40 { public: void invoke(); };
extern Rva005D8B40 Rva00EF6E00Object;
void Rva00C70860Shutdown() { Rva00EF6E00Object.invoke(); }
// ILT 0003536E -> body 005D8EE0; evidence build/astra_seat/callee-0003536E.asm.
class Rva005D8EE0 { public: void invoke(); };
extern Rva005D8EE0 Rva00EF6E18Object;
void Rva00C70870Shutdown() { Rva00EF6E18Object.invoke(); }
// ILT 00015A5F -> body 005D8890; evidence build/astra_seat/callee-00015A5F.asm.
class Rva005D8890 { public: void invoke(); };
extern Rva005D8890 Rva00EF6E34Object;
void Rva00C70880Shutdown() { Rva00EF6E34Object.invoke(); }
