# RVA 0x0029B760 is PhysicsBehavior::update

Retail constructor **0x0029A880** installs final primary table
**0x010C0C8C** at VA 0x0069A8CA and final **+0x10** table **0x010C0BBC**
at VA **0x0069A8D7**, replacing the UpdateModule-family base table at that
same offset. Primary slot 4, VA 0x010C0C9C, routes ILT 0x00424F82 to
matched getModuleNameKey **0x0029A990**. That body pushes literal
**0x01090C28** at VA 0x0069A9C0; independently read retail and Ghidra bytes
spell `PhysicsBehavior`. This anchors the owner independently of labels.

The +0x10 table's first entry stores the unique ILT **0x00404B06** ->
body **0x0029B760**. Named native DemoTrapUpdate::update at 0x0028CAD0
occupies that same first slot in its constructor's +0x10 two-entry update
interface table 0x010BD6D0. The sibling facts are recorded in
[0026e1f0-woundarrowupdate-update.md](0026e1f0-woundarrowupdate-update.md).
The target takes no stack arguments and returns UpdateSleepTime values,
including 0x3FFFFFFF. Thus it is the PhysicsBehavior update override,
`?update@PhysicsBehavior@@UAE?AW4UpdateSleepTime@@XZ`, reached with the
secondary-interface receiver at full-object +0x10.

The target reads module data at ECX-0x0C and Object at ECX-8, corresponding
to canonical full-object +4/+8, and performs physics/motion work. No direct
caller reaches this body or ILT. The complete 862-byte extent ends in plain
RET at +0x35D and INT3 at +0x35E; retail allocates a 0x4C-byte local frame.

The earlier PhysicsPathStep guess is unnecessary and unsupported. Identity
is now proven, but the preserved candidate previously emitted 886 bytes,
752 differing bytes and a 0x5C frame. This audit changes no source, pin or
progress row and keeps the frame/register reconstruction blocker.
