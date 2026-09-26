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
    void OnUpdateShowGrid(CCmdUI *pCmdUI);
};

void CWorldBuilderView::OnUpdateShowGrid(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(mShowGrid ? 1 : 0);
    pCmdUI->Enable(m_cellSize >= 4);
}
