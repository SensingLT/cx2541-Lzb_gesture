@echo off

:: 配置buildInfo.h是否影响重新编译
set CFG_IGNORE_DEP_OF_BUILD_INFO=1
:: 配置是否删除旧的bin文件
set CFG_DELETE_OLD_BIN=1
:: 配置是否删除旧的hex文件
set CFG_DELETE_OLD_HEX=1
:: 配置是否删除旧的dis文件
set CFG_DELETE_OLD_DIS=0
:: 配置是否删除旧的axf文件
set CFG_DELETE_OLD_ELF=1
:: 配置是否删除旧的map文件
set CFG_DELETE_OLD_MAP=1

setlocal enabledelayedexpansion

set targetDir="%~1"
if not exist "%targetDir%\" (  
    echo The directory %targetDir% does not exist.
	goto genBuildInfo
) 

if %CFG_DELETE_OLD_BIN% == 1 (
	del "%targetDir%\*.bin"
)

if %CFG_DELETE_OLD_HEX% == 1 (
	del "%targetDir%\*.hex"
)

if %CFG_DELETE_OLD_DIS% == 1 (
	del "%targetDir%\*.dis"
)

if %CFG_DELETE_OLD_ELF% == 1 (
	del "%targetDir%\*.axf"
)

if %CFG_DELETE_OLD_MAP% == 1 (
	del "%targetDir%\*.map"
)

endlocal

:genBuildInfo
pushd %~dp0
call genBuildInfo.bat
:: 将buildInfo.h改成2020-1-1的时间，避免只修改了它也要重新编译
if %CFG_IGNORE_DEP_OF_BUILD_INFO% == 1 (
	call python touchBuildInfo.py
)

popd