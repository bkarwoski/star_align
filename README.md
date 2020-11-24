# star_align
Using OpenCV to align star exposures.

# Setup Instructions

Tested on Ubuntu 16.04.

## Setup Dependencies

```sudo apt install cmake
mkdir deps
cd deps
```

### Eigen
```
git clone https://gitlab.com/libeigen/eigen.git
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/home/${USER}/star_align/deps/install -DCMAKE_BUILD_TYPE=Release ..
make install
```

### OpenCV
```
cd ~/star_align/deps
git clone git@github.com:opencv/opencv_contrib.git
git clone git@github.com:opencv/opencv.git
cd opencv
mkdir build
cd build
```
```
cmake -DCMAKE_INSTALL_PREFIX=/home/${USER}/star-align/deps/install -DCMAKE_PREFIX_PATH=/home/${USER}/star-align/deps/install -DOPENCV_EXTRA_MODULES_PATH=/home/${USER}/star_align/deps/opencv_contrib/modules -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_DOC=OFF -DOPENCV_ENABLE_NONFREE=ON ..

make install -j
```

### Ceres
```
sudo apt install libsuitesparse-dev libatlas-base-dev libgoogle-glog-dev -y
```
