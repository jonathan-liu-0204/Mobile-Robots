;; Auto-generated. Do not edit!


(when (boundp 'cp2::Num)
  (if (not (find-package "CP2"))
    (make-package "CP2"))
  (shadow 'Num (find-package "CP2")))
(unless (find-package "CP2::NUM")
  (make-package "CP2::NUM"))

(in-package "ROS")
;;//! \htmlinclude Num.msg.html


(defclass cp2::Num
  :super ros::object
  :slots (_num ))

(defmethod cp2::Num
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

(setf (get cp2::Num :md5sum-) "54b3c80efd6fae6e6ffff8a4b9facd69")
(setf (get cp2::Num :datatype-) "cp2/Num")
(setf (get cp2::Num :definition-)
      "int32 num

")



(provide :cp2/Num "54b3c80efd6fae6e6ffff8a4b9facd69")


