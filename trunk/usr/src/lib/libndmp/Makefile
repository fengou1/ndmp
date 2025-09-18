# SPDX-License-Identifier: BSD-3-Clause
#
# Simplified Linux-friendly build for libndmp.

CC ?= cc
AR ?= ar
RANLIB ?= ranlib
INSTALL ?= install
PREFIX ?= /usr/local
DESTDIR ?=
LIBDIR ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include
OBJDIR ?= build

OPENZFS_PREFIX ?= /usr
OPENZFS_INCLUDEDIR ?= $(OPENZFS_PREFIX)/include
OPENZFS_LIBDIR ?= $(OPENZFS_PREFIX)/lib
OPENZFS_CPPFLAGS ?= -I$(OPENZFS_INCLUDEDIR) \
-I$(OPENZFS_INCLUDEDIR)/libdoor \
-I$(OPENZFS_INCLUDEDIR)/libnvpair \
-I$(OPENZFS_INCLUDEDIR)/libscf \
-I$(OPENZFS_INCLUDEDIR)/libspl
OPENZFS_LDFLAGS ?= -L$(OPENZFS_LIBDIR)

SRCDIR := common
COMPATDIR := compat
SOURCES := $(SRCDIR)/libndmp.c \
    $(SRCDIR)/libndmp_base64.c \
    $(SRCDIR)/libndmp_door_data.c \
    $(SRCDIR)/libndmp_error.c \
    $(SRCDIR)/libndmp_prop.c \
    $(COMPATDIR)/door_compat.c \
    $(COMPATDIR)/libscf_compat.c
OBJECTS := $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

STATIC_LIB := libndmp.a
SHARED_LIB := libndmp.so

CPPFLAGS += -I$(SRCDIR) -I$(COMPATDIR) -I../cmd/ndmpd/include -I../../cmd/ndmpd/include $(OPENZFS_CPPFLAGS)
CFLAGS ?= -O2
CFLAGS += -fPIC
LDFLAGS += $(OPENZFS_LDFLAGS)
LDLIBS += -ldoor -lnvpair -lpthread -lintl -lscf

.PHONY: all clean install

all: $(STATIC_LIB) $(SHARED_LIB)

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(STATIC_LIB): $(OBJECTS)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(SHARED_LIB): $(OBJECTS)
	$(CC) -shared $(LDFLAGS) -o $@ $^ $(LDLIBS)

install: all
	$(INSTALL) -d $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0755 $(SHARED_LIB) $(DESTDIR)$(LIBDIR)/$(SHARED_LIB)
	$(INSTALL) -m 0644 $(STATIC_LIB) $(DESTDIR)$(LIBDIR)/$(STATIC_LIB)
	$(INSTALL) -d $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 $(SRCDIR)/libndmp.h $(DESTDIR)$(INCLUDEDIR)/libndmp.h

clean:
	rm -rf $(OBJDIR) $(STATIC_LIB) $(SHARED_LIB)

-include $(DEPS)
