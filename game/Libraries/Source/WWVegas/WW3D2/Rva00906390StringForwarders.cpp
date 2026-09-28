// cl: /O2 /Ob0
#include "../WWLib/wwstring.h"

// Eight independent int3-bounded tail calls. Retail adjusts ecx by the
// offset below and jumps to ILT RVA 000202E3 -> 007AF330, the witnessed
// StringClass::operator=(const char *) body (one stack slot, ret 4).
// The enclosing owners are unknown; each keeps its own address identity.
struct Rva00906390 { char pad00[4]; StringClass field04; const StringClass &assign(const char *); };
const StringClass &Rva00906390::assign(const char *text) { return field04 = text; }
struct Rva009063A0 { char pad00[8]; StringClass field08; const StringClass &assign(const char *); };
const StringClass &Rva009063A0::assign(const char *text) { return field08 = text; }
struct Rva009063B0 { char pad00[12]; StringClass field0C; const StringClass &assign(const char *); };
const StringClass &Rva009063B0::assign(const char *text) { return field0C = text; }
struct Rva009063C0 { char pad00[16]; StringClass field10; const StringClass &assign(const char *); };
const StringClass &Rva009063C0::assign(const char *text) { return field10 = text; }
struct Rva009063D0 { char pad00[20]; StringClass field14; const StringClass &assign(const char *); };
const StringClass &Rva009063D0::assign(const char *text) { return field14 = text; }
struct Rva009063E0 { char pad00[24]; StringClass field18; const StringClass &assign(const char *); };
const StringClass &Rva009063E0::assign(const char *text) { return field18 = text; }
struct Rva009063F0 { char pad00[28]; StringClass field1C; const StringClass &assign(const char *); };
const StringClass &Rva009063F0::assign(const char *text) { return field1C = text; }
struct Rva00906400 { char pad00[32]; StringClass field20; const StringClass &assign(const char *); };
const StringClass &Rva00906400::assign(const char *text) { return field20 = text; }
