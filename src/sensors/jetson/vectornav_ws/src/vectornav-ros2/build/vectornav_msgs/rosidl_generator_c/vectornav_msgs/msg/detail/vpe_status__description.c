// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vectornav_msgs:msg/VpeStatus.idl
// generated code does not contain a copyright notice

#include "vectornav_msgs/msg/detail/vpe_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
const rosidl_type_hash_t *
vectornav_msgs__msg__VpeStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x3b, 0x2d, 0x4d, 0xc5, 0x3c, 0x25, 0xba, 0xd9,
      0xda, 0x55, 0xee, 0x0b, 0x1d, 0xf0, 0x45, 0xdb,
      0x3f, 0x25, 0x96, 0x49, 0x7c, 0xef, 0x56, 0x74,
      0x4f, 0x3f, 0x14, 0x03, 0xbd, 0x0a, 0x3a, 0xd8,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char vectornav_msgs__msg__VpeStatus__TYPE_NAME[] = "vectornav_msgs/msg/VpeStatus";

// Define type names, field names, and default values
static char vectornav_msgs__msg__VpeStatus__FIELD_NAME__attitude_quality[] = "attitude_quality";
static char vectornav_msgs__msg__VpeStatus__FIELD_NAME__gyro_saturation[] = "gyro_saturation";
static char vectornav_msgs__msg__VpeStatus__FIELD_NAME__gyro_saturation_recovery[] = "gyro_saturation_recovery";
static char vectornav_msgs__msg__VpeStatus__FIELD_NAME__mag_disturbance[] = "mag_disturbance";
static char vectornav_msgs__msg__VpeStatus__FIELD_NAME__mag_saturation[] = "mag_saturation";
static char vectornav_msgs__msg__VpeStatus__FIELD_NAME__acc_disturbance[] = "acc_disturbance";
static char vectornav_msgs__msg__VpeStatus__FIELD_NAME__acc_saturation[] = "acc_saturation";
static char vectornav_msgs__msg__VpeStatus__FIELD_NAME__known_mag_disturbance[] = "known_mag_disturbance";
static char vectornav_msgs__msg__VpeStatus__FIELD_NAME__known_accel_disturbance[] = "known_accel_disturbance";

static rosidl_runtime_c__type_description__Field vectornav_msgs__msg__VpeStatus__FIELDS[] = {
  {
    {vectornav_msgs__msg__VpeStatus__FIELD_NAME__attitude_quality, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__VpeStatus__FIELD_NAME__gyro_saturation, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__VpeStatus__FIELD_NAME__gyro_saturation_recovery, 24, 24},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__VpeStatus__FIELD_NAME__mag_disturbance, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__VpeStatus__FIELD_NAME__mag_saturation, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__VpeStatus__FIELD_NAME__acc_disturbance, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__VpeStatus__FIELD_NAME__acc_saturation, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__VpeStatus__FIELD_NAME__known_mag_disturbance, 21, 21},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__VpeStatus__FIELD_NAME__known_accel_disturbance, 23, 23},
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
vectornav_msgs__msg__VpeStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vectornav_msgs__msg__VpeStatus__TYPE_NAME, 28, 28},
      {vectornav_msgs__msg__VpeStatus__FIELDS, 9, 9},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# VectorNav VPE Status\n"
  "# UM001 - 4.7.1\n"
  "\n"
  "uint8   attitude_quality\n"
  "bool    gyro_saturation\n"
  "bool    gyro_saturation_recovery\n"
  "uint8   mag_disturbance\n"
  "bool    mag_saturation\n"
  "uint8   acc_disturbance\n"
  "bool    acc_saturation\n"
  "bool    known_mag_disturbance\n"
  "bool    known_accel_disturbance";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vectornav_msgs__msg__VpeStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vectornav_msgs__msg__VpeStatus__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 278, 278},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vectornav_msgs__msg__VpeStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vectornav_msgs__msg__VpeStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
