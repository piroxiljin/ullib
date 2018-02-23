add_executable(smplULDlg WIN32 smplULDlg.cpp smplULDlg.rc manifest.xml ULCDlg/ULCDlg.cpp )
target_link_libraries(smplULDlg PRIVATE ULLib)
