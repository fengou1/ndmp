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

#pragma ident	"@(#)ndmp_execute.c	1.3	09/03/30 SMI"

/*
 * The sequence of operations to be executed for running a
 * particular test case, is decided here.
 * This files also methods to parse the command line input.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>
#include <ndmp.h>
#include <process_hdlr_table.h>
#include <notify_tester.h>
#include <fhistory_tester.h>
#include <log_tester.h>

/* Global variables used in execute() */
extern conn_handle *connection;
extern ProcessMsgHandler  process_hdlr_table[];
void
execute();
int
handlePostMessage(conn_handle *);

/*
 * clearRequestMem() :
 * Cleans up the memory for request objects
 */
static int
clearRequestMem(void *req, ndmp_message *ndmpMessage)
{
	if (req == 0)
		return (-1);
	switch (*ndmpMessage) {
		case NDMP_TAPE_WRITE:
			if (((ndmp_tape_write_request*) req)->
			    data_out.data_out_val != NULL)
				free(((ndmp_tape_write_request*) req)->
				    data_out.data_out_val);
			break;
		case NDMP_TAPE_EXECUTE_CDB:
			if (((ndmp_execute_cdb_request*) req)->cdb.cdb_val
			    != NULL)
				free(((ndmp_execute_cdb_request*) req)->
				    cdb.cdb_val);
			if (((ndmp_execute_cdb_request*) req)->
			    dataout.dataout_val != NULL)
				free(((ndmp_execute_cdb_request*) req)->
				    dataout.dataout_val);
			break;
		case NDMP_SCSI_EXECUTE_CDB:
			if (((ndmp_execute_cdb_request*) req)->
			    cdb.cdb_val != NULL)
				free(((ndmp_execute_cdb_request*) req)->
				    cdb.cdb_val);
			if (((ndmp_execute_cdb_request*) req)->
			    dataout.dataout_val != NULL)
				free(((ndmp_execute_cdb_request*) req)->
				    dataout.dataout_val);
			break;
		case NDMP_SCSI_OPEN:
			free(((ndmp_scsi_open_request*) req)->device);
			break;
		case NDMP_CONNECT_CLIENT_AUTH:
			clear_connect_client_auth_request(req);
			break;
		case NDMP_DATA_CONNECT:
			free(((ndmp_data_connect_request*) req)->
			    addr.ndmp_addr_u.tcp_addr.tcp_addr_val);
			break;
		case NDMP_DATA_LISTEN:
			break;
		case NDMP_DATA_START_BACKUP:
			clear_data_start_backup_request(req);
			break;
		case NDMP_DATA_START_RECOVER:
			clear_data_start_recover_request(req);
			break;
		case NDMP_DATA_START_RECOVER_FILEHIST:
			clear_data_start_recover_request(req);
			break;
		case NDMP_MOVER_SET_RECORD_SIZE:
			break;
		case NDMP_MOVER_CONNECT:
			clear_mover_connect_request(req);
			break;
		case NDMP_MOVER_LISTEN:
			break;
		case NDMP_MOVER_READ:
			break;
		default:
			(void) ndmp_dprintf(stdout, " ");
	}

	return (0);
}

/*
 * clearReplyMem() : Cleans up the memory that is being used by the
 * reply object after the object is used and the memory needs to
 * be cleaned.
 *
 * Arguments:  void  req - A pointer to the reply object.
 * ndmp_message - Ndmp Message code.
 *
 * Returns:int, 0 on success,
 *		-1 on failure
 */
