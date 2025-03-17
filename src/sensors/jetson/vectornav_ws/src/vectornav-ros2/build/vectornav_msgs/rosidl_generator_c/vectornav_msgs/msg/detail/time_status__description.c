// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vectornav_msgs:msg/TimeStatus.idl
// generated code does not contain a copyright notice

#include "vectornav_msgs/msg/detail/time_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
const rosidl_type_hash_t *
vectornav_msgs__msg__TimeStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x7e, 0x0c, 0xf8, 0x31, 0xd6, 0x7e, 0x6e, 0xdf,
      0x13, 0xe3, 0xc2, 0xf5, 0x97, 0x8e, 0x46, 0xac,
      0xa5, 0x5a, 0x8a, 0x55, 0xaf, 0xce, 0x17, 0x8b,
      0x7c, 0x1b, 0x0c, 0xf0, 0xb5, 0x44, 0xbe, 0x9e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char vectornav_msgs__msg__TimeStatus__TYPE_NAME[] = "vectornav_msgs/msg/TimeStatus";

// Define type names, field names, and default values
static char vectornav_msgs__msg__TimeStatus__FIELD_NAME__time_ok[] = "time_ok";
static char vectornav_msgs__msg__TimeStatus__FIELD_NAME__date_ok[] = "date_ok";
static char vectornav_msgs__msg__TimeStatus__FIELD_NAME__utctime_ok[] = "utctime_ok";

static rosidl_runtime_c__type_description__Field vectornav_msgs__msg__TimeStatus__FIELDS[] = {
  {
    {vectornav_msgs__msg__TimeStatus__FIELD_NAME__time_ok, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeStatus__FIELD_NAME__date_ok, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeStatus__FIELD_NAME__utctime_ok, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vectornav_msgs__msg__TimeStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vectornav_msgs__msg__TimeStatus__TYPE_NAME, 29, 29},
      {vectornav_msgs__msg__TimeStatus__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# VectorNav Time Status\n"
  "# UM001 - 4.7.1\n"
  "\n"
  "bool    time_ok\n"
  "bool    date_ok\n"
  "bool    utctime_ok";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vectornav_msgs__msg__TimeStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vectornav_msgs__msg__TimeStatus__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 92, 92},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vectornav_msgs__msg__TimeStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vectornav_msgs__msg__TimeStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
