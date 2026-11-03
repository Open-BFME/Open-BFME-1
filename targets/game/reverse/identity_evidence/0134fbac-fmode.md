# __fmode storage at VA 0x0134FBAC

The decorated identity `__fmode` (the C global `_fmode`) owns one four-byte integer at VA 0x0134FBAC in retail `.data`. Its initial value in retail `.data` is 0 (the CRT's O_TEXT default).

## Retail facts and contract

`_fmode` is the CRT's file-mode global, defined in the msvc71 CRT (vendored at `inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/lib/msvcrt.lib`). Retail's only code reference is `_WinMainCRTStartup` (matched at 0x009F72C4, vendored=msvc71-crt): at +0x8E it executes `mov ecx, [0x0134FBAC]` to select the text/binary mode at startup. The address falls in the section's zero-filled virtual tail (`.data` raw size ends at VA 0x012EE000 while its virtual size ends at 0x01358000), so retail holds 0 at the address with no file bytes. The data-only owner TU `game/GameEngine/Source/Common/Rva0134FBACFmode.c` defines `int _fmode;`, which the C compiler emits as `__fmode`.

## Extent and all users

4 bytes at VA 0x0134FBAC. Users: `_WinMainCRTStartup` at +0x8E (the only retail reference).
