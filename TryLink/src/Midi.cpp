// Midi.cpp
#include "stdafx.h"
#include "Midi.h"

#pragma comment(lib, "winmm")

CMidi::CMidi()
{
	m_dwDeviceID	=	0;
	m_hwndOwner		=	0;
}

//打开音乐文件
BOOL CMidi::Open(LPCTSTR szFile)
{
	Close();
	MCI_OPEN_PARMS	ParamOpen;
	ParamOpen.lpstrElementName	=	szFile;
	ParamOpen.lpstrDeviceType	=	NULL;
	if(0==mciSendCommand(0,MCI_OPEN,MCI_DEVTYPE_WAVEFORM_AUDIO,(DWORD)&ParamOpen))
	{
		m_dwDeviceID	=	ParamOpen.wDeviceID;
		return TRUE;
	}
	return FALSE;
}

//获得音乐文件的长度 dwLen
DWORD CMidi::GetSongLength()
{
	MCI_STATUS_PARMS ParamStatus;
	ParamStatus.dwItem			=	MCI_STATUS_LENGTH;
	if(0==mciSendCommand(m_dwDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&ParamStatus))
	{
		return ParamStatus.dwReturn;
	}
	return 0;
}

//根据 m_dwDeviceID 获得当前的播放位置 dwPos
DWORD CMidi::GetCurPos()
{
	MCI_STATUS_PARMS ParamStatus;
	ParamStatus.dwItem			=	MCI_STATUS_POSITION;
	if(0==mciSendCommand(m_dwDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&ParamStatus))
	{
		return ParamStatus.dwReturn;
	}
	return 0;
}

//根据 m_dwDeviceID 播放音乐文件
BOOL CMidi::Play()
{
	MCI_PLAY_PARMS	ParamPlay;
	DWORD			dwFlag	=	0;//MCI_FROM | MCI_TO;

	if(m_hwndOwner)
	{
		ParamPlay.dwCallback	=	(DWORD)m_hwndOwner;
		dwFlag	|=	MCI_NOTIFY;
	}
//	ParamPlay.dwFrom			=	MCI_MAKE_HMS(0,5,30);	//从 0 时 5 分 30 秒开始播放
//	ParamPlay.dwTo				=	dwLen;					//播放到最后
	return 0==mciSendCommand(m_dwDeviceID,MCI_PLAY,dwFlag,(DWORD)&ParamPlay);
}

//停止播放
BOOL CMidi::Close()
{
	BOOL bClose		=	(0==mciSendCommand(m_dwDeviceID,MCI_CLOSE,0,NULL));
	m_dwDeviceID	=	0;
	return bClose;
}
