// CSborkaDialog.cpp: файл реализации
//

#include "pch.h"
#include "lab1.h"
#include "afxdialogex.h"
#include "CSborkaDialog.h"
#ifndef SHARED_HANDLERS
#include "lab1.h"
#include "resource.h"	
#include "lab1Doc.h"
#include "lab1View.h"
#include "MainFrm.h"
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
KompasObjectPtr pKompasApp5;
ksPartPtr pPart;
ksDocument3DPtr pDoc;

#include "CMyTreeView.h"

// Диалоговое окно CSborkaDialog

IMPLEMENT_DYNAMIC(CSborkaDialog, CDialog)

CSborkaDialog::CSborkaDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CSborkaDialog, pParent)
{

}

CSborkaDialog::~CSborkaDialog()
{
}

void CSborkaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, SCRO);
	DDX_Control(pDX, IDC_EDIT1, D);
	DDX_Control(pDX, IDC_EDIT2, d);
	DDX_Control(pDX, IDC_EDIT4, D1);
	DDX_Control(pDX, IDC_EDIT5, d1);
	DDX_Control(pDX, IDC_EDIT3, L);
	DDX_Control(pDX, IDC_EDIT7, D2);
	DDX_Control(pDX, IDC_EDIT8, d2);
	DDX_Control(pDX, IDC_EDIT9, l);
	DDX_Control(pDX, IDC_EDIT10, l1);
	DDX_Control(pDX, IDC_EDIT11, l2);
	DDX_Control(pDX, IDC_EDIT12, D3);
	DDX_Control(pDX, IDC_EDIT13, d3);
	DDX_Control(pDX, IDC_EDIT14, S);
	DDX_Control(pDX, IDC_EDIT15, S1);
	DDX_Control(pDX, IDC_EDIT16, Step);
}


