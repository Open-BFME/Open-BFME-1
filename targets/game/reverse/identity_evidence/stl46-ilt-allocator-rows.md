# STLport 4.6 switch: allocator rows retail's ILT refutes

Six matched allocator rows lose their real names in the STLport 4.6 switch. Each
keeps its byte-verified body under an address-derived name (`?dup_<RVA>@@YAXXZ`)
whose `object-symbol=` is the symbol the 4.6 build compiles. None of the 4.5.3
names survives the switch:

- 4.6 declares `allocator<T>::allocate` / `deallocate` non-const, so every `QBE`
  spelling is now a symbol no TU emits; the compiled symbol is `QAE`.
- `_STLP_alloc_proxy<...>::deallocate` is inlined by 4.6. It has no out-of-line
  body.

The `QAE` spelling as compiled can't be the row name either. Retail's
incremental-link thunk table (`tools/ilt_oracle.py check NAME RVA`) contradicts it
at five of the addresses, and `tools/ilt_guard.py` refuses a contradicted real
name. The 4.5.3 `QBE` names were already contradicted there; they sat in
`ilt_contradicted_baseline.txt`, which may only shrink.

| RVA | 4.5.3 name (left the ledger) | oracle, QAE as compiled (U class key) | oracle, QAE with V class key |
|---|---|---|---|
| 0x0006CB10 | `allocator<_Rb_tree_node<pair<const AsciiString, Coord3D>>>::deallocate` QBE | CONTRADICTED | CONFIRMED exact, p_false 2.61e-04 |
| 0x0006CD40 | `allocator<_Rb_tree_node<pair<const AsciiString, MapMetaData>>>::allocate` QBE | CONTRADICTED | CONFIRMED exact, p_false 5.87e-04 |
| 0x000BEDC0 | `allocator<_Rb_tree_node<pair<const AsciiString, Coord3D>>>::allocate` QBE | CONTRADICTED | CONFIRMED exact, p_false 1.76e-03 |
| 0x001AFF70 | `allocator<..MapMetaData (V)..>::allocate` QBE | CONTRADICTED (U and V, QAE and QBE) | — |
| 0x001AFFB0 | `allocator<..MapMetaData (V)..>::deallocate` QBE | CONTRADICTED (U and V, QAE and QBE) | — |
| 0x001342F0 | `_STLP_alloc_proxy<..Coord3D..>::deallocate` | no 4.6 symbol (proxy inlined); byte-identical copy of 0x0006CB10's body | — |

For 0x0006CB10, 0x0006CD40 and 0x000BEDC0, the exact hit for the class-key-`V`,
non-const spelling is a lead for an identity pass. These TUs declare `Coord3D` /
`MapMetaData` as `struct`, so using that name needs either retail's class
declaration or an `object-symbol=` alias. Neither is decided here. A fit is
consistency, not proof. 0x001AFF70 and 0x001AFFB0 are byte-identical
instantiations for some other node type.

Each row's notes repeat its line of this table.
