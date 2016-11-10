//LinkMatrix.h
#pragma once

typedef	unsigned char ICONDATA;

class CLinkPath
{
public:
	CLinkPath();
	void	Empty();
	void	AddPoint(int x,int y);
public:
	int		m_Count;
	int		m_x[4];
	int		m_y[4];
};

class CLinkMatrix  
{
public:
	enum
	{
		MOVE_None,		//不变化
		MOVE_Up,		//向上
		MOVE_Down,		//向下
		MOVE_Left,		//向左
		MOVE_Right,		//向右
		MOVE_LU,		//向左上
		MOVE_LD,		//向左下
		MOVE_RU,		//向右上
		MOVE_RD,		//向右下
		MOVE_ULDR,		//上左下右
		MOVE_URDL,		//上右下左
		MOVE_LDRU,		//左下右上
		MOVE_LURD,		//左上右下
		MOVE_FenLiH,	//横向分离
		MOVE_FenLiV,	//竖向分离
		MOVE_JiZhongH,	//横向集中
		MOVE_JiZhongV,	//竖向集中
		MOVE_DengFenH,	//横向等分
		MOVE_DengFenV,	//竖向等分
		MOVE_JuZhongH,	//横向居中
		MOVE_JuZhongV,	//竖向居中
		MOVE_HCuo,		//横向错开(奇左偶右)
		MOVE_VCuo,		//竖向错开(奇上偶下)
		MOVE_HCuoFen,	//横向错开(奇分离偶集中)
		MOVE_VCuoFen,	//竖向错开(奇分离偶集中)
		MOVE_HCuoDeng,	//横向错开(奇等分偶居中)
		MOVE_VCuoDeng,	//竖向错开(奇等分偶居中)
		MOVE_KuoSanHV,	//扩散(先行后列)
		MOVE_KuoSanVH,	//扩散(先列后行)
		MOVE_JiZhongHV,	//集中(先行后列)
		MOVE_JiZhongVH,	//集中(先列后行)
		MOVE_ZUp,		//Z 形向上
		MOVE_ZDown,		//Z 形向下
		MOVE_NLeft,		//N 形向左
		MOVE_NRight,	//N 形向右
		MOVE_SUp,		//S 形向上
		MOVE_SDown,		//S 形向下
		MOVE_RotL,		//逆时针回形旋转
		MOVE_RotR,		//顺时针回形旋转
		MOVE_RotLR,		//交错回形旋转
		MOVE_RotNLuoW,	//逆时针螺旋向外
		MOVE_RotNLuoN,	//逆时针螺旋向内
		MOVE_RotSLuoW,	//顺时针螺旋向外
		MOVE_RotSLuoN,	//顺时针螺旋向内
		MOVE_COUNT,		//变化总数
	};
public:
	CLinkMatrix();
	~CLinkMatrix();
	void	Init(int nRows,int nCols,int nIconCount=0);
	void	Empty();
	BOOL	FindPath(int x1, int y1, int x2, int y2,CLinkPath*pPath=NULL);
	int		GetHelp(CLinkPath*pPath=NULL);
	int		GetHelp(int x0,int y0,CLinkPath*pPath=NULL);
	void	ChangeLayout();
	void	RemoveIcon(int x1,int y1,int x2,int y2);
	CString	GetMoveModeStr();
	void	SetMoveMode(int iMode);
	ICONDATA&	operator()(int x,int y)
	{
		return m_pMatrix[x + y * (m_iCols + 2)];
	}
	CLinkMatrix&operator=(CLinkMatrix&src);
	int		XYtoIndex(int x,int y)
	{
		return x + y * (m_iCols + 2);
	}
	void	IndexToXY(int nIndex,int&x,int&y)
	{
		x	=	nIndex % (m_iCols + 2);
		y	=	nIndex / (m_iCols + 2);
	}
private:
	void	MoveUp(int x1,int y1,int x2,int y2);		//向上
	void	MoveDown(int x1,int y1,int x2,int y2);		//向下
	void	MoveLeft(int x1,int y1,int x2,int y2);		//向左
	void	MoveRight(int x1,int y1,int x2,int y2);		//向右
	void	MoveLU(int x1,int y1,int x2,int y2);		//向左上
	void	MoveLD(int x1,int y1,int x2,int y2);		//向左下
	void	MoveRU(int x1,int y1,int x2,int y2);		//向右上
	void	MoveRD(int x1,int y1,int x2,int y2);		//向右下
	void	MoveULDR(int x1,int y1,int x2,int y2);		//上左下右
	void	MoveURDL(int x1,int y1,int x2,int y2);		//上右下左
	void	MoveLDRU(int x1,int y1,int x2,int y2);		//左下右上
	void	MoveLURD(int x1,int y1,int x2,int y2);		//左上右下
	void	MoveFenLiH(int x1,int y1,int x2,int y2);	//行分离
	void	MoveFenLiV(int x1,int y1,int x2,int y2);	//列分离
	void	MoveJiZhongH(int x1,int y1,int x2,int y2);	//行集中
	void	MoveJiZhongV(int x1,int y1,int x2,int y2);	//列集中
	void	MoveDengH(int x1,int y1,int x2,int y2);		//行等分
	void	MoveDengV(int x1,int y1,int x2,int y2);		//列等分
	void	MoveJuZhongH(int x1,int y1,int x2,int y2);	//行居中
	void	MoveJuZhongV(int x1,int y1,int x2,int y2);	//列居中
	void	MoveCuoH(int x1,int y1,int x2,int y2);		//行错开(奇左偶右)
	void	MoveCuoV(int x1,int y1,int x2,int y2);		//列错开(奇上偶下)
	void	MoveCuoFenH(int x1,int y1,int x2,int y2);	//行错开(奇分离偶集中)
	void	MoveCuoFenV(int x1,int y1,int x2,int y2);	//列错开(奇分离偶集中)
	void	MoveCuoDengH(int x1,int y1,int x2,int y2);	//行错开(奇等分偶居中)
	void	MoveCuoDengV(int x1,int y1,int x2,int y2);	//列错开(奇等分偶居中)
	void	MoveKuoSanHV(int x1,int y1,int x2,int y2);	//扩散(先行后列)
	void	MoveKuoSanVH(int x1,int y1,int x2,int y2);	//扩散(先列后行)
	void	MoveJiZhongHV(int x1,int y1,int x2,int y2);	//集中(先行后列)
	void	MoveJiZhongVH(int x1,int y1,int x2,int y2);	//集中(先列后行)
	void	MoveZUpDown(BOOL bUp);						//Z 形向上/Z 形向下
	void	MoveNLeftRight(BOOL bLeft);					//N 形向左/N 形向右
	void	MoveSUpDown(BOOL bUp);						//S 形向上/S 形向下
	void	MoveRotL(int x1,int y1,int x2,int y2);		//逆时针回形旋转
	void	MoveRotR(int x1,int y1,int x2,int y2);		//顺时针回形旋转
	void	MoveRotLR(int x1,int y1,int x2,int y2);		//交替旋转
	void	MoveRotLuo1(BOOL bNi);						//顺时针螺旋向外/逆时针螺旋向内
	void	MoveRotLuo2(BOOL bNi);						//顺时针螺旋向内/逆时针螺旋向外
private:
	void	MoveUp(int x);				//向上(一列)
	void	MoveDown(int x);			//向下(一列)
	void	MoveLeft(int y);			//向左(一行)
	void	MoveRight(int y);			//向右(一行)
	void	MoveLU(int c);				//向左上
	void	MoveLD(int c);				//向左下
	void	MoveRU(int c);				//向右上
	void	MoveRD(int c);				//向右下
	void	MoveFenLiRow(int y);		//分离一行
	void	MoveFenLiCol(int x);		//分离一列
	void	MoveJiZhongRow(int y);		//集中一行
	void	MoveJiZhongCol(int x);		//集中一列
	void	MoveDengRow(int y);			//等分一行
	void	MoveDengCol(int x);			//等分一列
	void	MoveJuZhongRow(int y);		//居中一行
	void	MoveJuZhongCol(int x);		//居中一列
	void	MoveRotL(int nLoop);		//逆时针旋转一圈
	void	MoveRotR(int nLoop);		//顺时针旋转一圈
private:
	BOOL	IsBlankH(int y,int xFrom,int xTo);
	BOOL	IsBlankV(int x,int yFrom,int yTo);
	int		CountIconRow(int y);						//统计一行的牌
	int		CountIconCol(int x);						//统计一列的牌
	int		GetLoopNumber(int x,int y);
	void	FillIcon(CDWordArray&arrIndex,CDWordArray&arrIcon,BOOL bLeft);
public:
	ICONDATA*	m_pMatrix;
	int			m_iRows;	//行数
	int			m_iCols;	//列数
	int			m_xSel;		//当前选中图片的坐标
	int			m_ySel;		//
	int			m_iMoveMode;//消牌模式
};
