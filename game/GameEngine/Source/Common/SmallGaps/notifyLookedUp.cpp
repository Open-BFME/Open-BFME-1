// ?notifyLookedUp@@YAXPAURva0020AA00Owner@@HH@Z
struct Rva0020AA00Target { void notify(int a, int b); };
struct Rva0020AA00Registry { Rva0020AA00Target* lookup(const int& id); };
extern Rva0020AA00Registry* Rva0020AA00TheRegistry;
struct Rva0020AA00Owner { char m_pad[0x20]; int* m_begin; int* m_end; };
void notifyLookedUp(Rva0020AA00Owner* owner, int a, int b)
{
	for (int* it = owner->m_begin; it != owner->m_end; ++it) {
		Rva0020AA00Target* t = Rva0020AA00TheRegistry->lookup(*it);
		if (t)
			t->notify(a, b);
	}
}
