# Before building this package, please

## Install the William Woodall's Serial lib

https://github.com/wjwwood/serial

Follow the installation steps in the README file of the repo.
1. Sourcing the ros setup bash to setup compile environment (catkin build tool depend)

```sh
source /opt/ros/noetic/setup.bash
```

2. Make a new folder for `serial` library and get the code

(The below command will create a folder named `serial_lib` at the `/home/<user_acc>`)
```sh
mkdir ~/serial_lib
```

Then clone the code from github
```sh
cd ~/serial_lib
git clone https://github.com/wjwwood/serial .
```

3. Buid
```sh
make -j
```

4. Install
```sh
make install
```

(After installation process is complete without errors, remember the location where all installation
file have in common, in my case, that is the `/tmp/usr/local`. This path is very important at the
exporting step below).

## Clone and build the serial node package

1. Please `cd` to the correct directory - that is inside a catkin workspace dir that you want to run
this along side with other catkin packages and ros nodes, in my case, that is the default catkin_ws
```sh
cd ~/catkin_ws/src
```

2. Clone this packge
```sh
git clone 
```

3. Build - before build, please `export` the location where wwjwood serial library has been installed.
```sh
export CMAKE_PREFIX_PATH=/tmp/usr/local:$CMAKE_PREFIX_PATH
cd ~/catkin_ws
catkin_make
```

4. Enjoy!