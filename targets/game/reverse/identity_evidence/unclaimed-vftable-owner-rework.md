# Unclaimed-lane vftable tail-jump destructors moved to their owners

Ten 11-byte bodies (0x007E9080, 0x007F03B0, 0x007F1C80, 0x007F2200,
0x007F2E90, 0x007F3590, 0x007F4120, 0x007F48A0, 0x007FADD0, 0x007FBC20) and
0x009EE5F0 are `mov dword ptr [ecx],<vftable> / jmp <rel32>`. A local
commit first spelled them as address-derived classes deriving from
`BfmeDirtyBase` (the matched `??1BfmeDirtyBase@@UAE@XZ` at 0x007EB6C0, the
jump target of nine of them) in UnclaimedVptrTailJumpDtors.cpp.

Review showed each vftable already has an owner: its slot 0 is a matched
`??_GRva<..>CleanupDeleting@@UAEPAXI@Z`, and VptrCleanupDeletingDestructors.cpp
already defines each owner's destructor out of line as
`((CLEANUP *)this)->run();` with CLEANUP pinned at the same jump target
(Rva007EB6C0Cleanup at 0x007EB6C0, Rva007FA650Cleanup at 0x007FA650,
Rva009EDD30Cleanup at 0x009EDD30). The rows now name those owner
destructors in that file, unchanged, and byte-verify EXACT.

`BfmeDirtyBase` therefore does not disappear from the repo (it stays in
Y2ScalarDeleters.cpp, whose `??0BfmeDirtyBase@@QAE@XZ` now lands at
0x007E9050); only the deleted lane file's spelling of the jump target
differs from the owner file's `Rva...Cleanup` spelling of the same address.
