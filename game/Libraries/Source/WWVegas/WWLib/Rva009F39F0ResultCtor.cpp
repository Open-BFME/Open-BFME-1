// Complete 69-byte result constructor at RVA 0x009F39F0.
// Callers at RVA 0x009F6600 and 0x009F63D0 construct this one-pointer result.
// The historical owner and payload element names are unknown.

struct Rva009F39F0Payload
{
    void *m_start;                 // +0x00
    void *m_finish;                // +0x04
    void *m_end;                   // +0x08
    void *m_cursor;                // +0x0C
    int m_refCount;                // +0x10

    // User-provided, inline-able constructor.  VC7's new-expression expansion
    // can emit these stores before publishing the returned pointer.
    Rva009F39F0Payload()
        : m_start(0), m_finish(0), m_end(0)
    {
    }
};

struct Rva009F39F0Result
{
    Rva009F39F0Payload *m_value;

    Rva009F39F0Result();
};

__declspec(noinline) Rva009F39F0Result::Rva009F39F0Result()
{
    // Do not spell the three payload stores here: they belong to the inline
    // Payload constructor and must occur before result->m_value is published.
    m_value = new Rva009F39F0Payload;
    m_value->m_refCount = 1;
    m_value->m_cursor = m_value->m_start;
}

