add_executable(smplPropShPg WIN32 FinishPage.cpp IntroPage.cpp PropShPg.cpp WorkPage.cpp smplPropShPg.rc manifest.xml)
target_link_libraries(smplPropShPg PRIVATE ULLib)
