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

#pragma ident	"@(#)process_hdlr_table.c	1.3	09/03/30 SMI"

#include <process_hdlr_table.h>
#include <tape_tester.h>
#include <scsi_tester.h>
#include <connect_tester.h>
#include <config_tester.h>
#include <data.h>
#include <mover.h>

/*
 * process_hdlr_table array is table.
 * Each row in this table has values for
 * a particular NDMP interface.
 * The whole array is held by the handler object.
 */
ProcessMsgHandler process_hdlr_table[] =
{
	{
		NDMP_CONNECT_OPEN,
		ndmp_connect_open_request_extract,
		ndmp_connect_open_reply_extract,
		ndmp_connect_open_reply_compare,
		ndmp_connect_open_reply_print
	},
	{
		NDMP_CONNECT_CLIENT_AUTH,
		ndmp_connect_client_auth_request_extract,
		ndmp_connect_client_auth_reply_extract,
		ndmp_connect_client_auth_reply_compare,
		ndmp_connect_client_auth_reply_print
	},
	{
		NDMP_CONNECT_SERVER_AUTH,
		ndmp_connect_server_auth_request_extract,
		ndmp_connect_server_auth_reply_extract,
		ndmp_connect_server_auth_reply_compare,
		ndmp_connect_server_auth_reply_print
	},
	{
		NDMP_CONNECT_CLOSE,
		ndmp_connect_close_request_extract,
		ndmp_connect_close_reply_extract,
		ndmp_connect_close_reply_compare,
		ndmp_connect_close_reply_print
	},
	{
		NDMP_CONFIG_GET_HOST_INFO,
		ndmp_config_get_host_info_request_extract,
		ndmp_config_get_host_info_reply_extract,
		ndmp_config_get_host_info_reply_compare,
		ndmp_config_get_host_info_reply_print
	},
	{
		NDMP_CONFIG_GET_SERVER_INFO,
		ndmp_config_get_server_info_request_extract,
		ndmp_config_get_server_info_reply_extract,
		ndmp_config_get_server_info_reply_compare,
		ndmp_config_get_server_info_reply_print
	},
	{
		NDMP_CONFIG_GET_CONNECTION_TYPE,
		ndmp_config_get_connection_type_request_extract,
		ndmp_config_get_connection_type_reply_extract,
		ndmp_config_get_connection_type_reply_compare,
		ndmp_config_get_connection_type_reply_print
	},
	{
		NDMP_CONFIG_GET_AUTH_ATTR,
		ndmp_config_get_auth_attr_request_extract,
		ndmp_config_get_auth_attr_reply_extract,
		ndmp_config_get_auth_attr_reply_compare,
		ndmp_config_get_auth_attr_reply_print
	},
	{
		NDMP_CONFIG_GET_BUTYPE_INFO,
		ndmp_config_get_butype_info_request_extract,
		ndmp_config_get_butype_info_reply_extract,
		ndmp_config_get_butype_info_reply_compare,
		ndmp_config_get_butype_info_reply_print
	},
	{
		NDMP_CONFIG_GET_FS_INFO,
		ndmp_config_get_fs_info_request_extract,
		ndmp_config_get_fs_info_reply_extract,
		ndmp_config_get_fs_info_reply_compare,
		ndmp_config_get_fs_info_reply_print
	},
	{
		NDMP_CONFIG_GET_TAPE_INFO,
		ndmp_config_get_tape_info_request_extract,
		ndmp_config_get_tape_info_reply_extract,
		ndmp_config_get_tape_info_reply_compare,
		ndmp_config_get_tape_info_reply_print
	},
	{
		NDMP_CONFIG_GET_SCSI_INFO,
		ndmp_config_get_scsi_info_request_extract,
		ndmp_config_get_scsi_info_reply_extract,
		ndmp_config_get_scsi_info_reply_compare,
		ndmp_config_get_scsi_info_reply_print
	},
	{
		NDMP_CONFIG_GET_EXT_LIST,
		ndmp_config_get_ext_list_request_extract,
		ndmp_config_get_ext_list_reply_extract,
		ndmp_config_get_ext_list_reply_compare,
		ndmp_config_get_ext_list_reply_print
	},
	{
		NDMP_CONFIG_SET_EXT_LIST,
		ndmp_config_set_ext_list_request_extract,
		ndmp_config_set_ext_list_reply_extract,
		ndmp_config_set_ext_list_reply_compare,
		ndmp_config_set_ext_list_reply_print
	},
	{
		NDMP_SCSI_OPEN,
		ndmp_scsi_open_request_extract,
		ndmp_scsi_open_reply_extract,
		ndmp_scsi_open_reply_compare,
		ndmp_scsi_open_reply_print
	},
	{
		NDMP_SCSI_CLOSE,
		ndmp_scsi_close_request_extract,
		ndmp_scsi_close_reply_extract,
		ndmp_scsi_close_reply_compare,
		ndmp_scsi_close_reply_print
	},
	{
		NDMP_SCSI_GET_STATE,
		ndmp_scsi_get_state_request_extract,
		ndmp_scsi_get_state_reply_extract,
		ndmp_scsi_get_state_reply_compare,
		ndmp_scsi_get_state_reply_print
	},
	{
		NDMP_SCSI_RESET_DEVICE,
		ndmp_scsi_reset_device_request_extract,
		ndmp_scsi_reset_device_reply_extract,
		ndmp_scsi_reset_device_reply_compare,
		ndmp_scsi_reset_device_reply_print
	},
	{
		NDMP_SCSI_EXECUTE_CDB,
		ndmp_scsi_execute_cdb_request_extract,
		ndmp_scsi_execute_cdb_reply_extract,
		ndmp_scsi_execute_cdb_reply_compare,
		ndmp_scsi_execute_cdb_reply_print
	},
	{
		NDMP_TAPE_OPEN,
		ndmp_tape_open_request_extract,
		ndmp_tape_open_reply_extract,
		ndmp_tape_open_reply_compare,
		ndmp_tape_open_reply_print
	},
	{
		NDMP_TAPE_CLOSE,
		ndmp_tape_close_request_extract,
		ndmp_tape_close_reply_extract,
		ndmp_tape_close_reply_compare,
		ndmp_tape_close_reply_print
	},
	{
		NDMP_TAPE_GET_STATE,
		ndmp_tape_get_state_request_extract,
		ndmp_tape_get_state_reply_extract,
		ndmp_tape_get_state_reply_compare,
		ndmp_tape_get_state_reply_print
	},
	{
		NDMP_TAPE_MTIO,
		ndmp_tape_mtio_request_extract,
		ndmp_tape_mtio_reply_extract,
		ndmp_tape_mtio_reply_compare,
		ndmp_tape_mtio_reply_print
	},
	{
		NDMP_TAPE_WRITE,
		ndmp_tape_write_request_extract,
		ndmp_tape_write_reply_extract,
		ndmp_tape_write_reply_compare,
		ndmp_tape_write_reply_print
	},
	{
		NDMP_TAPE_READ,
		ndmp_tape_read_request_extract,
		ndmp_tape_read_reply_extract,
		ndmp_tape_read_reply_compare,
		ndmp_tape_read_reply_print
	},
	{
		NDMP_TAPE_EXECUTE_CDB,
		ndmp_tape_execute_cdb_request_extract,
		ndmp_tape_execute_cdb_reply_extract,
		ndmp_tape_execute_cdb_reply_compare,
		ndmp_tape_execute_cdb_reply_print
	},
	{
		NDMP_DATA_GET_STATE,
		ndmp_data_get_state_request_extract,
		ndmp_data_get_state_reply_extract,
		ndmp_data_get_state_compare,
		ndmp_data_get_state_reply_print
	},
	{
		NDMP_DATA_START_BACKUP,
		ndmp_data_start_backup_request_extract,
		ndmp_data_start_backup_reply_extract,
		ndmp_data_start_backup_compare,
		ndmp_data_start_backup_reply_print
	},
	{
		NDMP_DATA_START_RECOVER,
		ndmp_data_start_recover_request_extract,
		ndmp_data_start_recover_reply_extract,
		ndmp_data_start_recover_compare,
		ndmp_data_start_recover_reply_print
	},
	{
		NDMP_DATA_START_RECOVER_FILEHIST,
		ndmp_data_start_recover_request_extract,
		ndmp_data_start_recover_reply_extract,
		ndmp_data_start_recover_compare,
		ndmp_data_start_recover_reply_print
	},
	{
		NDMP_DATA_ABORT,
		ndmp_data_abort_request_extract,
		ndmp_data_abort_reply_extract,
		ndmp_data_abort_compare,
		ndmp_data_abort_reply_print
	},
	{
		NDMP_DATA_GET_ENV,
		ndmp_data_get_env_request_extract,
		ndmp_data_get_env_reply_extract,
		ndmp_data_get_env_compare,
		ndmp_data_get_env_reply_print
	},
	{
		NDMP_DATA_STOP,
		ndmp_data_stop_request_extract,
		ndmp_data_stop_reply_extract,
		ndmp_data_stop_compare,
		ndmp_data_stop_reply_print
	},
	{
		NDMP_DATA_LISTEN,
		ndmp_data_listen_request_extract,
		ndmp_data_listen_reply_extract,
		ndmp_data_listen_compare,
		ndmp_data_listen_reply_print
	},
	{
		NDMP_DATA_CONNECT,
		ndmp_data_connect_request_extract,
		ndmp_data_connect_reply_extract,
		ndmp_data_connect_compare,
		ndmp_data_connect_reply_print
	},
	{
		NDMP_MOVER_GET_STATE,
		ndmp_mover_get_state_request_extract,
		ndmp_mover_get_state_reply_extract,
		ndmp_mover_get_state_compare,
		ndmp_mover_get_state_reply_print
	},
	{
		NDMP_MOVER_LISTEN,
		ndmp_mover_listen_request_extract,
		ndmp_mover_listen_reply_extract,
		ndmp_mover_listen_reply_compare,
		ndmp_mover_listen_reply_print
	},
	{
		NDMP_MOVER_CONTINUE,
		ndmp_mover_continue_request_extract,
		ndmp_mover_continue_reply_extract,
		ndmp_mover_continue_compare,
		ndmp_mover_continue_reply_print
	},
	{
		NDMP_MOVER_ABORT,
		ndmp_mover_abort_request_extract,
		ndmp_mover_abort_reply_extract,
		ndmp_mover_abort_compare,
		ndmp_mover_abort_reply_print
	},
	{
		NDMP_MOVER_STOP,
		ndmp_mover_stop_request_extract,
		ndmp_mover_stop_reply_extract,
		ndmp_mover_stop_compare,
		ndmp_mover_stop_reply_print
	},
	{
		NDMP_MOVER_SET_WINDOW,
		ndmp_mover_set_window_request_extract,
		ndmp_mover_set_window_reply_extract,
		ndmp_mover_set_window_compare,
		ndmp_mover_set_window_reply_print
	},
	{
		NDMP_MOVER_READ,
		ndmp_mover_read_request_extract,
		ndmp_mover_read_reply_extract,
		ndmp_mover_read_compare,
		ndmp_mover_read_reply_print
	},
	{
		NDMP_MOVER_CLOSE,
		ndmp_mover_close_request_extract,
		ndmp_mover_close_reply_extract,
		ndmp_mover_close_compare,
		ndmp_mover_close_reply_print
	},
	{
		NDMP_MOVER_SET_RECORD_SIZE,
		ndmp_mover_set_record_size_request_extract,
		ndmp_mover_set_record_size_reply_extract,
		ndmp_mover_set_record_size_compare,
		ndmp_mover_set_record_size_reply_print
	},
	{
		NDMP_MOVER_CONNECT,
		ndmp_mover_connect_request_extract,
		ndmp_mover_connect_reply_extract,
		ndmp_mover_connect_compare,
		ndmp_mover_connect_reply_print
	}
};
