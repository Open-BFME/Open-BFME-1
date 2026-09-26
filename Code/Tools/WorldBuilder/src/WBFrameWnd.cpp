#include <afxwin.h>

class CWB3dFrameWnd
{
    unsigned char m_unrecovered_0000[0x2840];
    int m_3dViewWidth;
    int m_field_2844;

protected:
    void OnUpdateWindowPreview1024x768(CCmdUI *pCmdUI);
    void OnUpdateWindowPreview640x480(CCmdUI *pCmdUI);
};

void CWB3dFrameWnd::OnUpdateWindowPreview1024x768(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_3dViewWidth == 1024 && m_field_2844 == 768);
}

void CWB3dFrameWnd::OnUpdateWindowPreview640x480(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_3dViewWidth == 640 && m_field_2844 == 480);
}
