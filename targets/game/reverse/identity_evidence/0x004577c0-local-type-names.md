# RVA 0x004577C0 local type names

The earlier attempt copied several type declarations into its source. The current attempt includes `Common/AsciiString.h`, `Common/FileSystem.h`, and `GameClient/MapUtil.h`, so it uses the project's declarations for `AsciiString`, `StringBase<char>`, `FilenameList`, and `FileInfo`.

- The current source still uses `StringBase<char>` from the AsciiString shim. `Rva004577C0StringView` and `Rva004577C0StringData` name only the pointer, length, and character layout that retail reads in this body. The earlier `StringBase` and `Data` declarations copied more fields and methods without evidence that those local names matched BFME's hidden layout.
- Retail loads the build-cache flag from `TheWritableGlobalData + 0xB7D`. `tools/name_oracle.py --class GlobalData --offset 0xB7D` reports that neither the BFME field table nor the Zero Hour layout witnesses a member at that offset. `Rva004577C0GlobalData` keeps the address in the type name and describes only that byte.
- Retail calls vtable slot 2 at object offset `+0x8` for `close`. `Rva004577C0FileView` declares the two preceding slots without names and `close` at slot 2. The type keeps the RVA because those bytes do not prove the complete `File` class layout.
- The earlier `BfmeStrEBC` shim contains only one pointer and supplied the file-list call signature. The current source includes `Common/FileSystem.h` and `GameClient/MapUtil.h`, which declare `getFileListInDirectory`, `FilenameList`, and its string element type. It removes the local shim because the headers supply those declarations.
