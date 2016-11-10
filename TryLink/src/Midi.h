//Midi.h
#pragma once

#include <mmsystem.h>

class CMidi  
{
public:
	CMidi();
	BOOL	Open(LPCTSTR szFile);
	DWORD	GetSongLength();
	DWORD	GetCurPos();
	BOOL	Play();
	BOOL	Close();
	void	SetOwner(HWND hwndOwner)
	{
		m_hwndOwner	=	hwndOwner;
	}
private:
	MCIDEVICEID	m_dwDeviceID;
	HWND		m_hwndOwner;
};
