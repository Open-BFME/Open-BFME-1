# Singleton forwarder target at VA 0x0130EA10

The decorated identity `?TheBfmeObject_00C70EB0@@3VGen_00C70EB0Target@@A` (C
`Gen_00C70EB0Target TheBfmeObject_00C70EB0`) owns storage at VA 0x0130EA10 in
retail `.data`. Retail holds zeros there (loader semantics per
`reloc_ledger.Image.read`). `Gen_00C70EB0Target` is an empty struct with a
single empty method:

```cpp
class Gen_00C70EB0Target
{
public:
    void bfmeForward(void);
};
```

so a plain definition emits zero-filled storage with no dynamic initializer.
(The empty `bfmeForward` body itself is the matched row at 0x008833B0,
defined in `Rva008833B0.cpp`; this row is only the storage.)

## Retail facts and contract

The sole retail code reference comes from `S3SingletonForwarders.cpp`:

- `TheBfmeObject_00C70EB0.bfmeForward();` — loads the object's address as
  the ECX receiver and calls the empty forwarder.

The 1-byte extent is the empty struct's `sizeof` under the build flags as
proven by the data gate.

## Extent and all users

`sizeof(::TheBfmeObject_00C70EB0)` byte at VA 0x0130EA10 as proven by the
data gate. Defined in place in
`game/GameEngine/Source/Common/S3SingletonForwarders.cpp` (its sole
consumer), next to its sibling forwarder targets.
