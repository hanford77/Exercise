# Microsoft Developer Studio Project File - Name="SolveEquationDll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SolveEquationDll - Win32 DU
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SolveEquationDll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SolveEquationDll.mak" CFG="SolveEquationDll - Win32 DU"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SolveEquationDll - Win32 RA" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SolveEquationDll - Win32 DA" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SolveEquationDll - Win32 RU" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SolveEquationDll - Win32 DU" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SolveEquationDll - Win32 RA"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Temp\RA"
# PROP BASE Intermediate_Dir "Temp\RA"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Temp\RA"
# PROP Intermediate_Dir "Temp\RA"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../../bin/vc6-win32-RA/SolveEquationDll.dll"
# Begin Special Build Tool
OutDir=.\Temp\RA
WkspDir=.
TargetDir=\(yhf)\Exercise\math\一元多次方程\SolveEquation\vc\dllSDK\bin\vc6-win32-RA
TargetPath=\(yhf)\Exercise\math\一元多次方程\SolveEquation\vc\dllSDK\bin\vc6-win32-RA\SolveEquationDll.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy "$(OutDir)\*.lib" "$(TargetDir)"	del "$(TargetDir)\*.ilk"	set ProjDirectory=%cd%	cd /d $(WkspDir)	if exist ..\build.bat call ..\build.bat	cd /d %ProjDirectory%	if defined RunDirectory echo d|xcopy "$(TargetPath)" "%RunDirectory%vc6-win32-RA" /Y
# End Special Build Tool

!ELSEIF  "$(CFG)" == "SolveEquationDll - Win32 DA"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Temp\DA"
# PROP BASE Intermediate_Dir "Temp\DA"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Temp\DA"
# PROP Intermediate_Dir "Temp\DA"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../bin/vc6-win32-DA/SolveEquationDll.dll" /pdbtype:sept
# Begin Special Build Tool
OutDir=.\Temp\DA
WkspDir=.
TargetDir=\(yhf)\Exercise\math\一元多次方程\SolveEquation\vc\dllSDK\bin\vc6-win32-DA
TargetPath=\(yhf)\Exercise\math\一元多次方程\SolveEquation\vc\dllSDK\bin\vc6-win32-DA\SolveEquationDll.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy "$(OutDir)\*.lib" "$(TargetDir)"	del "$(TargetDir)\*.ilk"	set ProjDirectory=%cd%	cd /d $(WkspDir)	if exist ..\build.bat call ..\build.bat	cd /d %ProjDirectory%	if defined RunDirectory echo d|xcopy "$(TargetPath)" "%RunDirectory%vc6-win32-DA" /Y
# End Special Build Tool

!ELSEIF  "$(CFG)" == "SolveEquationDll - Win32 RU"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Temp\RU"
# PROP BASE Intermediate_Dir "Temp\RU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Temp\RU"
# PROP Intermediate_Dir "Temp\RU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../../bin/vc6-win32-RU/SolveEquationDll.dll"
# Begin Special Build Tool
OutDir=.\Temp\RU
WkspDir=.
TargetDir=\(yhf)\Exercise\math\一元多次方程\SolveEquation\vc\dllSDK\bin\vc6-win32-RU
TargetPath=\(yhf)\Exercise\math\一元多次方程\SolveEquation\vc\dllSDK\bin\vc6-win32-RU\SolveEquationDll.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy "$(OutDir)\*.lib" "$(TargetDir)"	del "$(TargetDir)\*.ilk"	set ProjDirectory=%cd%	cd /d $(WkspDir)	if exist ..\build.bat call ..\build.bat	cd /d %ProjDirectory%	if defined RunDirectory echo d|xcopy "$(TargetPath)" "%RunDirectory%vc6-win32-RU" /Y
# End Special Build Tool

!ELSEIF  "$(CFG)" == "SolveEquationDll - Win32 DU"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Temp\DU"
# PROP BASE Intermediate_Dir "Temp\DU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Temp\DU"
# PROP Intermediate_Dir "Temp\DU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../bin/vc6-win32-DU/SolveEquationDll.dll" /pdbtype:sept
# Begin Special Build Tool
OutDir=.\Temp\DU
WkspDir=.
TargetDir=\(yhf)\Exercise\math\一元多次方程\SolveEquation\vc\dllSDK\bin\vc6-win32-DU
TargetPath=\(yhf)\Exercise\math\一元多次方程\SolveEquation\vc\dllSDK\bin\vc6-win32-DU\SolveEquationDll.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy "$(OutDir)\*.lib" "$(TargetDir)"	del "$(TargetDir)\*.ilk"	set ProjDirectory=%cd%	cd /d $(WkspDir)	if exist ..\build.bat call ..\build.bat	cd /d %ProjDirectory%	if defined RunDirectory echo d|xcopy "$(TargetPath)" "%RunDirectory%vc6-win32-DU" /Y
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "SolveEquationDll - Win32 RA"
# Name "SolveEquationDll - Win32 DA"
# Name "SolveEquationDll - Win32 RU"
# Name "SolveEquationDll - Win32 DU"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\inc\Solve.h
# End Source File
# Begin Source File

SOURCE=..\..\src\pch\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\pch\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\src\Solve.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SolveEquationDll.def
# End Source File
# End Group
# End Target
# End Project
