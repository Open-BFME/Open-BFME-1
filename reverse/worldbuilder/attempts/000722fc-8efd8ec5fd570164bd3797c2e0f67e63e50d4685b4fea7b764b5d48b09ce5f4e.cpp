#include <afxwin.h>

class CMainFrame : public CFrameWnd
{
protected:
    void OnUpdateViewBrushfeedback(CCmdUI *pCmdUI);
};

// The donor's inline API preserves the static symbol for independent relocation verification.
class DrawObject
{
public:
    static bool isFeedbackEnabled() { return !m_disableFeedback; }

protected:
    static bool m_disableFeedback;
};

void CMainFrame::OnUpdateViewBrushfeedback(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(DrawObject::isFeedbackEnabled() ? 1 : 0);
}
