// ?shutdownCurrent@Rva00579160Owner@@QAEXH@Z
struct Rva00579160Sub { virtual void s0(); virtual void s1(); virtual void s2(); virtual void shutdown(); };
struct Rva00579160Part { virtual void release(int flag); };
struct Rva00579160Current { char m_pad[0x58]; Rva00579160Part m_part; };
struct Rva00579160Manager { void notify(); };
extern Rva00579160Current* Rva00579160TheCurrent;
extern int Rva00579160Flag;
extern Rva00579160Manager* Rva00579160TheManager;
struct Rva00579160Owner {
	char m_pad[0x3ac];
	Rva00579160Sub m_sub;
	void shutdownCurrent(int unused);
};
void Rva00579160Owner::shutdownCurrent(int unused)
{
	m_sub.shutdown();
	if (Rva00579160TheCurrent)
		Rva00579160TheCurrent->m_part.release(1);
	Rva00579160TheCurrent = 0;
	if (Rva00579160Flag)
		Rva00579160TheManager->notify();
}
