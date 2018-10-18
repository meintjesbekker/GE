# Microsoft Developer Studio Project File - Name="GE" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GE - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GE.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GE.mak" CFG="GE - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GE - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GE - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GE - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "c:\Program Files\vtkNightly\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vtkdll.lib /nologo /subsystem:windows /machine:I386 /libpath:"c:\Program Files\vtkNightly\lib"
# SUBTRACT LINK32 /incremental:yes /debug /nodefaultlib

!ELSEIF  "$(CFG)" == "GE - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /I "c:\Program Files\vtkNightly\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vtkdll.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"c:\Program Files\vtkNightly\lib"
# SUBTRACT LINK32 /incremental:no /nodefaultlib /force

!ENDIF 

# Begin Target

# Name "GE - Win32 Release"
# Name "GE - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Actor.cpp
# End Source File
# Begin Source File

SOURCE=.\Average.cpp
# End Source File
# Begin Source File

SOURCE=.\AverageGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\AxesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CleanTriangulate.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipPolyData.cpp
# End Source File
# Begin Source File

SOURCE=.\Color.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorLevelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorRow.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorSpectrum.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorSpectrumDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorTable.cpp
# End Source File
# Begin Source File

SOURCE=.\DecimateSmoothGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\DecimateSmoothNormals.cpp
# End Source File
# Begin Source File

SOURCE=.\FilesExist.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\GE.cpp
# End Source File
# Begin Source File

SOURCE=.\GE.rc
# End Source File
# Begin Source File

SOURCE=.\Geometry.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModel.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelAverageGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelAverageGridRelaxationFactorEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelAverageGridTargetReductionEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelAveragePage.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoSpatialModelForLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelForLayerGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelGeneralGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelGeneralGridOpacityEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelGeneralPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelVisibleGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelVisiblePage.cpp
# End Source File
# Begin Source File

SOURCE=.\HexahedronTopology.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponents.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsAveragePage.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsGeneralGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsGeneralPage.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsGeneralPageTD.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicTDComponents.cpp
# End Source File
# Begin Source File

SOURCE=.\HydraulicTIComponents.cpp
# End Source File
# Begin Source File

SOURCE=.\Indexes.cpp
# End Source File
# Begin Source File

SOURCE=.\IterationsEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\LookUpTable.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Mapper.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Model.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelOutline.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelOutlineGeneralPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelOutlineSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMS.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorAddDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorRow.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorTable.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSGeneralPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSLookupTable.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\MT3DMSTopology.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectList.cpp
# End Source File
# Begin Source File

SOURCE=.\Parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\ParameterAveragePage.cpp
# End Source File
# Begin Source File

SOURCE=.\ParameterGeneralGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\ParameterGeneralPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ParameterGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\ParameterSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyData.cpp
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurfaceGeneralPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurfaceGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurfaceSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\QuadIndexes.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadFile.cpp
# End Source File
# Begin Source File

SOURCE=.\RelaxationFactorEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\ScaleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SidesQuadTopology.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StressPeriod.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeAndLayerParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeStep.cpp
# End Source File
# Begin Source File

SOURCE=.\TopQuadTopology.cpp
# End Source File
# Begin Source File

SOURCE=.\Visualization.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualizationObject.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualizeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualizeGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\vtkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\vtkView.cpp
# End Source File
# Begin Source File

SOURCE=.\XYZCoordinate.cpp
# End Source File
# Begin Source File

SOURCE=.\XYZSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceDecSmoothPage.cpp
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceGeneralPage.cpp
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceGeometryAndTopology.cpp
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceSheet.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Actor.h
# End Source File
# Begin Source File

SOURCE=.\Average.h
# End Source File
# Begin Source File

SOURCE=.\AverageGUI.h
# End Source File
# Begin Source File

SOURCE=.\AxesDlg.h
# End Source File
# Begin Source File

SOURCE=.\CleanTriangulate.h
# End Source File
# Begin Source File

SOURCE=.\ClipDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClipPolyData.h
# End Source File
# Begin Source File

SOURCE=.\Color.h
# End Source File
# Begin Source File

SOURCE=.\ColorEditBox.h
# End Source File
# Begin Source File

SOURCE=.\ColorGrid.h
# End Source File
# Begin Source File

SOURCE=.\ColorLevelDlg.h
# End Source File
# Begin Source File

SOURCE=.\ColorPage.h
# End Source File
# Begin Source File

SOURCE=.\ColorRow.h
# End Source File
# Begin Source File

SOURCE=.\ColorSpectrum.h
# End Source File
# Begin Source File

SOURCE=.\ColorSpectrumDlg.h
# End Source File
# Begin Source File

SOURCE=.\ColorTable.h
# End Source File
# Begin Source File

SOURCE=.\DecimateSmoothGUI.h
# End Source File
# Begin Source File

