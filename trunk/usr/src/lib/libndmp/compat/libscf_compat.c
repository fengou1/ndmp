#include "libscf.h"

#ifndef __sun
#include <errno.h>
#include <stdlib.h>

struct scf_handle {
        uint32_t version;
};

struct scf_scope {
        int unused;
};

struct scf_service {
        int unused;
};

struct scf_propertygroup {
        int unused;
};

struct scf_transaction {
        int unused;
};

struct scf_transaction_entry {
        int unused;
};

struct scf_property {
        int unused;
};

struct scf_value {
        scf_type_t type;
};

static int compat_scf_error = SCF_ERROR_NOT_SUPPORTED;

static void
compat_set_error(int err)
{
        compat_scf_error = err;
}

scf_handle_t *
scf_handle_create(uint32_t version)
{
        scf_handle_t *handle;

        if (version != SCF_VERSION) {
                errno = ENOTSUP;
                compat_set_error(SCF_ERROR_NOT_SUPPORTED);
                return (NULL);
        }

        handle = calloc(1, sizeof (*handle));
        if (handle == NULL) {
                compat_set_error(SCF_ERROR_INTERNAL);
                return (NULL);
        }

        handle->version = version;
        compat_set_error(SCF_ERROR_NONE);
        return (handle);
}

void
scf_handle_destroy(scf_handle_t *handle)
{
        free(handle);
}

int
scf_handle_bind(scf_handle_t *handle)
{
        (void)handle;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_handle_unbind(scf_handle_t *handle)
{
        (void)handle;
        compat_set_error(SCF_ERROR_NONE);
        return (0);
}

scf_scope_t *
scf_scope_create(scf_handle_t *handle)
{
        (void)handle;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (NULL);
}

void
scf_scope_destroy(scf_scope_t *scope)
{
        free(scope);
}

int
scf_handle_get_local_scope(scf_handle_t *handle, scf_scope_t *scope)
{
        (void)handle;
        (void)scope;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

scf_service_t *
scf_service_create(scf_handle_t *handle)
{
        (void)handle;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (NULL);
}

void
scf_service_destroy(scf_service_t *svc)
{
        free(svc);
}

int
scf_scope_get_service(scf_scope_t *scope, const char *name, scf_service_t *svc)
{
        (void)scope;
        (void)name;
        (void)svc;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

scf_propertygroup_t *
scf_pg_create(scf_handle_t *handle)
{
        (void)handle;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (NULL);
}

void
scf_pg_destroy(scf_propertygroup_t *pg)
{
        free(pg);
}

int
scf_service_get_pg(scf_service_t *svc, const char *name, scf_propertygroup_t *pg)
{
        (void)svc;
        (void)name;
        (void)pg;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_service_add_pg(scf_service_t *svc, const char *pgname, const char *pgtype,
    uint32_t flags, scf_propertygroup_t *pg)
{
        (void)svc;
        (void)pgname;
        (void)pgtype;
        (void)flags;
        (void)pg;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

scf_property_t *
scf_property_create(scf_handle_t *handle)
{
        (void)handle;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (NULL);
}

void
scf_property_destroy(scf_property_t *prop)
{
        free(prop);
}

int
scf_pg_get_property(scf_propertygroup_t *pg, const char *name,
    scf_property_t *prop)
{
        (void)pg;
        (void)name;
        (void)prop;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_property_get_value(scf_property_t *prop, scf_value_t *value)
{
        (void)prop;
        (void)value;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

scf_transaction_t *
scf_transaction_create(scf_handle_t *handle)
{
        (void)handle;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (NULL);
}

void
scf_transaction_destroy(scf_transaction_t *tx)
{
        free(tx);
}

void
scf_transaction_destroy_children(scf_transaction_t *tx)
{
        (void)tx;
}

int
scf_transaction_start(scf_transaction_t *tx, scf_propertygroup_t *pg)
{
        (void)tx;
        (void)pg;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_transaction_commit(scf_transaction_t *tx)
{
        (void)tx;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

scf_transaction_entry_t *
scf_entry_create(scf_handle_t *handle)
{
        (void)handle;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (NULL);
}

void
scf_entry_destroy(scf_transaction_entry_t *entry)
{
        free(entry);
}

int
scf_entry_add_value(scf_transaction_entry_t *entry, scf_value_t *value)
{
        (void)entry;
        (void)value;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_transaction_property_delete(scf_transaction_t *tx,
    scf_transaction_entry_t *entry, const char *name)
{
        (void)tx;
        (void)entry;
        (void)name;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_transaction_property_change(scf_transaction_t *tx,
    scf_transaction_entry_t *entry, const char *name, scf_type_t type)
{
        (void)tx;
        (void)entry;
        (void)name;
        (void)type;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_transaction_property_new(scf_transaction_t *tx,
    scf_transaction_entry_t *entry, const char *name, scf_type_t type)
{
        (void)tx;
        (void)entry;
        (void)name;
        (void)type;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

scf_value_t *
scf_value_create(scf_handle_t *handle)
{
        (void)handle;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (NULL);
}

void
scf_value_destroy(scf_value_t *value)
{
        free(value);
}

scf_type_t
scf_value_type(const scf_value_t *value)
{
        if (value == NULL)
                return (SCF_TYPE_INVALID);
        return (value->type);
}

int
scf_value_set_astring(scf_value_t *value, const char *str)
{
        (void)value;
        (void)str;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (SCF_FAILED);
}

void
scf_value_set_integer(scf_value_t *value, int64_t val)
{
        (void)value;
        (void)val;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
}

void
scf_value_set_boolean(scf_value_t *value, uint8_t val)
{
        (void)value;
        (void)val;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
}

ssize_t
scf_value_get_astring(const scf_value_t *value, char *buf, size_t bufsz)
{
        (void)value;
        (void)buf;
        (void)bufsz;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_value_get_integer(const scf_value_t *value, int64_t *out)
{
        (void)value;
        (void)out;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_value_get_boolean(const scf_value_t *value, uint8_t *out)
{
        (void)value;
        (void)out;
        errno = ENOTSUP;
        compat_set_error(SCF_ERROR_NOT_SUPPORTED);
        return (-1);
}

int
scf_error(void)
{
        return (compat_scf_error);
}

const char *
scf_strerror(int err)
{
        switch (err) {
        case SCF_ERROR_NONE:
                return ("no error");
        case SCF_ERROR_NOT_SUPPORTED:
                return ("operation not supported");
        case SCF_ERROR_PERMISSION_DENIED:
                return ("permission denied");
        default:
                break;
        }
        return ("libscf error");
}

char *
smf_get_state(const char *fmri)
{
        (void)fmri;
        errno = ENOTSUP;
        return (NULL);
}

int
smf_refresh_instance(const char *fmri)
{
        (void)fmri;
        errno = ENOTSUP;
        return (-1);
}

#endif /* __sun */
