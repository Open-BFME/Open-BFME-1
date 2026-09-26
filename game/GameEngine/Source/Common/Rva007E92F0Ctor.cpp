// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x007E92F0: two base vptrs and a payload at +8.
class Rva007E92F0BaseA
{
public:
    virtual void primary();
};

class Rva007E92F0BaseB
{
public:
    virtual void secondary();
    void *m_payload;
    Rva007E92F0BaseB(void *payload) : m_payload(payload) {}
};

class Rva007E92F0Object : public Rva007E92F0BaseA, public Rva007E92F0BaseB
{
public:
    Rva007E92F0Object(void *payload);
    virtual void primary();
    virtual void secondary();
};

Rva007E92F0Object::Rva007E92F0Object(void *payload) : Rva007E92F0BaseB(payload) {}
