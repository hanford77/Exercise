// Undo.cpp
#include "stdafx.h"
#include "Undo.h"

CUndo::CUndo()
{
	m_iHaveDoStep	=	0;
	m_arrState.SetSize(0,1024);
}

CUndo::~CUndo()
{
	Empty();
}

void CUndo::Empty()
{
	int i,c=m_arrState.GetSize();
	for(i=0;i<c;i++)
	{
		delete m_arrState[i];
	}
	m_arrState.RemoveAll();
	m_iHaveDoStep	=	0;
}

/********************************************\
bInit 是否为初始化状态
\********************************************/
void CUndo::AddState(CState*pState,BOOL bInit)
{
	if(bInit)
	{//初始化状态
		Empty();
		m_arrState.Add(pState);
		m_iHaveDoStep	=	0;
	}
	else
	{//非初始化状态
		int	count	=	m_arrState.GetSize();
		if(count < ++m_iHaveDoStep + 1)
		{
			m_arrState.Add(pState);
		}
		else
		{
			for(int p=count-1;p >= m_iHaveDoStep;)
			{
				delete m_arrState[p--];
			}
			m_arrState.SetSize(m_iHaveDoStep + 1);
			m_arrState[m_iHaveDoStep]=pState;
		}
	}
}

BOOL CUndo::CanUndo()
{
	return m_iHaveDoStep > 0;
}

BOOL CUndo::CanRedo()
{
	return m_iHaveDoStep < m_arrState.GetSize() - 1;
}

CUndo::CState* CUndo::Undo(CLinkPath*pPath)
{
	if(pPath)
	{
		pPath->Empty();
	}
	CState*pState=NULL;
	if(m_iHaveDoStep > 0)
	{
		if(pPath)
		{
			*pPath	=	m_arrState[m_iHaveDoStep]->m_path;
		}
		pState	=	m_arrState[--m_iHaveDoStep];
	}
	return pState;
}

CUndo::CState* CUndo::Redo(CLinkPath*pPath)
{
	if(pPath)
	{
		pPath->Empty();
	}
	CState*	pState	=	NULL;
	int		uBound	=	m_arrState.GetUpperBound();
	if(m_iHaveDoStep <  uBound)
	{
		pState	=	m_arrState[++m_iHaveDoStep];
		if(pPath && m_iHaveDoStep < uBound)
		{
			*pPath	=	m_arrState[m_iHaveDoStep + 1]->m_path;
		}
	}
	return pState;
}