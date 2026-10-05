# GetSymbol bool overload

The caller at RVA 0x0088CC40 pushes 1 before calling GetSymbol at RVA 0x0088C960. Retail reads that bool at EBP+0x34, where it selects whether to keep the full source path.

Retail returns at RVA 0x0088CC3F, and the next prologue starts at 0x0088CC40. Those addresses bound the body to 736 bytes. The adjacent operator overload returns at 0x0088CDB0 and occupies 369 bytes.

I placed the body in `game/Libraries/Source/debug/debug_stack.cpp`, where its helpers live. A local macro adds the bool parameter to this translation unit's view of the header declaration, so the shared header stays unchanged.
