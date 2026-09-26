struct Rva193180Record
{
    unsigned char first;
    unsigned char padding[3];
    unsigned int second;
    Rva193180Record *third;
    Rva193180Record *fourth;
};

class Rva193180RecordOwner
{
public:
    void reset();

private:
    Rva193180Record *m_record;
};

// ?d_00193180@@YAXXZ
void Rva193180RecordOwner::reset()
{
    m_record->first = 0;
    m_record->second = 0;
    m_record->third = m_record;
    m_record->fourth = m_record;
}