static int
clearReplyMem(void *rep, ndmp_message *ndmpMessage)
{

	if (rep == NULL)
		return (-1);

	switch (*ndmpMessage) {
		case NDMP_TAPE_READ:
			if (((ndmp_tape_read_reply*) rep)->
			    data_in.data_in_val != NULL)
				free(((ndmp_tape_read_reply*) rep)->
				    data_in.data_in_val);
			break;
		case NDMP_TAPE_EXECUTE_CDB:
			if (((ndmp_execute_cdb_reply*) rep)->
			    datain.datain_val != NULL)
				free(((ndmp_execute_cdb_reply*) rep)->
				    datain.datain_val);
			if (((ndmp_execute_cdb_reply*) rep)->
			    ext_sense.ext_sense_val != NULL)
				free(((ndmp_execute_cdb_reply*) rep)->
				    ext_sense.ext_sense_val);
			break;
		case NDMP_SCSI_EXECUTE_CDB:
			if (((ndmp_execute_cdb_reply*) rep)->
			    datain.datain_val != NULL)
				free(((ndmp_execute_cdb_reply*) rep)->
				    datain.datain_val);
			if (((ndmp_execute_cdb_reply*) rep)->
			    ext_sense.ext_sense_val != NULL)
				free(((ndmp_execute_cdb_reply*) rep)->
				    ext_sense.ext_sense_val);
			break;
		case NDMP_CONFIG_GET_HOST_INFO:
			clear_config_get_host_info(rep);
			break;
		case NDMP_CONFIG_GET_SERVER_INFO:
			clear_config_get_server_info(rep);
			break;
		case NDMP_CONFIG_GET_BUTYPE_INFO:

			(void) ndmp_dprintf(stdout,
			    "ndmp_message 0x%x \n", *ndmpMessage);

			if (((ndmp_config_get_butype_attr_reply*) rep)->
			    butype_info.butype_info_val != NULL)
				free(((ndmp_config_get_butype_attr_reply*) rep)
				    ->butype_info.butype_info_val);
			break;
		case NDMP_CONFIG_GET_FS_INFO:
			clear_config_get_fs_info(rep);
			break;
		case NDMP_CONFIG_GET_TAPE_INFO:
			clear_config_get_tape_info(rep);
			break;
		case NDMP_CONFIG_GET_SCSI_INFO:
			clear_config_get_scsi_info(rep);
			break;
		case NDMP_CONNECT_SERVER_AUTH:
			clear_connect_server_auth(rep);
			break;
		case NDMP_DATA_LISTEN:
			clear_data_listen(rep);
			break;
		case NDMP_DATA_GET_STATE:
			clear_data_get_state(rep);
			break;
		case NDMP_DATA_GET_ENV:
			clear_data_get_env(rep);
			break;
		case NDMP_MOVER_LISTEN:
			clear_mover_listen(rep);
			break;
		case NDMP_MOVER_GET_STATE:
			clear_mover_get_state(rep);
			break;
		default:
			(void) ndmp_dprintf(stdout, " ");
	}

	return (0);

}


/*
 * Opens the test scenario file. This is the input
 * file given at command line.
 */
static void
open_test_scenario(FILE **test)
{

	*test = fopen(testcase, "rt");

	if (*test == NULL) {
		(void) ndmp_dprintf(stdout,
		    "Error: unable to open test case file \n");
		exit(1);
	}

}

/*
 * Extracts a line from the test scenario file.
 */
static int
get_line_from_ts(char *line, FILE *test)
{

	if (feof(test))
		return (0);

	(void) fgets(line, 200, test);

	return (1);

}

ProcessMsgHandler*
get_process_hdlr(ndmp_message ndmpMessage)
{
	ProcessMsgHandler* process_hdlr;
	for (process_hdlr = process_hdlr_table; process_hdlr != 0;
	    process_hdlr++) {
		if (process_hdlr->msg == ndmpMessage)
			return (process_hdlr);
	}
	return (0);
}
/*
 * get_msg_handler() : Gets the ndmp message handler from the static hash
 * based on the ndmp message code passed.
 *
 * Arguments :
 * 		ProcessMsgHandler ** - Pointer to the hash of message handler
 * 		object.
 * 		ndmp_message * - Pointer to ndmp message code.
 * Return :
 * 		int - 0 is success and 1 is failure.
 */
