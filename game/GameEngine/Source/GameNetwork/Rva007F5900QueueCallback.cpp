class Rva007E8810Message;
class BfmeOwnerYA;
class Rva007F5840Owner
{
public:
    void handleQueueReply(Rva007E8810Message *message, BfmeOwnerYA *result);
};

struct Rva007F5900Context
{
    unsigned int m_unknown;
    Rva007F5840Owner *m_owner;
};

void __cdecl rva007F5900QueueCallback(Rva007E8810Message *message,
                                      Rva007F5900Context *context)
{
    context->m_owner->handleQueueReply(message, reinterpret_cast<BfmeOwnerYA *>(context));
}
