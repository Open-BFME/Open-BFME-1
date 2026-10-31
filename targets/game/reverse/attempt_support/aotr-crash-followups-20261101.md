# Age of the Ring / ROTWK crash follow-ups, 1 November 2026

These are pending investigations from two user-provided ROTWK minidumps,
not fixes or new BFME 1/2 regression claims. The original dumps and detailed
machine-local reports remain outside Git. Both captured modules identify
32-bit game.dat 2.1.2614.37001, image base 00400000, image size 00AD4000,
PE timestamp 460DA09E. Addresses below belong to that ROTWK build only.

## Confirmed observations

* AOTR-20261031: c0000005 write to 00000010 at game.dat+000D1E9E.
  The captured instruction is `fstp dword ptr [ecx+10h]`; ECX is zero.
* AOTR-20261029: c0000005 read from 0000002C at game.dat+002B4EAE.
  The captured instruction is `cmp dword ptr [eax+4],esi`; EAX is 28h,
  ESI zero. The following loop advances EAX through `[eax]`.
* The fault bytes come from the dumps and agree with 32-byte windows in
  the current local game.dat. Matching PE metadata/windows do not prove
  whole-binary identity or name either function.
* Flags 00000001 mean MiniDumpWithDataSegs. There is no full-memory or
  memory-region-information stream. No complete heap, free-address-space
  census, process-commit peak or allocation history is established.
* The current disk image is Large Address Aware. Its header is absent from
  the captured memory, and the current file changed after both crashes;
  its flag at crash time is not proven.

## Pending work and acceptance criteria

1. Trace the zero destination at ROTWK+000D1E9E to its actual owner and
   caller, then inspect allocation/initialization/resource-lock failure paths.
   Confirm a source correspondence independently before proposing a guard.
2. Trace the near-zero node at ROTWK+002B4EAE to the producing pointer and
   lifetime. Distinguish an invalid lookup/list head, a null-base member
   address, stale ownership and earlier corruption with a reproducible case.
3. Improve diagnostic capture on the later runnable engine: complete user
   memory plus memory-region information, allocation failures, private/commit
   usage, largest free virtual range, and relevant resource-lock errors.
   A single minidump cannot demonstrate a leak trend or RAM exhaustion.
4. Once the actual owners and counterparts are established, apply a shared
   allocation/ownership fix to both BFME engines and verify reproductions,
   load/save and large-army/faction stress cases. Keep 64-bit address-space
   work and leak/resource-lifetime work as separate measurable changes.

The immediate faults are confirmed. Memory exhaustion, a memory leak, the
same root cause in both dumps and applicability to BFME 1/2 remain unproven.
The ongoing retail-byte-matching work does not silently add guards or change
the original executable. No original game/mod installation was modified.

Format/meaning references: [exception parameters](https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-exception_record),
[dump flags](https://learn.microsoft.com/en-us/windows/win32/api/minidumpapiset/ne-minidumpapiset-minidump_type),
[module records](https://learn.microsoft.com/en-us/windows/win32/api/minidumpapiset/ns-minidumpapiset-minidump_module).
