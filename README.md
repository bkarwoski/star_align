# star_align
Using OpenCV to align star exposures.

# Setup Instructions

Tested on Ubuntu 16.04.

## Setup Dependencies

```Bash
sudo apt install cmake build-essential gfortran -y
mkdir deps
cd deps
```

### Eigen
```Bash
git clone https://gitlab.com/libeigen/eigen.git
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/home/${USER}/star_align/deps/install -DCMAKE_BUILD_TYPE=Release -DEIGEN_INCLUDE_DIR:PATH=/home/blake/star_align/deps/install/include/eigen3 ..
make install
```

### OpenCV
```Bash
cd ~/star_align/deps
git clone git@github.com:opencv/opencv_contrib.git
cd opencv_contrib
git checkout 3.4.1
cd ~/star_align/deps
git clone git@github.com:opencv/opencv.git
cd opencv
git checkout 3.4.1
mkdir build
cd build
sudo apt install libgtk2.0-dev pkg-config ffmpeg libpng-dev -y
```
```Bash
cmake -DCMAKE_INSTALL_PREFIX=/home/${USER}/star-align/deps/install -DCMAKE_PREFIX_PATH=/home/${USER}/star_align/deps/install -DOPENCV_EXTRA_MODULES_PATH=/home/${USER}/star_align/deps/opencv_contrib/modules -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_DOC=OFF -DOPENCV_ENABLE_NONFREE=ON ..

make install -j
```
Note: I ran into [this issue](https://github.com/opencv/opencv/issues/7636) when running make with multiple threads. If your build fails, try removing the `-j` option.

### Ceres
Download from here: https://github.com/ceres-solver/ceres-solver/archive/1.14.0.tar.gz

Download and extract to `~/star_align/deps/`
```Bash
sudo apt install libsuitesparse-dev libatlas-base-dev libgoogle-glog-dev -y
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/home/${USER}/star_align/deps/install -DCMAKE_PREFIX_PATH=/home/${USER}/star_align/deps/install -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF -DBUILD_SHARED_LIBS=ON -DBUILD_EXAMPLES=OFF -DBUILD_DOCUMENTATION=OFF ..
make install -j
```

### star_align
```Bash
cd ~/star_align
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_PREFIX_PATH=/home/${USER}/star_align/deps/install -DCMAKE_BUILD_TYPE=Release ..
make -j
```
