struct Rva13E810Node
{
    unsigned char flag;
    unsigned int value;
    Rva13E810Node *next;
    Rva13E810Node *previous;
};

class Rva13E810NodeReset
{
public:
    void reset();

private:
    Rva13E810Node *m_node;
};

// ?d_0013e810@@YAXXZ
void Rva13E810NodeReset::reset()
{
    m_node->flag = 0;
    m_node->value = 0;
    m_node->next = m_node;
    m_node->previous = m_node;
}