SOURCE=.\DecimateSmoothNormals.h
# End Source File
# Begin Source File

SOURCE=.\FilesExist.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\GE.h
# End Source File
# Begin Source File

SOURCE=.\Geometry.h
# End Source File
# Begin Source File

SOURCE=.\GeoSpatialModel.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelAverageGrid.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelAverageGridRelaxationFactorEditBox.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelAverageGridTargetReductionEditBox.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelAveragePage.h
# End Source File
# Begin Source File

SOURCE=.\GeoSpatialModelForLayer.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelForLayerGUI.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelGeneralGrid.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelGeneralGridOpacityEditBox.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelGeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelSheet.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelVisibleGrid.h
# End Source File
# Begin Source File

SOURCE=.\GeospatialModelVisiblePage.h
# End Source File
# Begin Source File

SOURCE=.\HexahedronTopology.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponent.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentGUI.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponents.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsAveragePage.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsGeneralGrid.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsGeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsGeneralPageTD.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicComponentsSheet.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicTDComponents.h
# End Source File
# Begin Source File

SOURCE=.\HydraulicTIComponents.h
# End Source File
# Begin Source File

SOURCE=.\Indexes.h
# End Source File
# Begin Source File

SOURCE=.\IterationsEditBox.h
# End Source File
# Begin Source File

SOURCE=.\LookUpTable.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Mapper.h
# End Source File
# Begin Source File

SOURCE=.\MenuButton.h
# End Source File
# Begin Source File

SOURCE=.\Model.h
# End Source File
# Begin Source File

SOURCE=.\ModelOutline.h
# End Source File
# Begin Source File

SOURCE=.\ModelOutlineGeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\ModelOutlineSheet.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMS.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorAddDlg.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorEditBox.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorGrid.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorPage.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorRow.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSContourAndColorTable.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSGeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSGUI.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSLookupTable.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSSheet.h
# End Source File
# Begin Source File

SOURCE=.\MT3DMSTopology.h
# End Source File
# Begin Source File

SOURCE=.\ObjectList.h
# End Source File
# Begin Source File

SOURCE=.\Parameter.h
# End Source File
# Begin Source File

SOURCE=.\ParameterAveragePage.h
# End Source File
# Begin Source File

SOURCE=.\ParameterGeneralGrid.h
# End Source File
# Begin Source File

SOURCE=.\ParameterGeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\ParameterGUI.h
# End Source File
# Begin Source File

SOURCE=.\ParameterSheet.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\PolyData.h
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurface.h
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurfaceAveragePage.cpp
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurfaceAveragePage.h
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurfaceGeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurfaceGUI.h
# End Source File
# Begin Source File

SOURCE=.\PotentiometricSurfaceSheet.h
# End Source File
# Begin Source File

SOURCE=.\QuadIndexes.h
# End Source File
# Begin Source File

SOURCE=.\ReadFile.h
# End Source File
# Begin Source File

SOURCE=.\RelaxationFactorEditBox.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor.h
# End Source File
# Begin Source File

SOURCE=.\ScaleDlg.h
# End Source File
# Begin Source File

SOURCE=.\SidesQuadTopology.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StressPeriod.h
# End Source File
# Begin Source File

SOURCE=.\TimeAndLayerParameter.h
# End Source File
# Begin Source File

SOURCE=.\TimeStep.h
# End Source File
# Begin Source File

SOURCE=.\TopQuadTopology.h
# End Source File
# Begin Source File

SOURCE=.\Visualization.h
# End Source File
# Begin Source File

SOURCE=.\VisualizationObject.h
# End Source File
# Begin Source File

SOURCE=.\VisualizeDlg.h
# End Source File
# Begin Source File

SOURCE=.\VisualizeGrid.h
# End Source File
# Begin Source File

SOURCE=.\vtkDoc.h
# End Source File
# Begin Source File

SOURCE=.\vtkView.h
# End Source File
# Begin Source File

SOURCE=.\XYZCoordinate.h
# End Source File
# Begin Source File

SOURCE=.\XYZSurface.h
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceDecSmoothPage.h
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceGeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceGeometryAndTopology.h
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceGUI.h
# End Source File
# Begin Source File

SOURCE=.\XYZSurfaceSheet.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmpCHECK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CHECK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GE.ico
# End Source File
# Begin Source File

SOURCE=.\res\GE.rc2
# End Source File
# Begin Source File

SOURCE=.\res\GE2000.ico
# End Source File
# Begin Source File

SOURCE=.\res\GEDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ICON.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_che.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SELECT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Splash.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UNCHECK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UNCHECK.ico
# End Source File
# Begin Source File

SOURCE=.\res\UNSELECT.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\READFOR.lib
# End Source File
# End Target
# End Project
# Section GE : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section GE : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
# Section GE : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section GE : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section GE : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section GE : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
