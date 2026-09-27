# Render2DClass batch vector element at 0x00937060 is not ProxyClass

`Render2DClass::Render2DClass` (0x00937060) builds a DynamicVectorClass at member
+0x34. It calls the VectorClass constructor 0x00933D30 at code +0x65 and stores
vtable 0x0113C8AC at code +0x6A. The reconstruction typed that element as Zero
Hour's `ProxyClass`, padded to 0x74 bytes, with a TU-local StringClass that
constructs to null.

Retail rules that out:

- 0x00933D30 passes `??_L` (the eh vector constructor iterator) an element size
  of 0x74. Zero Hour's `ProxyClass` is `StringClass Name` plus `Matrix3D Transform`,
  0x34 bytes.
- The element constructor it passes, 0x00933A40, is `mov eax,ecx; mov [eax],0;
  ret`. It only nulls +0. A `ProxyClass` default constructor builds `Name`,
  which points at StringClass's shared empty string, not at null.
- The element destructor (ILT 0x0001AAD2 -> 0x0005DBE0) loads the pointer at +0,
  tests it, and releases it. It does not free a StringClass buffer.

Nothing in retail names the 0x74-byte type, so it takes the opaque name
`Rva0113C8ACElem`, from its vector's vtable. The VectorClass constructor call is
pinned under that name at 0x00933D30, the address the aligned call encodes.
