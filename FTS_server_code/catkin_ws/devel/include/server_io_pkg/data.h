// Generated by gencpp from file server_io_pkg/data.msg
// DO NOT EDIT!


#ifndef SERVER_IO_PKG_MESSAGE_DATA_H
#define SERVER_IO_PKG_MESSAGE_DATA_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace server_io_pkg
{
template <class ContainerAllocator>
struct data_
{
  typedef data_<ContainerAllocator> Type;

  data_()
    : servertime()
    , serverstate(0)
    , raw_loadcell()  {
    }
  data_(const ContainerAllocator& _alloc)
    : servertime()
    , serverstate(0)
    , raw_loadcell(_alloc)  {
  (void)_alloc;
    }



   typedef ros::Time _servertime_type;
  _servertime_type servertime;

   typedef uint16_t _serverstate_type;
  _serverstate_type serverstate;

   typedef std::vector<uint32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint32_t>> _raw_loadcell_type;
  _raw_loadcell_type raw_loadcell;





  typedef boost::shared_ptr< ::server_io_pkg::data_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::server_io_pkg::data_<ContainerAllocator> const> ConstPtr;

}; // struct data_

typedef ::server_io_pkg::data_<std::allocator<void> > data;

typedef boost::shared_ptr< ::server_io_pkg::data > dataPtr;
typedef boost::shared_ptr< ::server_io_pkg::data const> dataConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::server_io_pkg::data_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::server_io_pkg::data_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::server_io_pkg::data_<ContainerAllocator1> & lhs, const ::server_io_pkg::data_<ContainerAllocator2> & rhs)
{
  return lhs.servertime == rhs.servertime &&
    lhs.serverstate == rhs.serverstate &&
    lhs.raw_loadcell == rhs.raw_loadcell;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::server_io_pkg::data_<ContainerAllocator1> & lhs, const ::server_io_pkg::data_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace server_io_pkg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::server_io_pkg::data_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::server_io_pkg::data_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::server_io_pkg::data_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::server_io_pkg::data_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::server_io_pkg::data_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::server_io_pkg::data_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::server_io_pkg::data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8eafbed3b402bae6038c14d1654d8886";
  }

  static const char* value(const ::server_io_pkg::data_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8eafbed3b402bae6ULL;
  static const uint64_t static_value2 = 0x038c14d1654d8886ULL;
};

template<class ContainerAllocator>
struct DataType< ::server_io_pkg::data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "server_io_pkg/data";
  }

  static const char* value(const ::server_io_pkg::data_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::server_io_pkg::data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "time servertime\n"
"uint16 serverstate\n"
"uint32[] raw_loadcell\n"
;
  }

  static const char* value(const ::server_io_pkg::data_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::server_io_pkg::data_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.servertime);
      stream.next(m.serverstate);
      stream.next(m.raw_loadcell);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct data_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::server_io_pkg::data_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::server_io_pkg::data_<ContainerAllocator>& v)
  {
    s << indent << "servertime: ";
    Printer<ros::Time>::stream(s, indent + "  ", v.servertime);
    s << indent << "serverstate: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.serverstate);
    s << indent << "raw_loadcell[]" << std::endl;
    for (size_t i = 0; i < v.raw_loadcell.size(); ++i)
    {
      s << indent << "  raw_loadcell[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.raw_loadcell[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // SERVER_IO_PKG_MESSAGE_DATA_H