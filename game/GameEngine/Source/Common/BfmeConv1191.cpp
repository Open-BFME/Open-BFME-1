// cl: /EHsc
// Open-BFME5 conversions.

extern "C" char g_bfmeEmpty1191[];
extern "C" char g_bfmeFmtA1191[];
extern "C" char g_bfmeFmtB1191[];
extern "C" char g_bfmeFmtC1191[];
extern "C" int (__cdecl *g_bfmeFmt1191)(char *dst, const char *fmt, ...);
extern "C" __declspec(dllimport) void * __cdecl fopen(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl fprintf(void *, const char *, ...);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);

class Rva0036CA00Str
{
public:
	Rva0036CA00Str() : m_item(0) {}
	~Rva0036CA00Str();
	void clear();

	void *m_item;
};

class Rva0013A820
{
public:
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	Rva0036CA00Str m_10;
	int m_14;
	int m_18;
	Rva0036CA00Str m_1C;
	Rva0036CA00Str m_20;
	int m_24;
	Rva0036CA00Str m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	Rva0036CA00Str m_3C;
	int m_40;
	Rva0036CA00Str m_44;

	void reset();
};

class BfmeD1191 : public Rva0013A820
{
public:
	BfmeD1191(const char *filename);
	void bfmeDump1191(void);
	char *m_bfme48;
};

BfmeD1191::BfmeD1191(const char *filename)
{
	reset();
	m_bfme48 = (char *)fopen(filename, "w+");
	GetLastError();
	fprintf(m_bfme48, "Thing,Class,Draw,Tag,Model,Verts,Polys,Skel,Anim,Frames,Texture,Width,Height,Depth,TexTotl,File,Line,Desc\n");
}

void BfmeD1191::bfmeDump1191(void)
{
	char *s0 = m_00.m_item != 0 ? (char *)m_00.m_item + 8 : g_bfmeEmpty1191;
	int (__cdecl *fn)(char *dst, const char *fmt, ...) = g_bfmeFmt1191;

	fn(m_bfme48, g_bfmeFmtA1191, s0);
	fn(m_bfme48, g_bfmeFmtA1191, m_04.m_item != 0 ? (char *)m_04.m_item + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtA1191, m_08.m_item != 0 ? (char *)m_08.m_item + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtA1191, m_0C.m_item != 0 ? (char *)m_0C.m_item + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtA1191, m_10.m_item != 0 ? (char *)m_10.m_item + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtB1191, m_14);
	fn(m_bfme48, g_bfmeFmtB1191, m_18);
	fn(m_bfme48, g_bfmeFmtA1191, m_1C.m_item != 0 ? (char *)m_1C.m_item + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtA1191, m_20.m_item != 0 ? (char *)m_20.m_item + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtB1191, m_24);
	fn(m_bfme48, g_bfmeFmtA1191, m_28.m_item != 0 ? (char *)m_28.m_item + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtB1191, m_2C);
	fn(m_bfme48, g_bfmeFmtB1191, m_30);
	fn(m_bfme48, g_bfmeFmtB1191, m_34);
	fn(m_bfme48, g_bfmeFmtB1191, m_38);
	fn(m_bfme48, g_bfmeFmtA1191, m_3C.m_item != 0 ? (char *)m_3C.m_item + 8 : g_bfmeEmpty1191);
	fn(m_bfme48, g_bfmeFmtB1191, m_40);
	fn(m_bfme48, g_bfmeFmtC1191, m_44.m_item != 0 ? (char *)m_44.m_item + 8 : g_bfmeEmpty1191);
}
