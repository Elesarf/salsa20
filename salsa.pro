QT += core quick svg

CONFIG += c++14

TARGET = salsa20
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QML_IMPORT_PATH += /home/elesar/Develop/Qt/5.13.1/android_armv7/

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/salsa20.cpp \
    src/view_model.cpp \
    src/data_model.cpp \
    src/data_model_controller.cpp

HEADERS += \
    include/salsa20.h \
    include/data_model.h \
    include/view_model.h \
    include/data_model_controller.h

OTHER_FILES += \
    qml/main.qml \
    qml/PasswordDelegate.qml

RESOURCES += qml/qml_resources.qrc

INCLUDEPATH += ./include

android: \
{
    DISTFILES += \
        android/AndroidManifest.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew \
        android/gradlew.bat \
        android/res/values/libs.xml
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
