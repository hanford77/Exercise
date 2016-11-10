//LinkMatrix.cpp
#include "stdafx.h"
#include "LinkMatrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CLinkPath::CLinkPath()
{
	Empty();
}

void CLinkPath::Empty()
{
	m_Count	=	0;
}

void CLinkPath::AddPoint(int x,int y)
{
	BOOL	bAdd	=	FALSE;

	if(m_Count >= 4)
	{
	}
	else if(m_Count)
	{
		bAdd	=	(x!=m_x[m_Count - 1] || y!=m_y[m_Count - 1]);
	}
	else
	{
		bAdd	=	TRUE;
	}
	if(bAdd)
	{
		m_x[m_Count]	=	x;
		m_y[m_Count]	=	y;
		m_Count++;
	}
}

CLinkMatrix::CLinkMatrix()
{
	m_pMatrix	=	NULL;
	m_iRows		=
	m_iCols		=	0;
	m_xSel		=
	m_ySel		=	0;
	m_iMoveMode	=	0;
}

CLinkMatrix::~CLinkMatrix()
{
	Empty();
}

void CLinkMatrix::Empty()
{
	if(m_pMatrix)
	{
		delete[] m_pMatrix;
		m_pMatrix	=	NULL;
	}
	m_iRows		=	0;
	m_iCols		=	0;
}

/*************************************************\
初始化矩阵（连连看布局）
nRows		[in]	行数
nCols		[in]	列数
nIconCount	[in]	图标数 (小于 1 则不洗牌)
\*************************************************/
void CLinkMatrix::Init(int nRows,int nCols,int nIconCount)
{
	if(nRows < 1 || nCols < 1)
	{//行数或列数太小
		Empty();
		return;
	}
	if((nRows & 1) && (nCols & 1))
	{//行数、列数均为奇数
		Empty();
		return;
	}
	DWORD	dwCountOld	=	(m_iRows + 2) * (m_iCols + 2);
	DWORD	dwCountNew	=	(nRows + 2) * (nCols + 2);
	if(NULL==m_pMatrix || dwCountOld < dwCountNew)
	{//需要重新分配内存
		if(m_pMatrix)
		{
			delete[] m_pMatrix;
		}
		m_pMatrix	=	new ICONDATA[dwCountNew];
	}
	memset(m_pMatrix,0,dwCountNew * sizeof(ICONDATA));
	m_iRows		=	nRows;
	m_iCols		=	nCols;
	m_xSel		=
	m_ySel		=	0;
	if(nIconCount > 0)
	{//洗牌
		srand(time(NULL) + GetTickCount());
		int			i,j,n,p;
		int			nIconTotal;
		CDWordArray arrIcon;

		do 
		{
			nIconTotal	=	m_iRows * m_iCols;						//总的图片数
			n			=	(nIconTotal / (nIconCount << 1)) << 1;	//每个图片最多有 n 个
			p			=	0;
			arrIcon.SetSize(nIconTotal);
			for(i=1;i <= nIconCount;i++)
			{
				for(j=n;j>0;j--)
				{
					arrIcon[p++]=i;
				}
			}
			i	=	1;
			while(p < nIconTotal)
			{
				arrIcon[p++]	=	i;
				arrIcon[p++]	=	i;
				i++;
			}
			for(i=1;i<=m_iRows;i++)
			{
				for(j=1;j<=m_iCols;j++)
				{
					p				=	rand() % (nIconTotal--);
					operator()(j,i)	=	(ICONDATA)arrIcon.GetAt(p);
					arrIcon.RemoveAt(p);
				}
			}
		}while(0==GetHelp());
	}
}

/*************************************************\
水平方向是否连通
[in]	y		水平线 y 坐标
[in]	xFrom	水平线起始 x 坐标
[in]	xTo		水平线终止 x 坐标
\*************************************************/
BOOL CLinkMatrix::IsBlankH(int y,int xFrom,int xTo)
{
	for(int x=xFrom;x<=xTo;x++)
	{
		if(operator()(x,y))
		{
			return FALSE;
		}
	}
	return TRUE;
}

