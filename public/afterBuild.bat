@echo off

:: 配置是否生成bin文件
set CFG_GEN_BIN_FILE=1
:: 配置是否生成dis文件
set CFG_GEN_DIS_FILE=0
:: 配置是否重命名map文件
set CFG_RENAME_MAP_FILE=1
:: 配置是否拷贝并重命名hex文件
set CFG_COPY_AND_RENAME_HEX_FILE=1

:: 检查参数数量  
if "%~2"=="" (  
    echo Usage: %~nx0 "TargetDir"  "ElfFilePath"
    exit /b 1
)  


:: 获取参数  
set "targetDir=%~1"
:: 获取参数，可选，如果提供，为其反汇编
set "elfFilePath=%~2"

:: 检查文件是否存在  
if not exist "%elfFilePath%" (  
    echo Elf file not found: %elfFilePath%  
    exit /b 1  
)

pushd %~dp0
:: 获取版本号等信息
call buildInfo.bat
popd

:: VERSION and COMPILE_DATE/COMPILE_TIME are from renameInfo.bat
set COMPILE_DATE_TIME=%COMPILE_DATE:~2%_%COMPILE_TIME%
echo VERSION = %VERSION%
echo COMPILE_DATE_TIME = %COMPILE_DATE_TIME%
echo TARGET_DIR = %targetDir%
echo ELF_FILE = %elfFilePath%

:: 获取文件名（不含扩展名）  
for %%F in ("%elfFilePath%") do set "oldBaseFileName=%%~nF"  
  
:: 构建新的文件名  
set "newBaseFileName=%oldBaseFileName%_%VERSION%_%COMPILE_DATE_TIME%" 

::for %%F in ("%targetDir%") do set "newBaseFileNameWithPath=%%~dpF%newBaseFileName%" 
set "newBaseFileNameWithPath=%targetDir%\%newBaseFileName%"

:: 复制并重命名axf文件
copy /V /Y "%elfFilePath%" "%newBaseFileNameWithPath%.axf"

:: 生成bin
if %CFG_GEN_BIN_FILE% == 1 (
	fromelf.exe --bin --output "%newBaseFileNameWithPath%.bin" "%elfFilePath%"
)

:: 生成dis
if %CFG_GEN_DIS_FILE% == 1 (
	fromelf.exe --text -acdegrstyz --output "%newBaseFileNameWithPath%.dis" "%elfFilePath%"
)

::重命名map文件
if %CFG_RENAME_MAP_FILE% == 1 (
	move /Y "%targetDir%\%oldBaseFileName%.map" "%newBaseFileNameWithPath%.map"  
)

::拷贝并重命名hex文件
if %CFG_COPY_AND_RENAME_HEX_FILE% == 1 (
	copy /V /Y "%elfFilePath:.axf=.hex%" "%newBaseFileNameWithPath%.hex"
)