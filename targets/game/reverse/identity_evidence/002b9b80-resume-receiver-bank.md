# DozerAIUpdate::aiDoCommand bank: receiver correction

The preferred 330-byte bank differs at one ModRM byte (+0xF7), but that byte
is a semantic receiver error, not an interchangeable register choice.
Independent retail decoding starts `mov ebx,ecx`, then derives the complete
object with `lea edi,[ebx-0x20]`. The incoming ECX/EBX is the secondary
AICommandInterface subobject. At resume-construction +0xF6, retail passes
EBX to ILT 0x00024D70 -> AICommandInterface::aiIdle at 0x000D87E0. The bank's
reinterpret_cast of the complete `this` passes EDI instead, 0x20 bytes wrong.
The repair arm at +0x12B already passes EBX correctly.

GeneralsMD DozerAIUpdate.cpp:2343 supplies the named aiDoCommand twin, with
ordinary inherited aiIdle calls in both repair/resume arms. AIUpdate.h:234
declares AIUpdateInterface as UpdateModule plus AICommandInterface. The
retail method ends at RET4 +0x147 through +0x149, followed by INT3 at +0x14A
(RVA 0x002B9CCA), confirming 330 bytes.

A qualified AICommandInterface::aiIdle call corrects the receiver and emits
330 bytes, with 40 allocation differences. Six receiver forms, four explicit
command-pointer lifetime variants and five case-order permutations did not
improve that correct-ABI result. Static-cast locals and null guards made it
larger. The corrected candidate is archived by re_log; the higher byte-score
preferred bank must not be landed while its resume receiver is wrong.

No native conversion, header change, callee pin or register-forcing assembly
is introduced by this attempt.
