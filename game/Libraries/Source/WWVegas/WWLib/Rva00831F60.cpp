// cl: /O2 /MD
// Distinct no-argument thiscall leaves at slots1/2 of the RTTI-anchored
// _Locale_impl table. Matched locale lifetime callers prove both ABIs.
// Their method spellings remain opaque; no _Locale_impl layout is duplicated.
class Rva00831F60
{
public:
    void method();
};
class Rva00831F70
{
public:
    void method();
};

void Rva00831F60::method() {}
void Rva00831F70::method() {}
