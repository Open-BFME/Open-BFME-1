// ?replayEntries@Rva00367E30Owner@@QAEXPAURva00367E30Sink@@@Z
struct Rva00367E30Logic { char m_pad[0x3c]; int m_frame; };
extern Rva00367E30Logic* TheBfmeGameLogic;
struct Rva00367E30Entry { int m_0; int m_data; int m_frame; int m_c; };
struct Rva00367E30Sink { void apply(int* data, int delta); };
struct Rva00367E30Owner {
	char m_pad[0x20];
	Rva00367E30Entry* m_begin;
	Rva00367E30Entry* m_end;
	void replayEntries(Rva00367E30Sink* sink);
};
void Rva00367E30Owner::replayEntries(Rva00367E30Sink* sink)
{
	if (!sink)
		return;
	for (Rva00367E30Entry* e = m_begin; e != m_end; ++e)
		sink->apply(&e->m_data, e->m_frame - TheBfmeGameLogic->m_frame);
}
