// cl: /DNDEBUG /MD
// ZH twin: IMEManager::resizeCandidateWindow
// Retail 0x0048D060, 210 bytes. Font height at +0x10; line spacing global.

extern int IMECandidateWindowLineSpacing;

class GameFont
{
public:
	char m_pad[0x10];
	int height;
};

class GameWindow
{
public:
	GameFont *winGetFont(void);
	int winGetSize(int *w, int *h);
	int winSetSize(int w, int h);
	int winGetPosition(int *x, int *y);
	int winSetPosition(int x, int y);
};

class IMEManager
{
public:
	void resizeCandidateWindow(int pageSize);

private:
	char m_pad00[0x304C];
	GameWindow *m_candidateWindow;
	GameWindow *m_statusWindow;
	GameWindow *m_candidateTextArea;
	GameWindow *m_candidateUpArrow;
	GameWindow *m_candidateDownArrow;
};

void IMEManager::resizeCandidateWindow(int pageSize)
{
	if (m_candidateWindow == 0)
		return;

	GameFont *font = m_candidateTextArea->winGetFont();
	if (font == 0)
		return;

	int newh = pageSize * (font->height + IMECandidateWindowLineSpacing);
	int w, h;
	m_candidateTextArea->winGetSize(&w, &h);
	int dif = newh - h;
	m_candidateTextArea->winSetSize(w, newh);
	m_candidateWindow->winGetSize(&w, &h);
	h += dif;
	m_candidateWindow->winSetSize(w, h);
	if (m_candidateDownArrow)
	{
		int x, y;
		m_candidateDownArrow->winGetPosition(&x, &y);
		y += dif;
		m_candidateDownArrow->winSetPosition(x, y);
	}
}
