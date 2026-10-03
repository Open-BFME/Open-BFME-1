// cl: /O2 /MD
// Original createmesh.obj sections354/372; distinct native template bodies.
// See identity_evidence/00a07fb9-native-mesh-wrappers.md.
struct Rva00A07FB9Interface;
struct Rva00A07FB9Table
{
    void *at00[12];
    long (__stdcall *at30)(Rva00A07FB9Interface *);
};
struct Rva00A07FB9Interface
{
    Rva00A07FB9Table *at00;
};
class Rva00A07FB9
{
public:
    long method();
private:
    char at000[0x234];
    Rva00A07FB9Interface *at234;
};
class Rva00A08036
{
public:
    long method();
private:
    char at000[0x234];
    Rva00A07FB9Interface *at234;
};
long Rva00A07FB9::method() { return at234->at00->at30(at234); }
long Rva00A08036::method() { return at234->at00->at30(at234); }