/*************************************************\
垂直方向是否连通
[in]	x		垂直线 x 坐标
[in]	yFrom	垂直线起始 y 坐标
[in]	yTo		垂直线终止 y 坐标
\*************************************************/
BOOL CLinkMatrix::IsBlankV(int x,int yFrom,int yTo)
{
	for(int y=yFrom;y<=yTo;y++)
	{
		if(operator()(x,y))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CLinkMatrix::FindPath(int x1, int y1, int x2, int y2,CLinkPath*pPath)
{
	if(pPath)
	{
		pPath->Empty();
	}
	if(x1 < 1 || x1 > m_iCols
	|| x2 < 1 || x2 > m_iCols
	|| y1 < 1 || y1 > m_iRows
	|| y2 < 1 || y2 > m_iRows)
	{//在范围外，则直接返回 FALSE
		return FALSE;
	}
	RECT	rect;		//外接矩形
	int		iFlag	=	0;

	if(x1 <= x2)
	{
		rect.left	=	x1;
		rect.right	=	x2;
	}
	else
	{
		iFlag	   |=	1;
		rect.left	=	x2;
		rect.right	=	x1;
	}
	if(y1 <= y2)
	{
		rect.top	=	y1;
		rect.bottom	=	y2;
	}
	else
	{
		iFlag	   |=	2;
		rect.top	=	y2;
		rect.bottom	=	y1;
	}
	BOOL	b45		=	(0==iFlag || 3==iFlag);	//起点到终点的连线是否为“\”(还有可能为“/”)
	int		x,y;

	if(x1==x2)
	{//起点到终点连线为“|”
		if(y1==y2)
		{//起点和终点重合
			return FALSE;
		}
		if(IsBlankV(x1,rect.top + 1,rect.bottom - 1))
		{
			if(pPath)
			{
				pPath->AddPoint(x1,rect.top);
				pPath->AddPoint(x1,rect.bottom);
			}
			return TRUE;
		}
	}
	if(y1==y2)
	{//起点到终点连线为“-”
		if(IsBlankH(y1,rect.left + 1,rect.right - 1))
		{
			if(pPath)
			{
				pPath->AddPoint(rect.left,y1);
				pPath->AddPoint(rect.right,y1);
			}
			return TRUE;
		}
	}
	if(x1!=x2 && y1!=y2)
	{//内部检查
		if(b45)
		{//起点到终点连线为“\”
			//从左到右
			for(x=rect.left;x<=rect.right;x++)
			{
				if(IsBlankH(rect.top,rect.left + 1,x)
				&& IsBlankV(x,rect.top + 1,rect.bottom - 1)
				&& IsBlankH(rect.bottom,x,rect.right - 1))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.left,rect.top);
						pPath->AddPoint(x,rect.top);
						pPath->AddPoint(x,rect.bottom);
						pPath->AddPoint(rect.right,rect.bottom);
					}
					return TRUE;
				}
			}
			//从上到下
			for(y=rect.top;y<=rect.bottom;y++)
			{
				if(IsBlankV(rect.left,rect.top + 1,y)
				&& IsBlankH(y,rect.left + 1,rect.right - 1)
				&& IsBlankV(rect.right,y,rect.bottom - 1))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.left,rect.top);
						pPath->AddPoint(rect.left,y);
						pPath->AddPoint(rect.right,y);
						pPath->AddPoint(rect.right,rect.bottom);
					}
					return TRUE;
				}
			}
		}
		else
		{//起点到终点连线为“/”
			//从左到右
			for(x=rect.left;x<=rect.right;x++)
			{
				if(IsBlankH(rect.bottom,rect.left + 1,x)
				&& IsBlankV(x,rect.top + 1,rect.bottom - 1)
				&& IsBlankH(rect.top,x,rect.right - 1))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.right,rect.top);
						pPath->AddPoint(x,rect.top);
						pPath->AddPoint(x,rect.bottom);
						pPath->AddPoint(rect.left,rect.bottom);
					}
					return TRUE;
				}
			}
			//从上到下
			for(y=rect.top;y<=rect.bottom;y++)
			{
				if(IsBlankV(rect.right,rect.top + 1,y)
				&& IsBlankH(y,rect.left + 1,rect.right - 1)
				&& IsBlankV(rect.left,y,rect.bottom - 1))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.left,rect.bottom);
						pPath->AddPoint(rect.left,y);
						pPath->AddPoint(rect.right,y);
						pPath->AddPoint(rect.right,rect.top);
					}
					return TRUE;
				}
			}
		}
	}
	if(b45)
	{//起点到终点连线为“\”
		if(y1!=y2)
		{
			//向右找
			for(x=rect.right + 1;x<=m_iCols+1;x++)
			{
				if(IsBlankH(rect.top,rect.left + 1,x)
				&& IsBlankV(x,rect.top + 1,rect.bottom - 1)
				&& IsBlankH(rect.bottom,rect.right + 1,x))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.left,rect.top);
						pPath->AddPoint(x,rect.top);
						pPath->AddPoint(x,rect.bottom);
						pPath->AddPoint(rect.right,rect.bottom);
					}
					return TRUE;
				}
			}
			//向左找
			for(x=rect.left - 1;x>=0;x--)
			{
				if(IsBlankH(rect.top,x,rect.left - 1)
				&& IsBlankV(x,rect.top + 1,rect.bottom - 1)
				&& IsBlankH(rect.bottom,x,rect.right - 1))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.left,rect.top);
						pPath->AddPoint(x,rect.top);
						pPath->AddPoint(x,rect.bottom);
						pPath->AddPoint(rect.right,rect.bottom);
					}
					return TRUE;
				}
			}
		}
		if(x1!=x2)
		{
			//向上找
			for(y=rect.top-1;y>=0;y--)
			{
				if(IsBlankV(rect.left,y,rect.top - 1)
				&& IsBlankH(y,rect.left + 1,rect.right - 1)
				&& IsBlankV(rect.right,y,rect.bottom - 1))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.left,rect.top);
						pPath->AddPoint(rect.left,y);
						pPath->AddPoint(rect.right,y);
						pPath->AddPoint(rect.right,rect.bottom);
					}
					return TRUE;
				}
			}
			//向下找
			for(y=rect.bottom + 1;y<=m_iRows + 1;y++)
			{
				if(IsBlankV(rect.left,rect.top + 1,y)
				&& IsBlankH(y,rect.left + 1,rect.right - 1)
				&& IsBlankV(rect.right,rect.bottom + 1,y))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.left,rect.top);
						pPath->AddPoint(rect.left,y);
						pPath->AddPoint(rect.right,y);
						pPath->AddPoint(rect.right,rect.bottom);
					}
					return TRUE;
				}
			}
		}
	}
	else
	{//起点到终点连线为“/”
		if(y1!=y2)
		{
			//向右找
			for(x=rect.right + 1;x<=m_iCols+1;x++)
			{
				if(IsBlankH(rect.bottom,rect.left + 1,x)
				&& IsBlankV(x,rect.top + 1,rect.bottom - 1)
				&& IsBlankH(rect.top,rect.right + 1,x))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.right,rect.top);
						pPath->AddPoint(x,rect.top);
						pPath->AddPoint(x,rect.bottom);
						pPath->AddPoint(rect.left,rect.bottom);
					}
					return TRUE;
				}
			}
			//向左找
			for(x=rect.left - 1;x>=0;x--)
			{
				if(IsBlankH(rect.bottom,x,rect.left - 1)
				&& IsBlankV(x,rect.top + 1,rect.bottom - 1)
				&& IsBlankH(rect.top,x,rect.right - 1))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.right,rect.top);
						pPath->AddPoint(x,rect.top);
						pPath->AddPoint(x,rect.bottom);
						pPath->AddPoint(rect.left,rect.bottom);
					}
					return TRUE;
				}
			}
		}
		if(x1!=x2)
		{
			//向上找
			for(y=rect.top-1;y>=0;y--)
			{
				if(IsBlankV(rect.right,y,rect.top - 1)
				&& IsBlankH(y,rect.left + 1,rect.right - 1)
				&& IsBlankV(rect.left,y,rect.bottom - 1))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.left,rect.bottom);
						pPath->AddPoint(rect.left,y);
						pPath->AddPoint(rect.right,y);
						pPath->AddPoint(rect.right,rect.top);
					}
					return TRUE;
				}
			}
			//向下找
			for(y=rect.bottom + 1;y<=m_iRows + 1;y++)
			{
				if(IsBlankV(rect.right,rect.top + 1,y)
				&& IsBlankH(y,rect.left + 1,rect.right - 1)
				&& IsBlankV(rect.left,rect.bottom + 1,y))
				{
					if(pPath)
					{
						pPath->AddPoint(rect.left,rect.bottom);
						pPath->AddPoint(rect.left,y);
						pPath->AddPoint(rect.right,y);
						pPath->AddPoint(rect.right,rect.top);
					}
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

/**************************************************\
获取提示
返回
-1		失败（已经没有图标了）
0		失败
1		成功，提示路径在 pPath 中
\**************************************************/
int CLinkMatrix::GetHelp(CLinkPath*pPath)
{
	int	nHaveIcon = -1;
	if(pPath)
	{
		pPath->Empty();
	}
	int	x1,y1;	//起点
	int	x2,y2;	//终点
	int	f	=	XYtoIndex(1,1);
	int	t	=	XYtoIndex(m_iCols,m_iRows);
	int	i,j;
	ICONDATA nIcon;

	for(i=f;i<=t;i++)
	{
		if(nIcon=m_pMatrix[i])
		{
			nHaveIcon	=	0;
			IndexToXY(i,x1,y1);
			for(j=i+1;j<=t;j++)
			{
				if(nIcon==m_pMatrix[j])
				{
					IndexToXY(j,x2,y2);
					if(FindPath(x1,y1,x2,y2,pPath))
						return 1;
				}
			}
		}
	}
	return nHaveIcon;
}

/**************************************************\
重新布局
\**************************************************/
void CLinkMatrix::ChangeLayout()
{
	CDWordArray	arrX;
	CDWordArray	arrY;
	CDWordArray	arrIcon;
	int			x,y,nIcon;
	int			i,p;

	do 
	{
		for(y=1;y<=m_iRows;y++)
		{
			for(x=1;x<=m_iCols;x++)
			{
				if(nIcon=operator()(x,y))
				{
					arrIcon.Add(nIcon);
					arrX.Add(x);
					arrY.Add(y);
				}
			}
		}
		for(i=arrIcon.GetSize() - 1;i>=0;i--)
		{
			p	=	rand() % (i + 1);
			operator()(arrX[i],arrY[i])	=	(ICONDATA)arrIcon[p];
			arrIcon.RemoveAt(p);
		}
		arrX.RemoveAll();
		arrY.RemoveAll();
	}while(0==GetHelp());
}

/**************************************************\
获取提示
返回
0		失败
1		成功，提示路径在 pPath 中
\**************************************************/
int CLinkMatrix::GetHelp(int x0,int y0,CLinkPath*pPath)
{
	if(pPath)
	{
		pPath->Empty();
	}
	if(x0 < 1 || x0 > m_iCols
	|| y0 < 1 || y0 > m_iRows)
	{//在范围外，则直接返回 FALSE
		return 0;
	}
	ICONDATA nIcon	=	operator()(x0,y0);
	if(nIcon)
	{
		int x,y;
		int	f	=	XYtoIndex(1,1);
		int	t	=	XYtoIndex(m_iCols,m_iRows);
		int	i;
		for(i=f;i<=t;i++)
		{
			if(nIcon==m_pMatrix[i])
			{
				IndexToXY(i,x,y);
				if(FindPath(x0,y0,x,y,pPath))
					return 1;
			}
		}
	}
	return 0;
}

CString CLinkMatrix::GetMoveModeStr()
{
	switch(m_iMoveMode)
	{
		case MOVE_Up:			return _T("向上");
		case MOVE_Down:			return _T("向下");
		case MOVE_Left:			return _T("向左");
		case MOVE_Right:		return _T("向右");
		case MOVE_LU:			return _T("向左上");
		case MOVE_LD:			return _T("向左下");
		case MOVE_RU:			return _T("向右上");
		case MOVE_RD:			return _T("向右下");
		case MOVE_ULDR:			return _T("上左下右");
		case MOVE_URDL:			return _T("上右下左");
		case MOVE_LDRU:			return _T("左下右上");
		case MOVE_LURD:			return _T("左上右下");
		case MOVE_FenLiH:		return _T("横向分离");
		case MOVE_FenLiV:		return _T("竖向分离");
		case MOVE_JiZhongH:		return _T("横向集中");
		case MOVE_JiZhongV:		return _T("竖向集中");
		case MOVE_DengFenH:		return _T("横向等分");
		case MOVE_DengFenV:		return _T("竖向等分");
		case MOVE_JuZhongH:		return _T("横向居中");
		case MOVE_JuZhongV:		return _T("竖向居中");
		case MOVE_HCuo:			return _T("横向错开(奇数行向左,偶数行向右)");
		case MOVE_VCuo:			return _T("竖向错开(奇数列向上,偶数列向下)");
		case MOVE_HCuoFen:		return _T("横向错开(奇数行分离,偶数行集中)");
		case MOVE_VCuoFen:		return _T("竖向错开(奇数列分离,偶数列集中)");
		case MOVE_HCuoDeng:		return _T("横向错开(奇数行等分,偶数行居中)");
		case MOVE_VCuoDeng:		return _T("竖向错开(奇数列等分,偶数列居中)");
		case MOVE_KuoSanHV:		return _T("扩散(每行等分,然后每列等分)");
		case MOVE_KuoSanVH:		return _T("扩散(每列等分,然后每行等分)");
		case MOVE_JiZhongHV:	return _T("集中(每行居中,然后每列居中)");
		case MOVE_JiZhongVH:	return _T("集中(每列居中,然后每行居中)");
		case MOVE_ZUp:			return _T("Z 形向上");
		case MOVE_ZDown:		return _T("Z 形向下");
		case MOVE_NLeft:		return _T("N 形向左");
		case MOVE_NRight:		return _T("N 形向右");
		case MOVE_SUp:			return _T("S 形向上");
		case MOVE_SDown:		return _T("S 形向下");
		case MOVE_RotL:			return _T("逆时针回形旋转");
		case MOVE_RotR:			return _T("顺时针回形旋转");
		case MOVE_RotLR:		return _T("交错回形旋转");
		case MOVE_RotNLuoW:		return _T("逆时针螺旋向外");
		case MOVE_RotNLuoN:		return _T("逆时针螺旋向内");
		case MOVE_RotSLuoW:		return _T("顺时针螺旋向外");
		case MOVE_RotSLuoN:		return _T("顺时针螺旋向内");
	}
	return _T("不变化");
}

void CLinkMatrix::RemoveIcon(int x1,int y1,int x2,int y2)
{
	m_xSel	=
	m_ySel	=	0;
	operator()(x1,y1)=0;
	operator()(x2,y2)=0;
	switch(m_iMoveMode)
	{
		case MOVE_Up:		//向上
			MoveUp(x1,y1,x2,y2);	break;
		case MOVE_Down:		//向下
			MoveDown(x1,y1,x2,y2);	break;
		case MOVE_Left:		//向左
			MoveLeft(x1,y1,x2,y2);	break;
		case MOVE_Right:	//向右
			MoveRight(x1,y1,x2,y2);	break;
		case MOVE_LU:		//向左上
			MoveLU(x1,y1,x2,y2);	break;
		case MOVE_LD:		//向左下
			MoveLD(x1,y1,x2,y2);	break;
		case MOVE_RU:		//向右上
			MoveRU(x1,y1,x2,y2);	break;
		case MOVE_RD:		//向右下
			MoveRD(x1,y1,x2,y2);	break;
		case MOVE_ULDR:		//上左下右
			MoveULDR(x1,y1,x2,y2);	break;
		case MOVE_URDL:		//上右下左
			MoveURDL(x1,y1,x2,y2);	break;
		case MOVE_LDRU:		//左下右上
			MoveLDRU(x1,y1,x2,y2);	break;
		case MOVE_LURD:		//左上右下
			MoveLURD(x1,y1,x2,y2);	break;
		case MOVE_FenLiH:	//行分离
			MoveFenLiH(x1,y1,x2,y2);break;
		case MOVE_FenLiV:	//列分离
			MoveFenLiV(x1,y1,x2,y2);break;
		case MOVE_JiZhongH:	//行集中
			MoveJiZhongH(x1,y1,x2,y2);break;
		case MOVE_JiZhongV:	//列集中
			MoveJiZhongV(x1,y1,x2,y2);break;
		case MOVE_DengFenH:	//行等分
			MoveDengH(x1,y1,x2,y2);break;
		case MOVE_DengFenV:	//列等分
			MoveDengV(x1,y1,x2,y2);break;
		case MOVE_JuZhongH:	//行居中
			MoveJuZhongH(x1,y1,x2,y2);break;
		case MOVE_JuZhongV:	//列居中
			MoveJuZhongV(x1,y1,x2,y2);break;
		case MOVE_HCuo:		//行错开(奇左偶右)
			MoveCuoH(x1,y1,x2,y2);break;
		case MOVE_VCuo:		//列错开(奇上偶下)
			MoveCuoV(x1,y1,x2,y2);break;
		case MOVE_HCuoFen:	//行错开(奇分离偶集中)
			MoveCuoFenH(x1,y1,x2,y2);break;
		case MOVE_VCuoFen:	//列错开(奇分离偶集中)
			MoveCuoFenV(x1,y1,x2,y2);break;
		case MOVE_HCuoDeng:	//行错开(奇等分偶居中)
			MoveCuoDengH(x1,y1,x2,y2);break;
		case MOVE_VCuoDeng:	//列错开(奇等分偶居中)
			MoveCuoDengV(x1,y1,x2,y2);break;
		case MOVE_KuoSanHV:	//扩散(先行后列)
			MoveKuoSanHV(x1,y1,x2,y2);break;
		case MOVE_KuoSanVH:	//扩散(先行后列)
			MoveKuoSanVH(x1,y1,x2,y2);break;
		case MOVE_JiZhongHV://集中(先行后列)
			MoveJiZhongHV(x1,y1,x2,y2);break;
		case MOVE_JiZhongVH://集中(先行后列)
			MoveJiZhongVH(x1,y1,x2,y2);break;
		case MOVE_ZUp:		//Z 形向上
			MoveZUpDown(TRUE);break;
		case MOVE_ZDown:	//Z 形向下
			MoveZUpDown(FALSE);break;
		case MOVE_NLeft:	//N 形向左
			MoveNLeftRight(TRUE);break;
		case MOVE_NRight:	//N 形向右
			MoveNLeftRight(FALSE);break;
		case MOVE_SUp:		//S 形向上
			MoveSUpDown(TRUE);break;
		case MOVE_SDown:	//S 形向下
			MoveSUpDown(FALSE);break;
		case MOVE_RotL:		//逆时针回形旋转
			MoveRotL(x1,y1,x2,y2);break;
		case MOVE_RotR:		//顺时针回形旋转
			MoveRotR(x1,y1,x2,y2);break;
		case MOVE_RotLR:	//交错回形旋转
			MoveRotLR(x1,y1,x2,y2);break;
		case MOVE_RotNLuoW:	//逆时针螺旋向外
			MoveRotLuo2(TRUE);break;
		case MOVE_RotNLuoN:	//逆时针螺旋向内
			MoveRotLuo1(TRUE);break;
		case MOVE_RotSLuoW:	//顺时针螺旋向外
			MoveRotLuo1(FALSE);break;
		case MOVE_RotSLuoN:	//顺时针螺旋向内
			MoveRotLuo2(FALSE);break;
	}
}

void CLinkMatrix::MoveDown(int x1,int y1,int x2,int y2)
{
	MoveDown(x1);
	if(x1!=x2)
	{
		MoveDown(x2);
	}
}

void CLinkMatrix::MoveLeft(int x1,int y1,int x2,int y2)
{
	MoveLeft(y1);
	if(y1!=y2)
	{
		MoveLeft(y2);
	}
}

/***********************************************\
向上移动一列
\***********************************************/
void CLinkMatrix::MoveUp(int x)
{
	int	p,y;

	for(p = y = 1;y <= m_iRows;y++)
	{
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(y > p)
			{
				operator()(x,p)	=	nIcon;
				nIcon			=	0;
			}
			p++;
		}
	}
}

/***********************************************\
向下移动一列
\***********************************************/
void CLinkMatrix::MoveDown(int x)
{
	int	p,y;

	for(p = y = m_iRows;y > 0;y--)
	{
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(y < p)
			{
				operator()(x,p)	=	nIcon;
				nIcon			=	0;
			}
			p--;
		}
	}
}

