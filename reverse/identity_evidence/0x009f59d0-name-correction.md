# 0x009F59D0 naming correction

The 0.90 bank names this body `T_009f59d0::m(unsigned)`. `Rva009F5970StateCtor.cpp` declares `T_009f59d0::m()` without an argument. It casts that member pointer to a one-unsigned-argument function pointer. It calls the pointer with zero. Retail ends with `ret 4`, confirming one four-byte stack argument. The caller's local type view does not prove the body's class.

The symbol pin ledger, `reverse/symbols.csv`, maps the no-argument name `?m@T_009f59d0@@QAEXXZ` to 0x009F59D0 as a generated call target. The generated source `Code/gen_small/fun_005.cpp` still calls that spelling. Those references explain the pin, but they do not prove the body uses that class or signature. The new source uses `Rva009F59D0::method(unsigned)` to keep the unknown owner tied to the retail address.

The bank calls its traversal node `BfmeNode912C` and its helper owner `BfmeThing912C`. Retail loads the head at `this + 0xE4`, follows each link at `node + 0x0C`, and passes the same node pointer to byte-verified `Gen009F5040::linkNode_009F4D80`. The new source uses an address-named node view for the +0x0C link and the helper's forward-declared parameter type for the call.

Retail calls the byte-verified `Vector_base<Gen_t_009f51f0_p8cd>` constructor at +0x7A, then calls the byte-verified `vector<ICoord2D>` assignment at +0xB4. The new source keeps `ICoord2D` from `coord.h`, the WWMath coordinate header, for the stored vectors. It uses a separate two-`Int` temporary for the constructor and labels unproven fields by offset.
