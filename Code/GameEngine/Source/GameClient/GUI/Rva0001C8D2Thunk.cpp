// cl: /DNDEBUG /MD /EHsc
// Retail ILT 0x0001C8D2 forwards to the identity-unresolved 0x00526660 body.

class Rva0001C8D2Thunk
{
public:
    void forward(int arg0, int arg1);
};

class Rva00526660Body
{
public:
    void run(int arg0, int arg1);
};

void Rva0001C8D2Thunk::forward(int arg0, int arg1)
{
    ((Rva00526660Body *)this)->run(arg0, arg1);
}
