// cl: /DNDEBUG /MD /EHsc
// Distinct scalar accessors whose retail owners remain unproved.
// Evidence: targets/game/reverse/identity_evidence/aiupdate-identity-corrections.md.

// Identity remains unknown; preserve the 13-byte setter body at 0x0045DC60.
class Rva0045DC60Owner {
public:
    void set(unsigned int value);
private:
    unsigned char m_beforeValue[0x1f4];
    unsigned int m_value;
};
void Rva0045DC60Owner::set(unsigned int value) { m_value = value; }

// Identity remains unknown; preserve the 13-byte setter body at 0x007F21F0.
class Rva007F21F0Owner {
public:
    void set(unsigned int value);
private:
    unsigned char m_beforeValue[0x154];
    unsigned int m_value;
};
void Rva007F21F0Owner::set(unsigned int value) { m_value = value; }

// Two distinct seven-byte retail copies, with identities still unknown.
class Rva002B1020Owner {
public: unsigned int get() const;
private: unsigned char m_beforeValue[0x154]; unsigned int m_value;
};
unsigned int Rva002B1020Owner::get() const { return m_value; }

class Rva004A3AA0Owner {
public: unsigned int get() const;
private: unsigned char m_beforeValue[0x154]; unsigned int m_value;
};
unsigned int Rva004A3AA0Owner::get() const { return m_value; }

// Retail 0x0047A250/7 reads receiver+0x1F4. Its AIUpdateInterface
// getAttitude alias is false: proven AI attitude lives at +0x1F8.
class Rva0047A250Owner {
public: unsigned int get() const;
private: unsigned char m_beforeValue[0x1F4]; unsigned int m_value;
};
unsigned int Rva0047A250Owner::get() const { return m_value; }