/***********************************************\
向左移动一行
\***********************************************/
void CLinkMatrix::MoveLeft(int y)
{
	int	p,x;

	for(p = x = 1;x <= m_iCols;x++)
	{
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(x > p)
			{
				operator()(p,y)	=	nIcon;
				nIcon			=	0;
			}
			p++;
		}
	}
}

/***********************************************\
向右移动一行
\***********************************************/
void CLinkMatrix::MoveRight(int y)
{
	int	p,x;

	for(p = x = m_iCols;x > 0;x--)
	{
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(x < p)
			{
				operator()(p,y)	=	nIcon;
				nIcon			=	0;
			}
			p--;
		}
	}
}

void CLinkMatrix::MoveUp(int x1,int y1,int x2,int y2)
{
	MoveUp(x1);
	if(x1!=x2)
	{
		MoveUp(x2);
	}
}

void CLinkMatrix::MoveRight(int x1,int y1,int x2,int y2)
{
	MoveRight(y1);
	if(y1!=y2)
	{
		MoveRight(y2);
	}
}

void CLinkMatrix::SetMoveMode(int iMode)
{
	m_iMoveMode = iMode % MOVE_COUNT;
	if(m_iMoveMode < 0)
	{
		m_iMoveMode += MOVE_COUNT;
	}
}

