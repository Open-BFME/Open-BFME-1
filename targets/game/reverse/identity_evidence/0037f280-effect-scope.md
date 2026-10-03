# RVA0037F280 effect scope and native-header bank

Raw RET12 at0037F448 ends the459-byte body; INT3 starts0037F44B. Ghidra
FUN_0077f280 agrees with that complete extent and the following control flow.

The old bank incorrectly called the two-argument helper withC7h/Fh outside
the effect guard. Retail tests the incoming flag at0037F302, loads the frame
throughVA012F0898/+3C at0037F304..0037F30A, then branches at0037F30D and
0037F312 to0037F32B. That target is after BOTH calls: the two-word thiscall
through ILT00038843 at0037F318 and theC7h/Fh call through0002852E at0037F326.
Thus both calls occur only when the flag is true and the frame is at least10.
The frame load itself is unconditional. The old bitwise boolean expression
and unconditional second call were not merely register-allocation residues.

Native object.h and ascii_string.h alone preserve the original459B/47dif.
Moving the second call inside the guard, using a short-circuit expression,
and naming the upgrade pointer give457B/252dif. An explicit unsigned frame
local restores the unconditional load and reaches459B/9dif. Using the actual
Object::getExperienceTracker inline from the Zero Hour Object.h:238 for the
tracker accesses reduces that to8dif, quality0.9826.

The8 remaining byte differences are the argument/receiver preparation for
the StringBase<char>::set call at0037F338 and the first tracker store through
0037F348. Reference locals, a tracker local, native operator=, address-derived
setter/accessor wrappers and forced-inline helper factoring do not improve
the final bank. The volatile-frame control equals the ordinary frame local;
the selected bank uses the ordinary local.

This is not a production claim. The native Object/string headers are adopted,
but inherited ExperienceTracker/ExperienceLevelData member labels and the
effect member-pointer union still need an independent identity/ABI audit.
In particular name_oracle does not witness ExperienceTracker+8 as m_name.
The21 masked relocations and literal key address also need their normal full
binding verification. No new callee alias, datum pin or production source
was added. Scratch controls are build/n1/session4/experience*.
