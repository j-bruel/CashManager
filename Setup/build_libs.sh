#!/bin/bash

currentDir=$PWD

#
# Google Test install lib
#
gtestDir=${currentDir}/Libs/googletest
if [[ ! -d ${gtestDir}/googletest/build ]]; then
        echo " - Install Google Test"
        mkdir -p ${gtestDir}/googletest/build
        cd ${gtestDir}/googletest/build && cmake ..
        cd ${gtestDir}/googletest/build && make
else
        echo " - Bypass install Google Test (file ${gtestDir}/googletest/build exist)"
fi

##
## Qt install lib
#
qtDir=${currentDir}/Libs/qt
chmod 777 ${qtDir}/qt-unified-linux-x64-3.0.5-online.run
${qtDir}/qt-unified-linux-x64-3.0.5-online.run

