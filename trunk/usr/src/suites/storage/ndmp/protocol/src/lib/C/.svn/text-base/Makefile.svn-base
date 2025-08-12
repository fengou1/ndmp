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
# ident	"@(#)Makefile	1.4	09/03/30 SMI"
#

.KEEP_STATE:
include $(TET_SUITE_ROOT)/ndmp/protocol/Targetdirs

INCLUDE = ../../../include

CC = cc

CFLAGS = -g -w -I$(INCLUDE)

SRCS = ndmp_xdr.c ndmp_conv.c log.c connect_utils.c ndmp_connect.c xdr_utils.c notifications_queue.c

LIBDIR = ../../../lib/

AR = ar

all install default : LIBDIR_CHECK ndmp_xdr.c libndmpprototest.a

LIBDIR_CHECK :
	if [ ! -d "$(LIBDIR)" ]; then \
		mkdir $(LIBDIR); \
	fi

ndmp_xdr.c : 
	rpcgen -C -h -o $(INCLUDE)/ndmp.h $(INCLUDE)/ndmp.x
	rpcgen -c -o ndmp_xdr.c $(INCLUDE)/ndmp.x

OBJS = $(SRCS:.c=.o)

libndmpprototest.a: $(OBJS)
	$(AR) rv $(LIBDIR)$@ $?

lint	:
	@if [ ! -z "$(SRCS)" ]; then \
		for p in $(SRCS) "";	do \
			if [ ! -z "$$p" ]; then \
				echo $$p; \
				$(LINT.c) -errfmt=simple -errhdr=%user -ux $(CFLAGS_ADDa) $$p; \
			fi; \
		done; \
	fi


tags:
	etags -t *.[ch]

clean:
	rm -f $(LIBDIR)libndmpprototest.a *.o core *~ TAGS .make.state ndmp_xdr.c $(INCLUDE)/ndmp.h