//分离一行
void CLinkMatrix::MoveFenLiRow(int y)
{
	int	p,x;
	int	xm	=	(m_iCols >> 1);

	for(p = x = 1;x <= xm;x++)
	{
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(x > p)
			{
				operator()(p,y)	=	nIcon;
				nIcon			=	0;
			}
			p++;
		}
	}
	for(p = x = m_iCols;x > xm;x--)
	{
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(x < p)
			{
				operator()(p,y)	=	nIcon;
				nIcon			=	0;
			}
			p--;
		}
	}
}

//分离一列
void CLinkMatrix::MoveFenLiCol(int x)
{
	int	p,y;
	int	ym	=	(m_iRows >> 1);

	for(p = y = m_iRows;y > ym;y--)
	{//向下移
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(y < p)
			{
				operator()(x,p)	=	nIcon;
				nIcon			=	0;
			}
			p--;
		}
	}
	for(p = y = 1;y <= ym;y++)
	{//向上移
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(y > p)
			{
				operator()(x,p)	=	nIcon;
				nIcon			=	0;
			}
			p++;
		}
	}
}

//集中一行
void CLinkMatrix::MoveJiZhongRow(int y)
{
	int	p,x;
	int	xm	=	(m_iCols >> 1);

	for(p = x = xm;x >= 1;x--)
	{
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(x < p)
			{
				operator()(p,y)	=	nIcon;
				nIcon			=	0;
			}
			p--;
		}
	}
	for(p = x = xm + 1;x <= m_iCols;x++)
	{
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(x > p)
			{
				operator()(p,y)	=	nIcon;
				nIcon			=	0;
			}
			p++;
		}
	}
}

//集中一列
void CLinkMatrix::MoveJiZhongCol(int x)
{
	int	p,y;
	int	ym	=	(m_iRows >> 1);

	for(p = y = ym + 1;y <= m_iRows;y++)
	{//向上移
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(y > p)
			{
				operator()(x,p)	=	nIcon;
				nIcon			=	0;
			}
			p++;
		}
	}
	for(p = y = ym;y >= 1;y--)
	{//向下移
		ICONDATA&nIcon=operator()(x,y);
		if(nIcon)
		{
			if(y < p)
			{
				operator()(x,p)	=	nIcon;
				nIcon			=	0;
			}
			p--;
		}
	}
}

//统计一行的牌
int CLinkMatrix::CountIconRow(int y)
{
	int count	=	0;
	int	p		=	XYtoIndex(1,y);

	for(int x=1;x<=m_iCols;x++)
	{
		if(m_pMatrix[p++])
		{
			count++;
		}
	}
	return count;
}

//统计一列的牌
int CLinkMatrix::CountIconCol(int x)
{
	int count	=	0;
	int	p		=	XYtoIndex(x,1);

	for(int y=1;y<=m_iRows;y++)
	{
		if(m_pMatrix[p])
		{
			count++;
		}
		p+=m_iCols+2;
	}
	return count;
}

