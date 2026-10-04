# INIException destructor and copy constructor come from its ThrowInfo

## ThrowInfo proof

Retail `lotrbfme.exe` (`inputs/baselines/bfme1/retail-1.03-unpacked/files/`):
the INIException ThrowInfo at RVA 0x00DDFC30 (symbols.csv pin
`__TI1?AVINIException@@`) holds attributes 0, pmfnUnwind VA 0x0041460F, 0 and
pCatchableTypeArray VA 0x011DFC28. Its catchable type has size 8 and copy
constructor VA 0x00448621.

- 0x0001460F is ILT `E9` to 0x00061BD0: `mov eax,[ecx]; push eax;
  call operator delete[] (0x00881EF0); pop ecx; ret`. As the unwind function
  of the ThrowInfo it is `INIException::~INIException` (it frees
  `mFailureMessage`, the field at +0).
- 0x00048621 is ILT `E9` to 0x00061BB0: zeroes `[this]`, calls 0x00850670 with
  the source object, returns `this` with `ret 4`. As the catchable type's copy
  constructor it is `INIException::INIException(const INIException &)`.

A ThrowInfo names its own type's destructor and copy constructor.

## Refuted claims

- `?release@Rva00061BD0@@QAEXXZ` and `??0Rva00061BB0Owner@@QAE@PAX@Z` were
  address-derived guesses for the same bodies; the proof above replaces them.
- `??1INIException@@QAE@XZ` at 0x00139FF0 (14 B) is
  `mov eax,[ecx]; test eax,eax; jz; push eax; call operator delete[]; pop ecx;
  ret` with a null check, referenced only by its own ILT 0x0001A5DC. It is not
  the ThrowInfo's unwind function (that is 0x00061BD0) and nothing links it to
  INIException; one body has one identity, so it becomes
  `?release@Rva00139FF0@@QAEXXZ`.
