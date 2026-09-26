// cl: /DNDEBUG /MD /EHsc

// Retail 0x00343EB0, 22 bytes: forward this, the hidden result buffer, and
// one value pointer through ILT 0x0002EA7D to the body at 0x00341C70.
// That body walks a tree and compares string-backed keys; it is not the
// integer hash-table equal_range named by the former generated claim.
// Its precise container identity remains unknown, so retain address names.
struct Rva00343EB0Result
{
    void *m_00;
    bool m_04;
};

// Both callee exits write result+0 and result+4, return the hidden buffer
// in EAX, and use ret 8. The pointer/bool result occupies eight bytes.
class Rva00341C70
{
public:
    Rva00343EB0Result invoke(const void *value);
};

class Rva00343EB0
{
public:
    Rva00343EB0Result invoke(const void *value);
};

Rva00343EB0Result Rva00343EB0::invoke(const void *value)
{
    return reinterpret_cast<Rva00341C70 *>(this)->invoke(value);
}
