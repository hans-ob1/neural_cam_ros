; Auto-generated. Do not edit!


(cl:in-package neural_cam_ros-msg)


;//! \htmlinclude obstacleStack.msg.html

(cl:defclass <obstacleStack> (roslisp-msg-protocol:ros-message)
  ((stack_name
    :reader stack_name
    :initarg :stack_name
    :type cl:string
    :initform "")
   (stack_len
    :reader stack_len
    :initarg :stack_len
    :type cl:integer
    :initform 0)
   (stack_obstacles
    :reader stack_obstacles
    :initarg :stack_obstacles
    :type (cl:vector neural_cam_ros-msg:obstacle)
   :initform (cl:make-array 0 :element-type 'neural_cam_ros-msg:obstacle :initial-element (cl:make-instance 'neural_cam_ros-msg:obstacle))))
)

(cl:defclass obstacleStack (<obstacleStack>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <obstacleStack>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'obstacleStack)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name neural_cam_ros-msg:<obstacleStack> is deprecated: use neural_cam_ros-msg:obstacleStack instead.")))

(cl:ensure-generic-function 'stack_name-val :lambda-list '(m))
(cl:defmethod stack_name-val ((m <obstacleStack>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader neural_cam_ros-msg:stack_name-val is deprecated.  Use neural_cam_ros-msg:stack_name instead.")
  (stack_name m))

(cl:ensure-generic-function 'stack_len-val :lambda-list '(m))
(cl:defmethod stack_len-val ((m <obstacleStack>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader neural_cam_ros-msg:stack_len-val is deprecated.  Use neural_cam_ros-msg:stack_len instead.")
  (stack_len m))

(cl:ensure-generic-function 'stack_obstacles-val :lambda-list '(m))
(cl:defmethod stack_obstacles-val ((m <obstacleStack>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader neural_cam_ros-msg:stack_obstacles-val is deprecated.  Use neural_cam_ros-msg:stack_obstacles instead.")
  (stack_obstacles m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <obstacleStack>) ostream)
  "Serializes a message object of type '<obstacleStack>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'stack_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'stack_name))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'stack_len)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'stack_len)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'stack_len)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'stack_len)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'stack_obstacles))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'stack_obstacles))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <obstacleStack>) istream)
  "Deserializes a message object of type '<obstacleStack>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stack_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'stack_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'stack_len)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'stack_len)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'stack_len)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'stack_len)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'stack_obstacles) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'stack_obstacles)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'neural_cam_ros-msg:obstacle))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<obstacleStack>)))
  "Returns string type for a message object of type '<obstacleStack>"
  "neural_cam_ros/obstacleStack")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'obstacleStack)))
  "Returns string type for a message object of type 'obstacleStack"
  "neural_cam_ros/obstacleStack")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<obstacleStack>)))
  "Returns md5sum for a message object of type '<obstacleStack>"
  "78f69d2c2bc1534a704126e4efe4e06e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'obstacleStack)))
  "Returns md5sum for a message object of type 'obstacleStack"
  "78f69d2c2bc1534a704126e4efe4e06e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<obstacleStack>)))
  "Returns full string definition for message of type '<obstacleStack>"
  (cl:format cl:nil "string stack_name~%uint32 stack_len~%obstacle[] stack_obstacles~%~%================================================================================~%MSG: neural_cam_ros/obstacle~%#info: topleft_, bottomright_ refering to image~%#info: planar_ is plane position information~%~%string name~%geometry_msgs/Point topleft~%geometry_msgs/Point bottomright~%~%#string name~%#float32 depth~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'obstacleStack)))
  "Returns full string definition for message of type 'obstacleStack"
  (cl:format cl:nil "string stack_name~%uint32 stack_len~%obstacle[] stack_obstacles~%~%================================================================================~%MSG: neural_cam_ros/obstacle~%#info: topleft_, bottomright_ refering to image~%#info: planar_ is plane position information~%~%string name~%geometry_msgs/Point topleft~%geometry_msgs/Point bottomright~%~%#string name~%#float32 depth~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <obstacleStack>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'stack_name))
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'stack_obstacles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <obstacleStack>))
  "Converts a ROS message object to a list"
  (cl:list 'obstacleStack
    (cl:cons ':stack_name (stack_name msg))
    (cl:cons ':stack_len (stack_len msg))
    (cl:cons ':stack_obstacles (stack_obstacles msg))
))
