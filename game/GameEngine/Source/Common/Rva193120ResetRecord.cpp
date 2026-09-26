struct Rva193120Record
{
    unsigned char first;
    unsigned char padding[3];
    unsigned int second;
    Rva193120Record *third;
    Rva193120Record *fourth;
};

class Rva193120RecordOwner
{
public:
    void reset();

private:
    Rva193120Record *m_record;
};

// ?d_00193120@@YAXXZ
void Rva193120RecordOwner::reset()
{
    m_record->first = 0;
    m_record->second = 0;
    m_record->third = m_record;
    m_record->fourth = m_record;
}
