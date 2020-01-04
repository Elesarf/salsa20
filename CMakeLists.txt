# Check minimum required CMake version
cmake_minimum_required(VERSION 3.9)

project("salsa")

if (WIN32)
    set(FUCK_THE_WIN WIN32)
endif()

set(SOURCES
    src/main.cpp
    src/salsa20.cpp
    src/view_model.cpp
    src/data_model.cpp
    src/data_model_controller.cpp
    )

set(HEADERS
    include/salsa20.h
    include/data_model.h
    include/view_model.h
    include/data_model_controller.h
    )

set(QML_SOURCES
    qml/main.qml
    qml/CardList.qml
    qml/EnterScreen.qml
    qml/PasswordDelegate.qml
    qml/FilePicker.qml
    qml/CardView.qml
    )

find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)
qt5_add_resources(QT_RESOURCES qml/qml_resources.qrc)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${QML_SOURCES} ${QT_RESOURCES} ${FUCK_THE_WIN})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${QtQml_DEFINITIONS})

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOUIC ON)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD 14)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_EXTENSIONS OFF)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INCLUDE_CURRENT_DIR ON)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC -Wall
    PUBLIC -Wextra
    PUBLIC -Werror
    )

target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    )

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_include_directories(${PROJECT_NAME} PRIVATE ${QtQml_INCLUDE_DIRECTORY})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND python3 ${CMAKE_SOURCE_DIR}/build_number.py -p)
file (STRINGS "build_number" BUILD_NUMBER)
message("build_number = ${BUILD_NUMBER}")

# Install section (make install):
# DESTINATION: /usr/local by default
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION /usr/local/bin
    LIBRARY DESTINATION /usr/local/lib
    ARCHIVE DESTINATION /usr/local/lib
)

install(
    FILES files/usr/share/applications/salsa.desktop
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION /usr/share/applications
)

install(
    FILES files/usr/share/icons/hicolor/48x48/apps/salsa.png
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION /usr/share/icons/hicolor/48x48/apps/
)

# Packaging (make package, make package_source)
set(CPACK_GENERATOR "DEB")
set(CPACK_SOURCE_GENERATOR "TGZ")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Aleksey Fedchenko, Ass, Tver") #required

set(CPACK_PACKAGE_VERSION 0.1.${BUILD_NUMBER})
set(CPACK_PACKAGE_VERSION_MAJOR 2)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH ${BUILD_NUMBER})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qml-module-qtquick-controls2, qml-module-qtquick-layouts, qml-module-qtquick2, qml-module-qtquick-window2")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

set(CPACK_SOURCE_IGNORE_FILES
    "${CMAKE_SOURCE_DIR}/CMake*"
    "${CMAKE_SOURCE_DIR}/*.pro"
    "${CMAKE_SOURCE_DIR}/.git"
    "${CMAKE_SOURCE_DIR}/.gitignore"
    "${CMAKE_SOURCE_DIR}/README.md"
    "${CMAKE_SOURCE_DIR}/build/"
)

message("Ignoring in sources: ${CPACK_SOURCE_IGNORE_FILES}")

include(CPack)
