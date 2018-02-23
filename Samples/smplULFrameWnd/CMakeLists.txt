add_executable(smplULFrameWnd WIN32 smplULFrameWnd.cpp smplULFrameWnd.rc manifest.xml ULCFrameWnd/ULCFrameWnd.cpp)
target_link_libraries(smplULFrameWnd PRIVATE ULLib)
