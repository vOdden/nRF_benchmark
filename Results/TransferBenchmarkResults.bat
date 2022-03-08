@ECHO OFF

REM source folder location
set Source_Folder=C:\Users\sigur\eembc\runner\sessions\
REM destination folder location
set Dest_Folder=C:\MasterThesis_Nrf\Results
REM copy the files
xcopy /s/e %Source_Folder%\*.* %Dest_Folder%\.
