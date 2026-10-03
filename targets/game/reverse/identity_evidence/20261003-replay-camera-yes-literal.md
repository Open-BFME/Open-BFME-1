# Replay camera affirmative literal

`?saveCameraInReplays@OptionPreferences@@QAE_NXZ`, RVA `0x00090800`, 95 bytes,
retains its existing identity and extent. The GeneralsMD `OptionsMenu.cpp` twin
(lines 385–395) supplies the same key, absent-key true return and case-insensitive
comparison with `"yes"`.

Retail independently loads VA `0x0107FA1C` (`SaveCameraInReplays\0`) at
`0x00490805`. At `0x00490846` it pushes VA `0x0107C76C`, whose complete bytes
are `79 65 73 00` (`yes\0`), then calls the imported `_strcmpi` through
`0x0135933C`. Ghidra read_memory and the unpacked 1.03 PE agree. The final RET
is at VA `0x0049085E`, followed by INT3 at `0x0049085F`.

The old source emitted `y\0`: a contradicted literal, not merely an unproven
name. The old prefix-only string check accepted it; the strengthened complete
string check fails with source `y\0` versus the first two retail bytes `ye`.
Replacing the literal with `"yes"` preserves the 95 instruction bytes and
passes the strict scoped build: 1/1 function, both complete literals and both
DIR32 references. No new identity, ABI, pin, extent or byte coverage is claimed.

The inherited ledger note saying “compares against y” is also false. Its
metadata correction is deferred with the existing ledger-wide alias integration
blocker; this note records the independently proved replacement.
