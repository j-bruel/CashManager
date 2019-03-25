#!/bin/bash

currentDir=$PWD
##
## Qt install info
##
echo "What is the QT root directory ?"
read -p "QT_ROOT = " qtRootDir
export QT_ROOT_DIR=${qtRootDir}
echo "What is the QT include directory ?"
read -p "QT_INCLUDEDIR = " qtIncludeDir
export QT_INCLUDEDIR=${qtIncludeDir}
echo "What is the QT libraries directory ?"
read -p "QT_LIBRARYDIR = " qtLibrariesDir
export QT_LIBRARYDIR=${qtLibrariesDir}
for projectDir in "Components/Client" \

do
	if [[ ! -d ${currentDir}/${projectDir}/build ]]; then
	    mkdir ${currentDir}/${projectDir}/build
	    cd ${currentDir}/${projectDir}/build && cmake ..
            cd ${currentDir}/${projectDir}/build && make
#            cd ${currentDir}/${projectDir}/build && make install
        else
	    cd ${currentDir}/${projectDir}/build && cmake ..
            cd ${currentDir}/${projectDir}/build && make
        fi
done
