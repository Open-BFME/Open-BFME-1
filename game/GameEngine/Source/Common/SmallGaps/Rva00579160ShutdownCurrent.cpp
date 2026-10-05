// ?shutdownCurrent@Rva00579160Owner@@QAEXH@Z
struct Rva00579160Sub { virtual void s0(); virtual void s1(); virtual void s2(); virtual void shutdown(); };
struct Rva00579160Part { virtual void release(int flag); };
struct Rva00579160Current { char m_pad[0x58]; Rva00579160Part m_part; };
struct Rva00579160Manager { void notify(); };
class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;
class BfmeAptScreenSkirmish;
extern BfmeAptScreenSkirmish *Rva012F4B54Skirmish;
// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager* g_rva012F19E8WindowManager;
struct Rva00579160Owner {
	char m_pad[0x3ac];
	Rva00579160Sub m_sub;
	void shutdownCurrent(int unused);
};
void Rva00579160Owner::shutdownCurrent(int unused)
{
	m_sub.shutdown();
	if (TheSkirmishGameInfo)
		reinterpret_cast<Rva00579160Current *>(TheSkirmishGameInfo)->m_part.release(1);
	TheSkirmishGameInfo = 0;
	if (reinterpret_cast<int &>(Rva012F4B54Skirmish))
		((Rva00579160Manager*)g_rva012F19E8WindowManager)->notify();
}