BEGIN_MESSAGE_MAP(CSborkaDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CSborkaDialog::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSborkaDialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// Обработчики сообщений CSborkaDialog


void CSborkaDialog::OnBnClickedButton2()
{

	CString strD, strd, strD1, strd1, strL, strD2, strd2, strl, strl1, strl2, strD3, strd3, strS, strS1, strStep;
	D.GetWindowText(strD);
	d.GetWindowText(strd);
	D1.GetWindowText(strD1);
	d1.GetWindowText(strd1);
	L.GetWindowText(strL);
	D2.GetWindowText(strD2);
	d2.GetWindowText(strd2);
	l.GetWindowText(strl);
	l1.GetWindowText(strl1);
	l2.GetWindowText(strl2);
	D3.GetWindowText(strD3);
	d3.GetWindowText(strd3);
	S.GetWindowText(strS);
	S1.GetWindowText(strS1);
	Step.GetWindowText(strStep);

	double D = _wtof(strD);
	double d = _wtof(strd);
	double D1 = _wtof(strD1);
	double d1 = _wtof(strd1);
	double L = _wtof(strL);
	double D2 = _wtof(strD2);
	double d2 = _wtof(strd2);
	double l = _wtof(strl);
	double l1 = _wtof(strl1);
	double l2 = _wtof(strl2);
	double D3 = _wtof(strD3);
	double d3 = _wtof(strd3);
	double S = _wtof(strS);
	double S1 = _wtof(strS1);
	double Step = _wtof(strStep);

	BeginWaitCursor();

	CComPtr<IUnknown> pKompasAppUnk = nullptr;//CComPtr - универсальный указатель на любой интерфейс любого сервера
	//IUnknown для первичного подключения
	if (!pKompasApp5)//проверка повторное ли подключение кнопки
	{
		// Получаем CLSID для Компас(айдишник короче получаем от системы) который нужен для запуска
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);//запуск, если еще не запущен
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);//получем указатель на компасобджект
		if (FAILED(hRes)) {
			return;
		}
	}

	// делаем Компас видимым
	pKompasApp5->Visible = true;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////// ГНЕЗДО (nest) ///////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//создание документа
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	//эскиз общий
	ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch);//эскиз для 3д детали
	ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));//устанавливаем плоскость эскизу
	pSketch->Create();//открываем на редактирование
	ksDocument2DPtr p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования

	//массив для точек в эскизе
	double point[8][2];
	point[0][0] = 0;
	point[0][1] = d2/ 2;
	point[1][0] = 0;
	point[1][1] = D2 / 2;
	point[2][0] = l;
	point[2][1] = D2 / 2;
	point[3][0] = l;
	point[3][1] = D1 / 2;
	point[4][0] = l2;
	point[4][1] = D1 / 2;
	point[5][0] = l2;
	point[5][1] = 2;
	point[6][0] = l - 2;
	point[6][1] = 2;
	point[7][0] = l - 2;
	point[7][1] = d2 / 2;


	//соединяю точки
	p2DDoc->ksLineSeg(point[0][0], point[0][1], point[1][0], point[1][1], 1);
	p2DDoc->ksLineSeg(point[1][0], point[1][1], point[2][0], point[2][1], 1);
	p2DDoc->ksLineSeg(point[2][0], point[2][1], point[3][0], point[3][1], 1);
	p2DDoc->ksLineSeg(point[3][0], point[3][1], point[4][0], point[4][1], 1);
	p2DDoc->ksLineSeg(point[4][0], point[4][1], point[5][0], point[5][1], 1);
	p2DDoc->ksLineSeg(point[5][0], point[5][1], point[6][0], point[6][1], 1);

	p2DDoc->ksLineSeg(point[6][0], point[6][1], point[7][0], point[7][1], 1);
	p2DDoc->ksLineSeg(point[7][0], point[7][1], point[0][0], point[0][1], 1);

	p2DDoc->ksLineSeg(0, 0, l2, 0, 3);//рисую осевую

	pSketchDef->EndEdit();//закрыли эскиз

	//выдавливаю эскиз вращением
	ksEntityPtr pRotate = pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotDef = pRotate->GetDefinition();
	pRotDef->SetSketch(pSketch);
	pRotDef->SetSideParam(TRUE, 360);
	pRotate->Create();//создали


	//эскиз под малое отверстие
	ksEntityPtr pSketch8 = pPart->NewEntity(o3d_sketch);//эскиз для 3д детали
	pSketchDef = pSketch8->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));//устанавливаем плоскость эскизу
	pSketch8->Create();//открываем на редактирование
	p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования

	p2DDoc->ksCircle(0, 0, d1 / 2, 1);//рисую круг

	pSketchDef->EndEdit();//закрыл эскиз

	//вырезаю отверстие
	ksEntityPtr pExtrude6 = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pExDef7 = pExtrude6->GetDefinition();
	pExDef7->directionType = dtNormal;
	pExDef7->SetSketch(pSketch8);
	pExDef7->SetSideParam(true, etThroughAll, 0, 0, false);

	pExtrude6->Create();

	//фаска
	ksEntityCollectionPtr fledges = pPart->EntityCollection(o3d_edge);//создаем коллекцию граней

	ksEntityPtr pChamfer = pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamferDef = pChamfer->GetDefinition();
	pChamferDef->SetChamferParam(true, 1.5, 1.5);

	ksEntityCollectionPtr fl = pChamferDef->array();

	fl->Clear();

	for (int i = 0; i < fledges->GetCount(); i++)//цикл по всем граням
	{
		ksEntityPtr ed = fledges->GetByIndex(i);//получаем текущую грань из коллекции
		ksEdgeDefinitionPtr def = ed->GetDefinition();

		ksVertexDefinitionPtr p1 = def->GetVertex(true);
		ksVertexDefinitionPtr p2 = def->GetVertex(false);

		if (p1 && p2)
		{
			double x1, y1, z1;
			p1->GetPoint(&x1, &y1, &z1);

			if ((int(fabs(x1)) == l2) && (d1/2 == int(fabs(z1)))) {

				fl->Add(ed);

			}
		}
	}
	pChamfer->Create();
	

	//фаска
	fledges = pPart->EntityCollection(o3d_edge);//создаем коллекцию граней
	ksEntityPtr pChamfer1 = pPart->NewEntity(o3d_chamfer);
	pChamferDef = pChamfer1->GetDefinition();

	pChamferDef = pChamfer1->GetDefinition();
	pChamferDef->SetChamferParam(true, 1, 1);

	fl = pChamferDef->array();
	fl->Clear();

	for (int i = 0; i < fledges->GetCount(); i++)//цикл по всем граням
	{
		ksEntityPtr ed = fledges->GetByIndex(i);//получаем текущую грань из коллекции
		ksEdgeDefinitionPtr def = ed->GetDefinition();

		ksVertexDefinitionPtr p1 = def->GetVertex(true);
		ksVertexDefinitionPtr p2 = def->GetVertex(false);

		if (p1 && p2)
		{
			double x1, y1, z1;
			p1->GetPoint(&x1, &y1, &z1);

			if ((int(fabs(x1)) == l-2) && (int(fabs(y1)) == d2/2) && (0 == int(fabs(z1)))) {

				ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
				ksEntityPtr face = f->GetEntity();

				face->Update();

				ksEntityPtr pThread = pPart->NewEntity(o3d_thread);

				ksThreadDefinitionPtr pThDef = pThread->GetDefinition();
				pThDef->PutallLength(true);
				pThDef->PutautoDefinDr(true);
				pThDef->SetBaseObject(face);
				pThDef->Putp(Step);
				pThread->Create();
			}

			if ((0 == fabs(z1)) && (x1 == 0) && (fabs(y1) == D2/2)) {

					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("nest_circle");//для соосности гнезда
					face->Update();

			}
			
		}



		if (def->IsCircle())
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);

			if (p1 && p2)
			{
				double x1, y1, z1;
				p1->GetPoint(&x1, &y1, &z1);

				if ((d2 / 2 == fabs(y1)) && (x1 == 0)) {
					fl->Add(ed);
				}				
			}
		}
	}

	pChamfer1->Create();

	fledges = pPart->EntityCollection(o3d_edge);//создаем коллекцию граней

	for (int i = 0; i < fledges->GetCount(); i++)//цикл по всем граням
	{
		ksEntityPtr ed = fledges->GetByIndex(i);//получаем текущую грань из коллекции
		ksEdgeDefinitionPtr def = ed->GetDefinition();

		ksVertexDefinitionPtr p1 = def->GetVertex(true);
		ksVertexDefinitionPtr p2 = def->GetVertex(false);

		if (p1 && p2)
		{
			double x1, y1, z1;
			p1->GetPoint(&x1, &y1, &z1);

			if ((l - 2 == fabs(x1)) && (int(fabs(z1)) == d1/2)) {

				ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
				ksEntityPtr face = f->GetEntity();
				face->Putname("nest_plane");//совпадение шайбы и гнезда
				face->Update();

			}

			if ((l2 == fabs(x1)) && (fabs(z1) == 0)) {

				ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
				ksEntityPtr face = f->GetEntity();
				face->Putname("nest_plane2");//на расстояние от гайки до гнезда
				face->Update();

			}
		}
	}
	
	DeleteFile(L"C://Users//sophia//Desktop//kurs//nest.m3d");
	pDoc->SaveAs("C://Users//sophia//Desktop//kurs//nest.m3d");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////// гайка исп 1 (nut1) ///////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Clab1Doc* pDoc1 = (Clab1Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	ASSERT_VALID(pDoc1);
	if (!pDoc1)
		return;

	if (pDoc1->isp1) {
		//создание документа
		pDoc = pKompasApp5->Document3D();
		pDoc->Create(false, true);
		pPart = pDoc->GetPart(pTop_Part);

		//эскиз для шестиугольного основани
		ksEntityPtr pSketch3 = pPart->NewEntity(o3d_sketch);//эскиз для 3д детали
		pSketchDef = pSketch3->GetDefinition();
		pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));//устанавливаем плоскость эскизу
		pSketch3->Create();//открываем на редактирование
		p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования

		//строю 6-ти угольник
		ksRegularPolygonParamPtr rect = pKompasApp5->GetParamStruct(ko_RegularPolygonParam);
		rect->ang = 0;//без наклона
		rect->count = 6;//шестиугольник
		rect->describe = true;
		rect->radius = S1 / 2;//радиус вписанной окружности
		rect->style = 1;//основной стиль линии
		rect->xc = 0;//координаты центра вписанной окружности
		rect->yc = 0;
		p2DDoc->ksRegularPolygon(rect, 0);
		pSketchDef->EndEdit();//закрыли эскиз

		//выдавливаю шестиугольник
		ksEntityPtr pExtrude = pPart->NewEntity(o3d_baseExtrusion);//объект для выдавливания
		ksBaseExtrusionDefinitionPtr pExDef = pExtrude->GetDefinition();//Получаем интерфейс параметров операции "выдавливание"
		pExDef->directionType = dtNormal;//выбираем тип выдавливания
		pExDef->SetSideParam(true, etBlind, 5, 0, false);// параметры операции выдавливания
		pExDef->SetSketch(pSketch3);//какой эскиз будем давить
		pExtrude->Create();//создали

		//эскиз всего остального
		ksEntityPtr pSketch2 = pPart->NewEntity(o3d_sketch);//эскиз для 3д детали
		pSketchDef = pSketch2->GetDefinition();
		pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));//устанавливаем плоскость эскизу
		pSketch2->Create();//открываем на редактирование
		p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования

		double point1[7][2];
		point1[0][0] = 0;
		point1[0][1] = d / 2;
		point1[1][0] = 0;
		point1[1][1] = d / 2 + 1;
		point1[2][0] = -l1 / 3;
		point1[2][1] = d / 2 + 1;
		point1[3][0] = -l1 / 3;
		point1[3][1] = d2 / 2;
		point1[4][0] = -l1 + 1;//здесь задаем значение фаски
		point1[4][1] = d2 / 2;
		point1[5][0] = -l1;
		point1[5][1] = d / 2 + 1;//здесь задаем значение фаски
		point1[6][0] = -l1;
		point1[6][1] = d / 2;

		p2DDoc->ksLineSeg(point1[0][0], point1[0][1], point1[1][0], point1[1][1], 1);
		p2DDoc->ksLineSeg(point1[1][0], point1[1][1], point1[2][0], point1[2][1], 1);
		p2DDoc->ksLineSeg(point1[2][0], point1[2][1], point1[3][0], point1[3][1], 1);
		p2DDoc->ksLineSeg(point1[3][0], point1[3][1], point1[4][0], point1[4][1], 1);
		p2DDoc->ksLineSeg(point1[4][0], point1[4][1], point1[5][0], point1[5][1], 1);
		p2DDoc->ksLineSeg(point1[5][0], point1[5][1], point1[6][0], point1[6][1], 1);
		p2DDoc->ksLineSeg(point1[6][0], point1[6][1], point1[0][0], point1[0][1], 1);

		p2DDoc->ksLineSeg(0, 0, -l1, 0, 3);//рисую осевую

		pSketchDef->EndEdit();//закрыли эскиз

		//выдавливаю эскиз вращением
		pRotate = pPart->NewEntity(o3d_bossRotated);
		pRotDef = pRotate->GetDefinition();
		pRotDef->SetSketch(pSketch2);
		pRotDef->SetSideParam(TRUE, 360);
		pRotate->Create();//создали

		//эскиз для отверстия
		ksEntityPtr pSketch4 = pPart->NewEntity(o3d_sketch);//эскиз для 3д детали
		pSketchDef = pSketch4->GetDefinition();
		pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));//устанавливаем плоскость эскизу
		pSketch4->Create();//открываем на редактирование
		p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования

		p2DDoc->ksCircle(0, 0, d / 2, 1);//рисую круг

		pSketchDef->EndEdit();//закрыл эскиз

		//вырезаю отверстие
		ksEntityPtr pExtrude1 = pPart->NewEntity(o3d_cutExtrusion);
		ksCutExtrusionDefinitionPtr pExDef2 = pExtrude1->GetDefinition();
		pExDef2->directionType = dtReverse;
		pExDef2->SetSketch(pSketch4);
		pExDef2->SetSideParam(true, etThroughAll, 0, 0, false);
		pExtrude1->Create();

		//фаска
		fledges = pPart->EntityCollection(o3d_edge);//создаем коллекцию граней
		ksEntityPtr pChamfer2 = pPart->NewEntity(o3d_chamfer);
		pChamferDef = pChamfer2->GetDefinition();

		pChamferDef = pChamfer2->GetDefinition();
		pChamferDef->SetChamferParam(true, 1, 1);

		fl = pChamferDef->array();
		fl->Clear();

		for (int i = 0; i < fledges->GetCount(); i++)//цикл по всем граням
		{
			ksEntityPtr ed = fledges->GetByIndex(i);//получаем текущую грань из коллекции
			ksEdgeDefinitionPtr def = ed->GetDefinition();

			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);

			if (p1 && p2)
			{
				double x1, y1, z1;
				p1->GetPoint(&x1, &y1, &z1);
				if ((5 == int(fabs(x1))) && (int(fabs(z1)) == int(S1 / 2))) {

					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("nut_plane2");
					face->Update();

				}
			}

			if (def->IsCircle())
			{
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);

				if (p1 && p2)
				{
					double x1, y1, z1;
					p1->GetPoint(&x1, &y1, &z1);

					if ((d / 2 == fabs(z1)) && (fabs(x1) <= 1)) {

						fl->Add(ed);

					}

					if ((0 == fabs(z1)) && (fabs(x1) == l1)) {

						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Putname("nut_circle");//для соосности с гнездом
						face->Update();

					}

					if ((d / 2 == fabs(z1)) && (fabs(x1) == l1)) {//7 == fabs(y1) fabs(x1) == 7

						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Putname("nut_plane1");
						face->Update();

					}

					if ((d2/2 == fabs(y1)) && (fabs(x1) == l1-1)) {

						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Update();

						ksEntityPtr pThread = pPart->NewEntity(o3d_thread);

						ksThreadDefinitionPtr pThDef = pThread->GetDefinition();
						pThDef->PutallLength(true);
						pThDef->PutautoDefinDr(true);
						pThDef->SetBaseObject(face);
						/*pThDef->SetFaceBegin();
						pThDef->SetFaceEnd();*/
						pThDef->Putp(Step);
						pThread->Create();
					}
				}
			}
		}
		pChamfer2->Create();

		DeleteFile(L"C://Users//sophia//Desktop//kurs//nut1.m3d");
		pDoc->SaveAs("C://Users//sophia//Desktop//kurs//nut1.m3d");
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////// гайка исп 2 (nut2) ///////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (pDoc1->isp2) {
		pDoc = pKompasApp5->Document3D();
		pDoc->Create(false, true);
		pPart = pDoc->GetPart(pTop_Part);

		//эскиз для шестиугольного основани
		ksEntityPtr pSketch10 = pPart->NewEntity(o3d_sketch);//эскиз для 3д детали
		pSketchDef = pSketch10->GetDefinition();
		pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));//устанавливаем плоскость эскизу
		pSketch10->Create();//открываем на редактирование
		p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования

		//строю 6-ти угольник
		ksRegularPolygonParamPtr rect1 = pKompasApp5->GetParamStruct(ko_RegularPolygonParam);
		rect1->ang = 0;//без наклона
		rect1->count = 6;//шестиугольник
		rect1->describe = true;
		rect1->radius = S1 / 2;//радиус вписанной окружности
		rect1->style = 1;//основной стиль линии
		rect1->xc = 0;//координаты центра вписанной окружности
		rect1->yc = 0;
		p2DDoc->ksRegularPolygon(rect1, 0);
		p2DDoc->ksCircle(0,0, d/2, 1);
		pSketchDef->EndEdit();//закрыли эскиз

		//выдавливаю шестиугольник
		ksEntityPtr pExtrude10 = pPart->NewEntity(o3d_baseExtrusion);//объект для выдавливания
		ksBaseExtrusionDefinitionPtr pExDef1 = pExtrude10->GetDefinition();//Получаем интерфейс параметров операции "выдавливание"
		pExDef1->directionType = dtNormal;//выбираем тип выдавливания
		pExDef1->SetSideParam(true, etBlind, 4, 0, false);// параметры операции выдавливания
		pExDef1->SetSketch(pSketch10);//какой эскиз будем давить
		pExtrude10->Create();//создали

		//эскиз всего остального
		ksEntityPtr pSketch11 = pPart->NewEntity(o3d_sketch);//эскиз для 3д детали
		pSketchDef = pSketch11->GetDefinition();
		pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));//устанавливаем плоскость эскизу
		pSketch11->Create();//открываем на редактирование
		p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования

		double point2[10][2];
		point2[0][0] = 0;
		point2[0][1] = d / 2;
		point2[1][0] = 0;
		point2[1][1] = D / 2;
		point2[2][0] = 2; //толщина окружности
		point2[2][1] = D / 2;
		point2[3][0] = 2; //толщина окружности
		point2[3][1] = d2 / 2;
		point2[4][0] = 2;
		point2[4][1] = d2 / 2;
		point2[5][0] = 2;
		point2[5][1] = d2 / 2;
		point2[6][0] = l1 - 1;
		point2[6][1] = d2 / 2;
		point2[7][0] = l1;
		point2[7][1] = d2 / 2 - 1;
		point2[8][0] = l1;
		point2[8][1] = d / 2;
		point2[9][0] = 0;
		point2[9][1] = d / 2;

		p2DDoc->ksLineSeg(point2[0][0], point2[0][1], point2[1][0], point2[1][1], 1);
		p2DDoc->ksLineSeg(point2[1][0], point2[1][1], point2[2][0], point2[2][1], 1);
		p2DDoc->ksLineSeg(point2[2][0], point2[2][1], point2[3][0], point2[3][1], 1);
		p2DDoc->ksLineSeg(point2[3][0], point2[3][1], point2[4][0], point2[4][1], 1);
		p2DDoc->ksLineSeg(point2[4][0], point2[4][1], point2[5][0], point2[5][1], 1);
		p2DDoc->ksLineSeg(point2[5][0], point2[5][1], point2[6][0], point2[6][1], 1);
		p2DDoc->ksLineSeg(point2[6][0], point2[6][1], point2[7][0], point2[7][1], 1);
		p2DDoc->ksLineSeg(point2[7][0], point2[7][1], point2[8][0], point2[8][1], 1);
		p2DDoc->ksLineSeg(point2[8][0], point2[8][1], point2[9][0], point2[9][1], 1);
		p2DDoc->ksLineSeg(point2[9][0], point2[9][1], point2[0][0], point2[0][1], 1);

		p2DDoc->ksLineSeg(0, 0, l1, 0, 3);//рисую осевую

		pSketchDef->EndEdit();//закрыли эскиз

		//выдавливаю эскиз вращением
		pRotate = pPart->NewEntity(o3d_bossRotated);
		pRotDef = pRotate->GetDefinition();
		pRotDef->SetSketch(pSketch11);
		pRotDef->SetSideParam(TRUE, 360);
		pRotate->Create();//создали

		//эскиз для фаски
		ksEntityPtr pSketch7 = pPart->NewEntity(o3d_sketch);//эскиз для 3д детали
		pSketchDef = pSketch7->GetDefinition();
		pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));//устанавливаем плоскость эскизу
		pSketch7->Create();//открываем на редактирование
		p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования

		p2DDoc->ksLineSeg(-4, -d / 2, -3, -d / 2, 1);
		p2DDoc->ksLineSeg(-3, -d / 2, -4, -d / 2 - 1, 1);
		p2DDoc->ksLineSeg(-4, -d / 2 - 1, -4, -d / 2, 1);
		p2DDoc->ksLineSeg(0, 0, -4, 0, 3);

		pSketchDef->EndEdit();//закрыл эскиз

		ksEntityPtr pCutRotated = pPart->NewEntity(o3d_cutRotated);
		ksCutRotatedDefinitionPtr pCutRotDef = pCutRotated->GetDefinition();
		pCutRotDef->SetSketch(pSketch7);
		pCutRotDef->SetSideParam(TRUE, 360);
		pCutRotated->Create();//создали

		//фаска
		fledges = pPart->EntityCollection(o3d_edge);//создаем коллекцию граней

		fl = pChamferDef->array();
		fl->Clear();

		for (int i = 0; i < fledges->GetCount(); i++)//цикл по всем граням
		{
			ksEntityPtr ed = fledges->GetByIndex(i);//получаем текущую грань из коллекции
			ksEdgeDefinitionPtr def = ed->GetDefinition();

			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);

			if (p1 && p2)
			{
				double x1, y1, z1;
				p1->GetPoint(&x1, &y1, &z1);

				if ((4 == int(fabs(x1))) && (fabs(z1) == S1 / 2)) {

					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("nut2_plane2");
					face->Update();

				}
			}

			if (def->IsCircle())
			{
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);

				if (p1 && p2)
				{
					double x1, y1, z1;
					p1->GetPoint(&x1, &y1, &z1);

					if ((l1 == fabs(x1)) && (fabs(y1) == d / 2)) {

						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Putname("nut2_circle");//для соосности с гнездом
						face->Update();

					}

					if ((d2 / 2 - 1 == int(fabs(y1))) && (fabs(x1) == l1)) {

						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Putname("nut2_plane1");
						face->Update();

					}
					if ((d2 / 2 == fabs(y1)) && (fabs(x1) == 2) && (fabs(z1) == 0)) {

						ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
						ksEntityPtr face = f->GetEntity();
						face->Update();

						ksEntityPtr pThread = pPart->NewEntity(o3d_thread);

						ksThreadDefinitionPtr pThDef = pThread->GetDefinition();
						pThDef->PutallLength(true);
						pThDef->PutautoDefinDr(true);
						pThDef->SetBaseObject(face);
						pThDef->Putp(Step);
						pThread->Create();
					}
				}
			}
		}

		DeleteFile(L"C://Users//sophia//Desktop//kurs//nut2.m3d");
		pDoc->SaveAs("C://Users//sophia//Desktop//kurs//nut2.m3d");

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////// Шайба (washer) ///////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//создание документа
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	//эскиз для большойокружности
	ksEntityPtr pSketch5 = pPart->NewEntity(o3d_sketch);//эскиз для 3д детали
	pSketchDef = pSketch5->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));//устанавливаем плоскость эскизу
	pSketch5->Create();//открываем на редактирование
	p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования

	p2DDoc->ksCircle(0, 0, D3 / 2, 1);//рисую круг

	pSketchDef->EndEdit();// закрыл эскиз

	//выдавливаю окружность
	ksEntityPtr pExtrude2 = pPart->NewEntity(o3d_baseExtrusion);//объект для выдавливания
	ksBaseExtrusionDefinitionPtr pExDef3 = pExtrude2->GetDefinition();//Получаем интерфейс параметров операции "выдавливание"
	pExDef3->directionType = dtNormal;//выбираем тип выдавливания
	pExDef3->SetSideParam(true, etBlind, S, 0, false);// параметры операции выдавливания
	pExDef3->SetSketch(pSketch5);//какой эскиз будем давить
	pExtrude2->Create();//создали

	ksEntityPtr pSketch6 = pPart->NewEntity(o3d_sketch);//искиз для 3д детали
	pSketchDef = pSketch6->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pSketch6->Create();//открываем на редактирование
	p2DDoc = pSketchDef->BeginEdit();//устанавливаем режим редактирования
	p2DDoc->ksCircle(0, 0, d3 / 2, 1);//рисую круг
	pSketchDef->EndEdit();
	//вырезаю отверстие
	ksEntityPtr pExtrude3 = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pExDef4 = pExtrude3->GetDefinition();
	pExDef4->directionType = dtReverse;
	pExDef4->SetSketch(pSketch6);
	pExDef4->SetSideParam(true, etThroughAll, 0, 0, false);
	pExtrude3->Create();

	//ищю и именную грань внутреннюю (отверстия)
	ksEntityCollectionPtr flFaces = pPart->EntityCollection(o3d_face);//создаем коллекцию граней
	for (int i = 0; i < flFaces->GetCount(); i++)//цикл по всем граням
	{
		ksEntityPtr face = flFaces->GetByIndex(i);//получаем текущую грань из коллекции
		ksFaceDefinitionPtr def = face->GetDefinition();

		if (def->GetOwnerEntity() == pExtrude2)//проверяем принадлежит ли эта грань объекту ротейт
		{
			face->Putname("whasher_circle");//присваиваем имя грани
			face->Update();//обновляем
		}
	}

	fledges = pPart->EntityCollection(o3d_edge);//создаем коллекцию граней

	for (int i = 0; i < fledges->GetCount(); i++)//цикл по всем граням
	{
		ksEntityPtr ed = fledges->GetByIndex(i);//получаем текущую грань из коллекции
		ksEdgeDefinitionPtr def = ed->GetDefinition();

		ksVertexDefinitionPtr p1 = def->GetVertex(true);
		ksVertexDefinitionPtr p2 = def->GetVertex(false);

		if (p1 && p2)
		{
			double x1, y1, z1;
			p1->GetPoint(&x1, &y1, &z1);

			if ((0 == fabs(y1)) && (fabs(z1) == D3 / 2)) {

				ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
				ksEntityPtr face = f->GetEntity();
				face->Putname("whasher_plane");
				face->Update();
			}
		}
	}

	DeleteFile(L"C://Users//sophia//Desktop//kurs//washer.m3d");
	pDoc->SaveAs("C://Users//sophia//Desktop//kurs//washer.m3d");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////// Сборка ///////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, false);
	pPart = pDoc->GetPart(pTop_Part);

	ksPartPtr pnest, pscrew, pwasher1, pwasher2;

	pDoc->SetPartFromFile("C://Users//sophia//Desktop//kurs//nest.m3d", pPart, true);
	if (pDoc1->isp1) {
		pDoc->SetPartFromFile("C://Users//sophia//Desktop//kurs//nut1.m3d", pPart, true);//1е исполнение гайки
	}
	if (pDoc1->isp2) {
		pDoc->SetPartFromFile("C://Users//sophia//Desktop//kurs//nut2.m3d", pPart, true);//2е исполнение гайки
	}
	pDoc->SetPartFromFile("C://Users//sophia//Desktop//kurs//washer.m3d", pPart, true);
	pDoc->SetPartFromFile("C://Users//sophia//Desktop//kurs//washer.m3d", pPart, true);
	
	pnest = pDoc->GetPart(0);
	pscrew = pDoc->GetPart(1); //исполнение гайки
	pwasher1 = pDoc->GetPart(2);
	pwasher2 = pDoc->GetPart(3);
	
	ksEntityCollectionPtr col = pnest->EntityCollection(o3d_face);
	ksEntityPtr nest_alignment = col->GetByName("nest_circle", true, true);//гнездо СООСНОСТЬ
	ksEntityPtr nest_4_coincidence1 = col->GetByName("nest_plane", true, true);//гнездо нутро для СОВПАДЕНИЯ с шайбой
	ksEntityPtr nest_4_coincidence2 = col->GetByName("nest_plane2", true, true);//гнездо наружная плоскость для СОВПАДЕНИЯ

	//Шайба1:
	col = pwasher1->EntityCollection(o3d_face);
	ksEntityPtr washer1_alignment = col->GetByName("whasher_circle", true, true);//шайба 1 СООСНОСТЬ
	ksEntityPtr washer1_4_coincidence = col->GetByName("whasher_plane", true, true);//шайба 1 плоскость для СОВПАДЕНИЯ

	//Шайба2:
	col = pwasher2->EntityCollection(o3d_face);
	ksEntityPtr washer2_alignment = col->GetByName("whasher_circle", true, true);// шайба 2 СООСНОСТЬ
	ksEntityPtr washer2_4_coincidence = col->GetByName("whasher_plane", true, true);// шайба 2 плоскость для СОВПАДЕНИЯ

	//Соосность шайб к гнезду
	pDoc->AddMateConstraint(mc_Concentric, washer1_alignment, nest_alignment, 1, 1, 0);//гнездо + шайба 1 СООСНОСТЬ
	pDoc->AddMateConstraint(mc_Concentric, washer2_alignment, nest_alignment, 1, 1, 0);//гнездо + шайба 2 СООСНОСТЬ

	if (pDoc1->isp1) {
		//Гайка исп1:
		col = pscrew->EntityCollection(o3d_face);
		ksEntityPtr nut_alignment = col->GetByName("nut_circle", true, true);//гайка исп 1 СООСНОСТЬ
		ksEntityPtr nut_4_coincidence1 = col->GetByName("nut_plane1", true, true);//гайка СОВПАДЕНИЕ для шайбы
		ksEntityPtr nut_4_coincidence2 = col->GetByName("nut_plane2", true, true);//гайка СОВПАДЕНИЕ для гнезда

		pDoc->AddMateConstraint(mc_Concentric, nut_alignment, nest_alignment, -1, 1, 0);//гайка исп 1 СООСНОСТЬ
		pDoc->AddMateConstraint(mc_Distance, nut_4_coincidence1, washer2_4_coincidence, 1, 1, S);//гайка + шайба 2 СОВПАДЕНИЕ
		pDoc->AddMateConstraint(mc_Coincidence, nest_4_coincidence1, washer1_4_coincidence, -1, 1, 0);//шайбу один в глубь гнезда прилипил
		pDoc->AddMateConstraint(mc_Distance, nut_4_coincidence2, nest_4_coincidence2, 1, 1, L-5);//на L объекты
	}

	if (pDoc1->isp2) {
		//Гайка исп2
		col = pscrew->EntityCollection(o3d_face);
		ksEntityPtr nut2_alignment = col->GetByName("nut2_circle", true, true);//гайка исп 1 СООСНОСТЬ
		ksEntityPtr nut2_4_coincidence1 = col->GetByName("nut2_plane1", true, true);//гайка СОВПАДЕНИЕ для шайбы
		ksEntityPtr nut2_4_coincidence2 = col->GetByName("nut2_plane2", true, true);//гайка СОВПАДЕНИЕ для гнезда

		pDoc->AddMateConstraint(mc_Concentric, nut2_alignment, nest_alignment, -1, 1, 0);//гайка исп 1 СООСНОСТЬ
		pDoc->AddMateConstraint(mc_Distance, nut2_4_coincidence1, washer2_4_coincidence, 1, 1, S);//гайка + шайба 2 СОВПАДЕНИЕ
		pDoc->AddMateConstraint(mc_Coincidence, nest_4_coincidence1, washer1_4_coincidence, -1, 1, 0);//шайбу один в глубь гнезда прилипил
		pDoc->AddMateConstraint(mc_Distance, nut2_4_coincidence2, nest_4_coincidence2, -1, 1, -L);//
	}

	pDoc->RebuildDocument();//обновляем документ
	DeleteFile(L"C://Users//sophia//Desktop//kurs//oilseal.a3d");
	pDoc->SaveAs("C://Users//sophia//Desktop//kurs//oilseal.a3d");
}



