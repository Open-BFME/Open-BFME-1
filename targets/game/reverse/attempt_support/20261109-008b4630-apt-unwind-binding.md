# Apt constructor unwind binding at 0x008B4630

The retail exception action at 0x00C58CC0 loads the base subobject from
`[ebp-0x10]` and jumps to the complete destructor at 0x00899380.
The current action instead names `??1Rva00899F00Base@@UAE@XZ`. The
153-byte main body calls `??0Rva00899F00Base@@QAE@IH@Z` at 0x00899F00,
so a class rename also disturbs a verified constructor binding.

Four VC7.1 probes kept the main bytes, their relocations and the handler
bytes. An inline forwarding destructor, both virtual and non-virtual,
still gave the unwind action a relocation to the forwarding destructor.
Modelling the target cleanup as the base's base or as its offset-zero
member also made the compiler emit the intermediate complete destructor.
A byte match in the constructor therefore leaves the same wrong action
target. The virtual variants can also introduce extra vtable definitions.

The pinned BFME2 constructor family uses the same stand-in name but does
not establish this BFME1 unwind binding. The useful next probe must
preserve the verified constructor call and give state zero a direct
relocation to `??1Gen_uwm_00899380@@QAE@XZ`.
