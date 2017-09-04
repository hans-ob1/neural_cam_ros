; Auto-generated. Do not edit!


(cl:in-package neural_cam_ros-msg)


;//! \htmlinclude obstacle.msg.html

(cl:defclass <obstacle> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (prob
    :reader prob
    :initarg :prob
    :type cl:float
    :initform 0.0)
   (topleft
    :reader topleft
    :initarg :topleft
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (bottomright
    :reader bottomright
    :initarg :bottomright
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass obstacle (<obstacle>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <obstacle>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'obstacle)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name neural_cam_ros-msg:<obstacle> is deprecated: use neural_cam_ros-msg:obstacle instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader neural_cam_ros-msg:name-val is deprecated.  Use neural_cam_ros-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'prob-val :lambda-list '(m))
(cl:defmethod prob-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader neural_cam_ros-msg:prob-val is deprecated.  Use neural_cam_ros-msg:prob instead.")
  (prob m))

(cl:ensure-generic-function 'topleft-val :lambda-list '(m))
(cl:defmethod topleft-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader neural_cam_ros-msg:topleft-val is deprecated.  Use neural_cam_ros-msg:topleft instead.")
  (topleft m))

(cl:ensure-generic-function 'bottomright-val :lambda-list '(m))
(cl:defmethod bottomright-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader neural_cam_ros-msg:bottomright-val is deprecated.  Use neural_cam_ros-msg:bottomright instead.")
  (bottomright m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <obstacle>) ostream)
  "Serializes a message object of type '<obstacle>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'prob))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'topleft) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'bottomright) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <obstacle>) istream)
  "Deserializes a message object of type '<obstacle>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'prob) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'topleft) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'bottomright) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<obstacle>)))
  "Returns string type for a message object of type '<obstacle>"
  "neural_cam_ros/obstacle")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'obstacle)))
  "Returns string type for a message object of type 'obstacle"
  "neural_cam_ros/obstacle")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<obstacle>)))
  "Returns md5sum for a message object of type '<obstacle>"
  "2ed324cc68b63371ced6bc19d77946d2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'obstacle)))
  "Returns md5sum for a message object of type 'obstacle"
  "2ed324cc68b63371ced6bc19d77946d2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<obstacle>)))
  "Returns full string definition for message of type '<obstacle>"
  (cl:format cl:nil "#info: topleft_, bottomright_ refering to image~%#info: planar_ is plane position information~%~%string name~%float32 prob~%geometry_msgs/Point topleft~%geometry_msgs/Point bottomright~%~%#string name~%#float32 depth~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'obstacle)))
  "Returns full string definition for message of type 'obstacle"
  (cl:format cl:nil "#info: topleft_, bottomright_ refering to image~%#info: planar_ is plane position information~%~%string name~%float32 prob~%geometry_msgs/Point topleft~%geometry_msgs/Point bottomright~%~%#string name~%#float32 depth~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <obstacle>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'topleft))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'bottomright))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <obstacle>))
  "Converts a ROS message object to a list"
  (cl:list 'obstacle
    (cl:cons ':name (name msg))
    (cl:cons ':prob (prob msg))
    (cl:cons ':topleft (topleft msg))
    (cl:cons ':bottomright (bottomright msg))
))
