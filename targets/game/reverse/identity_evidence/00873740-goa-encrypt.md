# 0x00873740 is GOAEncrypt (GameSpy sb_crypt.c)

The gen-alias row `?dup_00873740@@YAXXZ` (50 bytes) named `_GOADecrypt` as its
object symbol. Since f4b01f3dc5's gen-alias rule it failed: its one call, at
+0x1E, reaches 0x00873650 (`_GOAEncryptByte`, vendored=gamespy-2004), while
`_GOADecrypt`'s reaches 0x00873780 (`_GOADecryptByte`).

- Shape: 50 bytes, the same loop as `_GOADecrypt` at 0x00873870 (50 bytes):
  `for (i = 0; i < len; i++) bp[i] = XByte(state, bp[i]);`, a __cdecl leaf
  whose only call is the byte routine.
- Callee: `_GOAEncryptByte` at 0x00873650 is the only encrypt-byte routine in
  the file, and GOAEncrypt is its only caller in sb_crypt.c.
- Address order matches the vendored file's definition order exactly:
  keyrand 0x008734D0, GOAHashInit 0x00873550, GOACryptInit 0x00873590,
  GOAEncryptByte 0x00873650, **GOAEncrypt 0x00873740**, GOADecryptByte
  0x00873780, GOADecrypt 0x00873870, GOAHashFinal 0x008738B0.
  GOAEncrypt (sb_crypt.c line 167) was the one definition with no row.

So the row takes the vendored function's own name, `_GOAEncrypt`, compiled
from the pristine game/GameEngine/Source/GameNetwork/GameSpy/serverbrowsing/sb_crypt.c.
