#pragma once

#include "afxwin.h"

class CMyDialog : public CDialogEx
{
public:
    CMyDialog(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MYDIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    HICON m_hIcon;

    CEdit m_editX1;
    CEdit m_editY1;
    CEdit m_editX2;
    CEdit m_editY2;

    int m_x1, m_y1, m_x2, m_y2;

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedDraw();
    afx_msg void OnBnClickedAction();
    afx_msg void OnBnClickedOpen();
    afx_msg void OnPaint();
};