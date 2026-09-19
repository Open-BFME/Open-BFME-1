// cl: /O2

struct Rva009A2B80Node
{
    char m_padding00[0x30];
    Rva009A2B80Node * volatile m_next;
};

class Rva009A2B80Owner
{
public:
    void clear();

private:
    Rva009A2B80Node *m_buckets[0x493];
    Rva009A2B80Node * volatile m_freeHead;
};

void Rva009A2B80Owner::clear()
{
    for (unsigned int i = 0; i < 0x493; ++i)
    {
        Rva009A2B80Node *node = m_buckets[i];
        while (node)
        {
            Rva009A2B80Node *next = node->m_next;
            node->m_next = m_freeHead;
            m_freeHead = node;
            node = next;
        }

        m_buckets[i] = 0;
    }
}