static int
get_msg_handler(ProcessMsgHandler **process_hdlr,
    ndmp_message *ndmpMessage, char *request_line)
{

	static size_t i_strcspn;
	char ndmpMessageStr[80];
	char *delimeters = " \n";
	(void) ndmp_dprintf(stdout,
	    "(void) get_msg_handler: request_line %s \n",
	    request_line);
	(void) memset(ndmpMessageStr, '\0', sizeof (ndmpMessageStr));
	i_strcspn = strcspn(request_line, delimeters);
	(void) strncpy(ndmpMessageStr, request_line,
	    i_strcspn);
	(void) ndmp_dprintf(stdout,
	    "(void) get_msg_handler: ndmpMessageStr %s \n",
	    ndmpMessageStr);
	*ndmpMessage = strToNdmpMessageCode(ndmpMessageStr);
	(void) ndmp_dprintf(stdout,
	    "(void) get_msg_handler: ndmpMessage 0x%x \n",
	    *ndmpMessage);
	*process_hdlr = get_process_hdlr(*ndmpMessage);
	(void) ndmp_dprintf(stdout,
	    "(void) get_msg_handler: &process_hdlr 0x%x \n",
	    *process_hdlr);
	if (*process_hdlr == 0) {
		(void) ndmp_dprintf(stdout,
		    "(void) get_msg_handler: handler is null \n");
		return (0);
	} else {
		(void) ndmp_dprintf(stdout,
		    "(void) get_msg_handler: handler is not null \n");
		return (1);
	}
}

/*
 * send_request() : Helper function to send the request to the ndmp server
 *
 * Arguments :
 * 		Connection * - Pointer to the connection object.
 * 		ndmp_message - Ndmp message code.
 * 		void *request_mem - Pointer to the request object.
 * 		void **reply_mem - Pointer to the reply object.
 *
 * Return :
 * 		int - 0 is success and 1 is Failure.
 */
static int
send_request(conn_handle *connection, ndmp_message message,
    void *request_mem, void **reply_mem)
{
	int r;

	ndmp_dprintf("tape device is %s message is 0x%x\n",
	    ((ndmp_tape_open_request *) request_mem)->device, message);
	r = process_request(request_mem, message, connection, reply_mem,
	    logfile);
	(void) ndmp_dprintf(stdout, "(void) send_request: r is %d \n", r);
	if (r != NULL) {
		(void) ndmp_dprintf(stdout,
		    "init: error sending 0x%x\n",
		    message);
		return (0);
	}
	return (1);
}

/*
 * compare_print_reply() : Helper function to comapre and print the
 * reply object after the response is received from the NDMP server.
 *
 * Arguments :
 * 		ProcessMsgHandler * - Pointer to the handler table.
 * 		FILE * - Handle to log file.
 * 		void *reply_mem - Pointer to reply object.
 * 		void **expect_mem - Pointer to expected reply object.
 * 		char * - Reply line got from the input file.
 * Return :
 * 		int - 0 is success and 1 is failure.
 */
