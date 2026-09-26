// The caller at 0x0035A060 pushes an owner pointer and an AsciiString pointer,
// calls 0x00359FE0, and cleans both arguments.  The body therefore has a
// neutral cdecl identity here: no named owner for this address is proven yet.
// Its table and record offsets are fixed by the matched StringRecord release
// bodies at 0x00359330/0x00359530: table +0x0C, records +0x18, and the
// released byte at record +0x0C.

class AsciiString
{
public:
    void *m_data;
};

template <class T> class StringBase
{
public:
    int compare(const StringBase<T> &other) const throw();
};

bool rvaLookupReleased00359fe0(void *owner, AsciiString *name);

struct Rva00359330Record
{
    int m_previous;
    int m_next;
    AsciiString m_name;
    bool m_released;
    unsigned char m_pad;
    unsigned short m_references;
    void *m_nodes;
};

class Rva00359330StringRecordTable
{
    friend bool rvaLookupReleased00359fe0(void *owner, AsciiString *name);

private:
    int findNameIndex(AsciiString *name);

public:
    int *m_nameIndexesBegin;
    int *m_nameIndexesEnd;
    int *m_nameIndexesCapacity;
    Rva00359330Record *m_records;
    int m_10;
    int m_14;
    int m_freeHead;
    int m_activeTail;
};

class Rva00359FE0Owner
{
public:
    unsigned char m_head[0xc];
    Rva00359330StringRecordTable m_nameTable;
};

bool rvaLookupReleased00359fe0(void *owner, AsciiString *name)
{
    Rva00359330StringRecordTable *table =
        &((Rva00359FE0Owner *)owner)->m_nameTable;
    unsigned int nameIndex = table->findNameIndex(name);

    if (nameIndex < (unsigned int)(table->m_nameIndexesEnd -
                                   table->m_nameIndexesBegin))
    {
        int recordIndex = table->m_nameIndexesBegin[nameIndex];

        if (((StringBase<char> *)&table->m_records[recordIndex].m_name)->
                compare(*(StringBase<char> *)name) == 0 &&
            recordIndex != -1)
            return ((Rva00359FE0Owner *)owner)->m_nameTable
                .m_records[recordIndex].m_released;
    }

    return true;
}
