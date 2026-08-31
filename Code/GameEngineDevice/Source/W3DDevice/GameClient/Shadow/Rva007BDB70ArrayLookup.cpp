// cl: /DNDEBUG /MD
// Clean reconstruction of the bounded fixed-record lookup at RVA 0x007BDB70.

struct Rva007BDB70Record
{
    unsigned char bytes[22];
};

class Rva007BDB70ArrayOwner
{
public:
    Rva007BDB70Record *lookup(int index);
    void ensureStorage(void);

private:
    unsigned char m_prefix[0x24];
    Rva007BDB70Record *m_records;
    int m_count;
};

Rva007BDB70Record *Rva007BDB70ArrayOwner::lookup(int index)
{
    if (!m_records)
        ensureStorage();

    if (index >= 0 && index < m_count)
        return &m_records[index];

    return 0;
}
