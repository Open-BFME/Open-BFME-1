// cl: /O2 /Ob0 /DNDEBUG /MD
// Five cdecl callback entries, each 15 bytes ending RET then INT3.
// Their starts are 007F6FE0, 007F6FF0, 007F7000, 007F7010, 007F7020.
// Each forwards its first argument to a thiscall target with its second
// argument as ECX. Callee names are resolved from the retail call operands.
class Rva007E8810Message;
class Rva007F7980Browser {
public:
    void onGame(Rva007E8810Message *);
    void onPlayer(Rva007E8810Message *);
    void rva007f63f0(void *message);
};
class BfmeDictESI;
class BfmeHostESI { public: void bfmeApplyESI(BfmeDictESI *); };
class BfmeThingVJK { public: void bfmeGoVJK(int); };

void Rva007F6FE0(Rva007E8810Message *message, Rva007F7980Browser *browser)
{
    browser->onGame(message);
}
void Rva007F6FF0(Rva007E8810Message *message, Rva007F7980Browser *browser)
{
    browser->onPlayer(message);
}
void Rva007F7000(void *message, Rva007F7980Browser *browser)
{
    browser->rva007f63f0(message);
}
void Rva007F7010(BfmeDictESI *message, BfmeHostESI *browser)
{
    browser->bfmeApplyESI(message);
}
void Rva007F7020(int message, BfmeThingVJK *browser)
{
    browser->bfmeGoVJK(message);
}
