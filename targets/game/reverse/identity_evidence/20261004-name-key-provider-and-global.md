# Native NameKeyGenerator provider and pointer identity

Retail BFME 1 v1.03 unpacked SHA256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

## Provider

RVA `0008FFC0`, extent 299, is the existing canonical `NameKeyGenerator::nameToKey(const char*)` source in `Common/NameKeyGenerator.cpp`. It hashes the one string argument by multiplying by 33, selects one of 45007 sockets (`0xAFCF`), compares bucket names, creates a 16-byte Bucket on a miss, assigns the incrementing key at receiver+`2BF44`, and returns that key in EAX. Its `RET 4` consumes one string argument. This is incompatible with `MemoryPoolFactory::createMemoryPool(const char*,int,int,int)`, which requires four arguments and returns a pool pointer. The latter row at the same 299-byte extent merely uses `object-symbol=` naming the actual NameKeyGenerator method; its ICF rationale is false because retail has no identical-COMDAT folding. Retire only that duplicate ledger identity and retain the existing canonical method at its unchanged extent.

The candidate `findMemoryPool`/`createMemoryPool` pins at ILT `0003ADD7` remain explicit unresolved naming debt: current cached objects expose at least 181 matched rows, 111 unique RVAs across ten TUs using those aliases. This change does not guess the true factory addresses or pretend to complete that migration. ILT `0003ADD7` actually jumps to the proven `0008FFC0` name-key provider.

## Global

Native module-name getters at `002A6520`, `00121FA0`, and `002B2B30` load their NameKeyGenerator receiver from **VA `012ED600`** before calling ILT `0003ADD7`. Subtracting the image base `00400000` gives **RVA `00EED600`**, not the previously recorded `012ED600`.

An independent provider audit found native GameEngine startup allocating `2BF5C` bytes, calling ILT `00048211` to the NameKeyGenerator constructor at `00090380`, storing the initialized receiver at VA `012ED600` at native `000791B0`, then calling its virtual `init` at slot +4. `NameKeyGenerator.cpp` owns exactly one `NameKeyGenerator *TheNameKeyGenerator = NULL`. The actual COFF provider is four-byte aligned zero BSS, followed by `AsciiString::TheEmptyString` at offset four; it needs no static pointer constructor. These separate runtime/type/layout facts establish the global identity independently of a masked byte comparison.

Only the canonical NameKeyGenerator pin is corrected. The wrong MemoryPoolFactory global alias remains for the separately bounded dependent-caller migration; retaining it does not establish its identity. No global data extent is claimed by this repair.

## Verification and scope

The pin-specific before and after checks and `pin_consistency --check` are recorded in the immutable worker receipt. Fresh scoped validation covers the ten audited caller TUs plus the canonical provider. Source change is limited to removing the false provider comment that labelled the NameKeyGenerator TU as a GameMemory createMemoryPool body. No header, shim, reference input, baseline, compiler option or function extent changes. Newly recovered source bytes and validated data bytes: zero.
