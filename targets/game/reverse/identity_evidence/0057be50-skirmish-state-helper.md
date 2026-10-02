# RVA 0x0057BE50 is an address-derived Skirmish state-machine helper

Existing clean matched BfmeAptScreenSkirmish::rva0057BE50() is 1000 bytes.
The old backlog claim that its owner and callable ABI are unproven is stale.
Authentic method spelling remains unknown; no real-name rename is justified.
All native facts below use retail-1.03-unpacked lotrbfme.exe, base
0x00400000, with pefile and capstone.

The matched Skirmish constructor at 0x0057DA50 installs primary table
VA 0x0110B030 at 0x0057DAA6, secondary tables at receiver+0x218/+0x258,
and constructs preferences at +0x3AC and honors at +0x3C4. Its matched
initGadgets registers the AptSkirmish::InitGadgets BFME selector. Primary
slot 5 (VA 0x0110B044) stores ILT 0x00023533 -> 0x0057EDB0.

That 514-byte body saves ECX into ESI at 0x0057EDB2 and dispatches on the
receiver state at +0x400. On its preference-checked branch it restores
ECX=ESI at 0x0057EEB9 and calls ILT 0x00025F2C at 0x0057EEBB. The ILT
reaches target 0x0057BE50, and caller immediately tests AL at 0x0057EEC0.
The target saves incoming ECX into EDI at 0x0057BE6B, sets up the current
skirmish game, reads preferences/honors fields on that same receiver and
returns AL=1 at 0x0057C22A. Final plain RET at 0x0057C237 is followed by
INT3 at 0x0057C238: 1000 bytes, no stack arguments, bool result.

This is a same-receiver helper called by the class's native state-machine
slot, not itself primary slot 5: slot 5 is the 0x0057EDB0 caller. The existing
method-only reconstruction's virtual declaration does not establish a
retail slot or authentic C++ spelling. Do not use it to rename this helper
to an inferred virtual event name. Existing production source is preserved,
with no additional match credit, table correction or guessed name.
