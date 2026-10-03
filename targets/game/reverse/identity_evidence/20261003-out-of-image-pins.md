# Retire two impossible candidate pins

AGENTS.md requires every pin to be supported by the actual retail target.
These two inherited records lie outside every loaded image section both as
RVA and as VA minus image base 0x00400000. Retail image RVA end is 0x01016000
(preferred VA end 0x01416000). The exact removed records are:

```csv
?getClassMemoryPool@VertexMaterialClass@@CAPAXXZ,0x6B22FA14,packet 00921eba callee pin
?insert_unique@?$_Rb_tree@UOpen2Key6148F0@@U?$pair@$$CBUOpen2Key6148F0@@UOpen2Mapped6148F0@@@_STL@@U?$_Select1st@U?$pair@$$CBUOpen2Key6148F0@@UOpen2Mapped6148F0@@@_STL@@@3@UOpen2Less6148F0@@V?$allocator@U?$pair@$$CBUOpen2Key6148F0@@UOpen2Mapped6148F0@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBUOpen2Key6148F0@@UOpen2Mapped6148F0@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBUOpen2Key6148F0@@UOpen2Mapped6148F0@@@_STL@@@2@@2@U32@ABU?$pair@$$CBUOpen2Key6148F0@@UOpen2Mapped6148F0@@@2@@Z,0x21623145,Open2 0x6148f0 map twin callee
```

A fresh run of the existing `delta_sources.call_sites` over all retail .text
E8/E9 encodings found zero sites for both candidate values and for either
value minus the image base. A whole-file little-endian DWORD search also found
zero occurrences of either value. This is independent of missing cached objects
and proves no retail direct call or jump can require either candidate.

The current symbols ledger had only these rows for their respective names.
No replacement target or helper identity is inferred. Removal corrects pin
metadata; it changes no function row, source implementation or coverage.

Historical sample bounds: the VertexMaterialClass record is absent at the
August 12 sample and present at August 16 (`ac9b12132f`); the Open2 record is
absent at August 27 and present at August 29 (`938bb8130b`). These are bounds,
not asserted introduction commits. The independent full image/encoding proof
is unchanged after the authorized clean rebase.
