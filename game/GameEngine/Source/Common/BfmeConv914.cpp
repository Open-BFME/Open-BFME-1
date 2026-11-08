// Open-BFME5 conversions.

extern void *g_bfme914A;
extern void *g_bfme914B;
class ScreenBWFilter
{
protected:
	static int m_curFadeFrame;
	friend int bfmeGo914A();
};
extern void *g_bfme914Ptr;
extern char g_bfme914Obj[];
int bfmeTest914A(void);

int bfmeGo914A(void)
{
	ScreenBWFilter::m_curFadeFrame = 0;
	if (g_bfme914A && g_bfme914B && bfmeTest914A()) {
		g_bfme914Ptr = g_bfme914Obj;
		return 1;
	}
	return 0;
}