//向左上(x-y=c)
void CLinkMatrix::MoveLU(int x1,int y1,int x2,int y2)
{
	int	c1	=	x1 - y1;
	int	c2	=	x2 - y2;
	MoveLU(c1);
	if(c1!=c2)
	{
		MoveLU(c2);
	}
}

//向右下(x-y=c)
void CLinkMatrix::MoveRD(int x1,int y1,int x2,int y2)
{
	int	c1	=	x1 - y1;
	int	c2	=	x2 - y2;
	MoveRD(c1);
	if(c1!=c2)
	{
		MoveRD(c2);
	}
}

//向左下(x+y=c)
void CLinkMatrix::MoveLD(int x1,int y1,int x2,int y2)
{
	int	c1	=	x1 + y1;
	int	c2	=	x2 + y2;
	MoveLD(c1);
	if(c1!=c2)
	{
		MoveLD(c2);
	}
}

//向右上(x+y=c)
void CLinkMatrix::MoveRU(int x1,int y1,int x2,int y2)
{
	int	c1	=	x1 + y1;
	int	c2	=	x2 + y2;
	MoveRU(c1);
	if(c1!=c2)
	{
		MoveRU(c2);
	}
}

//向左上(x-y=c)
void CLinkMatrix::MoveLU(int c)
{
	int	xMin	=	max(1,c + 1);
	int xMax	=	min(m_iCols,c + m_iRows);

	int x,y,p;
	for(y = p = (x = xMin) - c;x <= xMax;x++,y++)
	{
		ICONDATA&nIcon	=	operator()(x,y);
		if(nIcon)
		{
			if(y > p)
			{
				operator()(c+p,p)	=	nIcon;
				nIcon				=	0;
			}
			p++;
		}
	}
}

//向右下(x-y=c)
void CLinkMatrix::MoveRD(int c)
{
	int	xMin	=	max(1,c + 1);
	int xMax	=	min(m_iCols,c + m_iRows);

	int x,y,p;

	for(y = p = (x = xMax) - c;x >= xMin;x--,y--)
	{
		ICONDATA&nIcon	=	operator()(x,y);
		if(nIcon)
		{
			if(y < p)
			{
				operator()(c+p,p)	=	nIcon;
				nIcon				=	0;
			}
			p--;
		}
	}
}

//向左下(x+y=c)
void CLinkMatrix::MoveLD(int c)
{
	int	xMin	=	max(1,c - m_iRows);
	int xMax	=	min(m_iCols,c - 1);

	int x,y,p;

	for(y = p = c - (x = xMin);x <= xMax;x++,y--)
	{
		ICONDATA&nIcon	=	operator()(x,y);
		if(nIcon)
		{
			if(y < p)
			{
				operator()(c-p,p)	=	nIcon;
				nIcon				=	0;
			}
			p--;
		}
	}
}

//向右上(x+y=c)
void CLinkMatrix::MoveRU(int c)
{
	int	xMin	=	max(1,c - m_iRows);
	int xMax	=	min(m_iCols,c - 1);

	int x,y,p;

	for(y = p = c - (x = xMax);x >= xMin;x--,y++)
	{
		ICONDATA&nIcon	=	operator()(x,y);
		if(nIcon)
		{
			if(y > p)
			{
				operator()(c-p,p)	=	nIcon;
				nIcon				=	0;
			}
			p++;
		}
	}
}

//上左下右
void CLinkMatrix::MoveULDR(int x1,int y1,int x2,int y2)
{
	int	ym	=	(m_iRows >> 1);
	int y;
	int i	=	(y1==y2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			y	=	y1;
		}
		else
		{
			y	=	y2;
		}
		if(y <= ym)
		{
			MoveLeft(y);
		}
		else
		{
			MoveRight(y);
		}
	}
}

//上右下左
void CLinkMatrix::MoveURDL(int x1,int y1,int x2,int y2)
{
	int	ym	=	(m_iRows >> 1);
	int y;
	int i	=	(y1==y2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			y	=	y1;
		}
		else
		{
			y	=	y2;
		}
		if(y <= ym)
		{
			MoveRight(y);
		}
		else
		{
			MoveLeft(y);
		}
	}
}

//左下右上
void CLinkMatrix::MoveLDRU(int x1,int y1,int x2,int y2)
{
	int	xm	=	(m_iCols >> 1);
	int x;
	int i	=	(x1==x2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			x	=	x1;
		}
		else
		{
			x	=	x2;
		}
		if(x <= xm)
		{
			MoveDown(x);
		}
		else
		{
			MoveUp(x);
		}
	}
}

//左上右下
void CLinkMatrix::MoveLURD(int x1,int y1,int x2,int y2)
{
	int	xm	=	(m_iCols >> 1);
	int x;
	int i	=	(x1==x2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			x	=	x1;
		}
		else
		{
			x	=	x2;
		}
		if(x <= xm)
		{
			MoveUp(x);
		}
		else
		{
			MoveDown(x);
		}
	}
}

//横向分离
void CLinkMatrix::MoveFenLiH(int x1,int y1,int x2,int y2)
{
	MoveFenLiRow(y1);
	if(y1!=y2)
	{
		MoveFenLiRow(y2);
	}
}

//竖向分离
void CLinkMatrix::MoveFenLiV(int x1,int y1,int x2,int y2)
{
	MoveFenLiCol(x1);
	if(x1!=x2)
	{
		MoveFenLiCol(x2);
	}
}

//横向集中
void CLinkMatrix::MoveJiZhongH(int x1,int y1,int x2,int y2)
{
	MoveJiZhongRow(y1);
	if(y1!=y2)
	{
		MoveJiZhongRow(y2);
	}
}

//竖向集中
void CLinkMatrix::MoveJiZhongV(int x1,int y1,int x2,int y2)
{
	MoveJiZhongCol(x1);
	if(x1!=x2)
	{
		MoveJiZhongCol(x2);
	}
}

//横向等分
void CLinkMatrix::MoveDengH(int x1,int y1,int x2,int y2)
{
	MoveDengRow(y1);
	if(y1!=y2)
	{
		MoveDengRow(y2);
	}
}

//竖向等分
void CLinkMatrix::MoveDengV(int x1,int y1,int x2,int y2)
{
	MoveDengCol(x1);
	if(x1!=x2)
	{
		MoveDengCol(x2);
	}
}

//行居中
void CLinkMatrix::MoveJuZhongH(int x1,int y1,int x2,int y2)
{
	MoveJuZhongRow(y1);
	if(y1!=y2)
	{
		MoveJuZhongRow(y2);
	}
}

//列居中
void CLinkMatrix::MoveJuZhongV(int x1,int y1,int x2,int y2)
{
	MoveJuZhongCol(x1);
	if(x1!=x2)
	{
		MoveJuZhongCol(x2);
	}
}

