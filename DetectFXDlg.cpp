#include "stdafx.h"
#include "DetectFX.h"
#include "DetectFXDlg.h"
#include "DetectDotNet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDetectFXDlg::CDetectFXDlg(CWnd* pParent)
  : CDialog(CDetectFXDlg::IDD, pParent)
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_pEditBkBrush = new CBrush(RGB(255, 255, 255));
}

void CDetectFXDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_EDIT, m_Edit);
}

BEGIN_MESSAGE_MAP(CDetectFXDlg, CDialog)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_WM_CTLCOLOR()
  ON_WM_DESTROY()
  ON_BN_CLICKED(ID_SAVE, &CDetectFXDlg::OnBnClickedSave)
END_MESSAGE_MAP()

BOOL CDetectFXDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  SetIcon(m_hIcon, TRUE);
  SetIcon(m_hIcon, FALSE);

  CString str = DoDetectDotNet();
  m_Edit.SetWindowText(str);

  return TRUE;
}

void CDetectFXDlg::OnPaint()
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialog::OnPaint();
  }
}

HCURSOR CDetectFXDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CDetectFXDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
  switch (nCtlColor)
  {
  case CTLCOLOR_STATIC:
    pDC->SetTextColor(RGB(0, 0, 0));
    pDC->SetBkColor(RGB(255, 255, 255));
    return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
  default:
    return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
  }
}

void CDetectFXDlg::OnDestroy()
{
  CDialog::OnDestroy();

  // Free the space allocated for the background brush
  delete m_pEditBkBrush;
}

BOOL CDetectFXDlg::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_KEYDOWN)
  {
    if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
    {
      return TRUE;
    }
  }

  return CDialog::PreTranslateMessage(pMsg);
}

void CDetectFXDlg::OnBnClickedSave()
{
  CString strTitle;
  GetWindowText(strTitle);

  CString strPath;
  DWORD dwPath = MAX_PATH + 1;
  SHGetSpecialFolderPath(HWND_DESKTOP, strPath.GetBufferSetLength(dwPath), CSIDL_DESKTOPDIRECTORY, FALSE);
  strPath.ReleaseBuffer();

  CString strComputer;
  DWORD dwComputer = MAX_COMPUTERNAME_LENGTH + 1;
  GetComputerName(strComputer.GetBufferSetLength(dwComputer), &dwComputer);
  strComputer.ReleaseBuffer();

  CTime time = CTime::GetCurrentTime();
  CString strFileName, strTime = time.Format(_T("%b %d, %Y"));
  strFileName.Format(_T("%s - %s - %s"), strTitle, strComputer, strTime);

  CString strExt = _T(".txt");
  CString strFilter = _T("Text Files (*.txt)|*.txt|");
  DWORD dwFlags = OFN_ENABLESIZING | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;

  CFileDialog dlg(FALSE, strExt, strFileName, dwFlags, strFilter, this);
  dlg.m_ofn.lpstrInitialDir = strPath;
  if (dlg.DoModal() != IDOK)
    return;

  CString strFilePath = dlg.GetPathName();
  if (strFilePath.IsEmpty())
    return;

  CString strText;
  m_Edit.GetWindowText(strText);

  FILE* fStream = nullptr;
  errno_t e = _tfopen_s(&fStream, strFilePath, _T("wt,ccs=UTF-8"));
  if (e != 0)
  {
    CString strTitle;
    GetWindowText(strTitle);
    MessageBox(_T("Error saving file"), strTitle, MB_OK | MB_ICONERROR);
    return;
  }

  CStdioFile f(fStream);
  f.WriteString(strText);
  f.Close();
}