static int
compare_print_reply(ProcessMsgHandler *process_hdlr, FILE *out,
    void *reply_mem, void **expect_mem, char *reply_line)
{

	if (process_hdlr->extractReply != NULL) {
		(process_hdlr->extractReply)(reply_line, expect_mem);

		if (reply_mem != NULL) {
			if ((process_hdlr->compareReply)
			    (*expect_mem, reply_mem)) {
				(void) fprintf(out, "NDMP REPLY MESSAGE :\n");
				(process_hdlr->printReplyMsg)(out, reply_mem);
				(void) fprintf(out,
				    "NDMP EXPECTED MESSAGE :\n");
				(process_hdlr->printReplyMsg)
				    (out, *expect_mem);
				(void) fprintf(out,
				    "TEST CASE RESULT : SUCCESS \n");

				(void) ndmp_dprintf(stdout, "after SUCCESS \n");

				return (1);
			} else {
				(void) fprintf(out, "NDMP REPLY MESSAGE :\n");
				(process_hdlr->printReplyMsg)(out, reply_mem);
				(void) fprintf(out,
				    "NDMP EXPECTED MESSAGE :\n");
				(process_hdlr->printReplyMsg)
				    (out, *expect_mem);
				(void) fprintf(out,
				    "TEST CASE RESULT : ERROR \n");
				return (0);
			}

		} else {
			(void) fprintf(out, "NDMP REPLY MESSAGE :\nNULL \n");
			(void) fprintf(out, "NDMP EXPECTED MESSAGE :\n");
			(process_hdlr->printReplyMsg)(out, *expect_mem);
			(void) fprintf(out, "TEST CASE RESULT : ERROR \n");
			return (0);
		}
	} else {
		(void) ndmp_dprintf(stdout,
		    "compare_print_reply: "
		    "process_hdlr->extractReply is null\n");
		return (0);
	}

}

/*
 * checkPostMessage() : Check if the post message flag is set
 * and do required logic based on the request.
 *
 * Return :
 * 		int - 0 is success and 1 is failure.
 */
static int
checkPostMessage(ndmp_message *ndmpMessage)
{

	(void) ndmp_dprintf(stdout, "postMsgFlag %d postSubMsgFlag %d\n",
	    postMsgFlag, postSubMsgFlag);

	if (postMsgFlag == NDMP_FH_ADD_DIR &&
	    (*ndmpMessage == NDMP_DATA_START_BACKUP ||
	    *ndmpMessage == NDMP_DATA_START_RECOVER))
		(void) sleep(3);
	else if (postMsgFlag == NDMP_NOTIFY_CONNECTION_STATUS)
		(void) sleep(3);
	else if (postMsgFlag == NDMP_FH_ADD_NODE &&
	    (*ndmpMessage == NDMP_DATA_START_BACKUP ||
	    *ndmpMessage == NDMP_DATA_START_RECOVER))
		(void) sleep(3);
	else if (postMsgFlag == NDMP_DATA_START_BACKUP &&
	    (*ndmpMessage == NDMP_DATA_START_BACKUP))
		(void) sleep(3);
	else if (postMsgFlag == NDMP_DATA_START_RECOVER &&
	    *ndmpMessage == NDMP_DATA_START_RECOVER)
		(void) sleep(6);
	else if (postMsgFlag == NDMP_FH_ADD_FILE &&
	    (*ndmpMessage == NDMP_DATA_START_BACKUP ||
	    *ndmpMessage == NDMP_DATA_START_RECOVER))
		(void) sleep(3);
	else if (postMsgFlag == NDMP_NOTIFY_DATA_HALTED &&
	    ((ndmp_data_halt_reason) postSubMsgFlag) ==
	    NDMP_DATA_HALT_SUCCESSFUL &&
	    (*ndmpMessage == NDMP_DATA_START_BACKUP)) {
		(void) sleep(3);
	} else if (postMsgFlag == NDMP_NOTIFY_MOVER_HALTED &&
	    ((ndmp_data_halt_reason) postSubMsgFlag) ==
	    NDMP_MOVER_HALT_CONNECT_CLOSED &&
	    (*ndmpMessage == NDMP_DATA_START_BACKUP))
		(void) sleep(3);
	else if (postMsgFlag == NDMP_NOTIFY_MOVER_PAUSED &&
	    (*ndmpMessage == NDMP_DATA_START_BACKUP ||
	    *ndmpMessage == NDMP_DATA_START_RECOVER))
		(void) sleep(3);
	else if (postMsgFlag == NDMP_LOG_FILE &&
	    (*ndmpMessage == NDMP_DATA_START_BACKUP ||
	    *ndmpMessage == NDMP_DATA_START_RECOVER))
		(void) sleep(3);
	else if (postMsgFlag == NDMP_LOG_MESSAGE &&
	    (*ndmpMessage == NDMP_DATA_START_BACKUP ||
	    *ndmpMessage == NDMP_DATA_START_RECOVER))
		(void) sleep(3);
	else
		return (0);
	return (1);
}

