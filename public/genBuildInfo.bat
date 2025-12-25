@echo off

@REM 设置主版本号, 格式为aa.bb.ccdd
set /a MAJOR_VERSION=1
set /a MINOR_VERSION=0

pushd %~dp0
pushd ..

set header=%~dp0/inc/buildInfo.h
echo #ifndef __BUILD_INFO_H__ > %header%
echo #define __BUILD_INFO_H__ >> %header%
echo. >> %header%

@REM svn update
@REM for /f "delims=" %%i in ('svn info ^| findstr "Rev:"') do set rev=%%i
@REM echo %rev%
@REM set rev=%rev:~18%

for /f "tokens=1,2 delims=:" %%a in ('svnversion -n') do (
   set first_part=%%a
   set second_part=%%b
)

if "%second_part%" == "" (
	set second_part=%first_part%
)
set rev=%second_part:M=%

set /a fullVersion = %MAJOR_VERSION% * 16777215 + %MINOR_VERSION% * 65536 + %rev%
set "fullVersionStr=%MAJOR_VERSION%.%MINOR_VERSION%.%rev%"
echo SVN_REVISION = %rev%
echo FULL_VERSION = %fullVersion%
echo FULL_VERSION_STR = %fullVersionStr%

echo #define SVN_REVISION %rev% >> %header%
echo #define FULL_VERSION %fullVersion% >> %header%
echo #define FULL_VERSION_STR "%fullVersionStr%" >> %header%

set cleanDate=%date:~0,10%
set "buildDate=%cleanDate:/=-%"
echo BUILD_DATE = %buildDate%
echo #define BUILD_DATE "%buildDate%" >> %header%

set buildTime=%time:~0,8%
set buildTime=%buildTime: =0%
echo BUILD_TIME = %buildTime%
echo #define BUILD_TIME "%buildTime%" >> %header%


echo. >> %header%
echo #endif //__BUILD_INFO_H__ >> %header%
echo. >> %header%

popd

::生成重命名脚本在public目录
echo set "FULL_VERSION=%fullVersion%" > buildInfo.bat
echo set "VERSION=%FULL_VERSION_STR%" >> buildInfo.bat
echo set "COMPILE_DATE=%buildDate:-=%" >> buildInfo.bat
echo set "COMPILE_TIME=%buildTime::=%" >> buildInfo.bat

popd