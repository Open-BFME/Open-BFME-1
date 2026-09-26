struct Rva13E740Node
{
    unsigned char flag;
    unsigned int value;
    Rva13E740Node *next;
    Rva13E740Node *previous;
};

class Rva13E740NodeReset
{
public:
    void reset();

private:
    Rva13E740Node *m_node;
};

// ?d_0013e740@@YAXXZ
void Rva13E740NodeReset::reset()
{
    m_node->flag = 0;
    m_node->value = 0;
    m_node->next = m_node;
    m_node->previous = m_node;
}
