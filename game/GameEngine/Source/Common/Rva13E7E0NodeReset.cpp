struct Rva13E7E0Node
{
    unsigned char flag;
    unsigned int value;
    Rva13E7E0Node *next;
    Rva13E7E0Node *previous;
};

class Rva13E7E0NodeReset
{
public:
    void reset();

private:
    Rva13E7E0Node *m_node;
};

// ?d_0013e7e0@@YAXXZ
void Rva13E7E0NodeReset::reset()
{
    m_node->flag = 0;
    m_node->value = 0;
    m_node->next = m_node;
    m_node->previous = m_node;
}
