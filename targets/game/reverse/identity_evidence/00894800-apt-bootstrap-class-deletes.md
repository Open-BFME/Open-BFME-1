# Apt bootstrap 0x00894800 and its class sized deletes

BFME 1 target evidence (retail 1.03 unpacked):

- 0x00894800 (524 B, ret at +0x20B, INT3 after) is the Apt bootstrap; EA
  file evidence (ea_evidence.csv, wb1) places it in Libraries/Source/Apt/Apt.cpp.
  Its only caller is the matched WindowManager::init 0x0046C5F0, which passes
  a Gen_004659D0 parameter block. No ILT, export or string names it, so the
  name stays address-derived (`Rva00894800`).
- Handler 0x00C56FAE -> FuncInfo 0x00E46420, five unwind states, one per
  new-expression in the body. Each cleanup pushes the allocation size and
  the new temp, then calls a 6-byte `jmp dword ptr [TheBfmeFree]` body:
  state 0/1 (new 0xC Gen_008A3070, ctor 0x008A3070) -> 0x008917F0;
  state 2 (new 0x18 Rva008947A0Owner, ctor 0x008947A0) -> 0x00891700;
  state 3 (new 0x1C item table stored to g_rva013377F0, type
  Gen_uw_00893e70) -> 0x00891750; state 4 (new 0x12B4 BfmeThingUEW, ctor
  0x008A2CF0) -> 0x00891690. Retail has no other caller of these four
  bodies (rel32 scan), and no ICF folding, so each is the class-scope
  `operator delete(void *, size_t)` of the class its funclet frees.
- Compiled from Apt.cpp, the inline class `operator delete(void *p,
  size_t n) { TheBfmeFree(p, n); }` emits byte-identical 6-byte COMDATs;
  the parent body is byte-exact (probe, 45 relocations).
- 0x00891C90 (13 B) is the default sized-free hook the bootstrap stores into
  TheBfmeFree at +0x70 (the only reference to its VA); name address-derived.

Donor lead (not proof): open-bfme-2 20a0cb6173 names the Apt parameter block
`AptInitParmsT` (AptScriptFunctionBase::InitializeStaticData); no donor row
for the bootstrap itself.
