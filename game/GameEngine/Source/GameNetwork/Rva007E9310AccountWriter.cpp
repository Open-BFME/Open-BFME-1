// cl: /O2

class Rva007E8810Message
{
public:
    char m_unknown[0x1C];
    unsigned int m_category;
};
class Rva007E8AC0
{
public:
    void run();
};
class Rva007E8980
{
public:
    void go(int key, unsigned char value);
};
class BfmeThingCIC
{
public:
    void bfmeGoCIC(void *key, void *value);
};
class Rva007E9310Identifier
{
public:
    virtual char *get();
};
class Rva007E9310AccountWriter
{
    void *m_vptr;
    Rva007E9310Identifier m_identifier;
public:
    void write(Rva007E8810Message *message, const char *name,
        const char *password, unsigned char returnEncryptedInfo,
        const char *encryptedInfo);
};
extern const char *g_Rva0130A50CTxn;

void Rva007E9310AccountWriter::write(Rva007E8810Message *message,
    const char *name, const char *password, unsigned char returnEncryptedInfo,
    const char *encryptedInfo)
{
    const char *txn = g_Rva0130A50CTxn;
    ((Rva007E8AC0 *)message)->run();
    message->m_category = 'acct';
    ((BfmeThingCIC *)message)->bfmeGoCIC((void *)"TXN", (void *)txn);
    ((Rva007E8980 *)message)->go((int)"returnEncryptedInfo", returnEncryptedInfo);
    if (encryptedInfo && *encryptedInfo) {
        ((BfmeThingCIC *)message)->bfmeGoCIC((void *)"encryptedInfo", (void *)encryptedInfo);
    } else {
        ((BfmeThingCIC *)message)->bfmeGoCIC((void *)"name", (void *)name);
        ((BfmeThingCIC *)message)->bfmeGoCIC((void *)"password", (void *)password);
    }
    char *identifier = m_identifier.get();
    ((BfmeThingCIC *)message)->bfmeGoCIC((void *)"machineId", (void *)(identifier + 0x183));
    identifier = m_identifier.get();
    ((BfmeThingCIC *)message)->bfmeGoCIC((void *)"macAddr", (void *)(identifier + 0x1E3));
}
