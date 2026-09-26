// The only known callers of these four adjacent members are import jump
// thunks.  Their bodies prove the member ABI and field offsets, but not the
// owning type or the fields' semantics, so the identities remain address
// derived.

class FieldAddress0043A4E0
{
public:
    char *getAddress0043A4E0();

private:
    char m_padding[0x04];
    char m_value;
};

char *FieldAddress0043A4E0::getAddress0043A4E0()
{
    return &m_value;
}

class FieldAddress0043A4F0
{
public:
    char *getAddress0043A4F0();

private:
    char m_padding[0x3C];
    char m_value;
};

char *FieldAddress0043A4F0::getAddress0043A4F0()
{
    return &m_value;
}

class FieldAddress0043A500
{
public:
    char *getAddress0043A500();

private:
    char m_padding[0x40];
    char m_value;
};

char *FieldAddress0043A500::getAddress0043A500()
{
    return &m_value;
}

class DwordAccessor0043A510
{
public:
    int getDword0043A510() const;

private:
    char m_padding[0x38];
    int m_value;
};

int DwordAccessor0043A510::getDword0043A510() const
{
    return m_value;
}
