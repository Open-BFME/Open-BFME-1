class Rva007E9FC0Owner
{
public:
    void begin(int count, void *peer);
};
class Rva007EA320Owner
{
public:
    void bind(void *first, void *second);
};
class Rva007EA380Owner
{
public:
    void bind(void *first, void *second);
};

void __cdecl rva007EAC10BeginCallback(Rva007E9FC0Owner *owner, int count, void *peer)
{
    owner->begin(count, peer);
}

void __cdecl rva007EAD10BindCallback(Rva007EA320Owner *owner, void *first, void *second)
{
    owner->bind(first, second);
}

void __cdecl rva007EADA0BindCallback(Rva007EA380Owner *owner, void *first, void *second)
{
    owner->bind(first, second);
}
