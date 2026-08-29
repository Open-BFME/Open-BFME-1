// Open-BFME5 conversions.

extern "C" char g_bfmeEmpty1191[];
extern "C" char g_bfmeFmtA1191[];
extern "C" char g_bfmeFmtB1191[];
extern "C" char g_bfmeFmtC1191[];
extern "C" int (__cdecl *g_bfmeFmt1191)(char *dst, const char *fmt, ...);

class BfmeD1191
{
public:
	void bfmeDump1191(void);
	char *m_bfme00;
	char *m_bfme04;
	char *m_bfme08;
	char *m_bfme0c;
	char *m_bfme10;
	int m_bfme14;
	int m_bfme18;
	char *m_bfme1c;
	char *m_bfme20;
	int m_bfme24;
	char *m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	char *m_bfme3c;
	int m_bfme40;
	char *m_bfme44;
	char *m_bfme48;
};

void BfmeD1191::bfmeDump1191(void)
{
	char *s0 = m_bfme00 != 0 ? m_bfme00 + 8 : g_bfmeEmpty1191;
	int (__cdecl *fn)(char *dst, const char *fmt, ...) = g_bfmeFmt1191;

	fn(m_bfme48, g_bfmeFmtA1191, s0);
	fn(m_bfme48, g_bfmeFmtA1191, m_bfme04 != 0 ? m_bfme04 + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtA1191, m_bfme08 != 0 ? m_bfme08 + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtA1191, m_bfme0c != 0 ? m_bfme0c + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtA1191, m_bfme10 != 0 ? m_bfme10 + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtB1191, m_bfme14);
	fn(m_bfme48, g_bfmeFmtB1191, m_bfme18);
	fn(m_bfme48, g_bfmeFmtA1191, m_bfme1c != 0 ? m_bfme1c + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtA1191, m_bfme20 != 0 ? m_bfme20 + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtB1191, m_bfme24);
	fn(m_bfme48, g_bfmeFmtA1191, m_bfme28 != 0 ? m_bfme28 + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtB1191, m_bfme2c);
	fn(m_bfme48, g_bfmeFmtB1191, m_bfme30);
	fn(m_bfme48, g_bfmeFmtB1191, m_bfme34);
	fn(m_bfme48, g_bfmeFmtB1191, m_bfme38);
	fn(m_bfme48, g_bfmeFmtA1191, m_bfme3c != 0 ? m_bfme3c + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtB1191, m_bfme40);
	fn(m_bfme48, g_bfmeFmtC1191, m_bfme44 != 0 ? m_bfme44 + 8 : g_bfmeEmpty1191);
}
