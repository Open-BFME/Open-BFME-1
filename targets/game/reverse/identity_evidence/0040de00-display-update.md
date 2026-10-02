# RVA 0x0040DE00 is Display::update

This session resolves the owner and method through the retail vtable, rather
than naming it from the address-derived forwarder. All image facts below
were checked with pefile and Capstone against
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, image base
0x00400000; GhidraMCP's byte search for `B3 AD 44 00` agrees on the only
stored pointer to the ILT at VA 0x010F0DD4.

## Independently identified Display table

Constructor RVA 0x0040F260 calls matched SubsystemInterface's constructor
at 0x009A1A30, then stores table VA 0x010F0DC0 at VA 0x0080F285.
It initializes width at +8, height at +0x0C, bit depth at +0x10 and the
windowed byte at +0x14, among the subsequent movie and display state.
The destructor at 0x0040F6D0 reinstalls the same table.

The table includes independently matched Display-specific slots:

| Slot | Table VA | ILT RVA | Body RVA | Matched name |
| --- | --- | --- | --- | --- |
| 2 | 0x010F0DC8 | direct | 0x009A1A50 | SubsystemInterface::loadIniFilesFromLegend |
| 3 | 0x010F0DCC | 0x000436B2 | 0x00067930 | SubsystemInterface::postProcessLoad |
| **5** | **0x010F0DD4** | **0x0004ADB3** | **0x0040DE00** | this body |
| 9 | 0x010F0DE4 | 0x000413C1 | 0x0040DC10 | Display::setWidth |
| 10 | 0x010F0DE8 | 0x00034C11 | 0x0040DC30 | Display::setHeight |
| 16 | 0x010F0E00 | 0x00027255 | 0x0040F570 | Display::getWindowed |
| 17 | 0x010F0E04 | 0x000073A1 | 0x0040DA80 | Display::setDisplayMode |

setWidth/setHeight independently write +8/+0x0C then notify the Mouse,
matching the constructor fields. This identifies Display without relying
on the destructor's synthetic BfmeObjEE name.

## Slot and BFME behavior identify update

GeneralsMD SubsystemInterface.h declares destructor, init,
postProcessLoad, reset, update and draw in that order. BFME's matched
loadIniFilesFromLegend slot lies between init and postProcessLoad, so its
update slot is 5. Display.h declares the public virtual update override.
The target is slot 5 of this independently identified Display table.

The body processes the video/movie receiver at +0x34, clocks and frame
state, and the movie/copyright timers at +0xDC/+0xE0/+0xE4/+0xE8.
Its timer comparisons and reset values (-1,0,0,-1) agree with the tail of
GeneralsMD Display::update. The matched forwarder at RVA 0x006E85D0 calls
this ILT before updating a transition subobject; its address-derived name
is supporting route evidence only.

The body is 502 bytes: final plain RET at +0x1F5 (RVA 0x0040DFF5), then
INT3 at +0x1F6. Prior log claims of `ret 0x10 at +0x302` are incorrect.
It takes no stack arguments, and the supported identity is
`?update@Display@@UAEXXZ`.

The prior 503-byte attempt still has frame/timestamp/register scheduling
residue. This session lands identity evidence only and changes no game
source, pins or progress row.
