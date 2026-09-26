class Rva007E8810Message;

class Rva007FBC30GameKey
{
public:
    explicit Rva007FBC30GameKey(Rva007E8810Message *message);
    int m_lid;
    int m_gid;
};

class Rva007F51B0GameKeyRecord : public Rva007FBC30GameKey
{
public:
    explicit Rva007F51B0GameKeyRecord(Rva007E8810Message *message);
};

Rva007F51B0GameKeyRecord::Rva007F51B0GameKeyRecord(Rva007E8810Message *message)
    : Rva007FBC30GameKey(message)
{
}
