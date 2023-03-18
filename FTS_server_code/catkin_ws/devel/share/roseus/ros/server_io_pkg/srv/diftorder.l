;; Auto-generated. Do not edit!


(when (boundp 'server_io_pkg::diftorder)
  (if (not (find-package "SERVER_IO_PKG"))
    (make-package "SERVER_IO_PKG"))
  (shadow 'diftorder (find-package "SERVER_IO_PKG")))
(unless (find-package "SERVER_IO_PKG::DIFTORDER")
  (make-package "SERVER_IO_PKG::DIFTORDER"))
(unless (find-package "SERVER_IO_PKG::DIFTORDERREQUEST")
  (make-package "SERVER_IO_PKG::DIFTORDERREQUEST"))
(unless (find-package "SERVER_IO_PKG::DIFTORDERRESPONSE")
  (make-package "SERVER_IO_PKG::DIFTORDERRESPONSE"))

(in-package "ROS")





(defclass server_io_pkg::diftorderRequest
  :super ros::object
  :slots (_option ))

(defmethod server_io_pkg::diftorderRequest
  (:init
   (&key
    ((:option __option) 0)
    )
   (send-super :init)
   (setq _option (round __option))
   self)
  (:option
   (&optional __option)
   (if __option (setq _option __option)) _option)
  (:serialization-length
   ()
   (+
    ;; uint16 _option
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _option
       (write-word _option s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _option
     (setq _option (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(defclass server_io_pkg::diftorderResponse
  :super ros::object
  :slots (_state ))

(defmethod server_io_pkg::diftorderResponse
  (:init
   (&key
    ((:state __state) 0)
    )
   (send-super :init)
   (setq _state (round __state))
   self)
  (:state
   (&optional __state)
   (if __state (setq _state __state)) _state)
  (:serialization-length
   ()
   (+
    ;; uint16 _state
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _state
       (write-word _state s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _state
     (setq _state (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(defclass server_io_pkg::diftorder
  :super ros::object
  :slots ())

(setf (get server_io_pkg::diftorder :md5sum-) "e02c72c1210af7da24f1a6fd961ebe93")
(setf (get server_io_pkg::diftorder :datatype-) "server_io_pkg/diftorder")
(setf (get server_io_pkg::diftorder :request) server_io_pkg::diftorderRequest)
(setf (get server_io_pkg::diftorder :response) server_io_pkg::diftorderResponse)

(defmethod server_io_pkg::diftorderRequest
  (:response () (instance server_io_pkg::diftorderResponse :init)))

(setf (get server_io_pkg::diftorderRequest :md5sum-) "e02c72c1210af7da24f1a6fd961ebe93")
(setf (get server_io_pkg::diftorderRequest :datatype-) "server_io_pkg/diftorderRequest")
(setf (get server_io_pkg::diftorderRequest :definition-)
      "uint16 option
---
uint16 state

")

(setf (get server_io_pkg::diftorderResponse :md5sum-) "e02c72c1210af7da24f1a6fd961ebe93")
(setf (get server_io_pkg::diftorderResponse :datatype-) "server_io_pkg/diftorderResponse")
(setf (get server_io_pkg::diftorderResponse :definition-)
      "uint16 option
---
uint16 state

")



(provide :server_io_pkg/diftorder "e02c72c1210af7da24f1a6fd961ebe93")


