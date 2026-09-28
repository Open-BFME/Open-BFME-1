// cl: /O2 /Ob0
// Independent opaque entries: each RVA has int3 padding on both sides of
// its complete body. The pointer offsets below are directly witnessed.
struct Rva0094BD10 { char *field00; char *value() const; };
char *Rva0094BD10::value() const { return field00 + 4; }
struct Rva0094BD20 { char *field00; char *value() const; };
char *Rva0094BD20::value() const { return field00 + 8; }
struct Rva0094BD30 { char *field00; char *value() const; };
char *Rva0094BD30::value() const { return field00 + 12; }
struct Rva0094BD40 { unsigned int value(unsigned int); };
unsigned int Rva0094BD40::value(unsigned int argument) { return argument; }
void rva0094BD50() {}
struct Rva0094BD60 { char *field00; char *value() const; };
char *Rva0094BD60::value() const { return field00 + 4; }
struct Rva0094BD70 { char *field00; char *value() const; };
char *Rva0094BD70::value() const { return field00 + 8; }
struct Rva0094BD80 { char *field00; char *value() const; };
char *Rva0094BD80::value() const { return field00 + 12; }
void rva0094BD90() {}
