// cl: /DNDEBUG /MD /O2
class Q3MakeBaseA
{
public:
    virtual void primary();
};

class Q3MakeBaseB
{
public:
    virtual void secondary();
    void *m_payload;
    Q3MakeBaseB(void *payload) : m_payload(payload) {}
};

#define BFME_DERIVED_CTOR(NAME)                                     \
class NAME##Object : public Q3MakeBaseA, public Q3MakeBaseB          \
{                                                                    \
public:                                                              \
    NAME##Object(void *payload);                                      \
    virtual void primary();                                           \
    virtual void secondary();                                         \
};                                                                   \
NAME##Object::NAME##Object(void *payload) : Q3MakeBaseB(payload)     \
{                                                                    \
}

BFME_DERIVED_CTOR(Rva007E9B40)
BFME_DERIVED_CTOR(Rva007F1C20)
BFME_DERIVED_CTOR(Rva007F2150)
BFME_DERIVED_CTOR(Rva007F2E60)
BFME_DERIVED_CTOR(Rva007FBB20)
BFME_DERIVED_CTOR(Rva007FCF80)
