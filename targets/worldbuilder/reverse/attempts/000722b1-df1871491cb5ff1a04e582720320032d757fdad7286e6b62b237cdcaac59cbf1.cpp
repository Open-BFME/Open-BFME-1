#include <afxwin.h>

class CMainFrame : public CFrameWnd
{
protected:
    void OnViewBrushfeedback();
};

// The donor's inline API preserves the static symbol for independent relocation verification.
class DrawObject
{
public:
    static void disableFeedback() { m_disableFeedback = true; }
    static void enableFeedback() { m_disableFeedback = false; }
    static bool isFeedbackEnabled() { return !m_disableFeedback; }

protected:
    static bool m_disableFeedback;
};

void CMainFrame::OnViewBrushfeedback()
{
    if (DrawObject::isFeedbackEnabled()) {
        DrawObject::disableFeedback();
        ::AfxGetApp()->WriteProfileInt("MainFrame", "ShowBrushFeedback", 0);
    } else {
        DrawObject::enableFeedback();
        ::AfxGetApp()->WriteProfileInt("MainFrame", "ShowBrushFeedback", 1);
    }
}
