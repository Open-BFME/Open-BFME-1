// Open-BFME: subobject reset wrapper reconstructed from retail RVA 0x000874A0.

extern "C" __declspec(dllimport) void __stdcall Rva01358D0CReset(void *body);

class Rva000874A0Object
{
public:
    void reset(void);
};

void Rva000874A0Object::reset(void)
{
    Rva01358D0CReset(reinterpret_cast<char *>(this) + 4);
}
