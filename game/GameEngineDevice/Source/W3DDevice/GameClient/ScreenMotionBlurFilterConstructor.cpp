// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D8880, the constructor installing ScreenMotionBlurFilter's
// proven vtable 0x01128BD0.  The table's slot map names init/preRender/
// setup/set/reset/shutdown as this class's surrounding methods.

extern int Gen01128BD0;

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
	m_vptr = &Gen01128BD0;
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
