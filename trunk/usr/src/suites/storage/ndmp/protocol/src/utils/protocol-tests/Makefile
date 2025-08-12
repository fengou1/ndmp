#
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

#
# BSD 3 Clause License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#       - Redistributions of source code must retain the above copyright
#         notice, this list of conditions and the following disclaimer.
#
#       - Redistributions in binary form must reproduce the above copyright
#         notice, this list of conditions and the following disclaimer in
#         the documentation and/or other materials provided with the
#         distribution.
#
#       - Neither the name of Sun Microsystems, Inc. nor the
#         names of its contributors may be used to endorse or promote products
#         derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY SUN MICROSYSTEMS, INC. "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL SUN MICROSYSTEMS, INC. BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

#
# ident	"@(#)Makefile	1.3	09/03/30 SMI"
#

include $(TET_SUITE_ROOT)/ndmp/protocol/Targetdirs

CC = cc
DEFINES =  -DNDMP_PROTOCOL_TEST 
#DEFINES =  -DUNIT_TEST_NOTIFY
#DEFINES =  -DUNIT_TEST_MOVER
#DEFINES =  -DUNIT_TEST_DATA
#DEFINES =  -DUNIT_TEST_TAPE
#DEFINES =  -DUNIT_TEST_SCSI
#DEFINES =  -DUNIT_TEST_CONFIG
#DEFINES =  -DUNIT_TEST_CONNECT

INCLUDE_DIR = ../../../include

CFLAGS = -g -w -I$(INCLUDE_DIR) $(DEFINES)
LIBDIR = ../../../lib
INCLUDES = -I$(LIBDIR)

LD = $(CC)
LDFLAGS = $(CFLAGS)
LIBS = -L$(LIBDIR) -lndmpprototest -lsocket -lnsl


SUBDIRS           = 
TSET_SRC_UTILS    = ../../../../src/utils

BIN_DIR = ../../../bin

_TARGET_C        = $(BIN_DIR)/ndmp_proto_test
SRCS_C            = ndmp_proto_test.c \
		    process_hdlr_table.c \
		    ndmp_comm_lib.c \
		    ndmp_lib.c \
		    config_tester.c \
		    connect_tester.c \
		    data.c \
		    mover.c \
		    scsi_tester.c \
		    fhistory_tester.c \
		    log_tester.c \
		    ndmp_execute.c \
		    tape_tester.c \
		    notify_tester.c

OBJS		= $(SRCS_C:.c=.o)
TARGET_C         = $(_TARGET_C:%=$(BIN_DIR)/%)

all install : $(OBJS) $(BIN_DIR) $(TARGETS_C) $(TARGETS_C_SU) $(TARGETS_KSH)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(_TARGET_C)

$(TARGET_C) : $(SRCS_C)
	@$(RM) $@
	$(CC) $(@:$(BIN_DIR)/%=%.c) -o $@

clean : $(SUBDIRS)
	@$(RM) $(TARGETS_C) $(BIN_DIR)/ndmp_proto_test $(TARGETS_C_SU) *.o $(TARGETS_KSH)

clobber : clean
	#@rmdir $(BIN_DIR) > /dev/null 2>&1
	@$(RM) $(BIN_DIR)/*

$(BIN_DIR):
	if [ ! -d "$(BIN_DIR)" ]; then\
		mkdir $(BIN_DIR);\
	fi

lint :
	@if [ ! -z "$(SRCS_C)" ]; then \
		for p in $(SRCS_C) ""; do \
			if [ ! -z "$$p" ]; then \
				echo $$p; \
				$(LINT.c) -errfmt=simple -errhdr=%user -ux $(CFLAGS_ADDa) $$p; \
			fi; \
		done; \
	fi

