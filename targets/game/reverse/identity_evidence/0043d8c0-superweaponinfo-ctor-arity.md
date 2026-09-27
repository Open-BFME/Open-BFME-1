# SuperweaponInfo's constructor takes TEN words, not the eleven its lifted name said

`game/GameEngine/Source/GameClient/SuperweaponInfoCtorThunk.cpp` carried a
`__declspec(naked)` `__emit` copy of the retail body at 0x0043D8C0 under the
name it copied out of Zero Hour's `InGameUI.cpp`:

    ??0SuperweaponInfo@@QAE@W4ObjectID@@I_N111ABVAsciiString@@H1HPBVSpecialPowerTemplate@@@Z

That decoration has one `Bool` more than the body can be: `evaReadyPlayed`,
which Zero Hour added between `ready` and the font. Three independent facts
say the body is the ten-word constructor, so the row now carries the decoration
that ten words actually mangles to,
`??0SuperweaponInfo@@QAE@W4ObjectID@@I_N11ABVAsciiString@@H1HPBVSpecialPowerTemplate@@@Z`
(the same prefix, one `1` fewer; MSVC 7.1 was asked, it is not a guess).

## The caller pushes ten

The only callers reach the body through the ILT thunk at RVA 0x0000751D, so the
push count is read there. Both call sites are `newInstance(SuperweaponInfo)(...)`
inside `InGameUI::addSuperweapon`; the aligned stream at 0x0044CA47..0x0044CA68
is ten pushes and nothing else between them:

    0044CA47  push ebp                    ; the SpecialPowerTemplate*
    0044CA48  push edx                    ; the colour, [player+0x1c4]
    0044CA4F  push ecx                    ; eva-less flag, xor ecx,ecx before
    0044CA50  push edx                    ; [InGameUI+0x75c] the point size
    0044CA5B  push ecx                    ; lea [InGameUI+0x758], the font
    0044CA60  push edi                    ; a zero flag
    0044CA61  push edx                    ; [esp+0x34] the timestamp
    0044CA62  push edi                    ; a zero flag
    0044CA63  push -1
    0044CA65  push ecx                    ; [esp+0x40] the ObjectID
    0044CA66  mov  ecx, eax               ; the allocation
    0044CA68  call 0x40751d               ; -> jmp 0x0043D8C0

## The body cleans ten and reads the last two from the tenth

- `0x0043D8E9: c2 28 00` -- `ret 0x28`, ten words. Eleven parameters make
  MSVC 7.1 emit `ret 0x2c`; the Zero Hour source in
  `game/GameEngine/Source/GameClient/InGameUI.cpp` does, and that build
  compiles to 248 bytes with `ret 0x2c`.
- The colour and the template are read at `+0016` (`mov edx,[esp+0x38]`) and
  `+001d` (`mov ecx,[esp+0x38]`), the ninth and tenth words. With an eleventh
  parameter the same two values sit at `[esp+0x3c]` and `[esp+0x40]`, and so
  does the Zero Hour build.
- `0x0044CA1D: push 0x24` before `operator new` -- `sizeof(SuperweaponInfo)` is
  0x24. With `m_evaReadyPlayed` in the class (Zero Hour's layout) it is 0x28,
  which is what the blocked `?addSuperweapon@InGameUI@@UAEXHABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z`
  verdict of 2026-09-27 recorded as BLOCKER ONE.

## The class identity itself is not in question

`??1SuperweaponInfo@@MAE@XZ` at 0x0043D9F0 is a MATCHED row
(`game/GameEngine/Source/GameClient/SuperweaponInfo.cpp`), and it installs the
same vtable this constructor stores at `+0x23`: VA 0x010F5754. The class name
therefore comes from a matched sibling, not from the lift. `tools/vtable_lookup.py
0x010F5754` finds exactly two bodies carrying that constant, this constructor
and that destructor.

## What the corrected signature is

    SuperweaponInfo(ObjectID id, UnsignedInt timestamp,
                    Bool hiddenByScript, Bool hiddenByScience, Bool ready,
                    const AsciiString &superweaponNormalFont,
                    Int superweaponNormalPointSize, Bool superweaponNormalBold,
                    Color c, const SpecialPowerTemplate *spt)

The member NAMES are Zero Hour's, from
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h`,
and every offset they produce agrees with the four bodies already matched in
`SuperweaponInfo.cpp` (display strings +0x04/+0x08, colour +0x0c, template
+0x10, power name +0x14) and with the `push 0x24` above. `m_evaReadyPlayed` is
absent because Zero Hour's is: the object's last byte is +0x23, and the
constructor's last store is `mov byte ptr [esi+0x23],al` with the zero already
in `eax`.
