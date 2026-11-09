# 0x000D95C0 applyInitialUpgrades: the member is a vector<AsciiString>, not an AttributeModifierAura member

Established from BFME 1 retail:

- `tools/eh_info.py 0x000D95C0`: the single unwind state's cleanup (RVA 0x00BF9CB0) is
  `lea ecx,[ebp-0x18]; jmp ILT 0x00026AB2`, and ILT 0x00026AB2 jumps to 0x000658A0.
- The ledger row at 0x000658A0 is `??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ`
  (AsciiStringVectorDestructor.cpp, matched). The copy call goes through ILT 0x00015474 to 0x000D2E70, the matched
  vector<AsciiString> copy constructor row.
- SubsystemLegend.cpp already reaches the same two bodies through the stand-in `BfmeLegendStringVec`
  (symbols.csv pins 0x000D2E70 and 0x000658A0).

So the local is the 12-byte vector<AsciiString>. The name `AttributeModifierAuraUpdateModuleDataMemberB` was an
over-claimed class name whose destructor only a pin at the ILT carried; nothing defined it. The opaque
`BfmeLegendStringVec` is the spelling bound to the real rows.
