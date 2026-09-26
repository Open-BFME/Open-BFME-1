// Two address-derived copies of the three 32-bit fields after a four-byte header.

#define RVA00808F70_COPY(NAME)                     \
struct NAME                                           \
{                                                     \
    unsigned int m_header;                            \
    unsigned int m_fields[3];                         \
    void copyFields(const NAME &source);              \
};                                                    \
void NAME::copyFields(const NAME &source)              \
{                                                     \
    m_fields[0] = source.m_fields[0];                  \
    m_fields[1] = source.m_fields[1];                  \
    m_fields[2] = source.m_fields[2];                  \
}

RVA00808F70_COPY(Rva00808F70)
RVA00808F70_COPY(Rva00808F90)
