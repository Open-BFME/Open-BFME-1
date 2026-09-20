// cl: /DNDEBUG /MD
// Carved tiny bodies, retail RVAs 0x0013CDB0 to 0x0013D590.
// Each shape follows from the retail bytes and the caller ABI alone;
// class and method names are address-derived because nothing names them.

class Rva0013CDB0MemberAddress
{
public:
    unsigned char *member();

private:
    unsigned char m_prefix[0x0C];
    unsigned char m_member;
};

unsigned char *Rva0013CDB0MemberAddress::member()
{
    return &m_member;
}

class Rva0013CF20ConstantTrue
{
public:
    bool value() const;
};

bool Rva0013CF20ConstantTrue::value() const
{
    return true;
}

class Rva0013CF60MemberValue
{
public:
    unsigned char *value() const;

private:
    unsigned char *m_first;
    unsigned char *m_value;
};

unsigned char *Rva0013CF60MemberValue::value() const
{
    return m_value;
}

class Rva0013CF70Identity
{
public:
    Rva0013CF70Identity *identity();
};

Rva0013CF70Identity *Rva0013CF70Identity::identity()
{
    return this;
}

class Rva0013CF90Identity
{
public:
    Rva0013CF90Identity *identity();
};

Rva0013CF90Identity *Rva0013CF90Identity::identity()
{
    return this;
}

class Rva0013CFD0Identity
{
public:
    Rva0013CFD0Identity *identity();
};

Rva0013CFD0Identity *Rva0013CFD0Identity::identity()
{
    return this;
}

class Rva0013D010Identity
{
public:
    Rva0013D010Identity *identity();
};

Rva0013D010Identity *Rva0013D010Identity::identity()
{
    return this;
}

class Rva0013D120Identity
{
public:
    Rva0013D120Identity *identity();
};

Rva0013D120Identity *Rva0013D120Identity::identity()
{
    return this;
}

class Rva0013D190Identity
{
public:
    Rva0013D190Identity *identity();
};

Rva0013D190Identity *Rva0013D190Identity::identity()
{
    return this;
}

class Rva0013D1B0Identity
{
public:
    Rva0013D1B0Identity *identity();
};

Rva0013D1B0Identity *Rva0013D1B0Identity::identity()
{
    return this;
}

class Rva0013D1E0Identity
{
public:
    Rva0013D1E0Identity *identity();
};

Rva0013D1E0Identity *Rva0013D1E0Identity::identity()
{
    return this;
}

class Rva0013D230Identity
{
public:
    Rva0013D230Identity *identity();
};

Rva0013D230Identity *Rva0013D230Identity::identity()
{
    return this;
}

class Rva0013D2F0Identity
{
public:
    Rva0013D2F0Identity *identity();
};

Rva0013D2F0Identity *Rva0013D2F0Identity::identity()
{
    return this;
}

class Rva0013D2A0AdvanceSixteen
{
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva0013D2A0AdvanceSixteen::advanced() const
{
    return m_value + 16;
}

class Rva0013D310AdvanceSixteen
{
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva0013D310AdvanceSixteen::advanced() const
{
    return m_value + 16;
}

class Rva0013D350AdvanceSixteen
{
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva0013D350AdvanceSixteen::advanced() const
{
    return m_value + 16;
}

class Rva0013D370AdvanceSixteen
{
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva0013D370AdvanceSixteen::advanced() const
{
    return m_value + 16;
}

class Rva0013D550AdvanceSixteen
{
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva0013D550AdvanceSixteen::advanced() const
{
    return m_value + 16;
}

class Rva0013D590AdvanceSixteen
{
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva0013D590AdvanceSixteen::advanced() const
{
    return m_value + 16;
}