//等分一行
void CLinkMatrix::MoveDengRow(int y)
{
	int	x;
	int p		=	XYtoIndex(1,y);
	int count	=	0;

	for(x = 1;x <= m_iCols;x++)
	{
		ICONDATA&nIcon	=	m_pMatrix[p++];
		if(nIcon)
		{
			m_pMatrix[count++]	=	nIcon;
		}
	}
	if(!count)
	{//无牌可分
		return;
	}
	if(count < m_iCols)
	{
		int	CountL	=	(count >> 1);	//左边的牌数
		int	CountR	=	count - CountL;	//右边的牌数
		p			=	XYtoIndex(1,y);

		if(CountL)
		{
			memcpy(m_pMatrix + p,m_pMatrix,sizeof(ICONDATA) * CountL);
		}
		memset(m_pMatrix + p + CountL,0,sizeof(ICONDATA) * (m_iCols - count));
		if(CountR)
		{
			memcpy(m_pMatrix + (p + CountL + m_iCols - count),m_pMatrix + CountL,sizeof(ICONDATA) * CountR);
		}
	}
	memset(m_pMatrix,0,sizeof(ICONDATA) * count);
}

//等分一列
void CLinkMatrix::MoveDengCol(int x)
{
	int	y;
	int p		=	XYtoIndex(x,1);
	int count	=	0;

	for(y = 1;y <= m_iRows;y++)
	{
		ICONDATA&nIcon	=	m_pMatrix[p];
		if(nIcon)
		{
			m_pMatrix[count++ * (m_iCols + 2)]	=	nIcon;
		}
		p+=(m_iCols + 2);
	}
	if(!count)
	{//无牌可分
		return;
	}
	if(count < m_iRows)
	{
		int	CountU	=	(count >> 1);	//上边的牌数
		int	CountD	=	count - CountU;	//下边的牌数
		p			=	0;

		for(y=1;y <= CountU;y++)
		{
			operator()(x,y) =	m_pMatrix[p];
			p			   +=	(m_iCols + 2);
		}
		for(y = m_iRows - count;y > 0;y--)
		{
			operator()(x,CountU + y)	=	0;
		}
		for(y = CountD - 1;y >= 0;y--)
		{
			operator()(x,m_iRows - y) =	m_pMatrix[p];
			p			   +=	(m_iCols + 2);
		}
	}
	for(p = y = 0;y < count;y++)
	{
		m_pMatrix[p]	=	0;
		p			   +=	(m_iCols + 2);
	}
}

//居中一行
void CLinkMatrix::MoveJuZhongRow(int y)
{
	int	x;
	int p		=	XYtoIndex(1,y);
	int count	=	0;

	for(x = 1;x <= m_iCols;x++)
	{
		ICONDATA&nIcon	=	m_pMatrix[p++];
		if(nIcon)
		{
			m_pMatrix[count++]	=	nIcon;
		}
	}
	if(!count)
	{//无牌可分
		return;
	}
	if(count < m_iCols)
	{
		p	=	XYtoIndex(1,y);
		memset(m_pMatrix + p,0,sizeof(ICONDATA) * m_iCols);
		memcpy(m_pMatrix + p + ((m_iCols - count)>>1)
			,m_pMatrix,sizeof(ICONDATA) * count);
	}
	memset(m_pMatrix,0,sizeof(ICONDATA) * count);
}

//居中一列
void CLinkMatrix::MoveJuZhongCol(int x)
{
	int	y;
	int p		=	XYtoIndex(x,1);
	int count	=	0;

	for(y = 1;y <= m_iRows;y++)
	{
		ICONDATA&nIcon	=	m_pMatrix[p];
		if(nIcon)
		{
			m_pMatrix[count++ * (m_iCols + 2)]	=	nIcon;
		}
		p+=(m_iCols + 2);
	}
	if(!count)
	{//无牌可分
		return;
	}
	if(count < m_iRows)
	{
		p	=	0;
		int	yf	=	((m_iRows + 2 - count) >> 1);
		int	yt	=	yf + count - 1;
		for(y=1;y <= m_iRows;y++)
		{
			ICONDATA&nIcon	=	operator()(x,y);
			if(y < yf || y > yt)
			{
				nIcon	=	0;
			}
			else
			{
				nIcon	=	m_pMatrix[p];
				p	   +=	(m_iCols + 2);
			}
		}
	}
	for(p = y = 0;y < count;y++)
	{
		m_pMatrix[p]	=	0;
		p			   +=	(m_iCols + 2);
	}
}

//行错开(奇左偶右)
void CLinkMatrix::MoveCuoH(int x1,int y1,int x2,int y2)
{
	int y;
	int	i	=	(y1==y2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			y	=	y1;
		}
		else
		{
			y	=	y2;
		}
		if(y & 1)
		{
			MoveLeft(y);
		}
		else
		{
			MoveRight(y);
		}
	}
}

//列错开(奇上偶下)
void CLinkMatrix::MoveCuoV(int x1,int y1,int x2,int y2)
{
	int x;
	int	i	=	(x1==x2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			x	=	x1;
		}
		else
		{
			x	=	x2;
		}
		if(x & 1)
		{
			MoveUp(x);
		}
		else
		{
			MoveDown(x);
		}
	}
}

//行错开(奇分离偶集中)
void CLinkMatrix::MoveCuoFenH(int x1,int y1,int x2,int y2)
{
	int y;
	int	i	=	(y1==y2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			y	=	y1;
		}
		else
		{
			y	=	y2;
		}
		if(y & 1)
		{
			MoveFenLiRow(y);
		}
		else
		{
			MoveJiZhongRow(y);
		}
	}
}

//列错开(奇分离偶集中)
void CLinkMatrix::MoveCuoFenV(int x1,int y1,int x2,int y2)
{
	int x;
	int	i	=	(x1==x2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			x	=	x1;
		}
		else
		{
			x	=	x2;
		}
		if(x & 1)
		{
			MoveFenLiCol(x);
		}
		else
		{
			MoveJiZhongCol(x);
		}
	}
}

//行错开(奇等分偶居中)
void CLinkMatrix::MoveCuoDengH(int x1,int y1,int x2,int y2)
{
	int y;
	int	i	=	(y1==y2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			y	=	y1;
		}
		else
		{
			y	=	y2;
		}
		if(y & 1)
		{
			MoveDengRow(y);
		}
		else
		{
			MoveJuZhongRow(y);
		}
	}
}

//列错开(奇等分偶居中)
void CLinkMatrix::MoveCuoDengV(int x1,int y1,int x2,int y2)
{
	int x;
	int	i	=	(x1==x2 ? 1 : 2);

	while(i--)
	{
		if(i)
		{
			x	=	x1;
		}
		else
		{
			x	=	x2;
		}
		if(x & 1)
		{
			MoveDengCol(x);
		}
		else
		{
			MoveJuZhongCol(x);
		}
	}
}

//扩散(先行后列)
void CLinkMatrix::MoveKuoSanHV(int x1,int y1,int x2,int y2)
{
	for(int y=1;y<=m_iRows;y++)
	{
		MoveDengRow(y);
	}
	for(int x=1;x<=m_iCols;x++)
	{
		MoveDengCol(x);
	}
}

//扩散(先列后行)
void CLinkMatrix::MoveKuoSanVH(int x1,int y1,int x2,int y2)
{
	for(int x=1;x<=m_iCols;x++)
	{
		MoveDengCol(x);
	}
	for(int y=1;y<=m_iRows;y++)
	{
		MoveDengRow(y);
	}
}

//集中(先行后列)
void CLinkMatrix::MoveJiZhongHV(int x1,int y1,int x2,int y2)
{
	for(int y=1;y<=m_iRows;y++)
	{
		MoveJuZhongRow(y);
	}
	for(int x=1;x<=m_iCols;x++)
	{
		MoveJuZhongCol(x);
	}
}

