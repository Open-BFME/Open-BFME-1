struct Rva192FB0Record
{
    unsigned char first;
    unsigned char padding[3];
    unsigned int second;
    Rva192FB0Record *third;
    Rva192FB0Record *fourth;
};

class Rva192FB0RecordOwner
{
public:
    void reset();

private:
    Rva192FB0Record *m_record;
};

// ?d_00192fb0@@YAXXZ
void Rva192FB0RecordOwner::reset()
{
    m_record->first = 0;
    m_record->second = 0;
    m_record->third = m_record;
    m_record->fourth = m_record;
}
