git submodule init
git submodule update
cd gtest
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="./install" ..
make install -j2
cd ../..
