
(cl:in-package :asdf)

(defsystem "server_io_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "data" :depends-on ("_package_data"))
    (:file "_package_data" :depends-on ("_package"))
  ))