#pragma once
#include "afxdialogex.h"


// Диалоговое окно CSborkaDialog

class Clab1Doc;

class CSborkaDialog : public CDialog
{
	DECLARE_DYNAMIC(CSborkaDialog)

public:
	CSborkaDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CSborkaDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSborkaDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	HICON m_hIcon;
	CComboBox SCRO;
	CEdit D;
	CEdit d;
	CEdit D1;
	CEdit d1;
	CEdit L;
	CEdit D2;
	CEdit d2;
	CEdit l;
	CEdit l1;
	CEdit l2;
	CEdit D3;
	CEdit d3;
	CEdit S;
	CEdit S1;
	CEdit Step;
};