/*
 * execute() : This function is the main function. It knows the sequence
 * of methods to be called. First the reuest is sent to ndmp server.
 * After the reply is received the reply object is comapred and printed.
 */
void
execute(conn_handle *connection, FILE *logfile)
{
	char request_line[200], reply_line[200];
	ndmp_message ndmpMessage;
	ProcessMsgHandler *process_hdlr;
	void *request_mem, *reply_mem, *expect_mem;
	open_test_scenario(&test_scenario);

	time_t timer;
	timer = time(NULL);
	(void) fprintf(logfile, "Test start : Date %s\n",
	    asctime(localtime(&timer)));
	while (!feof(test_scenario)) {

		(void) memset(request_line, '\0', sizeof (request_line));
		(void) memset(reply_line, '\0', sizeof (reply_line));

		/* Get the request line from the test scenarios file */
		(void) get_line_from_ts(request_line, test_scenario);
		/* Get the message handler object */
		(void) get_msg_handler(&process_hdlr,
		    &ndmpMessage, request_line);
		if (process_hdlr == 0)
			continue;

		/* Get the reply line from the test scenarios file */
		(void) get_line_from_ts(reply_line, test_scenario);
		if (process_hdlr->extractRequest != NULL) {

			(void) ndmp_dprintf(stdout,
			    "execute: b4 extracting request \n");

			(void) fprintf(logfile, "REQUEST : %s", request_line);
			(process_hdlr->extractRequest)
			    (request_line, &request_mem);
			(void) ndmp_dprintf(stdout,
			    "execute: aftr extracting request \n");
			/* Send the request */
			(void) send_request(connection,
			    ndmpMessage, request_mem, &reply_mem);
			(void) checkPostMessage(&ndmpMessage);
			if (process_hdlr != NULL) {

				/*
				 * compare and print the reply and
				 * expected reply
				 */
				(void) ndmp_dprintf(stdout,
				    "execute: b4 cpr()"
				    " reply_mem 0x%x \n", reply_mem);


				(void) ndmp_dprintf(stdout, "REQUEST : %s\n",
				    strtok(request_line, " "));
				(void) ndmp_dprintf(stdout,
				    "execute: middle cpr() reply_mem 0x%x \n",
				    reply_mem);

				(void) compare_print_reply(process_hdlr,
				    logfile, reply_mem,
				    &expect_mem, reply_line);

				(void) ndmp_dprintf(stdout,
				    "execute: after  cpr() ******"
				    "reply_mem 0x%x \n", reply_mem);

			} else {

				(void) ndmp_dprintf(stdout,
				    "execute: ndmpMsgHdlr->sizeof_reply"
				    " is null \n");

			}
			(void) ndmp_dprintf(stdout, "execute : b4 clear\n");

		}
		(void) ndmp_dprintf(stdout, "execute : b4 clear\n");
		(void) clearRequestMem(request_mem, &ndmpMessage);
		(void) ndmp_dprintf(stdout, "execute : b4 clear\n");
		(void) clearReplyMem(reply_mem, &ndmpMessage);
		(void) ndmp_dprintf(stdout, "execute : after clear\n");
		(void) ndmp_dprintf(stdout, "==========================\n");
		(void) ndmp_dprintf(logfile,
		    "-----------------------------------------"
		    "-------------------------\n");
	}

	timer = time(NULL);
	(void) fprintf(logfile, "Test finish : Date %s\n",
	    asctime(localtime(&timer)));
	(void) fclose(logfile);
	(void) fclose(test_scenario);
}


/*
 * End of file	: ndmp_execute.c
 */
