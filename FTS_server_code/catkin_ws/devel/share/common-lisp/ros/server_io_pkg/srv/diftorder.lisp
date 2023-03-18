; Auto-generated. Do not edit!


(cl:in-package server_io_pkg-srv)


;//! \htmlinclude diftorder-request.msg.html

(cl:defclass <diftorder-request> (roslisp-msg-protocol:ros-message)
  ((option
    :reader option
    :initarg :option
    :type cl:fixnum
    :initform 0))
)

(cl:defclass diftorder-request (<diftorder-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <diftorder-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'diftorder-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name server_io_pkg-srv:<diftorder-request> is deprecated: use server_io_pkg-srv:diftorder-request instead.")))

(cl:ensure-generic-function 'option-val :lambda-list '(m))
(cl:defmethod option-val ((m <diftorder-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader server_io_pkg-srv:option-val is deprecated.  Use server_io_pkg-srv:option instead.")
  (option m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <diftorder-request>) ostream)
  "Serializes a message object of type '<diftorder-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'option)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'option)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <diftorder-request>) istream)
  "Deserializes a message object of type '<diftorder-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'option)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'option)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<diftorder-request>)))
  "Returns string type for a service object of type '<diftorder-request>"
  "server_io_pkg/diftorderRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'diftorder-request)))
  "Returns string type for a service object of type 'diftorder-request"
  "server_io_pkg/diftorderRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<diftorder-request>)))
  "Returns md5sum for a message object of type '<diftorder-request>"
  "e02c72c1210af7da24f1a6fd961ebe93")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'diftorder-request)))
  "Returns md5sum for a message object of type 'diftorder-request"
  "e02c72c1210af7da24f1a6fd961ebe93")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<diftorder-request>)))
  "Returns full string definition for message of type '<diftorder-request>"
  (cl:format cl:nil "uint16 option~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'diftorder-request)))
  "Returns full string definition for message of type 'diftorder-request"
  (cl:format cl:nil "uint16 option~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <diftorder-request>))
  (cl:+ 0
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <diftorder-request>))
  "Converts a ROS message object to a list"
  (cl:list 'diftorder-request
    (cl:cons ':option (option msg))
))
;//! \htmlinclude diftorder-response.msg.html

(cl:defclass <diftorder-response> (roslisp-msg-protocol:ros-message)
  ((state
    :reader state
    :initarg :state
    :type cl:fixnum
    :initform 0))
)

(cl:defclass diftorder-response (<diftorder-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <diftorder-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'diftorder-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name server_io_pkg-srv:<diftorder-response> is deprecated: use server_io_pkg-srv:diftorder-response instead.")))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <diftorder-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader server_io_pkg-srv:state-val is deprecated.  Use server_io_pkg-srv:state instead.")
  (state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <diftorder-response>) ostream)
  "Serializes a message object of type '<diftorder-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <diftorder-response>) istream)
  "Deserializes a message object of type '<diftorder-response>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<diftorder-response>)))
  "Returns string type for a service object of type '<diftorder-response>"
  "server_io_pkg/diftorderResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'diftorder-response)))
  "Returns string type for a service object of type 'diftorder-response"
  "server_io_pkg/diftorderResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<diftorder-response>)))
  "Returns md5sum for a message object of type '<diftorder-response>"
  "e02c72c1210af7da24f1a6fd961ebe93")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'diftorder-response)))
  "Returns md5sum for a message object of type 'diftorder-response"
  "e02c72c1210af7da24f1a6fd961ebe93")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<diftorder-response>)))
  "Returns full string definition for message of type '<diftorder-response>"
  (cl:format cl:nil "uint16 state~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'diftorder-response)))
  "Returns full string definition for message of type 'diftorder-response"
  (cl:format cl:nil "uint16 state~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <diftorder-response>))
  (cl:+ 0
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <diftorder-response>))
  "Converts a ROS message object to a list"
  (cl:list 'diftorder-response
    (cl:cons ':state (state msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'diftorder)))
  'diftorder-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'diftorder)))
  'diftorder-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'diftorder)))
  "Returns string type for a service object of type '<diftorder>"
  "server_io_pkg/diftorder")