//集中(先列后行)
void CLinkMatrix::MoveJiZhongVH(int x1,int y1,int x2,int y2)
{
	for(int x=1;x<=m_iCols;x++)
	{
		MoveJuZhongCol(x);
	}
	for(int y=1;y<=m_iRows;y++)
	{
		MoveJuZhongRow(y);
	}
}

/************************************************\
获得圈的编号(最外一圈编号为 1,往里编号增大)
返回 0 表示不在圈上
\************************************************/
int CLinkMatrix::GetLoopNumber(int x,int y)
{
	if(x <= ((m_iCols + 1) >> 1))
	{//左边
		if(y >= x && y <= m_iRows + 1 - x)
		{
			return x;
		}
	}
	else
	{//右边
		if(y >= m_iCols + 1 - x && y <= x + m_iRows - m_iCols)
		{
			return m_iCols + 1 - x;
		}
	}
	if(y <= ((m_iRows + 1) >> 1))
	{//上边
		if(x >= y && x <= m_iCols + 1 - y)
		{
			return y;
		}
	}
	else
	{//下边
		if(x >= m_iRows + 1 - y && x <= y + m_iCols - m_iRows)
		{
			return m_iRows + 1 - y;
		}
	}
	return 0;
}

//逆时针回形旋转
void CLinkMatrix::MoveRotL(int x1,int y1,int x2,int y2)
{
	int	L1	=	GetLoopNumber(x1,y1);
	if(L1)
	{
		MoveRotL(L1);
	}
	int	L2	=	GetLoopNumber(x2,y2);
	if(L2 && L1!=L2)
	{
		MoveRotL(L2);
	}
}

//顺时针回形旋转
void CLinkMatrix::MoveRotR(int x1,int y1,int x2,int y2)
{
	int	L1	=	GetLoopNumber(x1,y1);
	if(L1)
	{
		MoveRotR(L1);
	}
	int	L2	=	GetLoopNumber(x2,y2);
	if(L2 && L1!=L2)
	{
		MoveRotR(L2);
	}
}

