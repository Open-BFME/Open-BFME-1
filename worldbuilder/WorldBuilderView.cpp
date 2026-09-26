#include <afxwin.h>

// The MFC class record gives 0x13c bytes; retain unnamed storage until more handlers establish its fields.
class CWorldBuilderView
{
    unsigned char m_unrecovered_000[0x11c];
    int m_cellSize;
    unsigned char m_unrecovered_120;
    bool m_showTexture;
    bool mShowGrid;
    unsigned char m_unrecovered_123[0x19];

protected:
    void OnShowGrid();
    void OnViewShowtexture();
    void OnUpdateViewShowtexture(CCmdUI *pCmdUI);
    void OnUpdateShowGrid(CCmdUI *pCmdUI);
};

void CWorldBuilderView::OnUpdateShowGrid(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(mShowGrid ? 1 : 0);
    pCmdUI->Enable(m_cellSize >= 4);
}

void CWorldBuilderView::OnShowGrid()
{
    mShowGrid = !mShowGrid;
    AfxGetApp()->WriteProfileInt("MainFrame", "ShowGrid", mShowGrid ? 1 : 0);
    reinterpret_cast<CWnd *>(this)->Invalidate(false);
}

void CWorldBuilderView::OnViewShowtexture()
{
    m_showTexture = !m_showTexture;
    AfxGetApp()->WriteProfileInt("MainFrame", "ShowTexture", m_showTexture ? 1 : 0);
    reinterpret_cast<CWnd *>(this)->Invalidate(false);
}

void CWorldBuilderView::OnUpdateViewShowtexture(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_showTexture ? 1 : 0);
}
