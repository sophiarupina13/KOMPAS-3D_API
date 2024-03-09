#pragma once
#include <afxcview.h>

// Просмотр CMyTreeView
class Clab1Doc;

class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView)

protected:
	CMyTreeView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CMyTreeView();

public:
	Clab1Doc* m_pDoc;

	//HTREEITEM m_sborka, m_gnezdo, m_gayka1, m_gayka2, m_shayba;
	HTREEITEM m_isp1, m_isp2;

	void FillTree();

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


