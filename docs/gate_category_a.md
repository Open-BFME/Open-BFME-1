# Gate Identity Failures: Category (a) Analysis

**Category (a) definition**: Both functions exist and are matched in the ledger; source calls the wrong one. The ledger proves both are real.

**Total**: 77 failures, not 28. The original count came from a parser that read
build.py's `(ledger: <name>, <note>)` field as if the free-text note were part of
the mangled name, so every annotated row looked unconverted. Corrected:

    77  both matched -- our source calls the wrong one of two real functions
    13  retail's target is matched; the symbol we emit is not a row
     0  blocked on an unconverted callee   (was reported as 54)

The 28 below were the subset visible before the fix, and the conclusions drawn
from them hold -- 1 fixable, the rest architectural. The other 49 have not been
attempted.

**Temper the optimism, though.** "Both functions are matched" means a source fix
is CONCEIVABLE, not that it is easy. The one that yielded was a same-class method
mix-up (`compare` vs `compareNoCase` on StringBase<char>), and across all 77 there
is exactly ONE other same-class pair: mesh.cpp's `MeshClass::Generate_Culling_Tree`
forwards to `MeshGeometryClass::Generate_Culling_Tree` (166 B @0x00925060) where
retail reaches 0x00924C30, which the ledger calls `Get_User_Text` (14 B). Different
sizes, so different functions, and deciding which the forward should reach is an
identity question for the image oracles rather than a one-line edit.

Everything else pairs methods of DIFFERENT classes, which is the signature of a
hierarchy modelled wrong rather than a call written wrong. Expect the 49 to behave
like the 27, and treat any that does not as a bonus.

**Key Rules Established**:
1. **ICF twins are identical length**: Different lengths mean different functions, not type aliases. A pin under the wrong name still byte-matches but hides the defect.
2. **Type swaps fix mangled names, never code shape**: Changing `AsciiString` to `UnicodeString` in template parameters changes which method name gets called at a site, but does not change the surrounding function body or register allocation. If bytes differ after a type swap, the body itself differs from retail.
3. **Ledger rows must reflect binary truth, not source output**: Renaming or pinning a row to match whatever our compiler emits makes the ledger agree with ourselves instead of with the retail binary. This hides defects.

---

## Status Breakdown

### ✅ FIXED (1 failure)

| File | Calls | Retail Calls | Fix | Evidence |
|------|-------|--------------|-----|----------|
| `Win32BIGFileSystem_mapIndex00093E60.cpp` | `?compare@StringBase<D>` | `?compareNoCase@StringBase<D>` | Changed `less<AsciiString>` comparator to use `compareNoCase()` instead of `compare()`. Retail's STLport instantiation was keyed on case-insensitive ordering. | Byte-verified immediately. Committed to master (cherry-picked by team lead). |

**Size check**: Both implementations are within the same comparator struct; no ICF twin issue.

---

### 🚫 NEEDS BODY RECONSTRUCTION (3 failures)

Body shape differs beyond just type names. Type swaps fix the mangled names but leave the surrounding code structure incompatible. These require architectural changes, not renames.

| File | Calls | Retail Calls | Reason | Evidence |
|------|-------|--------------|--------|----------|
| `RvaMapIndexAsciiStringNothrow.cpp` (2x) | `?compare@AsciiString`, `??0StringBase<D>` | `?compare@StringBase<G>`, `??0StringBase<G>` | Element type change (AsciiString→UnicodeString) fixes function names at call sites (+0x3C, +0x63) but bytes differ at +0x63, +0x89, +0x9e. Constructor calls, insert_unique, and releaseBuffer are code-generated from body structure; changing the key type changes the body shape. | Tested: changed source to UnicodeString, updated ledger row name, added missing symbols. Compiled successfully but retail bytes != compiled bytes at three offsets. Reverted. |
| `mixfile.cpp` (2x) | `??4StringClass` (operator=) | `??0StringBase<D>` (constructor) | Calling wrong method type entirely (assignment vs construction). Appears to be structural difference in how strings are initialized/stored. | Size mismatch suggests different functions, not an alias. |

