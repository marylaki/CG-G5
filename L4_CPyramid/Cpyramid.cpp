#include "CPyramid.h"
#include <iostream>
#define pi 3.14159265;
//CPyramid::CPyramid()//Работает
//{
//	this->Vertices.RedimMatrix(4, 5);
//	this->Nabcd.RedimMatrix(3);
//	this->Vertices(0, 0) = 10;//A
//	this->Vertices(1, 1) = -10;//B
//	this->Vertices(0, 2) = -10;//C
//	this->Vertices(1, 3) = 10;//D
//	this->Vertices(2, 4) = 20;//E
//	for (int i = 0; i < 5; i++)
//		this->Vertices(3, i) = 1;
//	this->Nabcd(0) = 1;
//	this->Nabcd(1) = 0;
//	this->Nabcd(2) = -1; //вектор нормали к основанию пирамиды
//}
CPyramid::CPyramid()
{
	this->Vertices.RedimMatrix(4, 7);
	this->Nabcd.RedimMatrix(3);
	this->Vertices(0, 0) = 5;//A
	this->Vertices(0, 1) = 3;//A1
	this->Vertices(2, 1) = 10;
	this->Vertices(2, 3) = 10;//B1
	this->Vertices(1, 4) = 5;//C
	this->Vertices(1, 5) = 3;//C1
	this->Vertices(2, 5) = 10;
	for (int i = 0; i < 7; i++)
		this->Vertices(3, i) = 1;
	this->Nabcd(0) = 1;
	this->Nabcd(1) = 0;
	this->Nabcd(2) = -1; //вектор нормали к основанию пирамиды
}


