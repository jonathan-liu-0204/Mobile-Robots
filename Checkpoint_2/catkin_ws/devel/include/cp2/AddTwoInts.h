// Generated by gencpp from file cp2/AddTwoInts.msg
// DO NOT EDIT!


#ifndef CP2_MESSAGE_ADDTWOINTS_H
#define CP2_MESSAGE_ADDTWOINTS_H

#include <ros/service_traits.h>


#include <cp2/AddTwoIntsRequest.h>
#include <cp2/AddTwoIntsResponse.h>


namespace cp2
{

struct AddTwoInts
{

typedef AddTwoIntsRequest Request;
typedef AddTwoIntsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct AddTwoInts
} // namespace cp2


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::cp2::AddTwoInts > {
  static const char* value()
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const ::cp2::AddTwoInts&) { return value(); }
};

template<>
struct DataType< ::cp2::AddTwoInts > {
  static const char* value()
  {
    return "cp2/AddTwoInts";
  }

  static const char* value(const ::cp2::AddTwoInts&) { return value(); }
};


// service_traits::MD5Sum< ::cp2::AddTwoIntsRequest> should match
// service_traits::MD5Sum< ::cp2::AddTwoInts >
template<>
struct MD5Sum< ::cp2::AddTwoIntsRequest>
{
  static const char* value()
  {
    return MD5Sum< ::cp2::AddTwoInts >::value();
  }
  static const char* value(const ::cp2::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::cp2::AddTwoIntsRequest> should match
// service_traits::DataType< ::cp2::AddTwoInts >
template<>
struct DataType< ::cp2::AddTwoIntsRequest>
{
  static const char* value()
  {
    return DataType< ::cp2::AddTwoInts >::value();
  }
  static const char* value(const ::cp2::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::cp2::AddTwoIntsResponse> should match
// service_traits::MD5Sum< ::cp2::AddTwoInts >
template<>
struct MD5Sum< ::cp2::AddTwoIntsResponse>
{
  static const char* value()
  {
    return MD5Sum< ::cp2::AddTwoInts >::value();
  }
  static const char* value(const ::cp2::AddTwoIntsResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::cp2::AddTwoIntsResponse> should match
// service_traits::DataType< ::cp2::AddTwoInts >
template<>
struct DataType< ::cp2::AddTwoIntsResponse>
{
  static const char* value()
  {
    return DataType< ::cp2::AddTwoInts >::value();
  }
  static const char* value(const ::cp2::AddTwoIntsResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // CP2_MESSAGE_ADDTWOINTS_H
