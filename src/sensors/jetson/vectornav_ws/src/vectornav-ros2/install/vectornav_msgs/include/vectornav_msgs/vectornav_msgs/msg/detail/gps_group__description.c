// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vectornav_msgs:msg/GpsGroup.idl
// generated code does not contain a copyright notice

#include "vectornav_msgs/msg/detail/gps_group__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
const rosidl_type_hash_t *
vectornav_msgs__msg__GpsGroup__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x23, 0x72, 0xc9, 0x6e, 0x2d, 0x3f, 0xc0, 0xd4,
      0xc7, 0x87, 0x68, 0x29, 0x2d, 0x0b, 0x0a, 0x91,
      0xc8, 0x26, 0xdc, 0x5f, 0xa8, 0xfd, 0x72, 0xc4,
      0x92, 0x9b, 0xd8, 0x88, 0xf4, 0x6e, 0xbc, 0x39,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "vectornav_msgs/msg/detail/dop__functions.h"
#include "vectornav_msgs/msg/detail/time_utc__functions.h"
#include "geometry_msgs/msg/detail/vector3__functions.h"
#include "std_msgs/msg/detail/header__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "geometry_msgs/msg/detail/point__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Vector3__EXPECTED_HASH = {1, {
    0xcc, 0x12, 0xfe, 0x83, 0xe4, 0xc0, 0x27, 0x19,
    0xf1, 0xce, 0x80, 0x70, 0xbf, 0xd1, 0x4a, 0xec,
    0xd4, 0x0f, 0x75, 0xa9, 0x66, 0x96, 0xa6, 0x7a,
    0x2a, 0x1f, 0x37, 0xf7, 0xdb, 0xb0, 0x76, 0x5d,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
static const rosidl_type_hash_t vectornav_msgs__msg__DOP__EXPECTED_HASH = {1, {
    0xef, 0x71, 0x35, 0x83, 0xcf, 0x04, 0xfc, 0x3c,
    0xfe, 0x0c, 0x1d, 0x49, 0x8c, 0x0a, 0x36, 0xb5,
    0xdd, 0x6b, 0x3f, 0x78, 0xa2, 0x2e, 0x12, 0x43,
    0x94, 0x86, 0xbb, 0x7e, 0xc7, 0x4e, 0xff, 0x6c,
  }};
static const rosidl_type_hash_t vectornav_msgs__msg__TimeUTC__EXPECTED_HASH = {1, {
    0xa2, 0x34, 0x1f, 0x6a, 0x21, 0xde, 0x28, 0xbf,
    0x03, 0xd0, 0x47, 0x4d, 0x4b, 0x83, 0x64, 0x6b,
    0x43, 0x2c, 0x1e, 0x21, 0x84, 0xbb, 0xd1, 0x7d,
    0xf3, 0x0c, 0x81, 0x10, 0x96, 0x7c, 0x4f, 0x8d,
  }};
#endif

static char vectornav_msgs__msg__GpsGroup__TYPE_NAME[] = "vectornav_msgs/msg/GpsGroup";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";
static char geometry_msgs__msg__Vector3__TYPE_NAME[] = "geometry_msgs/msg/Vector3";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";
static char vectornav_msgs__msg__DOP__TYPE_NAME[] = "vectornav_msgs/msg/DOP";
static char vectornav_msgs__msg__TimeUTC__TYPE_NAME[] = "vectornav_msgs/msg/TimeUTC";

// Define type names, field names, and default values
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__header[] = "header";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__group_fields[] = "group_fields";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__utc[] = "utc";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__tow[] = "tow";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__week[] = "week";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__numsats[] = "numsats";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__fix[] = "fix";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__poslla[] = "poslla";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__posecef[] = "posecef";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__velned[] = "velned";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__velecef[] = "velecef";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__posu[] = "posu";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__velu[] = "velu";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__timeu[] = "timeu";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__timeinfo_status[] = "timeinfo_status";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__timeinfo_leapseconds[] = "timeinfo_leapseconds";
static char vectornav_msgs__msg__GpsGroup__FIELD_NAME__dop[] = "dop";

