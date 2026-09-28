# Retail 0x00C6C8E0 is the CRT-called namespace-scope dynamic initializer
# for the Rva007F01F0 slot global at 0x0130A490, not an ordinary named
# function. The old ledger name claims a callable `initialize` member issues
# from this TU; retail has no such export. Defining the global here with its
# (value, second) initializer lets MSVC 7.1 emit those 22 bytes as its
# compiler-local _$E15 in .text$yc (called from the CRT init table via
# .CRT$XCU). The ledger now names the COFF symbol via object-symbol=_$E15
# under an address-derived row name.
#
# Proof:
# - `python3 tools/dis_retail.py 0x00C6C8E0 22` shows no one-time guard bit:
#   `mov eax,[0x012C37F0]` + `push 0x011299C8` + `push eax` +
#   `mov ecx,0x0130A490` + `call 0x007F01F0` + `ret`. That is a ctor call on a
#   namespace-scope global, the shape MSVC emits as _$E<n>.
# - `python3 tools/callees.py 0x00C6C8E0 22` resolves the callee to the
#   independently pinned 0x007F01F0 two-argument slot initializer
#   (`??0Rva007F01F0@@QAE@HH@Z` in targets/game/reverse/symbols.csv; the
#   address-derived ctor spelling of the class this TU defines).
# - Compiling this TU and reading the object with
#   `read_object_symbol_bytes(obj, '_$E15', 22)` yields the same 22 bytes
#   (DIR32 relocs: value at +1, slot global at +12; REL32 ctor call at +17).
#
# Precedent: `?bfmeInitBoxYP@@YAXXZ` at 0x00C6C350 (object-symbol=_$E1, global
# defined with its initializer in BfmeBoxInitYP.cpp); the
# `?Rva00C704AxFxAtexitThunk@@YAXXZ` family (object-symbol=_$E2, one
# address-derived ledger name per TU-local $E label).
