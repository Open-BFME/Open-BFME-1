# 0x000643F0: copy-out return contract

The 23-byte retail body at `0x000643F0` reads three dwords from `this`, loads its sole stack argument (the destination pointer) into `EAX` at `+0x02`, writes the three dwords through `EAX`, and ends in `ret 4` at `+0x14`. It leaves `EAX` equal to the destination pointer. The current matched, address-derived `Rva000643F0Value::copyTo` source in `W3SmallValueInitializers.cpp` declares `void` and reproduces the body only because the stores happen to leave `EAX` untouched. Its return contract is therefore incomplete.

Two separate retail callers use that result after the call through ILT `0x00025531`:

- The already matched `Rva006092D0State::rva00609360` at `0x00609360` calls the thunk at `+0xBA`, then reads `[EAX]`, `[EAX+4]`, and `[EAX+8]` at `+0xBF` through `+0xCC`. Its matched source already encodes a `Rva000643F0Triple *` member-function return through a local `CopyWithReturn` type to express the ABI despite the callee's void declaration.
- The dump body at `0x003BBE50` calls the same thunk at `+0xB6`, then reads `[EAX]` and `[EAX+4]` at `+0xBB` and `+0xC4` for the next by-value call. No instruction between the call and the first read defines `EAX`.

The retail bytes establish a pointer-producing return contract but cannot distinguish an original pointer return from a reference return. A pointer return is the least-specific source contract compatible with both callers. The owner and method names remain address-derived; this correction makes no additional semantic claim. The type is local to `W3SmallValueInitializers.cpp`; no shared header declares it. Changing the declaration and definition to return `Rva000643F0Triple *` and adding `return destination;` probed `EXACT` at `0x000643F0` (23/23 bytes, zero relocations) with MSVC 7.1. Its new mangled name is `?copyTo@Rva000643F0Value@@QBEPAURva000643F0Triple@@PAU2@@Z`. The old row must be retired at the same 23-byte range with an explicit identity correction.
