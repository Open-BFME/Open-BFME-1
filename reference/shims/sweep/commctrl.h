#pragma once
#ifndef SWEEP_COMMCTRL_SHIM_H
#define SWEEP_COMMCTRL_SHIM_H

#define ICC_WIN95_CLASSES 0x000000FF

extern "C" {
__declspec(dllimport) BOOL WINAPI InitCommonControlsEx(void *);
}

#define WC_LISTVIEWA "SysListView32"
#define WC_LISTVIEWW L"SysListView32"

#define LVS_REPORT 1
#define LVS_SINGLESEL 4
#define LVS_SHOWSELALWAYS 8
#define LVS_NOSORTHEADER 0x80000000

#define LVCF_TEXT 1
#define LVCF_WIDTH 2
#define LVCF_FMT 4

#define LVCFMT_LEFT 0
#define LVCFMT_RIGHT 1

#define LVIF_TEXT 1

typedef struct tagLVCOLUMNA {
    UINT mask;
    int fmt;
    int cx;
    LPSTR pszText;
    int cchTextMax;
    int iSubItem;
    int iImage;
    int iOrder;
} LVCOLUMNA, *LPLVCOLUMNA;
#define LVCOLUMN LVCOLUMNA

typedef struct tagLVITEMA {
    UINT mask;
    int iItem;
    int iSubItem;
    UINT state;
    UINT stateMask;
    LPSTR pszText;
    int cchTextMax;
    int iImage;
    LPARAM lParam;
    int iIndent;
} LVITEMA, *LPLVITEMA;
#define LVITEM LVITEMA

#define LVM_FIRST 0x1000
#define LVM_INSERTCOLUMN (LVM_FIRST + 27)
#define LVM_SETCOLUMN (LVM_FIRST + 26)
#define LVM_INSERTITEM (LVM_FIRST + 7)
#define LVM_SETITEM (LVM_FIRST + 6)
#define LVM_SETITEMTEXT (LVM_FIRST + 46)
#define LVM_GETITEMCOUNT (LVM_FIRST + 4)

#define ListView_InsertColumn(hwnd, iCol, pcol) \
    (int)SendMessageA((hwnd), LVM_INSERTCOLUMN, (WPARAM)(int)(iCol), (LPARAM)(const LVCOLUMNA *)(pcol))
#define ListView_InsertItem(hwnd, pitem) \
    (int)SendMessageA((hwnd), LVM_INSERTITEM, 0, (LPARAM)(const LVITEMA *)(pitem))

#endif
