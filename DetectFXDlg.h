#pragma once
#include "afxwin.h"

class CDetectFXDlg : public CDialog
{
public:
	CDetectFXDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_DETECTFX_DIALOG };
  CEdit m_Edit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg void OnDestroy();
  BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

protected:
	HICON m_hIcon;
  CBrush* m_pEditBkBrush;
public:
  afx_msg void OnBnClickedSave();
};
