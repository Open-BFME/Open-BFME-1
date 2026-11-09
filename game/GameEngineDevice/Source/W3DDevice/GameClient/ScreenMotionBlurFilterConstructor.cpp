// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D8880, the constructor installing ScreenMotionBlurFilter's
// proven vtable 0x01128BD0.  The table's slot map names init/preRender/
// setup/set/reset/shutdown as this class's surrounding methods.

void j_00022a07();
void j_00045133();
void j_00044e4f();
void j_000044ad();
void j_0004024b();
void j_0004838d();
void j_00028556();

// Retail VA 0x01128BD0: seven existing ILT entries (vtable_lookup.py), the
// vftable installed by the ScreenMotionBlurFilter constructor.
void *g_ScreenMotionBlurFilterVftable[7] = {
	reinterpret_cast<void *>(&j_00022a07),
	reinterpret_cast<void *>(&j_00045133),
	reinterpret_cast<void *>(&j_00044e4f),
	reinterpret_cast<void *>(&j_000044ad),
	reinterpret_cast<void *>(&j_0004024b),
	reinterpret_cast<void *>(&j_0004838d),
	reinterpret_cast<void *>(&j_00028556),
};

class ScreenMotionBlurFilter
{
public:
	ScreenMotionBlurFilter();

	int *m_vptr;
	int m_maxCount;
	int m_lastFrame;
	char m_decrement;
	char m_skipRender;
	char m_additive;
	char m_doZoomTo;
	int m_priorDeltaX;
	int m_priorDeltaY;
	int m_panFactor;
};

// ??0ScreenMotionBlurFilter@@QAE@XZ
ScreenMotionBlurFilter::ScreenMotionBlurFilter()
{
	m_vptr = reinterpret_cast<int *>(g_ScreenMotionBlurFilterVftable);
	m_maxCount = 0;
	m_lastFrame = 0;
	m_decrement = 0;
	m_skipRender = 0;
	m_additive = 0;
	m_doZoomTo = 0;
	m_priorDeltaX = 0;
	m_priorDeltaY = 0;
	m_panFactor = 0;
}
