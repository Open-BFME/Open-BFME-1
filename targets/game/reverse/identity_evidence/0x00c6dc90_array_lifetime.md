# Array lifetime at 0x00C6DC90 / 0x00C70F60

Retail: `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`.
The .CRT pointer at RVA 0x00EA5D50 names VA 0x0106DC90. The initializer
returns at +0x26 and INT3 starts at +0x27, proving 39 bytes. Its cleanup
returns at +0x16 with INT3 at +0x17, proving 23 bytes.

The initializer calls `eh vector constructor iterator` (0x009F6EE4), passing
VA 0x01338480, stride 4, count 178, constructor VA 0x00C91B40 and destructor
VA 0x00C91B80, then registers cleanup VA 0x01070F60 with atexit.
The cleanup calls `eh vector destructor iterator` (0x009F6D76), passing the
same array, stride, count and destructor. These are compiler-generated array
lifetime callbacks. No application-level name for the element or array is inferred.

The existing matched `Rva00891B40` constructor at RVA 0x00891B40 stores the
shared block VA 0x012D5298 at element +0, increments its 16-bit counter and
returns. The paired destructor at RVA 0x00891B80 decrements that counter;
when it becomes zero, it calls the pool global VA 0x01337A30 slot +4 with
the block pointer, then returns with no stack arguments. This independently
proves the same four-byte element's zero-argument thiscall destructor ABI.
The new destructor pin uses the existing address-derived constructor type.

The native destructor below was separately compiled with `/O2 /Ob0 /MD` in
the existing `Rva00891B80Release.cpp` declaration context; `probe.py` reported
all 22 bytes exact modulo its one pool-global relocation:

```cpp
Rva00891B40::~Rva00891B40()
{
    Rva00891B80Block *block = m_block;
    if (--block->m_ref == 0)
        g_pool01337A30->free(block);
}
```

The production native global array emits TU-local `_$E1` (39 bytes) and
`_$E2` (23 bytes). The ledger uses its existing `object-symbol=` mechanism
to select these compiler artifacts. Both rows pass strict source, function,
call target and DIR32 checks. The cleanup retains its existing opaque ledger
name while its manual wrapper TU is retired.

Retail SHA-256:

- 0x00C6DC90/39: `18e0dff99390d646b787bb0c631d679a8bd78ce9af8fd330c40220f1c9fa5927`
- 0x00C70F60/23: `f0f57fb8523434787c495e396a6b74c6bbabccb53842fc88b15d4a6c2aae4517`
- 0x00891B80/22: `6aa3a7eb444e5f3c821fd3ebd84972507ef0b80c9faad4b432413e8f9769ab55`
