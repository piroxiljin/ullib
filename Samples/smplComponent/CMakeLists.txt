add_library(Component Component/COMDllApp.cpp Component/GUID.cpp Component/ULComponent.cpp Component/Component.def )
target_link_libraries(Component PRIVATE ULLib)

add_library(Componet2 Componet2/COM2DllApp.cpp Componet2/Component2.cpp Componet2/Component2.def )
target_link_libraries(Componet2 PRIVATE ULLib)

add_executable(Client WIN32 Client/main.cpp)
target_link_libraries(Client PRIVATE ULLib)
