; Auto-generated. Do not edit!


(cl:in-package server_io_pkg-msg)


;//! \htmlinclude data.msg.html

(cl:defclass <data> (roslisp-msg-protocol:ros-message)
  ((servertime
    :reader servertime
    :initarg :servertime
    :type cl:real
    :initform 0)
   (serverstate
    :reader serverstate
    :initarg :serverstate
    :type cl:fixnum
    :initform 0)
   (raw_loadcell
    :reader raw_loadcell
    :initarg :raw_loadcell
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass data (<data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name server_io_pkg-msg:<data> is deprecated: use server_io_pkg-msg:data instead.")))

(cl:ensure-generic-function 'servertime-val :lambda-list '(m))
(cl:defmethod servertime-val ((m <data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader server_io_pkg-msg:servertime-val is deprecated.  Use server_io_pkg-msg:servertime instead.")
  (servertime m))

(cl:ensure-generic-function 'serverstate-val :lambda-list '(m))
(cl:defmethod serverstate-val ((m <data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader server_io_pkg-msg:serverstate-val is deprecated.  Use server_io_pkg-msg:serverstate instead.")
  (serverstate m))

(cl:ensure-generic-function 'raw_loadcell-val :lambda-list '(m))
(cl:defmethod raw_loadcell-val ((m <data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader server_io_pkg-msg:raw_loadcell-val is deprecated.  Use server_io_pkg-msg:raw_loadcell instead.")
  (raw_loadcell m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <data>) ostream)
  "Serializes a message object of type '<data>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'servertime)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'servertime) (cl:floor (cl:slot-value msg 'servertime)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'serverstate)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'serverstate)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'raw_loadcell))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) ele) ostream))
   (cl:slot-value msg 'raw_loadcell))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <data>) istream)
  "Deserializes a message object of type '<data>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'servertime) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'serverstate)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'serverstate)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'raw_loadcell) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'raw_loadcell)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<data>)))
  "Returns string type for a message object of type '<data>"
  "server_io_pkg/data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'data)))
  "Returns string type for a message object of type 'data"
  "server_io_pkg/data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<data>)))
  "Returns md5sum for a message object of type '<data>"
  "8eafbed3b402bae6038c14d1654d8886")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'data)))
  "Returns md5sum for a message object of type 'data"
  "8eafbed3b402bae6038c14d1654d8886")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<data>)))
  "Returns full string definition for message of type '<data>"
  (cl:format cl:nil "time servertime~%uint16 serverstate~%uint32[] raw_loadcell~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'data)))
  "Returns full string definition for message of type 'data"
  (cl:format cl:nil "time servertime~%uint16 serverstate~%uint32[] raw_loadcell~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <data>))
  (cl:+ 0
     8
     2
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'raw_loadcell) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <data>))
  "Converts a ROS message object to a list"
  (cl:list 'data
    (cl:cons ':servertime (servertime msg))
    (cl:cons ':serverstate (serverstate msg))
    (cl:cons ':raw_loadcell (raw_loadcell msg))
))
