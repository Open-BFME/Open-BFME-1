// Open-BFME: SelectObject wrapper reconstructed from retail RVA 0x0093C330.
// The two fields are passed in their retail order as the HDC and GDI object.

extern "C" __declspec(dllimport) void * __stdcall SelectObject(
    void *deviceContext,
    void *object);

class Rva0093C330SelectObject
{
public:
    void apply(void);

    void *m_deviceContext;
    void *m_object;
};

void Rva0093C330SelectObject::apply(void)
{
    SelectObject(m_deviceContext, m_object);
}
