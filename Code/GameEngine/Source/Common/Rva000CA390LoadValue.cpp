// ?load@Rva000CA390Value@@QAEHXZ
// Retail 0x000CA390 loads the first dword from this object and returns it.
// The only boundary evidence reaches the address through an ILT thunk.
// No caller or layout evidence proves a semantic class or method name.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva000CA390Value
{
public:
    int load();

private:
    int m_value;
};

int Rva000CA390Value::load()
{
    return m_value;
}
