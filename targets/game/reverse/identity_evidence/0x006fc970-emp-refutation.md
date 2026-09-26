# Anonymous W3D constructor at 0x006FC970

`W3DDisplay::init` at `0x006ED5B0` allocates `0x2868` bytes and calls ILT
`0x00007FC2`, which jumps to the 239-byte constructor at `0x006FC970`.
The constructor calls the body at `0x0060A000`, clears six words at
`this+0x70..0x84`, and installs vtable `0x011207C0`. That vtable also appears
in the matched 294-byte destructor at `0x006FD550`, which releases five
reference-counted pointers at `this+0x70..0x80`. Its slot 7 at `0x006FE3C0`
computes a camera ray through W3D display and camera calls. This is a W3D
rendering owner; no named caller, header, or vtable witness identifies its
semantic class.

The old bank called it `EMPUpdateModuleData` with `UpdateModuleData` as its
base. Those were guesses from a Zero Hour shape resemblance. The W3DDisplay
allocation, W3D vtable family, and destructor conflict with that GameLogic
module-data identity. The `0x0060A000` base constructor itself has no proven
class name, so the replacement keeps that address too. Member names borrowed
from the EMP guess (`startScale`, `targetScale`, `startColor`, `effectRadius`,
`disabledDuration`, `angle`, `victimGrid`) have no independent witness at the
respective offsets. The new bank uses offset names for them. The witnessed
zero-initialized fields keep their descriptive `m_zero*` names.

The revised native C++ source probes at 239/239 bytes with one aligned
relocation and 17 non-relocation differences, versus 71 differences in the old
bank. It remains attempt evidence, not a matched production claim.
