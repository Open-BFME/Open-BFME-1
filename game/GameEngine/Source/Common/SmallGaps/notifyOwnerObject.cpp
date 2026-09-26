// ?notifyOwnerObject@@YGXH@Z
class Object;
class GameLogic { public: Object* bfmeFind1011(int id); };
extern GameLogic* TheBfmeGameLogic;
struct Rva002B7240Source { virtual void s0(); virtual int getOwnerID(); };
struct Rva002B7240Module { virtual void s0(); virtual void s1(); virtual void onOwnerFound(); };
Rva002B7240Source* __cdecl Rva002B7240Lookup(int id);
Rva002B7240Module* __cdecl Rva002B7240FindModule(Object* obj);
void __stdcall notifyOwnerObject(int id)
{
	if (!id)
		return;
	Rva002B7240Source* src = Rva002B7240Lookup(id);
	if (!src)
		return;
	Object* owner = TheBfmeGameLogic->bfmeFind1011(src->getOwnerID());
	if (!owner)
		return;
	Rva002B7240Module* m = Rva002B7240FindModule(owner);
	if (!m)
		return;
	m->onOwnerFound();
}
