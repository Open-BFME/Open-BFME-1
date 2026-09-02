// Open-BFME5: clean C++ conversion of the nullable callback traversal.

typedef void *(__fastcall *Rva000C9E80Callback)(void *);

class Rva000C9E80Traversal
{
public:
    void advance();

private:
    unsigned char *m_current;
    int m_unused;
    Rva000C9E80Callback m_callback;
    int m_baseOffset;
    const unsigned char *m_offsets;
};

void Rva000C9E80Traversal::advance()
{
    unsigned char *current = m_current;
    if (current != 0) {
        int tableOffset = *reinterpret_cast<int *>(current + 0x68);
        int relative = *reinterpret_cast<const int *>(m_offsets + tableOffset);
        void *argument = current + 0x68 + relative + m_baseOffset;
        m_current = static_cast<unsigned char *>(m_callback(argument));
    }
}
