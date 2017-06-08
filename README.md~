# neural_cam_ros

neural_cam_ros is basically an extension of neural-cam except wrapped with ROS. The backend framework used is darknet developed by Joseph Redmon. This module is designed to quickly test the state-of-the-art obstacle detection for moving robots. No training option is available in this module.

##### Update
  - basic ros-wrapper for obstacle detection is complete

##### Additional Information
  - requires pre-trained weights, cfg files
  - rename the parent directory to neural_cam_ros
  - open another terminal and type "rostopic echo /obstacle" to see detected objects been published
  - edit/launch multiple cameras using multicam.launch file

##### System Requirement
- cmake 2.8 or above
- ROS indigo or above
- runs on opencv 3.1 (optional if you only intend to poccess images)
- ubuntu 14.04 above
- cuda 7.5 above (modify the CMakeList.txt if you dont have a GPU!)
- latest nvidia graphic driver 367.48

##### Usage Detail
requires ROS to run rosmake
  ```sh
    $ roscd neural_cam_ros
    $ rosmake
    $ rosrun neural_cam_ros detector
 ```

##### Common Error
if cmake complain cannot find curand/cublas, be sure to add the following symbolic link:

```sh
   sudo ln -s /usr/local/cuda/lib64/libcurand.so /usr/lib/libcurand.so
   sudo ln -s /usr/local/cuda/lib64/libcublas.so /usr/lib/libcublas.so
```
