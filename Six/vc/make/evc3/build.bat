@echo off
rem 定义环境变量-----------------------------------------------------------
set RunDirectory=%~dp0..\..\..\..\Run\
set VCWFILE="Six.vcw"
rem 环境变量 CECONFIG 是机器型号(Platform)，注意大小写
set CECONFIG="Pocket PC"
rem 环境变量 CFG 是“项目 - 配置”
set CFG="Six - Win32 (WCE ARM) RU"
rem 获得VC的安装目录-------------------------------------------------------
rem 设置本批处理文件所在目录为当前目录
cd /d %~dp0
rem 执行 vspath.vbs,生成 vspath.bat
cscript -e:vbs vspath.vbs
rem 执行 vspath.bat 设置环境变量(VC的安装目录)
call vspath.bat
rem 删除 vspath.bat
del vspath.bat
rem 执行编译--------------------------------------------------------------
if not defined evc3path goto :eof
rem 执行编译(MSDEV.EXE会创建新的命令窗口,MSDEV.COM不会;/NORECURSE 将不编译依赖项)
"%evc3path%EVC.COM" %VCWFILE% /make %CFG% /CEConfig=%CECONFIG% /rebuild
if not errorlevel 0 goto :eof
echo 编译成功完成
goto end
:eof
echo 编译失败
:end
pause