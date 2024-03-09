// CMyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "lab1.h"
#include "CMyTreeView.h"
#include "lab1Doc.h"
#include "lab1View.h"


// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	//ON_NOTIFY_REFLECT(NM_DBLCLK, &CMyTreeView::OnNMDblclk)
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}

void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_isp2 = tree.InsertItem(L"Исполнение 2", -1, -1, NULL, TVI_FIRST);
	m_isp1 = tree.InsertItem(L"Исполнение 1", -1, -1, NULL, TVI_FIRST);


	tree.SetCheck(m_isp1, m_pDoc->isp1);
	tree.SetCheck(m_isp2, m_pDoc->isp2);

	tree.Expand(m_isp1, TVE_EXPAND);
	tree.Expand(m_isp2, TVE_EXPAND);

}


void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();

	CRect rc;

	tree.GetItemRect(m_isp1, &rc, false);
	if (rc.PtInRect(point))
	{
		m_pDoc->isp1 = true;
		m_pDoc->isp2 = false;
		tree.SelectItem(m_isp1);
	}
	tree.GetItemRect(m_isp2, &rc, false);
	if (rc.PtInRect(point))
	{
		m_pDoc->isp2 = true;
		m_pDoc->isp1 = false;
		tree.SelectItem(m_isp2);
	}


	m_pDoc->pView->Invalidate();
}

