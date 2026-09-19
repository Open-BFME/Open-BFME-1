// cl: /O2 /Ob0

class Rva00604B10 {
public:
    void *field();
};

void *Rva00604B10::field()
{
    return reinterpret_cast<char *>(this) + 8;
}
