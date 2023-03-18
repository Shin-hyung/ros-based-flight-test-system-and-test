;; Auto-generated. Do not edit!


(when (boundp 'server_io_pkg::data)
  (if (not (find-package "SERVER_IO_PKG"))
    (make-package "SERVER_IO_PKG"))
  (shadow 'data (find-package "SERVER_IO_PKG")))
(unless (find-package "SERVER_IO_PKG::DATA")
  (make-package "SERVER_IO_PKG::DATA"))

(in-package "ROS")
;;//! \htmlinclude data.msg.html


(defclass server_io_pkg::data
  :super ros::object
  :slots (_servertime _serverstate _raw_loadcell ))

(defmethod server_io_pkg::data
  (:init
   (&key
    ((:servertime __servertime) (instance ros::time :init))
    ((:serverstate __serverstate) 0)
    ((:raw_loadcell __raw_loadcell) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _servertime __servertime)
   (setq _serverstate (round __serverstate))
   (setq _raw_loadcell __raw_loadcell)
   self)
  (:servertime
   (&optional __servertime)
   (if __servertime (setq _servertime __servertime)) _servertime)
  (:serverstate
   (&optional __serverstate)
   (if __serverstate (setq _serverstate __serverstate)) _serverstate)
  (:raw_loadcell
   (&optional __raw_loadcell)
   (if __raw_loadcell (setq _raw_loadcell __raw_loadcell)) _raw_loadcell)
  (:serialization-length
   ()
   (+
    ;; time _servertime
    8
    ;; uint16 _serverstate
    2
    ;; uint32[] _raw_loadcell
    (* 4    (length _raw_loadcell)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _servertime
       (write-long (send _servertime :sec) s) (write-long (send _servertime :nsec) s)
     ;; uint16 _serverstate
       (write-word _serverstate s)
     ;; uint32[] _raw_loadcell
     (write-long (length _raw_loadcell) s)
     (dotimes (i (length _raw_loadcell))
       (write-long (elt _raw_loadcell i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _servertime
     (send _servertime :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _servertime :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint16 _serverstate
     (setq _serverstate (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint32[] _raw_loadcell
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _raw_loadcell (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _raw_loadcell i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get server_io_pkg::data :md5sum-) "8eafbed3b402bae6038c14d1654d8886")
(setf (get server_io_pkg::data :datatype-) "server_io_pkg/data")
(setf (get server_io_pkg::data :definition-)
      "time servertime
uint16 serverstate
uint32[] raw_loadcell

")



(provide :server_io_pkg/data "8eafbed3b402bae6038c14d1654d8886")


