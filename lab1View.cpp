// lab1View.cpp: реализация класса Clab1View
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "lab1.h"
#endif

#include "lab1Doc.h"
#include "lab1View.h"
#include "Resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#include "MainFrm.h"
#include "afxdialogex.h"
#include "CSborkaDialog.h"
#include "afxdialogex.h"
#include "math.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\ksConstants3D.h"
#import "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\lib\kAPI5.tlb"
#include <atlsafe.h>
#include <comutil.h>
#include <propkey.h>
#endif


#pragma once
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace Kompas6API5;
extern KompasObjectPtr pKompasApp5;
extern ksPartPtr pPart;
extern ksDocument3DPtr pDoc;

#include "CMyTreeView.h"

// Clab1View

IMPLEMENT_DYNCREATE(Clab1View, CView)

BEGIN_MESSAGE_MAP(Clab1View, CView)
    // Стандартные команды печати
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение Clab1View

Clab1View::Clab1View() noexcept
{
    // TODO: добавьте код создания

}

Clab1View::~Clab1View()
{
}

BOOL Clab1View::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: изменить класс Window или стили посредством изменения
    //  CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}


// Рисование Clab1View

void Clab1View::OnDraw(CDC* pDC/*, int opt*/)
{
    Clab1Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    CRect rect;
    GetWindowRect(&rect);

    if (pDoc->isp1) {
        CImage image;
        image.Load(_T("C://Users//sophia//Desktop//lab1//lab1//res//isp1.png"));
        image.Draw(pDC->m_hDC, 0, 0);
        CSborkaDialog dlg;
        dlg.DoModal();
    }

    if (pDoc->isp2) {
        CImage image;
        image.Load(_T("C://Users//sophia//Desktop//lab1//lab1//res//isp2.png"));
        image.Draw(pDC->m_hDC, 0, 0);
        CSborkaDialog dlg;
        dlg.DoModal();
    }
}


// Печать Clab1View

BOOL Clab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
    // подготовка по умолчанию
    return DoPreparePrinting(pInfo);
}

void Clab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: добавьте дополнительную инициализацию перед печатью
}

void Clab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: добавьте очистку после печати
}


// Диагностика Clab1View

#ifdef _DEBUG
void Clab1View::AssertValid() const
{
    CView::AssertValid();
}

void Clab1View::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

Clab1Doc* Clab1View::GetDocument() const // встроена неотлаженная версия
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab1Doc)));
    return (Clab1Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений Clab1View

void Clab1View::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: добавьте свой код обработчика сообщений или вызов стандартного

    ClientToScreen(&point);

    CCmdUI state;

    CMenu* pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(3);

    state.m_pMenu = pMenu;
    state.m_nIndexMax = pMenu->GetMenuItemCount();

    for (UINT i = 0; i < state.m_nIndexMax; i++) {

        state.m_nIndex = i;
        state.m_nID = pMenu->GetMenuItemID(i);
        state.DoUpdate(this, FALSE);

    }

    pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

    CView::OnRButtonDown(nFlags, point);
}



