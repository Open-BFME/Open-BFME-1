// cl: /O2 /MD
// Five cdecl message callbacks no row claimed, each referenced only by the
// code that registers it: (message, owner) -> owner->handler(message). The
// handlers are matched members taking Rva007E8810Message *; the callbacks
// keep address-derived names.

class Rva007E8810Message;

class Rva007F45E0Aries { public: void rva007F4530(Rva007E8810Message *); };
class Rva007F66B0Browser { public: void onLobbyCounts(Rva007E8810Message *); };
class BfmeThingZI
{
public:
	void rva007F7640(Rva007E8810Message *);
	void rva007F7DA0(Rva007E8810Message *);
};
class BfmeHostBT { public: void Rva007F7C70(Rva007E8810Message *); };

void Rva007F4520Callback(Rva007E8810Message *message, Rva007F45E0Aries *owner) { owner->rva007F4530(message); }
class Rva007F6740Receiver;
void Rva007F6730Callback(Rva007E8810Message *message, Rva007F6740Receiver *owner) { ((Rva007F66B0Browser *)owner)->onLobbyCounts(message); }
void Rva007F7970Callback(Rva007E8810Message *message, BfmeThingZI *owner) { owner->rva007F7640(message); }
void Rva007F83E0Callback(Rva007E8810Message *message, BfmeThingZI *owner) { owner->rva007F7DA0(message); }
void Rva007F83F0Callback(Rva007E8810Message *message, BfmeHostBT *owner) { owner->Rva007F7C70(message); }
