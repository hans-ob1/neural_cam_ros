[![Travis](https://img.shields.io/travis/rust-lang/rust.svg)]()
[![Codecov](https://img.shields.io/codecov/c/github/codecov/example-python.svg)]()
# neural_cam_ros
neural_cam_ros is essentially an ros wrapper of neural-cam. The backend framework used is darknet developed by Joseph Redmon. You can visit his site here: https://pjreddie.com/darknet/yolo/. This module is designed to quickly test the state-of-the-art obstacle detection/tracking for mobile robot platform. No training option is available in this module.

##### Update
  - basic ros-wrapper for obstacle detection is complete
  - includes link for pre-trained weights/configuration files
  - added cv_bridge for ros image transport
  - tested on drive px 2 (detection does not work well with cuDNN! i think you would need to train directly on their platform)
  - tested on nvidia TX1 (low fps, wait for TX2!)

##### Additional Information
  - requires pre-trained weights, cfg files to run
  - open another terminal and type "rostopic echo /obstacle" to see detected objects been published
  - edit/launch multiple cameras using multicam.launch file
  - to get a decent framerate, use a good graphic card. preferably to be GTX 950 above and run the network with cuDNN
  - i had pre-trained a set of weights to detect road obstacles for my autonomous vehicle project. There are only three classes for the weights i trained (person, bike and vehicle). you can download and try it our yourself from this link: https://drive.google.com/open?id=0Bzdkh7sucheCRGlRYzZhdXNUWms. Do take note that is set of weights is trained with cuDNN v5, be sure to download that from nvidia website. Otherwise, there will be no detections!

##### Recommend System Requirement (Tested and Proven)
- cmake 3.2 above
- ROS Kinetic (due to its preloaded opencv 3, saved alot of hassle)
- ubuntu 16.04
- cuda 8.0 (for real time performance)
- cuDNN v5
- latest nvidia graphic driver 367.48

##### Minimum System Requirement
- cmake 2.8 or above
- ROS indigo or above
- runs on opencv 3.1
- ubuntu 14.04 above
- cuda 7.5 above (modify the CMakeList.txt if you dont have a GPU!)
- cuDNN v5 (download from nvidia official website, need v5 for cuda 8.0)
- latest nvidia graphic driver 367.48

##### Usage Detail
requires ROS to run rosmake
  ```sh
    $ roscd neural_cam_ros
    $ rosmake
    $ roslaunch neural_cam_ros multicam.launch
 ```

##### Common Error
for "installation" of the package, add this line to ~/.bashrc and source it:

```sh
    export ROS_PACKAGE_PATH=/your/path/to/workspace:$ROS_PACKAGE_PATH
```

if cmake display of not able to find "curand/cublas/cudnn", be sure to add the following symbolic link:

```sh
   sudo ln -s /usr/local/cuda/lib64/libcurand.so /usr/lib/libcurand.so
   sudo ln -s /usr/local/cuda/lib64/libcublas.so /usr/lib/libcublas.so
   sudo ln -s /usr/local/cuda/lib64/libcudnn.so /usr/lib/libcudnn.so
```

##### Demo Video on YouTube
[![IMAGE ALT TEXT](http://img.youtube.com/vi/ZW0B2wk8dPA/0.jpg)](http://www.youtube.com/watch?v=ZW0B2wk8dPA "Yolo Road Obstacle Detector")
