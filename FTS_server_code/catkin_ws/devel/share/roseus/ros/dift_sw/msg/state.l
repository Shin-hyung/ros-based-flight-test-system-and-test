;; Auto-generated. Do not edit!


(when (boundp 'dift_sw::state)
  (if (not (find-package "DIFT_SW"))
    (make-package "DIFT_SW"))
  (shadow 'state (find-package "DIFT_SW")))
(unless (find-package "DIFT_SW::STATE")
  (make-package "DIFT_SW::STATE"))

(in-package "ROS")
;;//! \htmlinclude state.msg.html


(defclass dift_sw::state
  :super ros::object
  :slots (_stamp ))

(defmethod dift_sw::state
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    )
   (send-super :init)
   (setq _stamp __stamp)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get dift_sw::state :md5sum-) "84d365d08d5fc49dde870daba1c7992c")
(setf (get dift_sw::state :datatype-) "dift_sw/state")
(setf (get dift_sw::state :definition-)
      "time stamp

")



(provide :dift_sw/state "84d365d08d5fc49dde870daba1c7992c")


