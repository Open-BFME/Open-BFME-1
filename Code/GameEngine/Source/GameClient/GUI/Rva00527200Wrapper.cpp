// cl: /DNDEBUG /MD /EHsc
// Retail wrapper 0x00527200 keeps the same receiver through ILT 0x0001C8D2.

class Rva0001C8D2Thunk
{
public:
    void forward(int arg0, int arg1);
};

class Rva00527200Owner
{
public:
    void rva00527200(int arg0);
};

void Rva00527200Owner::rva00527200(int arg0)
{
    ((Rva0001C8D2Thunk *)this)->forward(arg0, -1);
}
