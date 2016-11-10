@echo off
rem 定义环境变量-----------------------------------------------------------
set RunDirectory=%~dp0..\..\..\..\Run\
set VCWFILE="SolveEquation.vcw"
rem 获得VC的安装目录-------------------------------------------------------
rem 设置本批处理文件所在目录为当前目录
cd /d %~dp0
rem 执行 vspath.vbs,生成 vspath.bat
cscript -e:vbs vspath.vbs
rem 执行 vspath.bat 设置环境变量(VC的安装目录)
call vspath.bat
rem 删除 vspath.bat
del vspath.bat
rem 打开 dsw 文件----------------------------------------------------------
if defined evc3path start "" "%evc3path%EVC.EXE" %VCWFILE%
