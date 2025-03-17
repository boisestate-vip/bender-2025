// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vectornav_msgs:msg/TimeGroup.idl
// generated code does not contain a copyright notice

#include "vectornav_msgs/msg/detail/time_group__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vectornav_msgs
const rosidl_type_hash_t *
vectornav_msgs__msg__TimeGroup__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xd8, 0xb6, 0x25, 0xa0, 0x72, 0x62, 0x4a, 0xfe,
      0xb5, 0xaa, 0xfa, 0x75, 0x5b, 0x54, 0x6f, 0x80,
      0x1a, 0x12, 0xb6, 0x32, 0x6e, 0x0d, 0x75, 0xc5,
      0x50, 0x21, 0xdd, 0x62, 0xfb, 0xaf, 0x05, 0x96,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "vectornav_msgs/msg/detail/time_utc__functions.h"
#include "vectornav_msgs/msg/detail/time_status__functions.h"
#include "std_msgs/msg/detail/header__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
static const rosidl_type_hash_t vectornav_msgs__msg__TimeStatus__EXPECTED_HASH = {1, {
    0x7e, 0x0c, 0xf8, 0x31, 0xd6, 0x7e, 0x6e, 0xdf,
    0x13, 0xe3, 0xc2, 0xf5, 0x97, 0x8e, 0x46, 0xac,
    0xa5, 0x5a, 0x8a, 0x55, 0xaf, 0xce, 0x17, 0x8b,
    0x7c, 0x1b, 0x0c, 0xf0, 0xb5, 0x44, 0xbe, 0x9e,
  }};
static const rosidl_type_hash_t vectornav_msgs__msg__TimeUTC__EXPECTED_HASH = {1, {
    0xa2, 0x34, 0x1f, 0x6a, 0x21, 0xde, 0x28, 0xbf,
    0x03, 0xd0, 0x47, 0x4d, 0x4b, 0x83, 0x64, 0x6b,
    0x43, 0x2c, 0x1e, 0x21, 0x84, 0xbb, 0xd1, 0x7d,
    0xf3, 0x0c, 0x81, 0x10, 0x96, 0x7c, 0x4f, 0x8d,
  }};
#endif

static char vectornav_msgs__msg__TimeGroup__TYPE_NAME[] = "vectornav_msgs/msg/TimeGroup";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";
static char vectornav_msgs__msg__TimeStatus__TYPE_NAME[] = "vectornav_msgs/msg/TimeStatus";
static char vectornav_msgs__msg__TimeUTC__TYPE_NAME[] = "vectornav_msgs/msg/TimeUTC";

// Define type names, field names, and default values
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__header[] = "header";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__group_fields[] = "group_fields";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__timestartup[] = "timestartup";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__timegps[] = "timegps";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__gpstow[] = "gpstow";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__gpsweek[] = "gpsweek";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__timesyncin[] = "timesyncin";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__timegpspps[] = "timegpspps";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__timeutc[] = "timeutc";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__syncincnt[] = "syncincnt";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__syncoutcnt[] = "syncoutcnt";
static char vectornav_msgs__msg__TimeGroup__FIELD_NAME__timestatus[] = "timestatus";

static rosidl_runtime_c__type_description__Field vectornav_msgs__msg__TimeGroup__FIELDS[] = {
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__group_fields, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__timestartup, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__timegps, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__gpstow, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__gpsweek, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__timesyncin, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__timegpspps, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__timeutc, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vectornav_msgs__msg__TimeUTC__TYPE_NAME, 26, 26},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__syncincnt, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__syncoutcnt, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeGroup__FIELD_NAME__timestatus, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vectornav_msgs__msg__TimeStatus__TYPE_NAME, 29, 29},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vectornav_msgs__msg__TimeGroup__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeStatus__TYPE_NAME, 29, 29},
    {NULL, 0, 0},
  },
  {
    {vectornav_msgs__msg__TimeUTC__TYPE_NAME, 26, 26},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vectornav_msgs__msg__TimeGroup__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vectornav_msgs__msg__TimeGroup__TYPE_NAME, 28, 28},
      {vectornav_msgs__msg__TimeGroup__FIELDS, 12, 12},
    },
    {vectornav_msgs__msg__TimeGroup__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&vectornav_msgs__msg__TimeStatus__EXPECTED_HASH, vectornav_msgs__msg__TimeStatus__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = vectornav_msgs__msg__TimeStatus__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&vectornav_msgs__msg__TimeUTC__EXPECTED_HASH, vectornav_msgs__msg__TimeUTC__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = vectornav_msgs__msg__TimeUTC__get_type_description(NULL)->type_description.fields;
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
  "uint16                      TIMEGROUP_TIMESTARTUP           = 0x0001\n"
  "uint16                      TIMEGROUP_TIMEGPS               = 0x0002\n"
  "uint16                      TIMEGROUP_GPSTOW                = 0x0004\n"
  "uint16                      TIMEGROUP_GPSWEEK               = 0x0008\n"
  "uint16                      TIMEGROUP_TIMESYNCIN            = 0x0010\n"
  "uint16                      TIMEGROUP_TIMEGPSPPS            = 0x0020\n"
  "uint16                      TIMEGROUP_TIMEUTC               = 0x0040\n"
  "uint16                      TIMEGROUP_SYNCINCNT             = 0x0080\n"
  "uint16                      TIMEGROUP_SYNCOUTCNT            = 0x0100\n"
  "uint16                      TIMEGROUP_TIMESTATUS            = 0x0200\n"
  "\n"
  "# Fields\n"
  "uint64                      timestartup\n"
  "uint64                      timegps\n"
  "uint64                      gpstow\n"
  "uint16                      gpsweek\n"
  "uint64                      timesyncin\n"
  "uint64                      timegpspps\n"
  "vectornav_msgs/TimeUTC      timeutc\n"
  "uint32                      syncincnt\n"
  "uint32                      syncoutcnt\n"
  "vectornav_msgs/TimeStatus   timestatus";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vectornav_msgs__msg__TimeGroup__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vectornav_msgs__msg__TimeGroup__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1449, 1449},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vectornav_msgs__msg__TimeGroup__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vectornav_msgs__msg__TimeGroup__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    sources[3] = *vectornav_msgs__msg__TimeStatus__get_individual_type_description_source(NULL);
    sources[4] = *vectornav_msgs__msg__TimeUTC__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
