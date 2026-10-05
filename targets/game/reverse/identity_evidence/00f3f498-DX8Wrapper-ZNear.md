# DX8Wrapper::ZNear at VA 0x0133F498

The datum is one zero-initialized `float` (four bytes) in retail `.data`, with no initial pointer relocations. Its real spelling is the protected static member `?ZNear@DX8Wrapper@@1MA`. The competing public-access spelling `?ZNear@DX8Wrapper@@2MA` has the same scalar type but disagrees with the declaring class's access. Both existing DIR32 rows are retained.

The Zero Hour reference declares protected static `float ZNear` in `GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h` and defines `DX8Wrapper::ZNear` in `dx8wrapper.cpp`. The game header and native `dxwrapper.cpp` retain that declaration and definition. The public spelling comes from the TU-local projection-helper declaration. Correcting its access section makes it name the existing protected member.

Before correction, the protected spelling is declared or defined in two game files (the native header and `dxwrapper.cpp`), and the public spelling is declared in one game file (the projection helper). Inherited references and CameraClass's unrelated instance member do not add declarations of this static datum.

Retail RVA 0x00907120 stores its near-distance argument in this cell. RVA 0x00905990 reads it with `fld`, `fmul`, and `fsub` for the cached projection Z-bias formula, together with the far distance. Multiple other bodies reset it to zero. These accesses agree with the reference's projection-distance role and floating-point type. The receiver contract is static state in DX8Wrapper; the helper argument is a four-byte float, with no instance receiver.

Initial bytes are `00 00 00 00`. The next DIR32 datum starts at VA 0x0133F49C. There is no data row or DIR32 name strictly inside the four-byte extent, and this written global is not a compiler constant. A retail use of this cell as a pointer, a different near-distance destination in the matched projection helper, or any changed function instruction would refute the correction.

Raw evidence is in `build/rlink/identity-types-1791203017/0133F498-retail.txt`, `retail-summary.json`, `selected-bodies-fixed.txt`, `game-hits.txt`, and `znear-reference.txt`. Gate and LINKED receipts are recorded in `build/worker-final.md`. The native definition supplies the data row; no second definition is introduced.
