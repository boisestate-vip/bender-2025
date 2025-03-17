// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vectornav_msgs:msg/InsStatus.idl
// generated code does not contain a copyright notice

#include "vectornav_msgs/msg/detail/ins_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
const rosidl_type_hash_t *
vectornav_msgs__msg__InsStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x4f, 0x0d, 0xbc, 0xc2, 0x35, 0xf3, 0xe2, 0x27,
      0x83, 0x34, 0x5a, 0xeb, 0x92, 0x32, 0xd1, 0x6b,
      0x3d, 0x91, 0x8f, 0x75, 0x78, 0xd8, 0x76, 0x83,
      0x0a, 0xa5, 0x6b, 0x5c, 0x69, 0x8e, 0x80, 0xf3,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char vectornav_msgs__msg__InsStatus__TYPE_NAME[] = "vectornav_msgs/msg/InsStatus";

// Define type names, field names, and default values
static char vectornav_msgs__msg__InsStatus__FIELD_NAME__mode[] = "mode";
static char vectornav_msgs__msg__InsStatus__FIELD_NAME__gps_fix[] = "gps_fix";
static char vectornav_msgs__msg__InsStatus__FIELD_NAME__time_error[] = "time_error";
static char vectornav_msgs__msg__InsStatus__FIELD_NAME__imu_error[] = "imu_error";
static char vectornav_msgs__msg__InsStatus__FIELD_NAME__mag_pres_error[] = "mag_pres_error";
static char vectornav_msgs__msg__InsStatus__FIELD_NAME__gps_error[] = "gps_error";
static char vectornav_msgs__msg__InsStatus__FIELD_NAME__gps_heading_ins[] = "gps_heading_ins";
static char vectornav_msgs__msg__InsStatus__FIELD_NAME__gps_compass[] = "gps_compass";

static rosidl_runtime_c__type_description__Field vectornav_msgs__msg__InsStatus__FIELDS[] = {
  {
    {vectornav_msgs__msg__InsStatus__FIELD_NAME__mode, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__InsStatus__FIELD_NAME__gps_fix, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__InsStatus__FIELD_NAME__time_error, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__InsStatus__FIELD_NAME__imu_error, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__InsStatus__FIELD_NAME__mag_pres_error, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__InsStatus__FIELD_NAME__gps_error, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__InsStatus__FIELD_NAME__gps_heading_ins, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__InsStatus__FIELD_NAME__gps_compass, 11, 11},
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
vectornav_msgs__msg__InsStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vectornav_msgs__msg__InsStatus__TYPE_NAME, 28, 28},
      {vectornav_msgs__msg__InsStatus__FIELDS, 8, 8},
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
  "# UM005 - 10.2.2\n"
  "\n"
  "# TODO[Dereck] VNCXX does not match manual exactly\n"
  "\n"
  "uint8 mode           \n"
  "bool  gps_fix        \\t\\t\\t\n"
  "bool  time_error     \\t\\t\n"
  "bool  imu_error      \\t\n"
  "bool  mag_pres_error \n"
  "bool  gps_error      \n"
  "bool  gps_heading_ins\n"
  "bool  gps_compass    \n"
  "\n"
  "uint8 MODE_NOT_TRACKING     = 0\\t\\t\n"
  "uint8 MODE_ALIGNING         = 1\n"
  "uint8 MODE_TRACKING         = 2\n"
  "uint8 MODE_NO_GPS           = 3\\t";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vectornav_msgs__msg__InsStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vectornav_msgs__msg__InsStatus__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 408, 408},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vectornav_msgs__msg__InsStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vectornav_msgs__msg__InsStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
