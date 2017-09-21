#include "stdafx.h"
#include "DetectFX.h"
#include "DetectFXDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CDetectFXApp, CWinApp)
  ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CDetectFXApp::CDetectFXApp()
{
}

// The one and only CDetectFXApp object
static class CDetectFXApp theApp;

BOOL CDetectFXApp::InitInstance()
{
  INITCOMMONCONTROLSEX iccex;
  memset(&iccex, 0, sizeof(INITCOMMONCONTROLSEX));
  iccex.dwSize = sizeof(iccex);
  iccex.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx(&iccex);

  CWinApp::InitInstance();

  CDetectFXDlg dlg;
  m_pMainWnd = &dlg;
  dlg.DoModal();

  return FALSE;
}

