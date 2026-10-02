# RVA 0x0026EDD0: three-argument offset dispatcher

The authoritative retail-1.03-unpacked image (SHA256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`) contains `add ecx, 0x204; jmp 0x00001294` at RVA 0x0026EDD0, occupying eleven bytes. ILT 0x00001294 transfers to matched RVA 0x002E0E30, `Rva002E0E30::rva002E0E30Handle(int, void*, void*)`, whose 185-byte body ends in `ret 12`.

The caller at RVA 0x002E5790 independently pushes three arguments at 0x002E59AC, 0x002E59B1, and 0x002E59B2 before calling ILT 0x0000F083 at 0x002E59B3. The ILT transfers to RVA 0x0026EDD0. These arguments are the key read through the caller's first parameter, its object pointer, and its argument-list pointer. The receiver is the event-source object; the offset thunk adjusts it to its record dispatcher.

The former `Rva0026EDD0::invoke()` declaration describes a zero-argument ABI inconsistent with this matched callee and retail caller. The corrected address-derived identity remains `Rva0026EDD0::invoke(int, void*, void*)`; no semantic naming claim is added. Other macro instances and signatures are untouched.
