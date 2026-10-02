# RVA 0x008A5BF0 implements the sendAndLoad callback; native C++ name unknown

The sole stored pointer to body VA **0x00CA5BF0** occurs as the PUSH
immediate at **0x00CA7541** in matched property lookup RVA **0x008A73E0**.
Its case **3** constructs the callback wrapper at 0x00899FC0 using this
address, stores it in global 0x01337AAC and returns it. There is no ILT or
direct caller for the callback itself.

Native perfect-hash lookup RVA **0x008A44A0** accepts hash values **0..16**:
VA 0x00CA44BE compares EAX with 0x10 and rejects strictly greater values.
It indexes the eight-byte table at **0x012D5490**. Thus final entry
**0x012D5510** is part of this table, not the following word set. That entry
contains pointer **0x0113662C** to literal **sendAndLoad** and integer **3**.
The retail PE proves this callback's script-facing role. The existing
property-source comment incorrectly said ID 3 had no entry; this commit
corrects that comment without changing instructions or callback labels.

The callback's existing clean C++ match remains address-qualified as
aptReplacePairs008A5BF0. Its native decorated C++ spelling/class is not
proved by the script property. Full extent is 1189 bytes, plain RET at
+0x4A4 and INT3 at +0x4A5. No native rename, pin or progress change is made.
