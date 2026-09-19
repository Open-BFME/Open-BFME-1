// cl: /DNDEBUG /MD

class Rva0014A8C0
{
public:
    void *getVtablePlus8();

private:
    void *m_vtable;
};

void *Rva0014A8C0::getVtablePlus8()
{
    return static_cast<char *>(m_vtable) + 8;
}
