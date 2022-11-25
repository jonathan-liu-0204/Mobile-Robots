;; Auto-generated. Do not edit!


(when (boundp 'cp3::Num)
  (if (not (find-package "CP3"))
    (make-package "CP3"))
  (shadow 'Num (find-package "CP3")))
(unless (find-package "CP3::NUM")
  (make-package "CP3::NUM"))

(in-package "ROS")
;;//! \htmlinclude Num.msg.html


(defclass cp3::Num
  :super ros::object
  :slots (_num ))

(defmethod cp3::Num
  (:init
   (&key
    ((:num __num) 0)
    )
   (send-super :init)
   (setq _num (round __num))
   self)
  (:num
   (&optional __num)
   (if __num (setq _num __num)) _num)
  (:serialization-length
   ()
   (+
    ;; int32 _num
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _num
       (write-long _num s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _num
     (setq _num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get cp3::Num :md5sum-) "54b3c80efd6fae6e6ffff8a4b9facd69")
(setf (get cp3::Num :datatype-) "cp3/Num")
(setf (get cp3::Num :definition-)
      "int32 num

")



(provide :cp3/Num "54b3c80efd6fae6e6ffff8a4b9facd69")


