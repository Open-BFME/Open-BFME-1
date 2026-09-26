// cl: /DNDEBUG /MD /EHsc
// Without an explicit declaration MSVC reaches for the scalar ??3 here; retail
// frees the block through operator delete[] (??_V) at 0x00881EF0.
void __cdecl operator delete[](void *);

struct Rva943E10NodeMotion
{
    unsigned char data[28];
    ~Rva943E10NodeMotion();
};

// ??1Rva943E10NodeMotion@@QAE@XZ absent-from-retail (empty element dtor kept only
// so the matched free() emits retail's array-delete shape)
Rva943E10NodeMotion::~Rva943E10NodeMotion()
{
}

class Rva943E10CompressedAnim
{
public:
    void free();

private:
    unsigned char data[24];
    Rva943E10NodeMotion *node_motion;
};

// ?d_00943e10@@YAXXZ
void Rva943E10CompressedAnim::free()
{
    if (node_motion != 0) {
        delete[] node_motion;
    }
}
