#neural-cam-ros
is basically an extension of neural-cam except wrapped with ROS. The backend framework used is darknet developed by Joseph Redmon. This module is designed to quickly test the state-of-the-art obstacle detection for moving robots. No training option is available in this module.

Usage Details:
- remake the parent directory to neural_cam_ros (due to illegal name issue with ros)
- rosmake
- rosrun neural_cam_ros main (be sure to run roscore first)
- open another terminal and type "rostopic echo /obstacle" to see detected objects been published
- launch multiple cameras using multicam.launch file

Changes:
- basic ros-wrapper for obstacle detection is complete

Additional Notes:
- requires pre-trained weights, cfg files

Requirements:
- cmake 2.8 or above
- ROS indigo or above
- runs on opencv 3.1 (optional if you only intend to poccess images)
- ubuntu 14.04 above
- cuda 7.5 above (modify the CMakeList.txt if you dont have a GPU!)
- latest nvidia graphic driver 367.48
