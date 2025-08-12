/*
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*
 * BSD 3 Clause License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *      - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *      - Neither the name of Sun Microsystems, Inc. nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SUN MICROSYSTEMS, INC. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL SUN MICROSYSTEMS, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _MOVER_H
#define	_MOVER_H

#pragma ident	"@(#)mover.h	1.3	09/03/30 SMI"

/*
 * Function declarations and constants used by mover and other
 * interface.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <log.h>
#include <ndmp_connect.h>

#define	STD_REC_SIZE 8192
#define	STD_WIN_SIZE 8192000
/* NDMP_MOVER_LISTEN */

NdmpParamExtractFunc	ndmp_mover_listen_request_extract;
NdmpParamExtractFunc	ndmp_mover_listen_reply_extract;
NdmpCompareParamFunc	ndmp_mover_listen_reply_compare;
PrintNdmpMsgFunc	ndmp_mover_listen_reply_print;

/* NDMP_MOVER_STOP */

NdmpParamExtractFunc	ndmp_mover_stop_request_extract;
NdmpParamExtractFunc	ndmp_mover_stop_reply_extract;
NdmpCompareParamFunc	ndmp_mover_stop_compare;
PrintNdmpMsgFunc	ndmp_mover_stop_reply_print;

/* NDMP_MOVER_SET_RECORD_SIZE */

NdmpParamExtractFunc	ndmp_mover_set_record_size_request_extract;
NdmpParamExtractFunc	ndmp_mover_set_record_size_reply_extract;
NdmpCompareParamFunc	ndmp_mover_set_record_size_compare;
PrintNdmpMsgFunc	ndmp_mover_set_record_size_reply_print;

/* NDMP_MOVER_SET_WINDOW */

NdmpParamExtractFunc	ndmp_mover_set_window_request_extract;
NdmpParamExtractFunc	ndmp_mover_set_window_reply_extract;
NdmpCompareParamFunc	ndmp_mover_set_window_compare;
PrintNdmpMsgFunc	ndmp_mover_set_window_reply_print;

/* NDMP_MOVER_CONNECT */

NdmpParamExtractFunc	ndmp_mover_connect_request_extract;
NdmpParamExtractFunc	ndmp_mover_connect_reply_extract;
NdmpCompareParamFunc	ndmp_mover_connect_compare;
PrintNdmpMsgFunc	ndmp_mover_connect_reply_print;

/* NDMP_MOVER_READ */

NdmpParamExtractFunc	ndmp_mover_read_request_extract;
NdmpParamExtractFunc	ndmp_mover_read_reply_extract;
NdmpCompareParamFunc	ndmp_mover_read_compare;
PrintNdmpMsgFunc	ndmp_mover_read_reply_print;

/* NDMP_MOVER_GET_STATE */

NdmpParamExtractFunc	ndmp_mover_get_state_request_extract;
NdmpParamExtractFunc	ndmp_mover_get_state_reply_extract;
NdmpCompareParamFunc	ndmp_mover_get_state_compare;
PrintNdmpMsgFunc	ndmp_mover_get_state_reply_print;

/* NDMP_MOVER_CONTINUE */

NdmpParamExtractFunc	ndmp_mover_continue_request_extract;
NdmpParamExtractFunc	ndmp_mover_continue_reply_extract;
NdmpCompareParamFunc	ndmp_mover_continue_compare;
PrintNdmpMsgFunc	ndmp_mover_continue_reply_print;

/* NDMP_MOVER_CLOSE */

NdmpParamExtractFunc	ndmp_mover_close_request_extract;
NdmpParamExtractFunc	ndmp_mover_close_reply_extract;
NdmpCompareParamFunc	ndmp_mover_close_compare;
PrintNdmpMsgFunc	ndmp_mover_close_reply_print;

/* NDMP_MOVER_ABORT */

NdmpParamExtractFunc	ndmp_mover_abort_request_extract;
NdmpParamExtractFunc	ndmp_mover_abort_reply_extract;
NdmpCompareParamFunc	ndmp_mover_abort_compare;
PrintNdmpMsgFunc	ndmp_mover_abort_reply_print;

extern int
inf_mover_set_rec_size(ndmp_error, char *, char *, FILE *, conn_handle *);
extern int
inf_mover_set_window_size(ndmp_error, char *,
    char *, FILE *,  conn_handle *);
extern int
inf_mover_connect(ndmp_error, char *, char *, char **,
    FILE *,  conn_handle *);
int
inf_mover_listen(ndmp_error, char *, char *, char *, FILE *,  conn_handle *);
extern int
inf_mover_read(ndmp_error, char *,
    FILE *,  conn_handle *);
extern int
inf_mover_get_state(ndmp_error, char *,
    FILE *,  conn_handle *);
extern int
inf_mover_continue(ndmp_error, char *,
    char *, FILE *,  conn_handle *);
extern int
inf_mover_close(ndmp_error, char *,
    char *, FILE *,  conn_handle *);
extern int
inf_mover_abort(ndmp_error, char *,
    FILE *,  conn_handle *);
extern int
inf_mover_stop(ndmp_error, char *,
    FILE *,  conn_handle *);

extern int
mover_set_window_core(ndmp_error, ndmp_u_quad *,
    ndmp_u_quad *, FILE *, conn_handle *);

extern int
mover_set_rec_size_core(ndmp_error, ulong_t,
    FILE *, conn_handle *);

extern int
mover_abort_core(ndmp_error, FILE *, conn_handle *);

extern int
mover_stop_core(ndmp_error, FILE *, conn_handle *);

extern int
mover_listen_core(ndmp_error, ndmp_mover_mode,
    ndmp_addr_type, void **, FILE *, conn_handle *);

#ifdef __cplusplus
}
#endif

#endif /* _MOVER_H */
