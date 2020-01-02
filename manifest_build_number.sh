#!/bin/bash
PWD=$1
VERSION=$(cat $1/build_number)
echo $VERSION
REGEXP="s/android\:versionName=\"[0-9]{0,3}\"/android:versionName=\""${VERSION}"\"/" 
CHANGE=$(sed -i -r $REGEXP $PWD/android/AndroidManifest.xml)
echo $CHANGE
