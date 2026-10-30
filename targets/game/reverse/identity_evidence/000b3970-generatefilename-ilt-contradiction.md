# 0x000B3970 lazy filename generator: `?generateFilename@AudioEventRTS@@QAEXXZ` is ILT-contradicted

The 400-byte body at 0x000B3970 is the Zero Hour AudioEventRTS::generateFilename
twin (BFME adds a needs-generate flag at +0x46 and a weighted retry loop; the
delay roll moved to bfmeGenerateFilename 0x000B4840). It is reached through
ILT 0x0000ADFD (`jmp 0x000B3970`) from getFilename 0x000B3B70 (ECX untouched)
and bfmeGenerateFilename 0x000B4840 (`mov ecx,esi; jmp`).

`python3 tools/ilt_oracle.py check '?generateFilename@AudioEventRTS@@QAEXXZ' 0x000B3970`
is CONTRADICTED (slot 8088, window 7180-7193), as are the public/private/protected
non-const spellings. A brute force over Zero Hour AudioEventRTS method names,
three owner classes, six access letters, const/non-const and four return types
(about 10,000 names) fitted 5, including `?generateFilename@AudioEventRTS@@ABEXXZ`
and `...@@IBEXXZ` (a const member, consistent with BFME's lazy getFilename).
That rate is what chance predicts, and the two cannot be separated, so the
body keeps an address-derived name, `generateFilenameRva000B3970`, and the
contradicted symbols.csv pin is retired. In the interim commit the callers call
the ILT through the self-addressed `?j_0000adfd@@YIXPAVAudioEventRTS@@@Z`
(fastcall, this in ECX), which reproduces both call sites byte for byte.
Model: claude-opus-5-5, session 491, 2026-10-30.
