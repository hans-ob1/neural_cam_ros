
(cl:in-package :asdf)

(defsystem "neural_cam_ros-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "obstacleStack" :depends-on ("_package_obstacleStack"))
    (:file "_package_obstacleStack" :depends-on ("_package"))
    (:file "obstacle" :depends-on ("_package_obstacle"))
    (:file "_package_obstacle" :depends-on ("_package"))
  ))