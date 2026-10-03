# Exact constructor bank at RVA 0x00592640

The 339-byte constructor ends RET at 0x00592792 followed by INT3.
See 00592640-palantir-base-member.md for the independent containment proof:
Rva00597FC0Client constructs this opaque member at +0x488, and its destructor
calls the matched Rva00592640Owner destructor. No semantic owner is proposed.

The bank probes 339/339 bytes EXACT modulo 22 relocation slots with MSVC 7.1.
This is a shaping result, NOT a strict linked landing. Its new callback method
and virtual table have not been bound, and no ledger conversion is made.

Canonical DisplayStringManager slot 9 returns five DisplayString pointers.
ImageCollection::findImageByName receives Resource_Icon; Image width/height
getters reproduce the native +0x24/+0x28 reads. HelpBoxText uses the existing
WindowManager::registerAptCallback signature and singleton at VA 0x012F19E8.
Two embedded one-word Rva00590790 holders explain EH states 0 and 1; two
scoped AsciiString temporaries explain states 2 and 3. The native handler is
RVA 0x00C37856, FuncInfo RVA 0x00E26D24, state predecessors -1,0,1,1.

Shape lever: pass the two-word {receiver, single-inheritance member pointer}
binding BY VALUE into the holder constructor, which allocates a 16-byte
callback and copies the binding from const reference. Passing receiver and
method as separate constructor arguments produces 335 bytes and loses EBP;
this nested binding reproduces the complete native register/stack sequence.

Remaining integration work is concrete. Table VA 0x0110BD00 has slot 0
VA 0x00430C33 -> RVA 0x0058D580 (30-byte scalar deleting destructor), and
slot 1 VA 0x0041F613 -> RVA 0x0058D210 (8-byte member invoker). The existing
Rva0058D1E0FunctorSingleWrapper constructor owns that table identity but
currently derives from a one-virtual-anchor placeholder. Reconcile that
family with its two native slots before using it in production. Do not pin
a second guessed table identity merely to make the constructor link.
The bound target VA 0x0043524C routes to RVA 0x0058E390. Its RET 0x10 and
loads from [ebp+8]/[ebp+0xc] prove four argument slots, first two pointers;
the last two slots are unused in this body. The bank uses opaque void*
arguments as an ABI view, not an assertion of the original signature.
The existing owner destructor TU also has an abbreviated 0x28-byte owner
layout and integer-string view; this bank needs a coordinated owner view
before integration. No production declarations were changed.