//void CPyramid::Draw1(CDC &dc, CMatrix&PView, CRect &RW)//////////////////////////////////////////////Хуйня пошла
//{
//	CMatrix ViewCart = SphereToCart(PView);
//	CMatrix MV= CreateViewCoord(PView(0), PView(1), PView(2));
//	CMatrix ViewVert = MV*this->Vertices;                         //
//	CRectD RectView;
//	GetRect(ViewVert, RectView);
//	CMatrix MW = SpaceToWindow(RectView,RW);
//	CPoint MasVert[5];
//	CMatrix V(3);
//	V(2) = 1;
//	for (int i = 0; i < 5; i++)
//	{
//		V(0) = ViewVert(0, i);
//		V(1) = ViewVert(1, i);
//		V = MW*V;
//		MasVert[i].x = (int)V(0);
//		MasVert[i].y = (int)V(1);
//	}
//	CPen Pen(PS_SOLID, 2, RGB(0, 0, 255));
//	CPen *pOldPen = dc.SelectObject(&Pen);
//	CBrush Brush(RGB(255, 0, 0));
//	CBrush *pOldBrush = dc.SelectObject(&Brush);
//	CMatrix R1(3), R2(3), R3(3),VN(3);
//	double sm;
//	for (int i = 0; i < 6; i+=2)
//	{
//		int k;
//		if (i == 5)
//			k = 0;
//		else
//			k = i + 1;
//		R1 = this->Vertices.GetCol(i, 0, 2);
//		R2 = this->Vertices.GetCol(i+1, 0, 2);
//		R3 = this->Vertices.GetCol(k, 0, 2);
//		CMatrix V1 = R2 - R1;
//		CMatrix V2 = R3 - R1;
//		
//		VN = VectorMult(V2, V1);
//		//VN = VectorMult(R1, R2);
//		sm = ScalarMult(VN, ViewCart);
//
//		//if (sm>=0)
//		//{
//			dc.MoveTo(MasVert[i]);
//			dc.LineTo(MasVert[i+1]);
//			dc.LineTo(MasVert[k+1]);
//			dc.LineTo(MasVert[k]);
//		/*}*/
//		
//		sm = ScalarMult(Nabcd, ViewCart);
//		if (sm >= 0)
//			dc.Polygon(MasVert,4);
//	}
//	dc.SelectObject(pOldPen);
//	dc.SelectObject(pOldBrush);
//}
void CPyramid::Draw1(CDC &dc, CMatrix&PView, CRect &RW)//РАБОТАЕТ 
{
	CMatrix ViewCart = SphereToCart(PView);
	CMatrix XV = CreateViewCoord(PView(0), PView(1), PView(2));
	CMatrix ViewVert = XV*this->Vertices;                         //
	CRectD RectView;
	GetRect(this->Vertices, RectView);
	
	CMatrix MW = SpaceToWindow(RectView, RW);
	CPoint MasVert[6], a1b1c1[3], abc[3];
	CMatrix V(3);
	V(2) = 1;
	for (int i = 0; i < 6; i++)
	{
		V(0) = ViewVert(0, i);
		V(1) = ViewVert(1, i);
		V = MW*V;
		MasVert[i].x = (int)V(0);
		MasVert[i].y = (int)V(1);
	}
	abc[0] = MasVert[0];
	abc[1] = MasVert[2];
	abc[2] = MasVert[4];
	a1b1c1[0] = MasVert[1];
	a1b1c1[1] = MasVert[3];
	a1b1c1[2] = MasVert[5];

	CPen Pen(PS_SOLID, 2, RGB(0, 0, 255));
	CPen *pOldPen = dc.SelectObject(&Pen);
	CBrush Brush(RGB(255, 0, 0));
	CBrush Brus(RGB(0, 0, 255));
	CBrush Brsh(RGB(255, 255, 255));
	CBrush *pOldBrush = dc.SelectObject(&Brush);
	dc.SelectObject(&Brsh);
	CPoint ab[4];
	ab[0] = abc[0];
	ab[1] = abc[1];
	ab[2] = a1b1c1[1];
	ab[3] = a1b1c1[0];
	
	CPoint bc[4];
	bc[0] = abc[1];
	bc[1] = abc[2];
	bc[2] = a1b1c1[2];
	bc[3] = a1b1c1[1];
	
	CPoint ac[4];
	ac[0] = abc[2];
	ac[1] = abc[0];
	ac[2] = a1b1c1[0];
	ac[3] = a1b1c1[2];
	
	if (PView(1)<90)
	{
		dc.Polygon(ab, 4);
		dc.Polygon(ac, 4);
		//dc.Polygon(bc, 4);
		
	}else
	if (PView(1)<180)
	{
		//dc.Polygon(ab, 4);
		dc.Polygon(ac, 4);
		dc.Polygon(bc, 4);
		
	}else
	if (PView(1)<270)
	{
		//dc.Polygon(ac, 4);
		dc.Polygon(ab, 4);
		dc.Polygon(bc, 4);

	}
	else
	{
		//dc.Polygon(bc, 4);
		dc.Polygon(ac, 4);
		dc.Polygon(ab, 4);
	}
	
	if (PView(2) <=10 && PView(1)>180 && PView(1)<270)
	{
		dc.Polygon(ac, 4);
		dc.Polygon(ab, 4);
		dc.Polygon(bc, 4);
	}

	if (PView(2) <= 90)
	{
	
		dc.SelectObject(&Brus);
		dc.Polygon(a1b1c1, 3);

	}
	else
	{
		dc.SelectObject(&Brush);
		dc.Polygon(abc, 3);
	}
		
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

void CPyramid::Draw(CDC &dc, CMatrix&PView, CRect &RW)//РАБОТАЕТ
{
	CMatrix ViewCart = SphereToCart(PView);
	CMatrix XV = CreateViewCoord(PView(0), PView(1), PView(2));
	CMatrix ViewVert = XV*this->Vertices;                         
	CRectD RectView;
	GetRect(Vertices, RectView);
	CMatrix MW = SpaceToWindow(RectView, RW);
	CPoint MasVert[6],a1b1c1[3],abc[3];
	CMatrix V(3);
	V(2) = 1;
	for (int i = 0; i < 6; i++)
	{
		V(0) = ViewVert(0, i);
		V(1) = ViewVert(1, i);
		V = MW*V;
		MasVert[i].x = (int)V(0);
		MasVert[i].y = (int)V(1);
	}
	abc[0] = MasVert[0];
	abc[1] = MasVert[2];
	abc[2] = MasVert[4];
	a1b1c1[0] = MasVert[1];
	a1b1c1[1] = MasVert[3];
	a1b1c1[2] = MasVert[5];
	CPen Pen(PS_SOLID, 2, RGB(0, 0, 255));
	CPen *pOldPen = dc.SelectObject(&Pen);
	//dc.Polygon(abc, 3)
	dc.MoveTo(abc[0]);
	dc.LineTo(abc[1]);
	dc.LineTo(abc[2]);
	dc.LineTo(abc[0]);
	dc.MoveTo(a1b1c1[0]);
	dc.LineTo(a1b1c1[1]);
	dc.LineTo(a1b1c1[2]);
	dc.LineTo(a1b1c1[0]);
	//.Polygon(a1b1c1, 3);
	dc.MoveTo(abc[0]);
	dc.LineTo(a1b1c1[0]);
	dc.MoveTo(abc[1]);
	dc.LineTo(a1b1c1[1]);
	dc.MoveTo(abc[2]);
	dc.LineTo(a1b1c1[2]);
	
	dc.SelectObject(pOldPen);
}

void  CPyramid::GetRect(CMatrix& Vert, CRectD&RectView)
{
	RectView.top = Vert.GetRow(2).MinElement();
	RectView.bottom = Vert.GetRow(2).MaxElement();
	RectView.left = Vert.GetRow(0).MinElement();
	RectView.right = Vert.GetRow(0).MaxElement();

	/*RectView.top = Vert(0);
	RectView.bottom = 2 * Vert(0);
	RectView.left = Vert(0);
	RectView.right = 2*Vert(0);*/
}

CMatrix VectorMult(CMatrix& V1, CMatrix& V2)
{
	if (V1.rows() != V2.rows() || V1.cols() > 1 || V2.cols() > 1) // Число столбцов больше одного 
	{
		char* error = "CMatrix VectorMult(CMatrix& V1, CMatrix& V2) объект не вектор - число столбцов больше 1 ";
		MessageBoxA(NULL, error, "Ошибка", MB_ICONSTOP);
		exit(1);
	}

	CMatrix Temp = V1;
	Temp(0) = V1(1)*V2(2) - V1(2)*V2(1);
	Temp(1) = V1(2)*V2(0) - V1(0)*V2(2);
	Temp(2) = V1(0)*V2(1) - V1(1)*V2(0);

	return Temp;
}

double ScalarMult(CMatrix& V1, CMatrix& V2)
{
	if (V1.rows() != V2.rows() || V1.cols() > 1 || V2.cols() > 1) // Число столбцов больше одного 
	{
		char* error = "double ScalarMult(CMatrix& V1, CMatrix& V2) объект не вектор - число столбцов больше 1 ";
		MessageBoxA(NULL, error, "Ошибка", MB_ICONSTOP);
		exit(1);
	}

	return V1(0)*V2(0) + V1(1)*V2(1) + V1(2)*V2(2);
}
CMatrix CreateViewCoord(double r, double fi, double q)
{
	double fi_r = (fi / 180)*pi;
	double q_r = (q / 180)*pi;
	CMatrix K(4, 4);
	K(0, 0) = -sin(fi_r);
	K(0, 1) = cos(fi_r);
	K(1, 0) = -cos(q_r)*cos(fi_r);
	K(1, 1) = -cos(q_r)*sin(fi_r);
	K(1, 2) = sin(q_r);
	K(2, 0) = -sin(q_r)*cos(fi_r);
	K(2, 1) = -sin(q_r)*sin(fi_r);
	K(2, 2) = -cos(q_r);
	K(2, 3) = r;
	K(3, 3) = 1;
	return K;

}
