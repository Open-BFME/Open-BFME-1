# Complete InstantDeathBehavior onDie bank (0x00200DF0)

The existing identity witness is constructor 0x00200BA0 installing the
DieModuleInterface table 0x010A4DF0 at module+0x10; slot zero points through
ILT 0x0004AD63 to this body. Its source twin is GeneralsMD InstantDeathBehavior.
The opaque draft entry models that secondary receiver and does not rename it.
Retail RET4 starts at 0x00200FFA, ending at 0x00200FFD: exactly 525 bytes.
Ghidra creation/decompilation and independent Capstone PE decoding agree.

## Complete behavior and measurement

The draft starts with the existing SlowDeathBehavior_doPhaseStuff_Thunk.cpp
ABI declarations, then reconstructs all four vectors, death applicability,
AI dead-state guard/mark, and final GameLogic::destroyObject. The data vectors
are at +0x34/+0x40/+0x4C/+0x58. The fourth copies a pointer, increments +4 via
InterlockedIncrement, constructs a 0x70 AudioEventRTS via 0x000B4440 using
ObjectID at Object+0x74, calls audio-client slot +0x44, destroys the event via
0x000B31F0 and releases the retained pointer. The global is the independently
recorded TheAudioClientUpdate at VA0x012ED668, not TheAudio.

All four RNG calls use the complete retail source-path literal and line
numbers 135,145,155,169. PE bytes were read through the literal terminator.
The first draft was 525 bytes with two operand differences at +0x181/+0x185.
Copying Object* and ObjectID into locals before constructing the event fixes
those differences, as in the matched SlowDeath donor. No assembly, volatility
or barrier was introduced.

Probe: EXACT 525/525, 27 relocations. A scratch selected-row invocation of the
standard build.verify_functions, verify_string_refs, verify_constant_refs,
and verify_dir32_addresses passes: Functions OK1/1, four literals, six known
DIR32 references. No production ledger row was changed. This verifies the
experimental ABI view, not suitability of its local declarations for landing.

## Promotion blocker: canonical header adoption

The draft retains legacy donor local Object/FXList/ObjectCreationList/
WeaponStore/AudioEventRTS/AudioEventInfo declarations only as experiment
material. Do NOT copy these into game/ as a new conversion. Current rules
require canonical header adoption. The vendor InstantDeathBehavior header
has three vectors. The existing turretai AudioEventRTS shim has the 0x70
storage but no AudioEventInfoRef constructor; the vendor AudioEventInfo is
not BFME's counted type. The canonical callback also needs its secondary
receiver and BFME AI/Object offsets preserved. A coordinated BFME header
repair must cover those contracts, preserving all dependent verified bodies.

The lead confirms no such repair is underway and requests a header-queue
proposal, followed by continuing the packet. This is an exact BANK, not a
converted production claim or a patch ready for the full header gate.
