add_executable(smplMDIWnd WIN32 MDIApp.cpp MDIChild.cpp MDIFrame.cpp smplMDIWnd.rc manifest.xml )
target_link_libraries(smplMDIWnd PRIVATE ULLib)
