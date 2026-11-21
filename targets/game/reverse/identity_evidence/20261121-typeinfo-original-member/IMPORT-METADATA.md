# Keep the import thunk; reconcile its PE-derived target metadata

Original RVA009F7ED4 is the complete six-byte FF25[0135921C] thunk. The real
PE import directory and original x86 CODE import member independently identify
MSVCR71.dll!??1type_info@@UAE@XZ. The old generated row carries only the display
target ~type_info. The narrow unchanged route checker correctly refuses that
inconsistent metadata as authority for the real callable name.

Use the existing normal add_match --replace-existing path with the SAME
generated name, source, address and six-byte extent. Correct only its import
target note to the independently witnessed PE name. The generated source is
not edited, the import is not reclassified as C++, and no function is renamed
or aliased. Normal whole-source verification remains mandatory. This is zero
new bodies, zero C++ recovery and zero physical coverage. No verifier, gate,
baseline or route rule is weakened, and no pin is added by this prerequisite.

The separate planned whole-member recovery uses the original CRT ti_inst.obj,
with native B1 types/data as authority and the pinned authored BFME2 emitter as
a structural lead. Root assigns game/Libraries/Source/CRT/VS2003/ti_inst.cpp,
consistent with the original member and existing VS2003 library family. The
displaced library/type_info.cpp map entry is not claimed as an EA source path;
no tu_map rewrite is made. Its three body admissions remain conditional.
