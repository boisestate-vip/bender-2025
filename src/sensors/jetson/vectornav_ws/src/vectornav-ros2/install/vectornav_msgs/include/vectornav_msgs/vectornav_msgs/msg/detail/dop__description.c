// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vectornav_msgs:msg/DOP.idl
// generated code does not contain a copyright notice

#include "vectornav_msgs/msg/detail/dop__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
const rosidl_type_hash_t *
vectornav_msgs__msg__DOP__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xef, 0x71, 0x35, 0x83, 0xcf, 0x04, 0xfc, 0x3c,
      0xfe, 0x0c, 0x1d, 0x49, 0x8c, 0x0a, 0x36, 0xb5,
      0xdd, 0x6b, 0x3f, 0x78, 0xa2, 0x2e, 0x12, 0x43,
      0x94, 0x86, 0xbb, 0x7e, 0xc7, 0x4e, 0xff, 0x6c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char vectornav_msgs__msg__DOP__TYPE_NAME[] = "vectornav_msgs/msg/DOP";

// Define type names, field names, and default values
static char vectornav_msgs__msg__DOP__FIELD_NAME__g[] = "g";
static char vectornav_msgs__msg__DOP__FIELD_NAME__p[] = "p";
static char vectornav_msgs__msg__DOP__FIELD_NAME__t[] = "t";
static char vectornav_msgs__msg__DOP__FIELD_NAME__v[] = "v";
static char vectornav_msgs__msg__DOP__FIELD_NAME__h[] = "h";
static char vectornav_msgs__msg__DOP__FIELD_NAME__n[] = "n";
static char vectornav_msgs__msg__DOP__FIELD_NAME__e[] = "e";

static rosidl_runtime_c__type_description__Field vectornav_msgs__msg__DOP__FIELDS[] = {
  {
    {vectornav_msgs__msg__DOP__FIELD_NAME__g, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__DOP__FIELD_NAME__p, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__DOP__FIELD_NAME__t, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__DOP__FIELD_NAME__v, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__DOP__FIELD_NAME__h, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__DOP__FIELD_NAME__n, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__DOP__FIELD_NAME__e, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vectornav_msgs__msg__DOP__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vectornav_msgs__msg__DOP__TYPE_NAME, 22, 22},
      {vectornav_msgs__msg__DOP__FIELDS, 7, 7},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# VectorNav Dilution of Precision\n"
  "# UM005 - 5.7.14\n"
  "\n"
  "float32   g\n"
  "float32   p\n"
  "float32   t\n"
  "float32   v\n"
  "float32   h\n"
  "float32   n\n"
  "float32   e";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vectornav_msgs__msg__DOP__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vectornav_msgs__msg__DOP__TYPE_NAME, 22, 22},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 136, 136},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vectornav_msgs__msg__DOP__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vectornav_msgs__msg__DOP__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
