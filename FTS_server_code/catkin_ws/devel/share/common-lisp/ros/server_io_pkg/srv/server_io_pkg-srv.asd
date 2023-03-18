
(cl:in-package :asdf)

(defsystem "server_io_pkg-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "diftorder" :depends-on ("_package_diftorder"))
    (:file "_package_diftorder" :depends-on ("_package"))
  ))