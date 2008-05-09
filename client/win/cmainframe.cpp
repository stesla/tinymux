#include "stdafx.h"

LRESULT CALLBACK CMainFrame::MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRes = 0;
    CMainFrame *pWnd = (CMainFrame *)GetWindowPointer(hWnd);
    switch (message)
    {
    case WM_CREATE:
        {
            CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
            lRes = pWnd->OnCreate(pcs);
        }
        break;

    case WM_COMMAND:
        lRes = pWnd->OnCommand(wParam, lParam);
        break;

    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;

    case WM_NCDESTROY:
        {
            if (NULL != pWnd->m_pMDIControl)
            {
                lRes = pWnd->m_pMDIControl->DefaultMDIFrameHandler(message, wParam, lParam);
            }
            else
            {
                lRes = pWnd->DefaultWindowHandler(message, wParam, lParam);
            }
            (void)Detach(hWnd);
            delete pWnd;
            pWnd = NULL;
        }
        break;

    default:
        if (NULL != pWnd->m_pMDIControl)
        {
            lRes = pWnd->m_pMDIControl->DefaultMDIFrameHandler(message, wParam, lParam);
        }
        else
        {
            lRes = pWnd->DefaultWindowHandler(message, wParam, lParam);
        }
        break;
   }
   return lRes;
}

void CMainFrame::IncreaseDecreaseSessionCount(bool bIncrease)
{
    if (bIncrease)
    {
        if (0 == m_nChildren)
        {
            EnableDisableCloseItem(true);
        }
        m_nChildren++;
    }
    else
    {
        m_nChildren--;
        if (0 == m_nChildren)
        {
            EnableDisableCloseItem(false);
        }
    }
}

LRESULT CMainFrame::EnableDisableCloseItem(bool bActivate)
{
    HMENU hMenu = ::GetMenu(m_hwnd);

    UINT EnableFlag;
    if (bActivate)
    {
        EnableFlag = MF_ENABLED;
    }
    else
    {
        EnableFlag = MF_GRAYED;
    }

    EnableMenuItem(hMenu, 1, MF_BYPOSITION | EnableFlag);

    HMENU hFileMenu = ::GetSubMenu(hMenu, 0);

    ::EnableMenuItem(hFileMenu, IDM_FILE_CLOSE, MF_BYCOMMAND | EnableFlag);
    ::EnableMenuItem(hFileMenu, IDM_WINDOW_CLOSE_ALL, MF_BYCOMMAND | EnableFlag);

    DrawMenuBar();
    return 0;
}

LRESULT CMainFrame::OnCreate(CREATESTRUCT *pcs)
{
    EnableDisableCloseItem(false);

    // Create MDI Child Control.
    //
    CLIENTCREATESTRUCT ccs;
    memset(&ccs, 0, sizeof(ccs));
    ccs.hWindowMenu = ::GetSubMenu(GetMenu(m_hwnd), 1);
    ccs.idFirstChild = StartChildren;

    CMDIControl *pMDIControl = NULL;
    try
    {
        pMDIControl = new CMDIControl(this, &ccs, pcs);
    }
    catch (...)
    {
        ; // Nothing.
    }

    if (NULL != pMDIControl)
    {
        m_pMDIControl = pMDIControl;
    }
    return 0;
}

// Mesage handler for about box.
//
LRESULT CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        if (  IDOK     == LOWORD(wParam)
           || IDCANCEL == LOWORD(wParam))
        {
            ::EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}

LRESULT CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
    // Parse the menu selections:
    //
    int wmId    = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);
    switch (wmId)
    {
    case IDM_FILE_NEW:
        (void)m_pMDIControl->CreateNewChild();
        break;

    case IDM_FILE_CLOSE:
        {
            CWindow *pChild = m_pMDIControl->GetActive();
            if (NULL != pChild)
            {
                pChild->SendMessage(WM_CLOSE, 0, 0);
            }
        }
        break;

    case IDM_ABOUT:
        DialogBox(g_theApp.m_hInstance, (LPCTSTR)IDD_ABOUTBOX, m_hwnd, (DLGPROC)AboutProc);
        break;

    case IDM_EXIT:
        DestroyWindow(m_hwnd);
        break;

    case IDM_WINDOW_TILE:
        m_pMDIControl->Tile();
        break;

    case IDM_WINDOW_CASCADE:
        m_pMDIControl->Cascade();
        break;

    case IDM_WINDOW_ARRANGE:
        m_pMDIControl->IconArrange();
        break;

    case IDM_WINDOW_CLOSE_ALL:
        {
            CWindow *pChild = NULL;

            do {
                pChild = m_pMDIControl->GetActive();
                if (NULL != pChild)
                {
                    pChild->SendMessage(WM_CLOSE, 0, 0);
                }
            } while (NULL != pChild);
        }
        break;

    default:
        if (StartChildren <= wmId)
        {
            return m_pMDIControl->DefaultMDIFrameHandler(WM_COMMAND, wParam, lParam);
        }
        else
        {
            CWindow *pChild = m_pMDIControl->GetActive();
            if (NULL != pChild)
            {
                pChild->SendMessage(WM_CLOSE, 0, 0);
            }
        }
    }
    return 0;
}

CMainFrame::CMainFrame()
{
    m_pMDIControl = NULL;
    m_nChildren   = 0;
}

CMainFrame::~CMainFrame()
{
    delete m_pMDIControl;
    m_pMDIControl = NULL;
    m_nChildren   = 0;
}

bool CMainFrame::Create(void)
{
    // Create Main Frame Window.
    //
    WCHAR szTitle[MAX_LOADSTRING];
    g_theApp.LoadString(IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

    int xSize = ::GetSystemMetrics(SM_CXSCREEN);
    int ySize = ::GetSystemMetrics(SM_CYSCREEN);
    int cx = (9*xSize)/10;
    int cy = (9*ySize)/10;

    CreateParams cp;
    cp.pWindow = this;
    cp.pParentWindow = NULL;
    g_theApp.m_pTemp = this;
    HWND hWnd = ::CreateWindowEx(0L, g_theApp.m_szMainClass, szTitle,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        (xSize - cx)/2, (ySize - cy)/2, cx, cy,
        NULL, NULL, g_theApp.m_hInstance, &cp);

    if (NULL == hWnd)
    {
        return false;
    }
    return true;
}
