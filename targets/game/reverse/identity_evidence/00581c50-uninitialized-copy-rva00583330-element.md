# 0x00581C50 is __uninitialized_copy over Rva00583330Element

## Caller proof

The matched STLport `vector<Rva00583330Element>::_M_insert_overflow` at 0x00583330
(`game/GameEngine/Source/Common/Rva00583330VectorInsertOverflowBody.cpp`,
scoped byte-verified) moves the tail of the old buffer with one out-of-line
call through ILT 0x00015019 (symbols.csv pin), whose jmp lands on 0x00581C50. In
STLport 4.5.3 that phase is `__uninitialized_copy(position, _M_finish,
new_finish, __false_type())`, so the body is that template instantiated over
the caller's element pointer.

## Body proof

The 48-byte body copies 28-byte elements in a first!=last loop and returns
the end pointer; the same STLport template defined out of line in the
caller's TU over Rva00583330Element compiles to it byte for byte (./build.sh).

## Refuted claim

`?dup_00581c50@@YAXXZ` was a gen-alias placeholder whose object symbol named the
BannerMovieEntry instantiation; retail has no identical-code folding, so this
address has one identity, the one its only caller proves.
