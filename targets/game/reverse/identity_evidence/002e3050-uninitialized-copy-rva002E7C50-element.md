# 0x002E3050 is __uninitialized_copy over Rva002E7C50Element

## Caller proof

The matched STLport `vector<Rva002E7C50Element>::_M_insert_overflow` at 0x002E7C50
(`game/GameEngine/Source/Common/Rva002E7C50VectorInsertOverflowBody.cpp`,
scoped byte-verified) moves the tail of the old buffer with one out-of-line
call through ILT 0x0001BC93 (symbols.csv pin), whose jmp lands on 0x002E3050. In
STLport 4.5.3 that phase is `__uninitialized_copy(position, _M_finish,
new_finish, __false_type())`, so the body is that template instantiated over
the caller's element pointer.

## Body proof

The 48-byte body copies 28-byte elements in a first!=last loop and returns
the end pointer; the same STLport template defined out of line in the
caller's TU over Rva002E7C50Element compiles to it byte for byte (./build.sh).

## Refuted claim

`?dup_002e3050@@YAXXZ` was a gen-alias placeholder whose object symbol named the
BannerMovieEntry instantiation; retail has no identical-code folding, so this
address has one identity, the one its only caller proves.
