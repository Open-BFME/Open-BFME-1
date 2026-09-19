// cl: /O2 /DNDEBUG /MD

// The carved body returns the address of the field at this+0xC.
class Rva000C8A90Pointer
{
public:
    void *get();

private:
    char m_prefix[0xC];
    int m_value;
};

// ?get@Rva000C8A90Pointer@@QAEPAXXZ
void *Rva000C8A90Pointer::get()
{
    return &m_value;
}
