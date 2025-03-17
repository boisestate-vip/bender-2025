// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vectornav_msgs:msg/ImuGroup.idl
// generated code does not contain a copyright notice

#include "vectornav_msgs/msg/detail/imu_group__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
const rosidl_type_hash_t *
vectornav_msgs__msg__ImuGroup__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x87, 0x55, 0x96, 0x6a, 0xe5, 0x51, 0x33, 0xd6,
      0xe7, 0xa4, 0x2d, 0xf2, 0xb1, 0x47, 0xe0, 0x3c,
      0x72, 0x70, 0xda, 0x68, 0xb0, 0x87, 0x80, 0xf2,
      0x64, 0x83, 0xd8, 0xe9, 0xed, 0x70, 0x5a, 0x31,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "geometry_msgs/msg/detail/vector3__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "std_msgs/msg/detail/header__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
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
#endif

static char vectornav_msgs__msg__ImuGroup__TYPE_NAME[] = "vectornav_msgs/msg/ImuGroup";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char geometry_msgs__msg__Vector3__TYPE_NAME[] = "geometry_msgs/msg/Vector3";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__header[] = "header";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__group_fields[] = "group_fields";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__imustatus[] = "imustatus";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__uncompmag[] = "uncompmag";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__uncompaccel[] = "uncompaccel";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__uncompgyro[] = "uncompgyro";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__temp[] = "temp";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__pres[] = "pres";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__deltatheta_time[] = "deltatheta_time";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__deltatheta_dtheta[] = "deltatheta_dtheta";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__deltavel[] = "deltavel";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__mag[] = "mag";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__accel[] = "accel";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__angularrate[] = "angularrate";
static char vectornav_msgs__msg__ImuGroup__FIELD_NAME__sensat[] = "sensat";

static rosidl_runtime_c__type_description__Field vectornav_msgs__msg__ImuGroup__FIELDS[] = {
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__group_fields, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__imustatus, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__uncompmag, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__uncompaccel, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__uncompgyro, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__temp, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__pres, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__deltatheta_time, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__deltatheta_dtheta, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__deltavel, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__mag, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__accel, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__angularrate, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__ImuGroup__FIELD_NAME__sensat, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vectornav_msgs__msg__ImuGroup__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
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
};

const rosidl_runtime_c__type_description__TypeDescription *
vectornav_msgs__msg__ImuGroup__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vectornav_msgs__msg__ImuGroup__TYPE_NAME, 27, 27},
      {vectornav_msgs__msg__ImuGroup__FIELDS, 15, 15},
    },
    {vectornav_msgs__msg__ImuGroup__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Vector3__EXPECTED_HASH, geometry_msgs__msg__Vector3__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Vector3__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
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
  "uint16                      IMUGROUP_IMUSTATUS              = 0x0001\n"
  "uint16                      IMUGROUP_UNCOMPMAG              = 0x0002\n"
  "uint16                      IMUGROUP_UNCOMPACCEL            = 0x0004\n"
  "uint16                      IMUGROUP_UNCOMPGYRO             = 0x0008\n"
  "uint16                      IMUGROUP_TEMP                   = 0x0010\n"
  "uint16                      IMUGROUP_PRES                   = 0x0020\n"
  "uint16                      IMUGROUP_DELTATHETA             = 0x0040\n"
  "uint16                      IMUGROUP_DELTAVEL               = 0x0080\n"
  "uint16                      IMUGROUP_MAG                    = 0x0100\n"
  "uint16                      IMUGROUP_ACCEL                  = 0x0200\n"
  "uint16                      IMUGROUP_ANGULARRATE            = 0x0400\n"
  "uint16                      IMUGROUP_SENSSAT                = 0x0800\n"
  "# TODO[Dereck] SENSSAT exists in the header, but not the manual...\n"
  "\n"
  "\n"
  "# Fields\n"
  "uint16                      imustatus\n"
  "geometry_msgs/Vector3       uncompmag\n"
  "geometry_msgs/Vector3       uncompaccel\n"
  "geometry_msgs/Vector3       uncompgyro\n"
  "float32                     temp\n"
  "float32                     pres\n"
  "float32                     deltatheta_time\n"
  "geometry_msgs/Vector3       deltatheta_dtheta\n"
  "geometry_msgs/Vector3       deltavel\n"
  "geometry_msgs/Vector3       mag\n"
  "geometry_msgs/Vector3       accel\n"
  "geometry_msgs/Vector3       angularrate\n"
  "uint16                      sensat";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vectornav_msgs__msg__ImuGroup__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vectornav_msgs__msg__ImuGroup__TYPE_NAME, 27, 27},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1767, 1767},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vectornav_msgs__msg__ImuGroup__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vectornav_msgs__msg__ImuGroup__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Vector3__get_individual_type_description_source(NULL);
    sources[3] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
