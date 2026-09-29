# `DX8Wrapper::Release_Device` at RVA `0x00907B00`

`dx8wrapper.h` declares `Release_Device` as a protected static method of `DX8Wrapper`. The retail `DX8Wrapper::Shutdown` body at `0x0090B640` calls the body at `0x00907B00` while releasing the Direct3D device.

The body at `0x00907B00` clears the device's texture stages, stream source, index buffer, vertex-buffer references, and device pointer. The source method with those operations is `DX8Wrapper::Release_Device` in `dxwrapper.cpp`. The retail-run row at `0x00907B00` in `ea_evidence.csv` also names `Libraries/Source/WWVegas/WW3D2/dxwrapper.cpp`.
