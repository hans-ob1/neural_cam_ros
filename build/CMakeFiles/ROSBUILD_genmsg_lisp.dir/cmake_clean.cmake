FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/neural_cam_ros/msg"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/obstacleStack.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_obstacleStack.lisp"
  "../msg_gen/lisp/obstacle.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_obstacle.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