void CSborkaDialog::OnCbnSelchangeCombo1()
{
	// TODO: добавьте свой код обработчика уведомлений
	int selectedIndex = SCRO.GetCurSel();
	CString selectedText;
	SCRO.GetLBText(selectedIndex, selectedText);

	// Проверяем выбранный элемент и устанавливаем значение в EditControl
	if (selectedText == _T("СКРО16")) {
		D.SetWindowText(_T("21.9"));
		d.SetWindowText(_T("10"));
		D1.SetWindowText(_T("12"));
		d1.SetWindowText(_T("8"));
		L.SetWindowText(_T("37"));
		D2.SetWindowText(_T("20"));
		d2.SetWindowText(_T("16"));
		l.SetWindowText(_T("18"));
		l1.SetWindowText(_T("17"));
		l2.SetWindowText(_T("23"));
		D3.SetWindowText(_T("14"));
		d3.SetWindowText(_T("10"));
		S.SetWindowText(_T("1.5"));
		S1.SetWindowText(_T("19"));
		Step.SetWindowText(_T("1"));
	}
	else if (selectedText == _T("СКРО27")) {
		D.SetWindowText(_T("36.9"));
		d.SetWindowText(_T("20"));
		D1.SetWindowText(_T("24"));
		d1.SetWindowText(_T("18"));
		L.SetWindowText(_T("49"));
		D2.SetWindowText(_T("32"));
		d2.SetWindowText(_T("26"));
		l.SetWindowText(_T("26"));
		l1.SetWindowText(_T("23"));
		l2.SetWindowText(_T("31"));
		D3.SetWindowText(_T("24"));
		d3.SetWindowText(_T("18"));
		S.SetWindowText(_T("2"));
		S1.SetWindowText(_T("32"));
		Step.SetWindowText(_T("1.5"));
	}
	else if (selectedText == _T("СКРО42")) {
		D.SetWindowText(_T("53"));
		d.SetWindowText(_T("32"));
		D1.SetWindowText(_T("36"));
		d1.SetWindowText(_T("30"));
		L.SetWindowText(_T("67"));
		D2.SetWindowText(_T("48"));
		d2.SetWindowText(_T("42"));
		l.SetWindowText(_T("35"));
		l1.SetWindowText(_T("32"));
		l2.SetWindowText(_T("42"));
		D3.SetWindowText(_T("38"));
		d3.SetWindowText(_T("30"));
		S.SetWindowText(_T("3"));
		S1.SetWindowText(_T("46"));
		Step.SetWindowText(_T("2"));
	}
	else if (selectedText == _T("СКРО60")) {
		D.SetWindowText(_T("75"));
		d.SetWindowText(_T("45"));
		D1.SetWindowText(_T("50"));
		d1.SetWindowText(_T("46"));
		L.SetWindowText(_T("75"));
		D2.SetWindowText(_T("68"));
		d2.SetWindowText(_T("60"));
		l.SetWindowText(_T("39"));
		l1.SetWindowText(_T("37"));
		l2.SetWindowText(_T("46"));
		D3.SetWindowText(_T("55"));
		d3.SetWindowText(_T("40"));
		S.SetWindowText(_T("3"));
		S1.SetWindowText(_T("65"));
		Step.SetWindowText(_T("3"));
	}
	else if (selectedText == _T("СКРО76")) {
		D.SetWindowText(_T("92.4"));
		d.SetWindowText(_T("60"));
		D1.SetWindowText(_T("64"));
		d1.SetWindowText(_T("56"));
		L.SetWindowText(_T("83"));
		D2.SetWindowText(_T("85"));
		d2.SetWindowText(_T("76"));
		l.SetWindowText(_T("43"));
		l1.SetWindowText(_T("40"));
		l2.SetWindowText(_T("52"));
		D3.SetWindowText(_T("71"));
		d3.SetWindowText(_T("56"));
		S.SetWindowText(_T("3"));
		S1.SetWindowText(_T("80"));
		Step.SetWindowText(_T("3"));
	}
	else if (selectedText == _T("СКРО90")) {
		D.SetWindowText(_T("103.9"));
		d.SetWindowText(_T("80"));
		D1.SetWindowText(_T("82"));
		d1.SetWindowText(_T("70"));
		L.SetWindowText(_T("86"));
		D2.SetWindowText(_T("100"));
		d2.SetWindowText(_T("90"));
		l.SetWindowText(_T("45"));
		l1.SetWindowText(_T("41"));
		l2.SetWindowText(_T("54"));
		D3.SetWindowText(_T("84"));
		d3.SetWindowText(_T("70"));
		S.SetWindowText(_T("3"));
		S1.SetWindowText(_T("90"));
		Step.SetWindowText(_T("3"));
	}
}


