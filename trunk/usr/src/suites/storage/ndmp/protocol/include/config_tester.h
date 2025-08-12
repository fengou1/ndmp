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

#ifndef _CONFIG_TESTER_H
#define	_CONFIG_TESTER_H

#pragma ident	"@(#)config_tester.h	1.2	09/02/11 SMI"

/*
 * Declarations for testing the NDMP Config Interface
 */

#ifdef __cplusplus
extern "C" {
#endif

NdmpParamExtractFunc	ndmp_config_get_host_info_request_extract;
NdmpParamExtractFunc	ndmp_config_get_host_info_reply_extract;
NdmpCompareParamFunc	ndmp_config_get_host_info_reply_compare;
PrintNdmpMsgFunc		ndmp_config_get_host_info_reply_print;

NdmpParamExtractFunc	ndmp_config_get_server_info_request_extract;
NdmpParamExtractFunc	ndmp_config_get_server_info_reply_extract;
NdmpCompareParamFunc	ndmp_config_get_server_info_reply_compare;
PrintNdmpMsgFunc		ndmp_config_get_server_info_reply_print;

NdmpParamExtractFunc	ndmp_config_get_connection_type_request_extract;
NdmpParamExtractFunc	ndmp_config_get_connection_type_reply_extract;
NdmpCompareParamFunc	ndmp_config_get_connection_type_reply_compare;
PrintNdmpMsgFunc		ndmp_config_get_connection_type_reply_print;

NdmpParamExtractFunc	ndmp_config_get_auth_attr_request_extract;
NdmpParamExtractFunc	ndmp_config_get_auth_attr_reply_extract;
NdmpCompareParamFunc	ndmp_config_get_auth_attr_reply_compare;
PrintNdmpMsgFunc		ndmp_config_get_auth_attr_reply_print;

NdmpParamExtractFunc	ndmp_config_get_butype_info_request_extract;
NdmpParamExtractFunc	ndmp_config_get_butype_info_reply_extract;
NdmpCompareParamFunc	ndmp_config_get_butype_info_reply_compare;
PrintNdmpMsgFunc		ndmp_config_get_butype_info_reply_print;

NdmpParamExtractFunc	ndmp_config_get_fs_info_request_extract;
NdmpParamExtractFunc	ndmp_config_get_fs_info_reply_extract;
NdmpCompareParamFunc	ndmp_config_get_fs_info_reply_compare;
PrintNdmpMsgFunc		ndmp_config_get_fs_info_reply_print;

NdmpParamExtractFunc	ndmp_config_get_tape_info_request_extract;
NdmpParamExtractFunc	ndmp_config_get_tape_info_reply_extract;
NdmpCompareParamFunc	ndmp_config_get_tape_info_reply_compare;
PrintNdmpMsgFunc		ndmp_config_get_tape_info_reply_print;

NdmpParamExtractFunc	ndmp_config_get_scsi_info_request_extract;
NdmpParamExtractFunc	ndmp_config_get_scsi_info_reply_extract;
NdmpCompareParamFunc	ndmp_config_get_scsi_info_reply_compare;
PrintNdmpMsgFunc		ndmp_config_get_scsi_info_reply_print;

NdmpParamExtractFunc	ndmp_config_get_ext_list_request_extract;
NdmpParamExtractFunc	ndmp_config_get_ext_list_reply_extract;
NdmpCompareParamFunc	ndmp_config_get_ext_list_reply_compare;
PrintNdmpMsgFunc		ndmp_config_get_ext_list_reply_print;

NdmpParamExtractFunc	ndmp_config_set_ext_list_request_extract;
NdmpParamExtractFunc	ndmp_config_set_ext_list_reply_extract;
NdmpCompareParamFunc	ndmp_config_set_ext_list_reply_compare;
PrintNdmpMsgFunc		ndmp_config_set_ext_list_reply_print;

#ifdef __cplusplus
}
#endif

#endif /* _CONFIG_TESTER_H */