void CLinkMatrix::MoveRotL(int nLoop)
{
	int			xMin	=	nLoop;
	int			xMax	=	m_iCols + 1 - nLoop;
	int			yMin	=	nLoop;
	int			yMax	=	m_iRows + 1 - nLoop;
	int			x,y;
	int			nIndex;
	CDWordArray	arrIcon;
	CDWordArray	arrIndex;

	x	=	(m_iRows + m_iCols) << 1;
	arrIndex.SetSize(0,x);
	arrIcon.SetSize(0,x);

	//提取牌---------------------------------
	//上
	for(x = xMin,y = yMin;x <= xMax;x++)
	{
		arrIndex.Add(nIndex = XYtoIndex(x,y));
		ICONDATA&nIcon = m_pMatrix[nIndex];
		if(nIcon)
		{
			arrIcon.Add(nIcon);
		}
	}
	//右
	for(x = xMax,y = yMin + 1;y < yMax;y++)
	{
		arrIndex.Add(nIndex = XYtoIndex(x,y));
		ICONDATA&nIcon = m_pMatrix[nIndex];
		if(nIcon)
		{
			arrIcon.Add(nIcon);
		}
	}
	//下
	if(yMax > yMin)
	{
		for(x = xMax,y = yMax;x >= xMin;x--)
		{
			arrIndex.Add(nIndex = XYtoIndex(x,y));
			ICONDATA&nIcon = m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
	}
	//左
	if(xMax > xMin)
	{
		for(x = xMin,y = yMax - 1;y > yMin;y--)
		{
			arrIndex.Add(nIndex = XYtoIndex(x,y));
			ICONDATA&nIcon = m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
	}
	int	nCountIndex	=	arrIndex.GetSize();
	int	nCountIcon	=	arrIcon.GetSize();
	if(nCountIndex > nCountIcon)
	{
		int i;
		for(i=0;i<nCountIcon;i++)
		{
			m_pMatrix[arrIndex[i]]	=	(ICONDATA)arrIcon[i];
		}
		while(i < nCountIndex)
		{
			m_pMatrix[arrIndex[i++]]	=	0;
		}
	}
}

void CLinkMatrix::MoveRotR(int nLoop)
{
	int			xMin	=	nLoop;
	int			xMax	=	m_iCols + 1 - nLoop;
	int			yMin	=	nLoop;
	int			yMax	=	m_iRows + 1 - nLoop;
	int			x,y;
	int			nIndex;
	CDWordArray	arrIcon;
	CDWordArray	arrIndex;

	x	=	(m_iRows + m_iCols) << 1;
	arrIndex.SetSize(0,x);
	arrIcon.SetSize(0,x);

	//提取牌---------------------------------
	//左
	for(x = xMin,y = yMin;y <= yMax;y++)
	{
		arrIndex.Add(nIndex = XYtoIndex(x,y));
		ICONDATA&nIcon = m_pMatrix[nIndex];
		if(nIcon)
		{
			arrIcon.Add(nIcon);
		}
	}
	//下
	for(x = xMin + 1,y = yMax;x < xMax;x++)
	{
		arrIndex.Add(nIndex = XYtoIndex(x,y));
		ICONDATA&nIcon = m_pMatrix[nIndex];
		if(nIcon)
		{
			arrIcon.Add(nIcon);
		}
	}
	//右
	if(xMax > xMin)
	{
		for(x = xMax,y = yMax;y >= yMin;y--)
		{
			arrIndex.Add(nIndex = XYtoIndex(x,y));
			ICONDATA&nIcon = m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
	}
	//上
	if(yMax > yMin)
	{
		for(x = xMax - 1,y = yMin;x > xMin;x--)
		{
			arrIndex.Add(nIndex = XYtoIndex(x,y));
			ICONDATA&nIcon = m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
	}
	int	nCountIndex	=	arrIndex.GetSize();
	int	nCountIcon	=	arrIcon.GetSize();
	if(nCountIndex > nCountIcon)
	{
		int i;
		for(i=0;i<nCountIcon;i++)
		{
			m_pMatrix[arrIndex[i]]	=	(ICONDATA)arrIcon[i];
		}
		while(i < nCountIndex)
		{
			m_pMatrix[arrIndex[i++]]	=	0;
		}
	}
}

//交错回形旋转
void CLinkMatrix::MoveRotLR(int x1,int y1,int x2,int y2)
{
	int	L1	=	GetLoopNumber(x1,y1);
	int	L2	=	GetLoopNumber(x2,y2);
	int L;
	int	i	=	L1 == L2 ? 1 : 2;

	while(i--)
	{
		if(i)
		{
			L	=	L1;
		}
		else
		{
			L	=	L2;
		}

		if(L)
		{
			if(L & 1)
			{
				MoveRotL(L);
			}
			else
			{
				MoveRotR(L);
			}
		}
	}
}

void CLinkMatrix::FillIcon(CDWordArray&arrIndex,CDWordArray&arrIcon,BOOL bLeft)
{
	int	p;
	int	CountIcon	=	arrIcon.GetSize();
	int	CountIndex	=	arrIndex.GetSize();

	if(0==CountIcon || CountIcon==CountIndex)
	{
		return;
	}
	if(bLeft)
	{
		for(p=0;p < CountIcon;p++)
		{
			m_pMatrix[arrIndex[p]]=(ICONDATA)arrIcon[p];
		}
		while(p < CountIndex)
		{
			m_pMatrix[arrIndex[p++]]=0;
		}
	}
	else
	{
		for(p=1;p <= CountIcon;p++)
		{
			m_pMatrix[arrIndex[CountIndex - p]]	=	(ICONDATA)arrIcon[CountIcon - p];
		}
		for(p = CountIndex - CountIcon - 1;p>=0;p--)
		{
			m_pMatrix[arrIndex[p]]=0;
		}
	}
}

//S 形向上
void CLinkMatrix::MoveSUpDown(BOOL bUp)
{
	CDWordArray	arrIndex;
	CDWordArray	arrIcon;
	int			c	=	m_iRows * m_iCols;

	arrIndex.SetSize(0,c);
	arrIcon.SetSize(0,c);
	int x,y,nIndex;
	for(y=1;y<=m_iRows;y++)
	{
		if(y & 1)
		{
			for(x=m_iCols;x>=1;x--)
			{
				nIndex		=	XYtoIndex(x,y);
				arrIndex.Add(nIndex);
				ICONDATA&nIcon	=	m_pMatrix[nIndex];
				if(nIcon)
				{
					arrIcon.Add(nIcon);
				}
			}
		}
		else
		{
			for(x=1;x<=m_iCols;x++)
			{
				nIndex		=	XYtoIndex(x,y);
				arrIndex.Add(nIndex);
				ICONDATA&nIcon	=	m_pMatrix[nIndex];
				if(nIcon)
				{
					arrIcon.Add(nIcon);
				}
			}
		}
	}
	FillIcon(arrIndex,arrIcon,bUp);
}

//Z 形向上
void CLinkMatrix::MoveZUpDown(BOOL bUp)
{
	CDWordArray	arrIndex;
	CDWordArray	arrIcon;
	int			c	=	m_iRows * m_iCols;

	arrIndex.SetSize(0,c);
	arrIcon.SetSize(0,c);
	int x,y,nIndex;
	for(y=1;y<=m_iRows;y++)
	{
		for(x=1;x<=m_iCols;x++)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
	}
	FillIcon(arrIndex,arrIcon,bUp);
}

//N 形向左
void CLinkMatrix::MoveNLeftRight(BOOL bLeft)
{
	CDWordArray	arrIndex;
	CDWordArray	arrIcon;
	int			c	=	m_iRows * m_iCols;

	arrIndex.SetSize(0,c);
	arrIcon.SetSize(0,c);
	int x,y,nIndex;
	for(x=1;x<=m_iCols;x++)
	{
		for(y=m_iRows;y>=1;y--)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
	}
	FillIcon(arrIndex,arrIcon,bLeft);
}

//顺时针螺旋向外/逆时针螺旋向内
void CLinkMatrix::MoveRotLuo1(BOOL bNi)
{
	CDWordArray	arrIndex;
	CDWordArray	arrIcon;
	int			c	=	m_iRows * m_iCols;

	arrIndex.SetSize(0,c);
	arrIcon.SetSize(0,c);

	int x,y,nIndex;
	int xMin	=	1;
	int xMax	=	m_iCols;
	int yMin	=	1;
	int yMax	=	m_iRows;

	while(1)
	{
		if(xMin > xMax || yMin > yMax)
		{
			break;
		}
		if(xMin==xMax)
		{
			x	=	xMin;
			for(y=yMin;y<=yMax;y++)
			{
				nIndex		=	XYtoIndex(x,y);
				arrIndex.Add(nIndex);
				ICONDATA&nIcon	=	m_pMatrix[nIndex];
				if(nIcon)
				{
					arrIcon.Add(nIcon);
				}
			}
			break;
		}
		if(yMin==yMax)
		{
			y	=	yMin;
			for(x=xMin;x<=xMax;x++)
			{
				nIndex		=	XYtoIndex(x,y);
				arrIndex.Add(nIndex);
				ICONDATA&nIcon	=	m_pMatrix[nIndex];
				if(nIcon)
				{
					arrIcon.Add(nIcon);
				}
			}
			break;
		}
		//左
		x	=	xMin;
		for(y=yMin;y<=yMax;y++)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
		//下
		y	=	yMax;
		for(x=xMin + 1;x<=xMax;x++)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
		//右
		x	=	xMax;
		for(y=yMax-1;y>=yMin;y--)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
		//上
		y	=	yMin;
		for(x=xMax - 1;x > xMin;x--)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
		xMin++;
		yMin++;
		xMax--;
		yMax--;
	}
	FillIcon(arrIndex,arrIcon,!bNi);
}

//顺时针螺旋向内/逆时针螺旋向外
void CLinkMatrix::MoveRotLuo2(BOOL bNi)
{
	CDWordArray	arrIndex;
	CDWordArray	arrIcon;
	int			c	=	m_iRows * m_iCols;

	arrIndex.SetSize(0,c);
	arrIcon.SetSize(0,c);

	int x,y,nIndex;
	int xMin	=	1;
	int xMax	=	m_iCols;
	int yMin	=	1;
	int yMax	=	m_iRows;

	while(1)
	{
		if(xMin > xMax || yMin > yMax)
		{
			break;
		}
		if(xMin==xMax)
		{
			x	=	xMin;
			for(y=yMin;y<=yMax;y++)
			{
				nIndex		=	XYtoIndex(x,y);
				arrIndex.Add(nIndex);
				ICONDATA&nIcon	=	m_pMatrix[nIndex];
				if(nIcon)
				{
					arrIcon.Add(nIcon);
				}
			}
			break;
		}
		if(yMin==yMax)
		{
			y	=	yMin;
			for(x=xMin;x<=xMax;x++)
			{
				nIndex		=	XYtoIndex(x,y);
				arrIndex.Add(nIndex);
				ICONDATA&nIcon	=	m_pMatrix[nIndex];
				if(nIcon)
				{
					arrIcon.Add(nIcon);
				}
			}
			break;
		}
		//上
		y	=	yMin;
		for(x=xMin;x <= xMax;x++)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
		//右
		x	=	xMax;
		for(y=yMin + 1;y<=yMax;y++)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
		//下
		y	=	yMax;
		for(x=xMax - 1;x>=xMin;x--)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
		//左
		x	=	xMin;
		for(y=yMax-1;y>yMin;y--)
		{
			nIndex		=	XYtoIndex(x,y);
			arrIndex.Add(nIndex);
			ICONDATA&nIcon	=	m_pMatrix[nIndex];
			if(nIcon)
			{
				arrIcon.Add(nIcon);
			}
		}
		xMin++;
		yMin++;
		xMax--;
		yMax--;
	}
	FillIcon(arrIndex,arrIcon,bNi);
}

CLinkMatrix& CLinkMatrix::operator=(CLinkMatrix&src)
{
	if(this!=&src)
	{
		Init(src.m_iRows,src.m_iCols);
		if(m_pMatrix)
		{
			memcpy(m_pMatrix,src.m_pMatrix,(m_iRows + 2) * (m_iCols + 2) * sizeof(ICONDATA));
		}
		m_xSel		=	src.m_xSel;
		m_ySel		=	src.m_ySel;
		m_iMoveMode	=	src.m_iMoveMode;
	}
	return *this;
}