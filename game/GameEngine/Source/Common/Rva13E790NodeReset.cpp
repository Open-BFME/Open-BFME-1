struct Rva13E790Node
{
    unsigned char flag;
    unsigned int value;
    Rva13E790Node *next;
    Rva13E790Node *previous;
};

class Rva13E790NodeReset
{
public:
    void reset();

private:
    Rva13E790Node *m_node;
};

// ?d_0013e790@@YAXXZ
void Rva13E790NodeReset::reset()
{
    m_node->flag = 0;
    m_node->value = 0;
    m_node->next = m_node;
    m_node->previous = m_node;
}
