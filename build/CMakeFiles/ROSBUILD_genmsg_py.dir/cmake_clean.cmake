FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/neural_cam_ros/msg"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/neural_cam_ros/msg/__init__.py"
  "../src/neural_cam_ros/msg/_obstacleStack.py"
  "../src/neural_cam_ros/msg/_obstacle.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
