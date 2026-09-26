// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Five separate derived classes share the same secondary base and +8 payload.
class Rva007F1DE0BaseA
{
public:
    virtual void primary();
};

class Rva007F1DE0BaseB
{
public:
    virtual void secondary();
    void *m_payload;
    Rva007F1DE0BaseB(void *payload) : m_payload(payload) {}
};

#define BFME_DERIVED_CTOR(RVA) \
class Rva##RVA##Object : public Rva007F1DE0BaseA, public Rva007F1DE0BaseB \
{ \
public: \
    Rva##RVA##Object(void *payload); \
    virtual void primary(); \
    virtual void secondary(); \
}; \
Rva##RVA##Object::Rva##RVA##Object(void *payload) : Rva007F1DE0BaseB(payload) {}

BFME_DERIVED_CTOR(007F1DE0)
BFME_DERIVED_CTOR(007F2680)
BFME_DERIVED_CTOR(007F2F80)
BFME_DERIVED_CTOR(007FAE20)
BFME_DERIVED_CTOR(007FC150)
