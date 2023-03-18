
(cl:in-package :asdf)

(defsystem "tutorial-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "TestMsg" :depends-on ("_package_TestMsg"))
    (:file "_package_TestMsg" :depends-on ("_package"))
  ))