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

#ifndef _CONNECT_TESTER_H
#define	_CONNECT_TESTER_H

#pragma ident	"@(#)connect_tester.h	1.3	09/03/30 SMI"

/*
 * Function declarations used by connect interface.
 */

#ifdef __cplusplus
extern "C" {
#endif

NdmpParamExtractFunc	ndmp_connect_open_request_extract;
NdmpParamExtractFunc	ndmp_connect_open_reply_extract;
NdmpCompareParamFunc	ndmp_connect_open_reply_compare;
PrintNdmpMsgFunc		ndmp_connect_open_reply_print;

NdmpParamExtractFunc	ndmp_connect_client_auth_request_extract;
NdmpParamExtractFunc	ndmp_connect_client_auth_reply_extract;
NdmpCompareParamFunc	ndmp_connect_client_auth_reply_compare;
PrintNdmpMsgFunc		ndmp_connect_client_auth_reply_print;

NdmpParamExtractFunc	ndmp_connect_close_request_extract;
NdmpParamExtractFunc	ndmp_connect_close_reply_extract;
NdmpCompareParamFunc	ndmp_connect_close_reply_compare;
PrintNdmpMsgFunc		ndmp_connect_close_reply_print;

NdmpParamExtractFunc	ndmp_connect_server_auth_request_extract;
NdmpParamExtractFunc	ndmp_connect_server_auth_reply_extract;
NdmpCompareParamFunc	ndmp_connect_server_auth_reply_compare;
PrintNdmpMsgFunc	ndmp_connect_server_auth_reply_print;

int
inf_connect_client_auth(ndmp_error, host_info *, FILE *);
int
inf_connect_close(host_info *, FILE *);
int
inf_connect_open(ndmp_error, host_info *, FILE *);
int
inf_connect_server_auth(ndmp_error, host_info *, FILE *);

#ifdef __cplusplus
}
#endif

#endif /* _CONNECT_TESTER_H */
