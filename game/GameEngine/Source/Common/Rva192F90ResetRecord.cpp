struct Rva192F90Record
{
    unsigned char first;
    unsigned char padding[3];
    unsigned int second;
    Rva192F90Record *third;
    Rva192F90Record *fourth;
};

class Rva192F90RecordOwner
{
public:
    void reset();

private:
    Rva192F90Record *m_record;
};

// ?d_00192f90@@YAXXZ
void Rva192F90RecordOwner::reset()
{
    m_record->first = 0;
    m_record->second = 0;
    m_record->third = m_record;
    m_record->fourth = m_record;
}
