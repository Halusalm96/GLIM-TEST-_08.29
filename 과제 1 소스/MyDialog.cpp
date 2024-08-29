#include "stdafx.h"
#include "MyApp.h"
#include "MyDialog.h"
#include "afxdialogex.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMyDialog::CMyDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MYDIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_X1, m_editX1);
    DDX_Control(pDX, IDC_EDIT_Y1, m_editY1);
    DDX_Control(pDX, IDC_EDIT_X2, m_editX2);
    DDX_Control(pDX, IDC_EDIT_Y2, m_editY2);
}

BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_DRAW, &CMyDialog::OnBnClickedDraw)
    ON_BN_CLICKED(IDC_BUTTON_ACTION, &CMyDialog::OnBnClickedAction)
    ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMyDialog::OnBnClickedOpen)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void CMyDialog::OnBnClickedDraw()
{
    CString strX1, strY1;
    m_editX1.GetWindowTextW(strX1);
    m_editY1.GetWindowTextW(strY1);

    m_x1 = _ttoi(strX1);
    m_y1 = _ttoi(strY1);

    // 랜덤한 반지름 생성
    int radius = rand() % 50 + 10;  // 10 ~ 59 사이의 반지름

    CClientDC dc(this);
    dc.Ellipse(m_x1 - radius, m_y1 - radius, m_x1 + radius, m_y1 + radius);
}

void CMyDialog::OnBnClickedAction()
{
    CString strX1, strY1, strX2, strY2;
    m_editX1.GetWindowTextW(strX1);
    m_editY1.GetWindowTextW(strY1);
    m_editX2.GetWindowTextW(strX2);
    m_editY2.GetWindowTextW(strY2);

    m_x1 = _ttoi(strX1);
    m_y1 = _ttoi(strY1);
    m_x2 = _ttoi(strX2);
    m_y2 = _ttoi(strY2);

    int dx = (m_x2 - m_x1) / 10;
    int dy = (m_y2 - m_y1) / 10;

    for (int i = 0; i <= 10; ++i)
    {
        CClientDC dc(this);
        int x = m_x1 + dx * i;
        int y = m_y1 + dy * i;

        // 랜덤한 반지름 생성
        int radius = rand() % 50 + 10;

        dc.Ellipse(x - radius, y - radius, x + radius, y + radius);

        // 이미지 저장
        CImage image;
        image.Create(400, 400, 24);
        CDC* pDC = CDC::FromHandle(image.GetDC());
        pDC->BitBlt(0, 0, 400, 400, &dc, 0, 0, SRCCOPY);
        image.ReleaseDC();

        CString filename;
        filename.Format(_T("image\\image_%02d.bmp"), i);
        image.Save(filename, Gdiplus::ImageFormatBMP);
    }
}

void CMyDialog::OnBnClickedOpen()
{
    CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Image Files (*.bmp;*.jpg)|*.bmp;*.jpg||"));
    if (dlg.DoModal() == IDOK)
    {
        CString path = dlg.GetPathName();

        CImage image;
        image.Load(path);

        CClientDC dc(this);
        image.Draw(dc.m_hDC, 10, 10);

        // X 표시
        int centerX = 10 + image.GetWidth() / 2;
        int centerY = 10 + image.GetHeight() / 2;
        dc.MoveTo(centerX - 10, centerY - 10);
        dc.LineTo(centerX + 10, centerY + 10);
        dc.MoveTo(centerX + 10, centerY - 10);
        dc.LineTo(centerX - 10, centerY + 10);

        // 좌표값 표시
        CString str;
        str.Format(_T("(%d, %d)"), centerX, centerY);
        dc.TextOutW(centerX + 15, centerY + 15, str);
    }
}

void CMyDialog::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); 
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}