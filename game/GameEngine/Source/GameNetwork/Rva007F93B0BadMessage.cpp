struct Rva00800E50Header;
void Rva007F91D0(Rva00800E50Header *message, const char *tag);

class Rva007F93B0Logger
{
public:
    void reportBadMessage(Rva00800E50Header *message);
};

void Rva007F93B0Logger::reportBadMessage(Rva00800E50Header *message)
{
    Rva007F91D0(message, "<-[bad]");
}
