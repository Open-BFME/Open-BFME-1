# Default handle constructor identity probe

Retail RVA6910E0 is9 bytes followed by INT3. This independently compiled
probe matches all9 bytes with zero relocations. The existing gen-shim row
already supplies C++ bytes; final integration needs its canonical constructor
identity. Keep its definition outside the203-byte parent TU so MSVC cannot
use known clobbers to change the caller.

```cpp
// ??0Rva006910F0Handle@@QAE@XZ
// partial score=1.0 date=2026-10-03
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
class Gen006BA220;
class Rva006910F0Handle { public: Rva006910F0Handle(); ~Rva006910F0Handle(); Gen006BA220 *m_receiver; };
Rva006910F0Handle::Rva006910F0Handle() : m_receiver(0) {}
```
