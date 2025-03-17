// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vectornav_msgs:msg/TimeUTC.idl
// generated code does not contain a copyright notice

#include "vectornav_msgs/msg/detail/time_utc__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
const rosidl_type_hash_t *
vectornav_msgs__msg__TimeUTC__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xa2, 0x34, 0x1f, 0x6a, 0x21, 0xde, 0x28, 0xbf,
      0x03, 0xd0, 0x47, 0x4d, 0x4b, 0x83, 0x64, 0x6b,
      0x43, 0x2c, 0x1e, 0x21, 0x84, 0xbb, 0xd1, 0x7d,
      0xf3, 0x0c, 0x81, 0x10, 0x96, 0x7c, 0x4f, 0x8d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char vectornav_msgs__msg__TimeUTC__TYPE_NAME[] = "vectornav_msgs/msg/TimeUTC";

// Define type names, field names, and default values
static char vectornav_msgs__msg__TimeUTC__FIELD_NAME__year[] = "year";
static char vectornav_msgs__msg__TimeUTC__FIELD_NAME__month[] = "month";
static char vectornav_msgs__msg__TimeUTC__FIELD_NAME__day[] = "day";
static char vectornav_msgs__msg__TimeUTC__FIELD_NAME__hour[] = "hour";
static char vectornav_msgs__msg__TimeUTC__FIELD_NAME__min[] = "min";
static char vectornav_msgs__msg__TimeUTC__FIELD_NAME__sec[] = "sec";
static char vectornav_msgs__msg__TimeUTC__FIELD_NAME__ms[] = "ms";

static rosidl_runtime_c__type_description__Field vectornav_msgs__msg__TimeUTC__FIELDS[] = {
  {
    {vectornav_msgs__msg__TimeUTC__FIELD_NAME__year, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeUTC__FIELD_NAME__month, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeUTC__FIELD_NAME__day, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeUTC__FIELD_NAME__hour, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeUTC__FIELD_NAME__min, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeUTC__FIELD_NAME__sec, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeUTC__FIELD_NAME__ms, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vectornav_msgs__msg__TimeUTC__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vectornav_msgs__msg__TimeUTC__TYPE_NAME, 26, 26},
      {vectornav_msgs__msg__TimeUTC__FIELDS, 7, 7},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# VectorNav Timestamp (UTC)\n"
  "       \n"
  "uint8   year\n"
  "uint8   month\n"
  "uint8   day\n"
  "uint8   hour\n"
  "uint8   min\n"
  "uint8   sec\n"
  "uint16  ms";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vectornav_msgs__msg__TimeUTC__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vectornav_msgs__msg__TimeUTC__TYPE_NAME, 26, 26},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 123, 123},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vectornav_msgs__msg__TimeUTC__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vectornav_msgs__msg__TimeUTC__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
