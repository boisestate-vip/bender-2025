// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vectornav_msgs:msg/AttitudeGroup.idl
// generated code does not contain a copyright notice

#include "vectornav_msgs/msg/detail/attitude_group__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
const rosidl_type_hash_t *
vectornav_msgs__msg__AttitudeGroup__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xff, 0xbf, 0x6b, 0xbc, 0x90, 0x62, 0xb8, 0x15,
      0x53, 0x52, 0x73, 0x90, 0x01, 0xaa, 0xca, 0x97,
      0x9f, 0xa4, 0x57, 0xb6, 0x34, 0x54, 0xcc, 0x44,
      0x06, 0x1f, 0x6c, 0xea, 0x4c, 0x7e, 0x43, 0x4b,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "geometry_msgs/msg/detail/quaternion__functions.h"
#include "geometry_msgs/msg/detail/vector3__functions.h"
#include "std_msgs/msg/detail/header__functions.h"
#include "vectornav_msgs/msg/detail/vpe_status__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Quaternion__EXPECTED_HASH = {1, {
    0x8a, 0x76, 0x5f, 0x66, 0x77, 0x8c, 0x8f, 0xf7,
    0xc8, 0xab, 0x94, 0xaf, 0xcc, 0x59, 0x0a, 0x2e,
    0xd5, 0x32, 0x5a, 0x1d, 0x9a, 0x07, 0x6f, 0xff,
    0xf3, 0x8f, 0xbc, 0xe3, 0x6f, 0x45, 0x86, 0x84,
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
static const rosidl_type_hash_t vectornav_msgs__msg__VpeStatus__EXPECTED_HASH = {1, {
    0x3b, 0x2d, 0x4d, 0xc5, 0x3c, 0x25, 0xba, 0xd9,
    0xda, 0x55, 0xee, 0x0b, 0x1d, 0xf0, 0x45, 0xdb,
    0x3f, 0x25, 0x96, 0x49, 0x7c, 0xef, 0x56, 0x74,
    0x4f, 0x3f, 0x14, 0x03, 0xbd, 0x0a, 0x3a, 0xd8,
  }};
#endif

static char vectornav_msgs__msg__AttitudeGroup__TYPE_NAME[] = "vectornav_msgs/msg/AttitudeGroup";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char geometry_msgs__msg__Quaternion__TYPE_NAME[] = "geometry_msgs/msg/Quaternion";
static char geometry_msgs__msg__Vector3__TYPE_NAME[] = "geometry_msgs/msg/Vector3";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";
static char vectornav_msgs__msg__VpeStatus__TYPE_NAME[] = "vectornav_msgs/msg/VpeStatus";

// Define type names, field names, and default values
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__header[] = "header";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__group_fields[] = "group_fields";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__vpestatus[] = "vpestatus";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__yawpitchroll[] = "yawpitchroll";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__quaternion[] = "quaternion";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__dcm[] = "dcm";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__magned[] = "magned";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__accelned[] = "accelned";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__linearaccelbody[] = "linearaccelbody";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__linearaccelned[] = "linearaccelned";
static char vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__ypru[] = "ypru";

static rosidl_runtime_c__type_description__Field vectornav_msgs__msg__AttitudeGroup__FIELDS[] = {
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__group_fields, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__vpestatus, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vectornav_msgs__msg__VpeStatus__TYPE_NAME, 28, 28},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__yawpitchroll, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__quaternion, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Quaternion__TYPE_NAME, 28, 28},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__dcm, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      9,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__magned, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__accelned, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__linearaccelbody, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__linearaccelned, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__AttitudeGroup__FIELD_NAME__ypru, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Vector3__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vectornav_msgs__msg__AttitudeGroup__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Quaternion__TYPE_NAME, 28, 28},
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
    {vectornav_msgs__msg__VpeStatus__TYPE_NAME, 28, 28},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vectornav_msgs__msg__AttitudeGroup__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vectornav_msgs__msg__AttitudeGroup__TYPE_NAME, 32, 32},
      {vectornav_msgs__msg__AttitudeGroup__FIELDS, 11, 11},
    },
    {vectornav_msgs__msg__AttitudeGroup__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Quaternion__EXPECTED_HASH, geometry_msgs__msg__Quaternion__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Quaternion__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Vector3__EXPECTED_HASH, geometry_msgs__msg__Vector3__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = geometry_msgs__msg__Vector3__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&vectornav_msgs__msg__VpeStatus__EXPECTED_HASH, vectornav_msgs__msg__VpeStatus__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = vectornav_msgs__msg__VpeStatus__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# VectorNav Composite Data Packet\n"
  "#\n"
  "# Only the enabled fields will be populated with data and only the fields \n"
  "# you require for your application should be enabled to conserve bandwidth\n"
  "# and increase the update rate.\n"
  "#\n"
  "# TODO[Dereck] Requires rosidl patches\n"
  "\n"
  "# Data Received (ROS Time)\n"
  "std_msgs/Header header       \n"
  "\n"
  "# Field Enable Bits\n"
  "uint16                      group_fields\n"
  "\n"
  "uint16                      ATTITUDEGROUP_VPESTATUS         = 0x0001\n"
  "uint16                      ATTITUDEGROUP_YAWPITCHROLL      = 0x0002\n"
  "uint16                      ATTITUDEGROUP_QUATERNION        = 0x0004 \n"
  "uint16                      ATTITUDEGROUP_DCM               = 0x0008\n"
  "uint16                      ATTITUDEGROUP_MAGNED            = 0x0010\n"
  "uint16                      ATTITUDEGROUP_ACCELNED          = 0x0020\n"
  "uint16                      ATTITUDEGROUP_LINEARACCELBODY   = 0x0040\n"
  "uint16                      ATTITUDEGROUP_LINEARACCELNED    = 0x0080\n"
  "uint16                      ATTITUDEGROUP_YPRU              = 0x0100\n"
  "\n"
  "# Fields \n"
  "vectornav_msgs/VpeStatus    vpestatus         \n"
  "geometry_msgs/Vector3       yawpitchroll      \n"
  "geometry_msgs/Quaternion    quaternion       \n"
  "float32[9]                  dcm            \n"
  "geometry_msgs/Vector3       magned         \n"
  "geometry_msgs/Vector3       accelned         \n"
  "geometry_msgs/Vector3       linearaccelbody   \n"
  "geometry_msgs/Vector3       linearaccelned   \n"
  "geometry_msgs/Vector3       ypru            ";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vectornav_msgs__msg__AttitudeGroup__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vectornav_msgs__msg__AttitudeGroup__TYPE_NAME, 32, 32},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1425, 1425},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vectornav_msgs__msg__AttitudeGroup__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vectornav_msgs__msg__AttitudeGroup__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Quaternion__get_individual_type_description_source(NULL);
    sources[3] = *geometry_msgs__msg__Vector3__get_individual_type_description_source(NULL);
    sources[4] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    sources[5] = *vectornav_msgs__msg__VpeStatus__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
