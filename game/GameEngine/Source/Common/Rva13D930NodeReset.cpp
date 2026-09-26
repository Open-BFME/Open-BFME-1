struct Rva13D930Node
{
    unsigned char flag;
    unsigned int value;
    Rva13D930Node *next;
    Rva13D930Node *previous;
};

class Rva13D930NodeReset
{
public:
    void reset();

private:
    Rva13D930Node *m_node;
};

// ?d_0013d930@@YAXXZ
void Rva13D930NodeReset::reset()
{
    m_node->flag = 0;
    m_node->value = 0;
    m_node->next = m_node;
    m_node->previous = m_node;
}
