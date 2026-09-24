// cl: /DNDEBUG /MD /EHsc
// Retail ILT 0x0001C8D2 forwards to the 0x00526660 body, whose owner and
// method name remain unproven. The first argument is a bool (see
// reverse/identity_evidence/0x00526660-bool-enable-parameter.md).

class Rva0001C8D2Thunk
{
public:
    void forward(bool arg0, int arg1);
};

class Rva00526660Body
{
public:
    void run(bool arg0, int arg1);
};

void Rva0001C8D2Thunk::forward(bool arg0, int arg1)
{
    ((Rva00526660Body *)this)->run(arg0, arg1);
}
