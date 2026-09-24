// cl: /DNDEBUG /MD /EHsc
// Retail wrapper 0x00527200 keeps the same receiver through ILT 0x0001C8D2.
// Its argument is the bool enable flag of the 0x00526660 body (see
// reverse/identity_evidence/0x00526660-bool-enable-parameter.md).

class Rva0001C8D2Thunk
{
public:
    void forward(bool arg0, int arg1);
};

class Rva00527200Owner
{
public:
    void rva00527200(bool arg0);
};

void Rva00527200Owner::rva00527200(bool arg0)
{
    ((Rva0001C8D2Thunk *)this)->forward(arg0, -1);
}
