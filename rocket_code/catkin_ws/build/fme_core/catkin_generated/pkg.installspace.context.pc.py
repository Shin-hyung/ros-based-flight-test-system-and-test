# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "roscpp;serial;sensor_msgs;std_msgs;std_srvs;geometry_msgs".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lfme_core".split(';') if "-lfme_core" != "" else []
PROJECT_NAME = "fme_core"
PROJECT_SPACE_DIR = "/home/rocket/catkin_ws/install"
PROJECT_VERSION = "0.0.1"
