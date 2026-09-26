// cl: /O2
// Open-BFME: scalar-deleting destructor for Rva0005C110Surface, retail
// 0x0005FA60 (30 bytes). Vtable 0x01073740 slot zero routes here through
// ILT 0x0002C18D; the matched constructor at 0x0005C110 installs that
// vtable, and the matched complete destructor lives at 0x0005EC20.

class Rva0005C110Surface
{
public:
    __declspec(noinline) virtual ~Rva0005C110Surface();
};

Rva0005C110Surface::~Rva0005C110Surface()
{
}