---

### 🚫 NEEDS HEADER CHANGES (blocked by gate red) (3+ failures)

These cannot land while the gate is red. Pre-commit hook enforces: no staged `.h` files while gate is red.

| File | Calls | Retail Calls | Reason |
|------|-------|--------------|--------|
| `ConnectionManager.cpp` | `??0UnicodeString` | `??0StringBase<G>` | Constructor mismatch in templated code or headers. Likely requires header adoption or type system change. |
| `GSConfig.cpp` | `??0list<AsciiString>` | `??0StringBase<D>` | List instantiation with wrong element type. Likely requires header changes to vector/list templates. |
| (Others with similar patterns) | Various | Various | Type system mismatches requiring header fixes. |

---

### 🔄 IN ANOTHER SEAT'S QUEUE (7 failures, SKIP)

Luna is working on these files. Coordination required; skipped to avoid merge conflicts.

| File | Calls | Retail Calls |
|------|-------|--------------|
| `ini.cpp` (2x) | `??1Buffer`, `??1Buffer` | `?Reset@Buffer`, `?Reset@Buffer` |
| `DownloadManager.cpp` | `?set@UnicodeString` | `?set@StringBase<G>` |
| `NameKeyGenerator.cpp` (1x: freeSockets) | `?freeSockets@NameKeyGenerator` | `?bfmeGo920F@BfmeThing920F` |
| `LANGameSlot_getUser_Thunk.cpp` | `?set@UnicodeString` | `?set@StringBase<G>` |
| `decalmsh.cpp` | `?Resize@SimpleVecClass<Vector3i16>` | `?Resize@SimpleVecClass<Vector3>` |

---

### 🟡 NOT SOURCE-FIXABLE / ARCHITECTURAL ISSUES (11+ failures)

Different functions at different addresses with different sizes. These are real bugs or deliberate design changes in retail, not misnamed instances of the same code.

**ICF twin test**: When two functions share the same bytes, they are the same length. Different lengths = different functions = no pin will fix it.

| File | Calls | Retail Calls | Sizes | Issue |
|------|-------|--------------|-------|-------|
| `definitionmgr.cpp` | `?Free_Definitions@DefinitionMgrClass` (50B) | `?bfmeGo920F@BfmeThing920F` (27B) | 50 ≠ 27 | Different functions. Destructor calls wrong cleanup. Root cause unknown; requires design review. |
| `NameKeyGenerator.cpp` (freeSockets) | `?freeSockets@NameKeyGenerator` (64B) | `?bfmeGo920F@BfmeThing920F` (27B) | 64 ≠ 27 | Different functions. Same retail target as definitionmgr, but our source is a different size. Both are real, different functions. |
| `NameKeyGenerator.cpp` (operator new) | `??2@YAPAXI` (global operator new) | `?bfmeAllocBlock@@YAPAXI` (different) | — | Different allocator functions. Source uses global new; retail uses custom allocator. Likely fixable: one-line change at allocation site. **Recommended next attempt.** |
| `PlayerTemplate.cpp` | `??$__find@...AsciiString...` | `??$__find@...BFMEFindAsciiStringView...` | — | Category (c): TU-local type clone. BFMEFindAsciiStringView is a made-up struct in the same file, modeling the binary layout of a different type. Not fixable by name swap; requires understanding which struct the real type was. |
| `W3DTerrainVisual.cpp` | `?removeTreesAndPropsForConstruction@BaseHeight...` | `?bfmeGo1015I@BfmeI1015@@QAEXHHH@Z` | — | Different functions. Completely wrong method is being called. Would need caller investigation or architectural change. |
| `ModuleInfoNuggetVector.cpp` | `??1Nugget@ModuleInfo` | `??1BfmeOwnVUG` | — | Different classes. Retail uses BfmeOwnVUG; source uses ModuleInfo::Nugget. Structural difference, not a type alias. |
| `ThingFactory.cpp` | `??1Nugget@ModuleInfo` | `??1BfmeOwnVUG` | — | Same as ModuleInfoNuggetVector: different class hierarchy. |
| `INI_stl.cpp` | `??1AudioEventRTS` | `?releaseBuffer@UnicodeString` | — | Destructor vs releaseBuffer. Same pattern as Buffer/ini.cpp but inverse: AudioEventRTS destructor calls release instead. **Check if needs .h; if not, likely fixable.** |

