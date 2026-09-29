# 0x0083E8F0 is STLport ios_base::_M_throw_failure, not `process()`

The 24-byte body was claimed as `?process@@YAXXZ` in
game/GameEngine/Source/Common/process.cpp, a name with no caller or source
behind it ("fixed two-argument global dispatch").

Retail bytes:

    mov  eax, [__imp___iob]      ; MSVCR71 _iob (IAT 0x013592F0)
    add  eax, 0x40               ; &_iob[2] == stderr
    push eax
    push 0x0112EBAC              ; "ios failure"
    call [__imp__fputs]          ; MSVCR71 fputs (IAT 0x013593C8)
    add  esp, 8
    ret

- The literal at 0x0112EBAC is `ios failure`, STLport 4.5.3's message for
  ios_base::_M_throw_failure in src/ios.cpp, printed with fputs to stderr
  when the library is built without exceptions.
- It sits between the ios.cpp bodies already matched under real names:
  ios_base::failure's constructor at 0x0083E890 and destructor at 0x0083E8B0.
- tools/callers_of.py 0x0083E8F0: every named caller is an STLport stream
  path -- the twelve basic_ifstream/ofstream/fstream constructors
  (0x0084B980..0x0084D0A0), whose `setstate(failbit)` inlines
  basic_ios::clear -> _M_check_exception_mask -> _M_throw_failure, plus the
  file-open helpers at 0x0084AC60..0x0084AFE0 and ios_base::_S_uninitialize.
- The callers load no stack arguments and the body ignores ecx: a
  thiscall member with no parameters, which is `void _M_throw_failure()`
  (protected, vendored stl/_ios_base.h line 203) --
  `?_M_throw_failure@ios_base@_STL@@IAEXXZ`. symbols.csv already pinned
  that name to 0x0083E8F0.

The census (3361d5aec5) lists 27 objects that reference
`?_M_throw_failure@ios_base@_STL@@IAEXXZ` with nothing defining it.
