# RVA 004A747F is an interior block, not RiderChangeContain::onRemoving

Evidence read from the manifest-verified BFME1 retail-1.03-unpacked image,
SHA-256 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75.
All addresses below are RVAs unless explicitly marked VA.

* ILT entry 00044409 is E9 12 2A 46 00, targeting 004A6E20.
* The independently matched caller at 004A8F10 calls that ILT at 004A8F74.
  Its source is game/GameEngine/Source/GameClient/GUI/Gadget/Rva004A8F10Dispatch.cpp.
  The call passes a button/data pointer and two Boolean arguments; the
  destination uses ECX and ends its paths in RET 12.
* 004A6E20 has the SEH prologue (handler VA 010284BA) and reserves 0x60
  bytes before saving EBX, EBP, ESI, EDI. Its final RET 12 is 004A87BC.
* 004A728B loads the command from [ESI+0x10]. 004A729A reads a selector
  from VA 008A8848; 004A72A1 jumps through VA 008A87C0.
* That table has 34 DWORD entries. All are decoded instruction starts in
  [004A6E20,004A87BF). Entry 2 is 004A7451; entry 4 is 004A774A.
* The block at 004A7451 reaches 004A7470 (MOV ECX,ESI), 004A7472
  (CALL 000205CC), 004A7477 (MOV [ESP+0x20],-1), then falls through to
  004A747F (MOV EDI,[ESP+0x20]). 004A747F has no function prologue,
  incoming CALL/JMP/ILT reference, or padding before it. It consumes the
  parent's live frame, EAX result, ESI, EBP and saved registers.
* Branches from inside the claimed 715-byte interval reach outside it:
  004A748E -> 004A87A5, 004A749F -> 004A87A5, 004A74AE -> 004A87A5.
  The claimed end 004A774A is another case block of the same switch.

The parent is one function, not a chain of independent cases. Its exact
partition is 6559 code bytes [004A6E20,004A87BF), one NOP at 004A87BF,
136 jump-table bytes [004A87C0,004A8848), 50 selector bytes
[004A8848,004A887A), then INT3 padding through 004A8F10.

The ControlBar command-dispatch family is supported by the matched caller,
but an exact original method name is not asserted here. Use an opaque
address-derived name until independent identity evidence supplies one.

Do not extend the RiderChangeContain row under its current name. A complete
reconstruction must retire that interior claim and claim the proven parent
extent. This seat did not rewrite the existing naked lift, because copying
more retail bytes would violate the anti-lift rule. No byte-exact parent
reconstruction was produced; this document is evidence, not coverage.