---

The `ModuleInfoNuggetVector.cpp` clear failure above was resolved on 2026-09-18
by separating the actual record families into
`game/GameEngine/Source/Common/Containers/Rva0013B8F0Vector.cpp` and
`game/GameEngine/Source/Common/Containers/Rva007701C0Vector.cpp`. Their 821B and
1048B scoped unions remain exact. This does not establish original class names
or resolve the separately listed `ThingFactory.cpp` claims. The table retains
the original diagnostic evidence.

### 💡 NEXT ATTEMPTS (Recommended Order)

Based on team lead guidance, attempt in this order with 2-failure bound per item:

1. **NameKeyGenerator.cpp (operator new)**: Global `new` vs `?bfmeAllocBlock`. One-line fix likely at allocation site. Should be straightforward.

2. **NameKeyGenerator.cpp + definitionmgr.cpp (bfmeGo920F)**: Both have same retail target despite different sizes. Run `tools/callers_of.py` to understand what bfmeGo920F actually is and whether it's a real function or an alias.

3. **INI_stl.cpp**: Destructor vs releaseBuffer. Check whether fix requires `.h` edit first. If not, similar to Buffer pattern and should be fixable.

---

## Data Collection Notes

- Sizes obtained from ledger where available
- Two failures in mixfile.cpp listed twice due to parsing (actual: 1 failure with 2 distinct mismatches)
- Two failures in ini.cpp identical (Buffer destructor mismatch occurs in multiple contexts; luna's queue, skip)
- Two failures in NameKeyGenerator.cpp: one is operator new (fixable), one is freeSockets (architectural)

---

## Key Insight

Of 28 category (a) failures, the single successful fix (Win32BIGFileSystem) worked because it was a **pure comparator logic issue within the same template type**. No type change needed; no body restructuring needed; just a different comparison function.

Most other failures require either:
- **Type system changes** (header edits, blocked while gate red)
- **Body restructuring** (code shape differs, not just names)
- **Architectural decisions** (wrong functions being called, not type aliases)
- **Different class hierarchies** (not resolvable by renaming)

Only a handful (like NameKeyGenerator's operator new) appear to be simple source location changes.


## The other 13: our name is the real one, the ledger's is invented

The split also finds 13 failures where the symbol WE emit has no ledger row while
retail's target does. They are the same type-invention problem pointing the other
way -- here our source spells the real type and the LEDGER carries the stand-in:

    PeerThread.cpp   emits  _Rb_tree<int, pair<int, _SBServer *>>
                     retail _Rb_tree<int, pair<int, Gen_t_000a4c90_p12cd>>

    Locomotor.cpp    emits  _Rb_tree<NameKeyType, pair<NameKeyType, Locomotor *>>
                     retail _Rb_tree<NameKeyType, pair<NameKeyType, Object...>>

That matters for choosing which side to change. Where the ledger holds the
invented name, the fix is in the TU that MINTED it -- make that TU spell the real
type so its instantiation mangles the same way -- and not in the row. Renaming the
row to match our object is the move that hides defects, because the byte gate then
passes and nothing downstream can tell.

So all 99 remaining failures reduce to one cause in two directions: a translation
unit somewhere invented a local type instead of using the real one, and every
instantiation that touches it mangles differently from retail. That is conversion
work on those TUs, not ledger work, and it is why the count stopped falling.
