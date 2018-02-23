add_executable(smplWndCtrl WIN32 MainFrame.cpp smplWndCtrl.cpp smplWndCtrl.rc manifest.xml)
target_link_libraries(smplWndCtrl PRIVATE ULLib)
