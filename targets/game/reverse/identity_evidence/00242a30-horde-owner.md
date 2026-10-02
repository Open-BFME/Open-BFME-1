# RVA 0x00242A30: HordeContain owner, method spelling unresolved

Retail facts were read from the BFME1 retail-1.03-unpacked lotrbfme.exe
with pefile/Capstone (image base 0x00400000).

Matched HordeContain constructor RVA 0x0023EAF0 installs secondary vtable
VA 0x010AED58 at receiver +0xE4 (instruction VA 0x0063EB71).
Matched HorseHordeContain constructor RVA 0x0024D220 installs its analogous
table VA 0x010B07E0 at the same subobject position.
Their slot 7, at 0x010AED74 and 0x010B07FC respectively, stores ILT
VA 0x00403D2D -> body RVA 0x002458B0.

That 221-byte interface body looks up the member's ID in the map at its
receiver +0x3C, selects a formation entry or cached member position if
its byte at +0x118 is set, and otherwise calls ILT RVA 0x0002C53E.
At VA 0x00645977 it computes `ECX = receiver - 0xE4`, then at
0x0064597D calls the ILT into **RVA 0x00242A30**. This independently
identifies the target's receiver as the full HordeContain object, including
when reached through HorseHordeContain's inherited interface slot.

The target's map at full-object +0x120 equals interface +0x3C, its
formation vector at +0x1D8 equals interface +0xF4, and its flag at +0x1FC
equals interface +0x118. These three independent offset correspondences
agree with the constructor/subobject route. The target reads its owning
Object at full-object +8 and uses the caller's member ObjectID for lookup.

This proves the owner more strongly than a filename or neighbouring body.
It does **not** prove the BFME-only member spelling; GeneralsMD has no
HordeContain declaration. No real method name is invented here.

The current source's interface wrapper declares its final argument as
float and forwards that stack word, while the target interprets its final
argument as `Real*` and writes through it. The bytes agree at the call
boundary because both are one word. A native signature correction therefore
needs the interface's own callers, not just a byte match. No owner rename
or API rewrite is landed in this session. The existing exact 273-byte C++
body remains in its address-qualified class, and no byte progress is claimed.
