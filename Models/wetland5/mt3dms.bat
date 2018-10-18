@COPY wetland5.pm5 flagfile>NUL
C:\PROGRA~1\PM5\mt3dms\mt3dmsv.exe<mtmsfile
@DEL flagfile>NUL
@ECHO.
@ECHO ------------ PMWIN Message -------------
@ECHO MT3D run is complete. See the following file for full run details
@ECHO C:\CD\MODELS\WETLAND5\OUTPUT.MTM
@ECHO.
@ECHO In case of difficulties:
@ECHO 1. Check the version, path and file name of the MT3DMS program.
@ECHO 2. Regenerate all input files and run MT3DMS again.
@ECHO 3. Make sure that the packages used in your model are also supported by your
@ECHO    MT3DMS and modflow program. To find out which packages are included in
@ECHO    MT3DMS or Modflow, consult your program documents.
@ECHO --------- End of PMWIN Message ---------
@PAUSE
