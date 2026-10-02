# 0x00585CF0: popup selector 1 callback

This proves the indexed callback route and its receiver association. Authentic
owner/method spellings remain unresolved; existing matched source stays unchanged.
Addresses below are retail RVAs, except table addresses explicitly labelled VA.
All instructions were independently decoded from retail-1.03-unpacked with Capstone.

ILT `0x00032894` reaches the 90-byte body. Its stub VA `0x00432894` occurs once,
at VA `0x0110B9E0`: entry 1 of the four-entry callback array VA `0x0110B9DC`.
This array is not a vtable:

| Index | Stub RVA | Body RVA |
|---:|---:|---:|
| 0 | 0x000162E3 | 0x005868D0 |
| 1 | 0x00032894 | 0x00585CF0 |
| 2 | 0x0000514B | 0x00585D60 |
| 3 | 0x0002A97D | 0x00585E90 |

The consumer `0x005880C0` reads a record selector at `+0x30` at `0x00588418`,
loads `[selector*4+0x0110B9DC]` at `0x00588423`, places the one-pointer handle on
the stack, copies its saved complete receiver EDI to ECX at `0x0058842E`, and
calls the selected function at `0x00588434`. It repeats while the selector changes.

This consumer is itself virtual slot 5 of table VA `0x0110BA30` (word VA
`0x0110BA44` -> ILT `0x000202B6` -> `0x005880C0`). Independently matched opaque
constructor `Gen_00587D40::Gen_00587D40`, RVA `0x00587D40`, calls the authentic
SubsystemInterface constructor and installs that final table at `0x00587D65`.
The matched destructor at `0x00587B30` reinstalls it at `0x00587B4D`.
Therefore the callback receives the opaque subsystem's complete object in ECX;
this still does not establish an original C++ class or callback name.

The candidate ends RET 4 at `0x00585D47`, followed by INT3 at `0x00585D4A`.
It invokes matched sibling `0x00585C20` then native STL find over the pointed
record's four-byte range at `+0x24/+0x28` and updates its selector/state fields.
The existing clean address-bearing method and one-pointer handle are retained.
Adjacent `BannerUI` text and the sibling's portrait path identify UI context,
but do not name this separate subsystem or its member.
