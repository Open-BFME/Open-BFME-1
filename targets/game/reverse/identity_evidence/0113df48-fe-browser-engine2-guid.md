# __GUID_2b2cc8b0_2dc0_48c6_b6fd_c07820a6477e at VA 0x0113DF48

The decorated identity `__GUID_2b2cc8b0_2dc0_48c6_b6fd_c07820a6477e` owns 16 bytes in retail `.rdata` at VA 0x0113DF48.

## Retail facts and contract

Retail `lotrbfme.exe` holds 16 bytes at VA 0x0113DF48:
`b0 c8 2c 2b c0 2d c6 48 b6 fd c0 78 20 a6 47 7e`
which decodes to GUID `{2b2cc8b0-2dc0-48c6-b6fd-c07820a6477e}`, the CLSID of `FEBrowserEngine2`.
`DX8WebBrowser::Initialize` (RVA 0x00958F20) in `game/Libraries/Source/WWVegas/WW3D2/DX8WebBrowserInitialize.cpp` calls `CoCreateInstance` / `CreateInstance` with this CLSID.

## Extent and users

16 bytes at VA 0x0113DF48. Referenced by `DX8WebBrowser::Initialize`.
