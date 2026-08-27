// Open-BFME: conditional offset result reconstructed from retail RVA 0x0089CC10.

class Rva0089CC10Object
{
public:
    int m_value;
    void *m_guard;

    int get() const;
};

int Rva0089CC10Object::get() const
{
    void *guard = m_guard;
    int result = 2;
    if (guard)
        result = m_value + 2;
    return result;
}
