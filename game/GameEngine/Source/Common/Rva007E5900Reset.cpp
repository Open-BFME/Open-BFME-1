// Open-BFME: reset wrapper reconstructed from retail RVA 0x007E5900.

extern "C" __declspec(dllimport) void __stdcall Rva01358D0CReset(void *body);

class Rva007E5900Object
{
public:
    int reset(void);
};

int Rva007E5900Object::reset(void)
{
    Rva01358D0CReset(this);
    return 0;
}
