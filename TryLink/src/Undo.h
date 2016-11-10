//Undo.h
#pragma once

#include "LinkMatrix.h"

class CUndo  
{
public:
	class CState
	{
	public:
		CLinkPath	m_path;			//该步的消牌路径
		CLinkMatrix	m_Matrix;		//该步执行后的状态
	};
public:
	CUndo();
	~CUndo();
public:
	void	Empty();
	void	AddState(CState*pState,BOOL bInit=FALSE);
	BOOL	CanUndo();
	BOOL	CanRedo();
	CState*	Undo(CLinkPath*pPath=NULL);
	CState*	Redo(CLinkPath*pPath=NULL);
public:
	CTypedPtrArray<CPtrArray,CState*>m_arrState;
	int		m_iHaveDoStep;	//已经做的步骤数
};
