# Skirmish screen constructor, RVA 0057DA50

The matched factory in AptScreenFactories.cpp, the AptSkirmish selector names,
three installed vtable views and the complete RET4 at +BC2 establish this
3,013-byte constructor. The old bank was a 652-byte callback outline. The new
body uses native bases, members, owning callback holders and string objects;
there is no instruction emission, fake frame padding or new callee pin.

The retail unwind map supplies eight distinct owned objects. This is the
missing construction model that the earlier isolated placement-call attempts
could not recover:

| State | Receiver offset | Cleanup body | Source model |
|---:|---:|---:|---|
| 0 | 000 | 00465430 | complete _bfme_AptGameWindow base, including its +218 registry |
| 1 | 258 | 005165E0 | Gen00529110Owner interface base |
| 2 | 25C | 00529110 | SkirmishScreenState |
| 3 | 390 | 005668C0 | address-derived Rva00566EC0Profile member |
| 4 | 3AC | 0009F7A0 | SkirmishPreferences |
| 5 | 3C4 | 0009C1E0 | SkirmishBattleHonors |
| 6 | 424 | 005111E0 | address-derived field with vtable 011051EC |
| 7 | 438 | 0005EEA0 | UnicodeString, not an integer |

The base constructor 00465310 independently writes through +254 and installs
the +218 vtable. Therefore its registry is an inherited subobject of that
complete base, not a separate owned base of this constructor. The first 300
bytes, including all initialization/EH scheduling, match with this hierarchy.
The +25C member's bounded view includes its known 0x12C layout and eight
unmodeled bytes before the next constructor at +390; no field identity is
inferred for the gap.

The singleton branch compares the profile user name with the empty wide
string, initializes honors from a selected user, binds nine images, registers
11 ordinary screen callbacks, one tooltip, five level bars and InitGadgets,
and sets APT:OnlineOrNetwork to the localized APT:Skirmish label.

## Binding contracts and source levers

The three holder constructors at 0057C970 / 0057C9E0 / 0057CA50 consume a
16-byte FunctorBinding by value. Their four-byte handles are owned by the
registration calls, whose native definitions independently confirm the
member/free-call positions. The handle copy constructors retain the pointee
reference count at +4; these copies are elided in this caller. The PMF typedef
is storage only and is never used to invoke a callback. In particular,
ILT 00010924 reaches 00579990, whose actual callback consumes three stack
arguments (RET12), not the storage view's void() signature.

Inlining the registration helpers preserves the method value across each
string construction and reproduces the retail 16-byte binding copies. Using
an external function symbol for ILT 00010924, instead of its numeric address,
preserves the four repeated level-bar method loads: the raw-number version
was 23 bytes short. The other callback addresses are witnessed metadata
constants copied from their registrations, not semantic name guesses.

The wide comparison is nonthrowing: the existing StringBase wide comparison
reads the two buffers/lengths and delegates to the existing read-only string
comparison implementation; it allocates nothing and has no C++ throw path.
Its specialization declaration supplies that contract to this TU, removing
the two spurious temporary unwind-state stores. No shared header changes.

## Existing naming conflict

The separate 506-byte constructor at 00566EC0 constructs a 28-byte object
embedded at this+390, with vtable0110A314 and singleton012F4B3C. The full
screen uses singleton012F4B54 and distinct vtable views. Its legacy full-screen
class label has now been repaired across the constructor, 300-byte destructor,
30-byte deleting destructor and singleton pin to Rva00566EC0Profile. The native
virtual destructor naturally emits the deleting wrapper; the old force-delete
probe is removed. The main constructor continues to use its verified
address-derived member view and existing constructor ILT. See
[the lifecycle identity proof](../identity_evidence/00566ec0-profile-family.md).
The actual full-screen identity remains independently proved by its matched
factory caller.

## Verification

The final native body has the complete 3,013-byte extent and 203 relocation
sites. All 135 REL32 call sites resolve to the correct aligned retail targets,
with zero unresolved symbols and zero differing bytes. Independent review
checked the owning-handle ABI and nested-object identity. The normal scoped
add_match/build and commit/push gates supply the final string/global and
repository-integrity checks.
