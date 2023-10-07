cmake_minimum_required(VERSION 3.16)

project(xdict VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

qt_add_executable(appxdict
    source/main.cpp
    icons.qrc
)

qt_add_qml_module(appxdict
    URI xdict
    VERSION 1.0
    QML_FILES qml/Main.qml qml/SettingWin.qml qml/SettingMain.qml qml/SettingBaidu.qml
    QML_FILES qml/FloatingWin.qml
    RESOURCES icons.qrc
    SOURCES source/picker.h source/eventmonitor.h  source/blockingqueue.h
    SOURCES source/eventmonitor.cpp source/main.cpp source/picker.cpp
    SOURCES source/translator.h source/translator.cpp
    SOURCES source/baidutranslate.h source/baidutranslate.cpp
    SOURCES source/floatingwin.h source/floatingwin.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appxdict PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appxdict
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appxdict
    PRIVATE Qt6::Quick
    ${X11_LIBRARIES}
    ${X11_Xtst_LIB}

)

include(GNUInstallDirs)
install(TARGETS appxdict
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


