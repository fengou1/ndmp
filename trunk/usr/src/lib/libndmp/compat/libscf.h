#ifndef _LIBNDMP_COMPAT_LIBSCF_H
#define _LIBNDMP_COMPAT_LIBSCF_H

#ifdef __sun
#include_next <libscf.h>
#else
#include <stdint.h>
#include <sys/types.h>

#define SCF_VERSION                     1
#define SCF_SUCCESS                     0
#define SCF_FAILED                      (-1)

#define SCF_GROUP_FRAMEWORK             "framework"

typedef enum {
        SCF_TYPE_INVALID = 0,
        SCF_TYPE_ASTRING,
        SCF_TYPE_INTEGER,
        SCF_TYPE_BOOLEAN
} scf_type_t;

typedef struct scf_handle scf_handle_t;
typedef struct scf_scope scf_scope_t;
typedef struct scf_service scf_service_t;
typedef struct scf_propertygroup scf_propertygroup_t;
typedef struct scf_transaction scf_transaction_t;
typedef struct scf_transaction_entry scf_transaction_entry_t;
typedef struct scf_property scf_property_t;
typedef struct scf_value scf_value_t;

#define SCF_ERROR_NONE                  0
#define SCF_ERROR_NOT_SUPPORTED         1001
#define SCF_ERROR_PERMISSION_DENIED     1002
#define SCF_ERROR_INTERNAL              1003

scf_handle_t *scf_handle_create(uint32_t);
void scf_handle_destroy(scf_handle_t *);
int scf_handle_bind(scf_handle_t *);
int scf_handle_unbind(scf_handle_t *);

scf_scope_t *scf_scope_create(scf_handle_t *);
void scf_scope_destroy(scf_scope_t *);
int scf_handle_get_local_scope(scf_handle_t *, scf_scope_t *);
int scf_scope_get_service(scf_scope_t *, const char *, scf_service_t *);

scf_service_t *scf_service_create(scf_handle_t *);
void scf_service_destroy(scf_service_t *);
int scf_service_get_pg(scf_service_t *, const char *, scf_propertygroup_t *);
int scf_service_add_pg(scf_service_t *, const char *, const char *, uint32_t,
    scf_propertygroup_t *);

scf_propertygroup_t *scf_pg_create(scf_handle_t *);
void scf_pg_destroy(scf_propertygroup_t *);
int scf_pg_get_property(scf_propertygroup_t *, const char *, scf_property_t *);

scf_property_t *scf_property_create(scf_handle_t *);
void scf_property_destroy(scf_property_t *);
int scf_property_get_value(scf_property_t *, scf_value_t *);

scf_transaction_t *scf_transaction_create(scf_handle_t *);
void scf_transaction_destroy(scf_transaction_t *);
void scf_transaction_destroy_children(scf_transaction_t *);
int scf_transaction_start(scf_transaction_t *, scf_propertygroup_t *);
int scf_transaction_commit(scf_transaction_t *);

scf_transaction_entry_t *scf_entry_create(scf_handle_t *);
void scf_entry_destroy(scf_transaction_entry_t *);
int scf_entry_add_value(scf_transaction_entry_t *, scf_value_t *);

int scf_transaction_property_delete(scf_transaction_t *,
    scf_transaction_entry_t *, const char *);
int scf_transaction_property_change(scf_transaction_t *,
    scf_transaction_entry_t *, const char *, scf_type_t);
int scf_transaction_property_new(scf_transaction_t *,
    scf_transaction_entry_t *, const char *, scf_type_t);

scf_value_t *scf_value_create(scf_handle_t *);
void scf_value_destroy(scf_value_t *);
scf_type_t scf_value_type(const scf_value_t *);

int scf_value_set_astring(scf_value_t *, const char *);
void scf_value_set_integer(scf_value_t *, int64_t);
void scf_value_set_boolean(scf_value_t *, uint8_t);

ssize_t scf_value_get_astring(const scf_value_t *, char *, size_t);
int scf_value_get_integer(const scf_value_t *, int64_t *);
int scf_value_get_boolean(const scf_value_t *, uint8_t *);

int scf_error(void);
const char *scf_strerror(int);

char *smf_get_state(const char *);
int smf_refresh_instance(const char *);

#endif /* __sun */

#endif /* _LIBNDMP_COMPAT_LIBSCF_H */