static rosidl_runtime_c__type_description__Field vectornav_msgs__msg__GpsGroup__FIELDS[] = {
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__group_fields, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__utc, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vectornav_msgs__msg__TimeUTC__TYPE_NAME, 26, 26},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__tow, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__week, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__numsats, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__fix, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__poslla, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__posecef, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__velned, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__velecef, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__posu, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__velu, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__timeu, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__timeinfo_status, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__timeinfo_leapseconds, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__GpsGroup__FIELD_NAME__dop, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vectornav_msgs__msg__DOP__TYPE_NAME, 22, 22},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vectornav_msgs__msg__GpsGroup__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__DOP__TYPE_NAME, 22, 22},
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeUTC__TYPE_NAME, 26, 26},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vectornav_msgs__msg__GpsGroup__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vectornav_msgs__msg__GpsGroup__TYPE_NAME, 27, 27},
      {vectornav_msgs__msg__GpsGroup__FIELDS, 17, 17},
    },
    {vectornav_msgs__msg__GpsGroup__REFERENCED_TYPE_DESCRIPTIONS, 6, 6},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Vector3__EXPECTED_HASH, geometry_msgs__msg__Vector3__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = geometry_msgs__msg__Vector3__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&vectornav_msgs__msg__DOP__EXPECTED_HASH, vectornav_msgs__msg__DOP__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = vectornav_msgs__msg__DOP__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&vectornav_msgs__msg__TimeUTC__EXPECTED_HASH, vectornav_msgs__msg__TimeUTC__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = vectornav_msgs__msg__TimeUTC__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# VectorNav Composite Data Packet\n"
  "#\n"
  "# Only the enabled fields will be populated with data and only the fields\n"
  "# you require for your application should be enabled to conserve bandwidth\n"
  "# and increase the update rate.\n"
  "#\n"
  "# TODO[Dereck] Requires rosidl patches\n"
  "\n"
  "# Data Received (ROS Time)\n"
  "std_msgs/Header header\n"
  "\n"
  "# Field Enable Bits\n"
  "uint16                      group_fields\n"
  "\n"
  "uint16                      GPSGROUP_UTC                    = 0x0001\n"
  "uint16                      GPSGROUP_TOW                    = 0x0002\n"
  "uint16                      GPSGROUP_WEEK                   = 0x0004\n"
  "uint16                      GPSGROUP_NUMSATS                = 0x0008\n"
  "uint16                      GPSGROUP_FIX                    = 0x0010\n"
  "uint16                      GPSGROUP_POSLLA                 = 0x0020\n"
  "uint16                      GPSGROUP_POSECEF                = 0x0040\n"
  "uint16                      GPSGROUP_VELNED                 = 0x0080\n"
  "uint16                      GPSGROUP_VELECEF                = 0x0100\n"
  "uint16                      GPSGROUP_POSU                   = 0x0200\n"
  "uint16                      GPSGROUP_VELU                   = 0x0400\n"
  "uint16                      GPSGROUP_TIMEU                  = 0x0800\n"
  "uint16                      GPSGROUP_TIMEINFO               = 0x1000\n"
  "uint16                      GPSGROUP_DOP                    = 0x2000\n"
  "# TODO[Dereck] vncxx does not support SatInfo or RawMeas\n"
  "\n"
  "# Fields\n"
  "vectornav_msgs/TimeUTC      utc\n"
  "uint64                      tow\n"
  "uint16                      week\n"
  "uint8                       numsats\n"
  "uint8                       fix\n"
  "geometry_msgs/Point         poslla\n"
  "geometry_msgs/Point         posecef\n"
  "geometry_msgs/Vector3       velned\n"
  "geometry_msgs/Vector3       velecef\n"
  "geometry_msgs/Vector3       posu\n"
  "float32                     velu\n"
  "uint32                      timeu\n"
  "uint8                       timeinfo_status\n"
  "int8                        timeinfo_leapseconds\n"
  "vectornav_msgs/DOP          dop\n"
  "\n"
  "uint8                       GPSFIX_NOFIX                    = 0\n"
  "uint8                       GPSFIX_TIMEONLY                 = 1\n"
  "uint8                       GPSFIX_2D                       = 2\n"
  "uint8                       GPSFIX_3D                       = 3";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vectornav_msgs__msg__GpsGroup__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vectornav_msgs__msg__GpsGroup__TYPE_NAME, 27, 27},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 2194, 2194},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vectornav_msgs__msg__GpsGroup__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[7];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 7, 7};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vectornav_msgs__msg__GpsGroup__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[3] = *geometry_msgs__msg__Vector3__get_individual_type_description_source(NULL);
    sources[4] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    sources[5] = *vectornav_msgs__msg__DOP__get_individual_type_description_source(NULL);
    sources[6] = *vectornav_msgs__msg__TimeUTC__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
