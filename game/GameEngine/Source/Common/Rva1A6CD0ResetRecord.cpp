struct Rva1A6CD0Record
{
    unsigned char first;
    unsigned char padding[3];
    unsigned int second;
    Rva1A6CD0Record *third;
    Rva1A6CD0Record *fourth;
};

class Rva1A6CD0RecordOwner
{
public:
    void reset();

private:
    Rva1A6CD0Record *m_record;
};

// ?d_001a6cd0@@YAXXZ
void Rva1A6CD0RecordOwner::reset()
{
    m_record->first = 0;
    m_record->second = 0;
    m_record->third = m_record;
    m_record->fourth = m_record;
}
