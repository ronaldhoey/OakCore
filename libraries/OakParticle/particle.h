#ifndef particle_h
#define particle_h

#include <functional>
#include <WString.h>
#include "events.h"

#define PRODUCT_ID 82
#define PLATFORM_ID 82
#define OAK_SYSTEM_VERSION 1
extern char OAK_SYSTEM_VERSION_STRING[];


typedef int (user_function_int_str_t)(String paramString);
typedef user_function_int_str_t* p_user_function_int_str_t;

typedef std::function<user_function_int_str_t> user_std_function_int_str_t;
typedef std::function<void (const char*, const char*)> wiring_event_handler_t;

typedef int (*cloud_function_t)(void* data, const char* param, void* reserved);


typedef enum
{
  CLOUD_VAR_BOOLEAN = 1, CLOUD_VAR_INT = 2, CLOUD_VAR_STRING = 4, CLOUD_VAR_DOUBLE = 9
} Spark_Data_TypeDef;

struct  cloud_function_descriptor {
    uint16_t size;
    uint16_t padding;
    const char *funcKey;
    cloud_function_t fn;
    void* data;

     cloud_function_descriptor() {
         memset(this, 0, sizeof(*this));
         size = sizeof(*this);
     }
};

typedef struct spark_variable_t
{
    uint16_t size;
    const void* (*update)(const char* nane, Spark_Data_TypeDef type, const void* var, void* reserved);
} spark_variable_t;

typedef enum
{
  PUBLIC = 0, PRIVATE = 1
} Spark_Event_TypeDef;

typedef enum
{
  MY_DEVICES,
  ALL_DEVICES
} Spark_Subscription_Scope_TypeDef;


struct CloudVariableTypeBase {};
struct CloudVariableTypeBool : public CloudVariableTypeBase {
    using vartype = bool;
    using varref = const bool*;
    CloudVariableTypeBool(){};
    static inline Spark_Data_TypeDef value() { return CLOUD_VAR_BOOLEAN; }
};
struct CloudVariableTypeInt : public CloudVariableTypeBase {
    using vartype = int;
    using varref = const int*;
    CloudVariableTypeInt(){};
    static inline Spark_Data_TypeDef value() { return CLOUD_VAR_INT; }
};
struct CloudVariableTypeString : public CloudVariableTypeBase {
    using vartype = const char*;
    using varref = const char*;
    CloudVariableTypeString(){};
    static inline Spark_Data_TypeDef value() { return CLOUD_VAR_STRING; }
};
struct CloudVariableTypeDouble : public CloudVariableTypeBase {
    using vartype = double;
    using varref = const double*;

    CloudVariableTypeDouble(){};
    static inline Spark_Data_TypeDef value() { return CLOUD_VAR_DOUBLE; }
};

extern const CloudVariableTypeBool BOOLEAN;
extern const CloudVariableTypeInt INT;
extern const CloudVariableTypeString STRING;
extern const CloudVariableTypeDouble DOUBLE;


// Deferring to ASN.1 type codes
namespace SparkReturnType {
  enum Enum {
    BOOLEAN = 1,
    INT     = 2,
    STRING  = 4,
    DOUBLE  = 9
  };
}


#endif // particle_h
