# BFME1 0x00176A50: private review 2026-11-20

No improved bank and no production edit. Existing 1041-byte source remains best,
with two nonrelocation ModRM differences at +0xAF/+0xB3: the load/store beginning
at +0xAE/+0xB2 use EDX, where retail uses EAX. This is an observed allocation
residual, not evidence that clean C++ recovery is impossible.

Context: BFME1 d01f9d4ec5926b72b65d4a7fef8750e8e3b821ba; reviewed BFME2 donor
147fd3e52b36ee0306aaeef5b316beb09f7c7671. Bank SHA256
cbfcbd4179cd9e1acabae199b66321fbb82565873d1156473b552259b1379487.
Compiler MSVC 13.10.3077; native command construction, unchanged /O2 /GR- /EHsc-
/DNDEBUG /MD /EHsc /Ob1 and WWMath include. Private absolute input/output argument
substitution only, without shared cache or receipt edits. Commands saved per
candidate in *.command.json, input/tool/header hashes in input-hashes.json.

Forty-four compiler invocations, forty-two compiled, no exact candidate. Results:

- Assignment facts: equality/XOR/subtraction-zero __assume after the timestamp
  store, pointer-null facts before its already-required dereference, unsigned
  compound delta/XOR identity: all baseline 1041B/two differences.
- Closed the old handoff's untested implicit-assignment hypothesis using private
  copies of the canonical coord3d.h. Removing both Coord3DBase and Coord3D copy
  assignment declarations and replacing the source definitions by implicit
  assignment retains 1041B/two differences; changing to getFrame then still
  gives 1040B/364 differences. Only removing the derived assignment while the
  base remains explicit worsens to 995-1023 bytes. No shared header was changed.
- memcpy (including explicit intrinsic), one-word struct copy, source pointer
  and reference, redundant already-proven throttle condition and guarded
  nonzero fact: baseline. Destination pointer/reference exposes a new address
  and worsens to 1055B/707 differences.
- Comma/drop-result, modular invert/increment identities, uint64 zero-extension
  roundtrip, assignment-to-equality condition: baseline. getFrame only in the
  throttle condition is baseline; getFrame for both uses remains 1040B/364.
- Register-qualified timestamp local remains 1040B/364; register-qualified
  source pointer stays baseline. __restrict is unsupported by this VC7.1 build
  (C4235), so those two trials are compiler-setup rejections, not byte results.

Scope of evidence: private masked-byte comparisons only, not relocation
admission, native normal source gate, link coverage or runtime proof. No new
accepted body, task credit, pin, identity or claim generation. No gate, header,
ledger, journal, source-bank or production-file edits by this agent.

The six visible Coord3D methods remain necessary context per the earlier
64-way visibility matrix; no reason to repeat that matrix was found. The BFME2
same-method bank still has a distinct late-save allocation blocker and is not a
new exact donor. The existing same-position helper at 0x0016AA70 is already
rowed as C++, so its identical private copy is not additional coverage.
