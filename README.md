#neural-cam-ros
neural-cam-ros is basically an extension of neural-cam except wrapped with ROS. The backend framework used is darknet developed by Joseph Redmon. This moduele is designed to quickly test the state-of-the-art obstacle detection for moving robots. No training option is available in this module. You can browse through the weights folder for pre-trained weights such as VGG/Coco

Usage Details:
- rosmake
- rosrun neural-cam main (be sure to run roscore first)

Changes:
- Opencv component is completely decoupled from .c files

Requirements:
- cmake 2.8 above
- ROS indigo and above
- runs on opencv 3.1 (optional if you only intend to poccess images)
- ubuntu 14.04 above
- cuda 7.5 above (modify the CMakeList.txt if you dont have a GPU!)
- latest nvidia graphic driver 367.48
