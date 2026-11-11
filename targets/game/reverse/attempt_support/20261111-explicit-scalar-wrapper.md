# Explicit scalar-delete wrapper binds the verified cleanup

BfmeHolderCU scalar wrapper 0x5DD340+30 is independently anchored by constructor 0x5DD290, vtable 0xD1126C and ILT 0x3E3B. The complete cleanup route 0xCC16 reaches the existing 0x5DD320 Rva005DD320MultiTailDtor provider. Its uncertain class spelling stays unchanged.

Instead of asking VC7.1 to synthesize a deleting destructor that calls an unresolved class-name destructor, express the scalar operations in an address-derived thiscall method: call the qualified existing cleanup, delete this when flags & 1, return this. This has the same ECX receiver, stack flags and RET4 ABI. Normal add_match replacement verifies all 30 bytes and both native call relocations. The ledger retains the established BfmeHolderCU wrapper identity and boundary, recording the explicit object's symbol. No alias, pin, layout or new cleanup identity is invented.

Earlier inline-destructor trials added a vptr store and were refuted; this method does not define a C++ destructor and emits no extra table. Retain the old source from base 9de94413dc to reproduce those compiler-generated wrappers. BFME 2 donor 76f0baefa6f285d54bc1ca922397674312a5913f has no supported corresponding BfmeHolderCU provider; no donor body or target fact imported.

Compiler: MSVC 7.1, normal /O2 /GR- plus /DNDEBUG /MD /EHsc. Current live linking remains subject to dependency closure; no linked gain claimed from a stale census.

Sibling independently verified: `game/GameEngine/Source/GameClient/AttachedModelFXNuggetDeletingDestructor.cpp`, `??_GAttachedModelFXNugget@@MAEPAXI@Z` at 0x429b30+30. Original constructor/vtable/ILT evidence remains in the source header. Qualified cleanup calls `Rva00429B60`; add_match verifies the complete body and both relocations with the same flags. No extra vtable or unresolved class-name destructor emitted.

Sibling independently verified: `game/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateDeletingDestructor.cpp`, `??_GBeaconClientUpdate@@UAEPAXI@Z` at 0x603210+30. Original constructor/vtable/ILT evidence remains in the source header. Qualified cleanup calls `Rva00603120TailDtor`; add_match verifies the complete body and both relocations with the same flags. No extra vtable or unresolved class-name destructor emitted.