BOOL CSborkaDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Получаем дескриптор главного окна
	HWND hWndMain = AfxGetMainWnd()->GetSafeHwnd();

	// Получаем размеры главного окна
	CRect rectMain;
	::GetWindowRect(hWndMain, &rectMain);
	int mainWidth = rectMain.Width();
	int mainHeight = rectMain.Height();

	// Получаем размеры диалогового окна
	CRect rectDialog;
	GetWindowRect(&rectDialog);
	int dialogWidth = rectDialog.Width();
	int dialogHeight = rectDialog.Height();

	// Устанавливаем координаты диалогового окна в правый нижний угол главного окна
	int xPos = rectMain.right - dialogWidth;
	int yPos = rectMain.bottom - dialogHeight - 18;

	SetWindowPos(NULL, xPos, yPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);


	// TODO:  Добавить дополнительную инициализацию
	SCRO.AddString(_T("СКРО16"));
	SCRO.AddString(_T("СКРО27"));
	SCRO.AddString(_T("СКРО42"));
	SCRO.AddString(_T("СКРО60"));
	SCRO.AddString(_T("СКРО76"));
	SCRO.AddString(_T("СКРО90"));

	// Установить первый элемент по умолчанию
	SCRO.SetCurSel(0);

	D.SetWindowText(_T("21.9"));
	d.SetWindowText(_T("10"));
	D1.SetWindowText(_T("12"));
	d1.SetWindowText(_T("8"));
	L.SetWindowText(_T("37"));
	D2.SetWindowText(_T("20"));
	d2.SetWindowText(_T("16"));
	l.SetWindowText(_T("18"));
	l1.SetWindowText(_T("17"));
	l2.SetWindowText(_T("23"));
	D3.SetWindowText(_T("14"));
	d3.SetWindowText(_T("10"));
	S.SetWindowText(_T("1.5"));
	S1.SetWindowText(_T("19"));
	Step.SetWindowText(_T("1"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

