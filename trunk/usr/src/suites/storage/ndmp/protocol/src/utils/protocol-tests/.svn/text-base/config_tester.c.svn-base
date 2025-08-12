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

#pragma ident	"@(#)config_tester.c	1.3	09/03/30 SMI"

/*
 * Config Interface allows the DMA to discover
 * the configuration of the NDMP Server.
 * This files implements all the config interfaces.
 */

#include<stdio.h>
#include<string.h>

#include <ndmp.h>
#include <ndmp_lib.h>
#include <ndmp_comm_lib.h>
#include <log.h>
#include <ndmp_connect.h>

extern FILE *logfile;
/*
 * ndmp_config_get_host_info_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_get_host_info_request_extract(char *str, void **request_mem)
{
	str = NULL;
	*request_mem = NULL;
}

/*
 * ndmp_config_get_host_info_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_get_host_info_reply_extract(char *str, void **reply_mem)
{
	int	token_index = 0;
	ndmp_config_get_host_info_reply* reply;

	reply = (ndmp_config_get_host_info_reply *)malloc(
	    sizeof (ndmp_config_get_host_info_reply));
	*reply_mem = (void *)reply;
	extract_tokens(str);

	if (token_index < token_num)
		reply->error = strToNdmpErrorCode(tokens[token_index++]);

	if (++token_index < token_num)
		reply->hostname = strdup(tokens[token_index++]);

	if (++token_index < token_num)
		reply->os_type = strdup(tokens[token_index++]);

	if (++token_index < token_num)
		reply->os_vers = strdup(tokens[token_index++]);

	if (++token_index < token_num)
		reply->hostid = strdup(tokens[token_index++]);

	release_tokens();
}

/*
 * ndmp_config_get_host_info_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_get_host_info_reply_compare(void *expected, void *result)
{
	ndmp_config_get_host_info_reply *expectedMsg, *resultMsg;

	expectedMsg = (ndmp_config_get_host_info_reply *)expected;
	resultMsg = (ndmp_config_get_host_info_reply *)result;

	if (expectedMsg->error != resultMsg->error)
		return (FALSE);

	return (TRUE);
}

/*
 * ndmp_config_get_host_info_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_get_host_info_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_get_host_info_reply *msg;

	msg = (ndmp_config_get_host_info_reply*)ndmpMsg;
	(void) fprintf(out, "error = %s\n", ndmpErrorCodeToStr(msg->error));
	(void) fprintf(out, "hostname = %s\n", msg->hostname);
	(void) fprintf(out, "os_type = %s\n", msg->os_type);
	(void) fprintf(out, "os_vers = %s\n",
	    msg->os_vers ? msg->os_vers : "msg->os_vers is null");
	(void) fprintf(out, "hostid = %s\n",
	    msg->hostid ? msg->hostid : "msg->hostid is null");
}

/*
 * ndmp_config_get_server_info_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_get_server_info_request_extract(char *str, void **request_mem)
{
	str = NULL;
	*request_mem = NULL;
}

/*
 * ndmp_config_get_server_info_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_get_server_info_reply_extract(char *str, void **reply_mem)
{
	int	token_index = 0;

	ndmp_config_get_server_info_reply* reply;

	reply = (ndmp_config_get_server_info_reply *)malloc(
	    sizeof (ndmp_config_get_server_info_reply));

	*reply_mem = (void *)reply;
	extract_tokens(str);

	if (token_index < token_num)
		reply->error = strToNdmpErrorCode(tokens[token_index++]);

	if (++token_index < token_num)
		reply->vendor_name = strdup(tokens[token_index++]);

	if (++token_index < token_num)
		reply->product_name = strdup(tokens[token_index++]);

	if (++token_index < token_num)
		reply->revision_number = strdup(tokens[token_index++]);

	if (++token_index < token_num)
		reply->auth_type.auth_type_len = atoi(tokens[token_index++]);

	if (++token_index < token_num) {
		reply->auth_type.auth_type_val =
		    (ndmp_auth_type*)malloc(sizeof (ndmp_auth_type));
		*(reply->auth_type.auth_type_val) =
		    strToNdmpAuthType(tokens[token_index++]);
	}

	release_tokens();
}

/*
 * ndmp_config_get_server_info_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_get_server_info_reply_compare(void *expected, void *result)
{
	ndmp_config_get_server_info_reply *expectedMsg, *resultMsg;

	expectedMsg = (ndmp_config_get_server_info_reply *)expected;
	resultMsg = (ndmp_config_get_server_info_reply *)result;

	if (expectedMsg->error != resultMsg->error)
		return (FALSE);

	return (TRUE);
}

/*
 * ndmp_config_get_server_info_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_get_server_info_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_get_server_info_reply *msg;

	msg = (ndmp_config_get_server_info_reply*)ndmpMsg;
	(void) fprintf(out, "error = %s\n", ndmpErrorCodeToStr(msg->error));
	(void) fprintf(out, "vendor_name = %s\n", msg->vendor_name);
	(void) fprintf(out, "product_name = %s\n", msg->product_name);
	(void) fprintf(out, "revision_number = %s\n",
	    msg->revision_number ? msg->revision_number :
	    "msg->revision_number is null");
	(void) fprintf(out, "auth_type.auth_type_len = %d\n",
	    msg->auth_type.auth_type_len);
}

/*
 * ndmp_config_get_connection_type_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_get_connection_type_request_extract(char *str, void **request_mem)
{
	str = NULL;
	request_mem = 0;
}

/*
 * ndmp_config_get_connection_type_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_get_connection_type_reply_extract(char *str, void **reply_mem)
{
	ndmp_config_get_connection_type_reply	*reply;
	int						token_index = 0;

	reply = (ndmp_config_get_connection_type_reply*)malloc
	    (sizeof (ndmp_config_get_connection_type_reply));
	*reply_mem = reply;

	extract_tokens(str);

	if (token_index < token_num)
	reply->error = strToNdmpErrorCode(tokens[token_index]);

	extract_addr_types((addr_types *)&(reply->addr_types), &token_index);

	release_tokens();

}

/*
 * ndmp_config_get_connection_type_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_get_connection_type_reply_compare(void *expected, void *result)
{
	ndmp_config_get_connection_type_reply	*expMsg, *repMsg;

	expMsg = (ndmp_config_get_connection_type_reply*)expected;
	repMsg = (ndmp_config_get_connection_type_reply*)result;

	if (expMsg != 0 && repMsg != 0) {

	if (expMsg->error != repMsg->error)
		return (FALSE);

	return (TRUE);

	} else {


	return (FALSE);
	}

}

/*
 * ndmp_config_get_connection_type_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_get_connection_type_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_get_connection_type_reply	*reply;

	reply = (ndmp_config_get_connection_type_reply*)ndmpMsg;

	if (reply != 0) {

	(void) fprintf(out, "error %s \n", ndmpErrorCodeToStr(reply->error));
	print_addr_types(out, (addr_types *)&(reply->addr_types));

	}
}


/*
 * ndmp_config_get_auth_attr_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_get_auth_attr_request_extract(char *str, void **request_mem)
{
	ndmp_config_get_auth_attr_request	*request;
	int					token_index = 0;

	request = (ndmp_config_get_auth_attr_request*)malloc(
	    sizeof (ndmp_config_get_auth_attr_request));
	*request_mem = request;

	extract_tokens(str);

	if (token_index < token_num) {
	if (!(strcmp(tokens[token_index], "NDMP_AUTH_NONE")))
		request->auth_type = 0;
	else if (!(strcmp(tokens[token_index], "NDMP_AUTH_TEXT")))
		request->auth_type = NDMP_AUTH_TEXT;
	else if (!(strcmp(tokens[token_index], "NDMP_AUTH_MD5")))
		request->auth_type = 2;
	(void) ndmp_dprintf(logfile,
	    "ndmp_config_get_auth_attr_request_extract: ");
	(void) ndmp_dprintf(logfile,
	    " auth_type is %d\n", request->auth_type);
	}

	release_tokens();
}

/*
 * ndmp_config_get_connection_type_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_get_auth_attr_reply_extract(char *str, void **reply_mem)
{
	ndmp_config_get_auth_attr_reply	*reply;
	int token_index = 0;

	reply = (ndmp_config_get_auth_attr_reply*)malloc(
	    sizeof (ndmp_config_get_auth_attr_reply));
	*reply_mem = reply;

	extract_tokens(str);

	if (token_index < token_num)
	reply->error = strToNdmpErrorCode(tokens[token_index]);

	if (++token_index < token_num)
	extract_ndmp_auth_attr(&(reply->server_attr), &token_index);

	release_tokens();
}

/*
 * ndmp_config_get_auth_attr_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_get_auth_attr_reply_compare(void *expected, void *result)
{

	ndmp_config_get_auth_attr_reply	*expMsg, *repMsg;

	expMsg = (ndmp_config_get_auth_attr_reply*)expected;
	repMsg = (ndmp_config_get_auth_attr_reply*)result;

	if (expMsg != 0 && repMsg != 0) {

	if (expMsg->error != repMsg->error)
		return (FALSE);

	return (TRUE);

	} else {
	return (FALSE);
	}

}

/*
 * ndmp_config_get_auth_attr_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_get_auth_attr_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_get_auth_attr_reply	*reply;

	reply = (ndmp_config_get_auth_attr_reply*)ndmpMsg;

	if (reply != 0) {
	(void) fprintf(out, "error %s \n", ndmpErrorCodeToStr(reply->error));
	print_ndmp_auth_attr(out, &(reply->server_attr));
	}
}


/*
 * ndmp_config_get_butype_info_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_get_butype_info_request_extract(char *str, void **request_mem)
{
	str = NULL;
	request_mem = 0;
}

/*
 * ndmp_config_get_butype_info_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_get_butype_info_reply_extract(char *str, void **reply_mem)
{
	ndmp_config_get_butype_attr_reply	*reply;
	int				token_index = 0;

	reply = (ndmp_config_get_butype_attr_reply*)malloc(
	    sizeof (ndmp_config_get_butype_attr_reply));
	*reply_mem = (void *)reply;

	extract_tokens(str);

	if (token_index < token_num)
		reply->error = strToNdmpErrorCode(tokens[token_index]);

	if (++token_index < token_num) {
		reply->butype_info.butype_info_len = atoi(tokens[token_index]);
		reply->butype_info.butype_info_val =
		    (ndmp_butype_info*)malloc(sizeof (ndmp_butype_info));
	if (++token_index < token_num)
		reply->butype_info.butype_info_val->butype_name =
		    strdup(tokens[token_index]);
	if (++token_index < token_num)
		reply->butype_info.butype_info_val->
		    default_env.default_env_len =
		    atoi(tokens[token_index]);

		reply->butype_info.butype_info_val->
		    default_env.default_env_val =
		    (ndmp_pval*)malloc(sizeof (ndmp_pval));
	if (++token_index < token_num)
		reply->butype_info.butype_info_val->
		    default_env.default_env_val->name =
		    strdup(tokens[token_index]);
	if (++token_index < token_num)
		reply->butype_info.butype_info_val->
		    default_env.default_env_val->value =
		    strdup(tokens[token_index]);
	}

	release_tokens();
}

/*
 * ndmp_config_get_butype_info_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_get_butype_info_reply_compare(void *expected, void *result)
{

	ndmp_config_get_butype_attr_reply	*expMsg, *repMsg;

	expMsg = (ndmp_config_get_butype_attr_reply*)expected;
	repMsg = (ndmp_config_get_butype_attr_reply*)result;

	if (expMsg != 0 && repMsg != 0) {

	if (expMsg->error != repMsg->error)
		return (FALSE);

	return (TRUE);

	} else {

	return (FALSE);

	}
}

/*
 * ndmp_config_get_butype_info_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_get_butype_info_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_get_butype_attr_reply	*reply;
	reply = (ndmp_config_get_butype_attr_reply*)ndmpMsg;

	if (reply != 0) {
	(void) fprintf(out, "error %s\n", ndmpErrorCodeToStr(reply->error));
	print_butype_info(out, (butype_info *)&(reply->butype_info));
	} else
	(void) fprintf(out,
	    "ndmp_config_get_butype_info_reply_print: obj is null\n");
}

/*
 * ndmp_config_get_fs_info_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_get_fs_info_request_extract(char *str, void **request_mem)
{
	str = NULL;
	request_mem = 0;
}

/*
 * ndmp_config_get_fs_info_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_get_fs_info_reply_extract(char *str, void **reply_mem)
{
	ndmp_config_get_fs_info_reply	*reply;
	int					token_index = 0;

	reply = (ndmp_config_get_fs_info_reply*)malloc
	    (sizeof (ndmp_config_get_fs_info_reply));
	*reply_mem = reply;

	extract_tokens(str);

	if (token_index < token_num)
	reply->error = strToNdmpErrorCode(tokens[token_index]);

	extract_fs_info((fs_info *)&(reply->fs_info), &token_index);

	release_tokens();
}

/*
 * ndmp_config_get_fs_info_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_get_fs_info_reply_compare(void *expected, void *result)
{
	ndmp_config_get_fs_info_reply	*expMsg, *repMsg;

	expMsg = (ndmp_config_get_fs_info_reply*)expected;
	repMsg = (ndmp_config_get_fs_info_reply*)result;

	if (expMsg != 0 && repMsg != 0) {

	if (expMsg->error != repMsg->error)
		return (FALSE);

	return (TRUE);

	} else {

	return (FALSE);

	}
}

/*
 * ndmp_config_get_fs_info_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_get_fs_info_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_get_fs_info_reply	*reply;

	reply = (ndmp_config_get_fs_info_reply*)ndmpMsg;

	if (reply != 0) {

	(void) fprintf(out, "error %s \n", ndmpErrorCodeToStr(reply->error));

	print_fs_info(out, (fs_info *)&(reply->fs_info));

	}
}


/*
 * ndmp_config_get_tape_info_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_get_tape_info_request_extract(char *str, void **request_mem)
{
	str = NULL;
	request_mem = 0;
}

/*
 * ndmp_config_get_tape_info_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_get_tape_info_reply_extract(char *str, void **reply_mem)
{
	ndmp_config_get_tape_info_reply	*reply;
	int token_index = 0;

	reply = (ndmp_config_get_tape_info_reply*)malloc
	    (sizeof (ndmp_config_get_tape_info_reply));
	*reply_mem = reply;

	extract_tokens(str);

	if (token_index < token_num)
	reply->error = strToNdmpErrorCode(tokens[token_index]);

	extract_tape_info((tape_info *)&(reply->tape_info), &token_index);

	release_tokens();
}

/*
 * ndmp_config_get_tape_info_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_get_tape_info_reply_compare(void *expected, void *result)
{
	ndmp_config_get_tape_info_reply	*expMsg, *repMsg;

	expMsg = (ndmp_config_get_tape_info_reply*)expected;
	repMsg = (ndmp_config_get_tape_info_reply*)result;

	if (expMsg != 0 && repMsg != 0) {

	if (expMsg->error != repMsg->error)
		return (FALSE);

	return (TRUE);

	} else {
	return (FALSE);
	}
}

/*
 * ndmp_config_get_tape_info_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_get_tape_info_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_get_tape_info_reply	*reply;

	reply = (ndmp_config_get_tape_info_reply*)ndmpMsg;

	if (reply != 0) {

	(void) fprintf(out, "error %s \n", ndmpErrorCodeToStr(reply->error));

	print_tape_info(out, (tape_info *)&(reply->tape_info));

	}

}


/*
 * ndmp_config_get_scsi_info_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_get_scsi_info_request_extract(char *str, void **request_mem)
{
	str = NULL;
	request_mem = 0;
}

/*
 * ndmp_config_get_scsi_info_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_get_scsi_info_reply_extract(char *str, void **reply_mem)
{
	ndmp_config_get_scsi_info_reply	*reply;
	int token_index = 0;

	reply = (ndmp_config_get_scsi_info_reply*)malloc
	    (sizeof (ndmp_config_get_scsi_info_reply));
	*reply_mem = reply;

	extract_tokens(str);

	if (token_index < token_num)
	reply->error = strToNdmpErrorCode(tokens[token_index]);

	extract_scsi_info((scsi_info *)&(reply->scsi_info), &token_index);

	release_tokens();
}

/*
 * ndmp_config_get_scsi_info_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_get_scsi_info_reply_compare(void *expected, void *result)
{
	ndmp_config_get_scsi_info_reply	*expMsg, *repMsg;

	expMsg = (ndmp_config_get_scsi_info_reply*)expected;
	repMsg = (ndmp_config_get_scsi_info_reply*)result;

	if (expMsg != 0 && repMsg != 0) {

	if (expMsg->error != repMsg->error)
		return (FALSE);

	return (TRUE);
	} else {

	return (FALSE);

	}
}

/*
 * ndmp_config_get_scsi_info_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_get_scsi_info_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_get_scsi_info_reply	*reply;

	reply = (ndmp_config_get_scsi_info_reply*)ndmpMsg;

	if (reply != NULL) {

	(void) fprintf(out, "error %s \n", ndmpErrorCodeToStr(reply->error));
	print_scsi_info(out, (scsi_info *)&(reply->scsi_info));

	} else
	(void) fprintf(out, "ndmp_config_get_scsi_info_reply_print: ");
	(void) fprintf(out, "obj is null\n");

}


/*
 * ndmp_config_get_ext_list_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_get_ext_list_request_extract(char *str, void **request_mem)
{
	str = NULL;
	request_mem = NULL;
}

/*
 * ndmp_config_get_ext_list_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_get_ext_list_reply_extract(char *str, void **reply_mem)
{
	ndmp_config_get_ext_list_reply	*reply;
	int token_index = 0;

	reply = (ndmp_config_get_ext_list_reply*)malloc
	    (sizeof (ndmp_config_get_ext_list_reply));
	*reply_mem = reply;

	extract_tokens(str);

	if (token_index < token_num)
	reply->error = strToNdmpErrorCode(tokens[token_index]);

	extract_class_list((class_list *)&(reply->class_list), &token_index);

	release_tokens();
}

/*
 * ndmp_config_get_ext_list_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_get_ext_list_reply_compare(void *expected, void *result)
{
	ndmp_config_get_ext_list_reply	*expMsg, *repMsg;

	expMsg = (ndmp_config_get_ext_list_reply*)expected;
	repMsg = (ndmp_config_get_ext_list_reply*)result;

	if (expMsg != 0 && repMsg != 0) {

	if (expMsg->error != repMsg->error)
		return (FALSE);

	return (TRUE);

	} else {
	return (FALSE);
	}
}

/*
 * ndmp_config_get_ext_list_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_get_ext_list_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_get_ext_list_reply	*reply;

	reply = (ndmp_config_get_ext_list_reply*)ndmpMsg;

	if (reply != 0) {

	(void) fprintf(out, "error %s \n", ndmpErrorCodeToStr(reply->error));

	print_class_list(out, (class_list *)&(reply->class_list));

	}
}


/*
 * ndmp_config_set_ext_list_request_extract() :
 * Creates a request object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **request_mem - Pointer used to return the
 * 		request object.
 */
void
ndmp_config_set_ext_list_request_extract(char *str, void **request_mem)
{
	ndmp_config_set_ext_list_request	*request;
	int					token_index = 0;

	request = (ndmp_config_set_ext_list_request*)malloc
	    (sizeof (ndmp_config_set_ext_list_request));
	*request_mem = request;

	extract_tokens(str);

	if (token_index < token_num)
	extract_ndmp_selected_ext(
	    (ndmp_selected_ext *)&(request->ndmp_selected_ext), &token_index);
}

/*
 * ndmp_config_set_ext_list_reply_extract() :
 * Creates a reply object from the string obtained from
 * the input file.
 *
 * Arguments :
 * 		char * - The string got from input file.
 * 		void **reply_mem - Pointer used to return the
 * 		reply object.
 */
void
ndmp_config_set_ext_list_reply_extract(char *str, void **reply_mem)
{
	ndmp_config_set_ext_list_reply	*reply;
	int					token_index = 0;

	reply = (ndmp_config_set_ext_list_reply*)malloc
	    (sizeof (ndmp_config_set_ext_list_reply));
	*reply_mem = reply;

	extract_tokens(str);

	if (token_index < token_num)
	reply->error = strToNdmpErrorCode(tokens[token_index]);

	release_tokens();
}

/*
 * ndmp_config_set_ext_list_reply_compare() :
 * Compares the reply object from the ndmp server with
 * the expected reply object from the input file.
 *
 * Arguments :
 * 		void *expected - Expected object from the input
 * 		file.
 * 		void *result - Reply object from the ndmp server
 *
 * Return :
 * 		TRUE for success and FALSE for failure.
 */
bool_t
ndmp_config_set_ext_list_reply_compare(void *expected, void *result)
{
	ndmp_config_set_ext_list_reply	*expMsg, *repMsg;

	expMsg = (ndmp_config_set_ext_list_reply*)expected;
	repMsg = (ndmp_config_set_ext_list_reply*)result;

	if (expMsg != 0 && repMsg != 0) {

	if (expMsg->error != repMsg->error)
		return (FALSE);

	return (TRUE);

	} else {
	return (FALSE);
	}
}

/*
 * ndmp_config_set_ext_list_reply_print() :
 * Prints the reply object structure. This object gets
 * printed twice in the program, once when it comes
 * from the ndmp server and second time, the expected
 * reply
 *
 * Arguments :
 * 		FILE * - Log file handle.
 * 		void *ndmpMsg - Ndmp message object got from
 * 		the ndmp server response.
 *
 */
void
ndmp_config_set_ext_list_reply_print(FILE *out, void *ndmpMsg)
{
	ndmp_config_set_ext_list_reply	*reply;

	reply = (ndmp_config_set_ext_list_reply*)ndmpMsg;

	if (reply != 0) {
	(void) fprintf(out, "error %s \n", ndmpErrorCodeToStr(reply->error));
	}
}

/*
 * Enhancement code start
 */

/*
 * get_config_error()
 * Based on the ndmp message passed to the method return the error message.
 * Return :
 *  message - ndmp message.
 */
ndmp_error
get_config_err(void *reply, ndmp_message msg)
{
	switch (msg) {
		case NDMP_CONFIG_GET_HOST_INFO :
			return ((ndmp_config_get_host_info_reply *)
			    reply)->error;
		case NDMP_CONFIG_GET_SERVER_INFO:
			return ((ndmp_config_get_server_info_reply *)
			    reply)->error;
		case NDMP_CONFIG_GET_CONNECTION_TYPE:
			return ((ndmp_config_get_connection_type_reply *)
			    reply)->error;
		case NDMP_CONFIG_GET_AUTH_ATTR:
			return ((ndmp_config_get_auth_attr_reply *)
			    reply)->error;
		case NDMP_CONFIG_GET_BUTYPE_INFO:
			return ((ndmp_config_get_butype_attr_reply *)
			    reply)->error;
		case NDMP_CONFIG_GET_FS_INFO:
			return ((ndmp_config_get_fs_info_reply *)
			    reply)->error;
		case NDMP_CONFIG_GET_TAPE_INFO:
			return ((ndmp_config_get_tape_info_reply *)
			    reply)->error;
		case NDMP_CONFIG_GET_SCSI_INFO:
			return ((ndmp_config_get_scsi_info_reply *)
			    reply)->error;
		case NDMP_CONFIG_GET_EXT_LIST:
			return ((ndmp_config_get_ext_list_reply *)
			    reply)->error;
		case NDMP_CONFIG_SET_EXT_LIST:
			return ((ndmp_config_set_ext_list_reply *)
			    reply)->error;
		default:
			return (-1);
	}
}

/*
 * scsi_get_state_core()
 * Basic method to send scsi get state request to the ndmp server
 */
int
config_core(ndmp_error error, ndmp_message message,
    FILE *outfile, conn_handle *conn)
{
	void *reply_mem = NULL, *req = NULL;
	/* Create and print the object end */
	ndmp_lprintf(outfile, "REQUEST : %s\n", ndmpMessageCodeToStr(message));
	/*  send the request start */
	if (message == NDMP_CONFIG_GET_AUTH_ATTR) {
		req = (ndmp_config_get_auth_attr_request *)malloc
		    (sizeof (ndmp_config_get_auth_attr_request));
		((ndmp_config_get_auth_attr_request *)req)->auth_type =
		    NDMP_AUTH_TEXT;
	} else if (message == NDMP_CONFIG_SET_EXT_LIST) {
		req = (ndmp_config_set_ext_list_request *) malloc
		    (sizeof (ndmp_config_set_ext_list_request));
		ndmp_class_version class;
		class.ext_class_id = 1;
		class.ext_version = 2;
		((ndmp_config_set_ext_list_request *)req)->
		    ndmp_selected_ext.ndmp_selected_ext_len = 1;
		((ndmp_config_set_ext_list_request *)req)->
		    ndmp_selected_ext.ndmp_selected_ext_val = &class;
	}
	if (! process_request((void *)req, message, conn, &reply_mem,
	    logfile)) {
		if (reply_mem != NULL && error >= 0)
			return (SUCCESS);
	}
	else
		return (ERROR);
}

/*
 * inf_config() :
 * The flow of the test case is decided by this method.
 */
int
inf_config(ndmp_error error, char *ndmp_msg,
    FILE *outfile, conn_handle *conn)
{
	int ret = 0;
	ndmp_message message = strToNdmpMessageCode(ndmp_msg);
	(void) ndmp_fprintf(outfile,
	    "Test case name : %s\n", ndmp_msg);
	(void) ndmp_fprintf(outfile,
	    "Error Condition : %s\n", ndmpErrorCodeToStr(error));

	/* Send the request */
	ret = config_core(error, message, outfile, conn);
	print_test_result(ret, outfile);

	return (ret);
}

/*
 * NDMP_CONFIG
 */
int
unit_test_config(host_info *host, FILE *logfile)
{
	conn_handle conn;
	int count;
	char ndmp_msg[10][50] = {
		"NDMP_CONFIG_GET_FS_INFO",
		"NDMP_CONFIG_GET_SERVER_INFO",
		"NDMP_CONFIG_GET_CONNECTION_TYPE",
		"NDMP_CONFIG_GET_AUTH_ATTR",
		"NDMP_CONFIG_GET_BUTYPE_INFO",
		"NDMP_CONFIG_GET_FS_INFO",
		"NDMP_CONFIG_GET_TAPE_INFO",
		"NDMP_CONFIG_GET_SCSI_INFO",
		"NDMP_CONFIG_GET_EXT_LIST",
		"NDMP_CONFIG_SET_EXT_LIST"
	};

	strcpy(host->password, "admn");
	(void) open_connection(host, &conn, logfile);
	for (count = 0; count < 10; count++) {
		(void) ndmp_dprintf(logfile,
		    "unit_test_config:"
		    "Test 1: NDMP_NOT_AUTHORIZED_ERR start\n");
		inf_config(NDMP_NOT_AUTHORIZED_ERR, ndmp_msg[count],
		    logfile, &conn);
		(void) ndmp_dprintf(logfile,
		    "unit_test_config: Test 1: NDMP_NOT_AUTHORIZED_ERR end\n");
	}
	close_connection(&conn, logfile);

	strcpy(host->password, "admin");
	(void) open_connection(host, &conn, logfile);
	for (count = 0; count < 10; count++) {
		(void) ndmp_dprintf(logfile,
		    "unit_test_config: Test 2: NDMP_NO_ERR start\n");
		inf_config(NDMP_NO_ERR, ndmp_msg[count], logfile, &conn);
		(void) ndmp_dprintf(logfile,
		    "unit_test_config: Test 2: NDMP_NO_ERR end\n");
	}
	close_connection(&conn, logfile);

	return (1);
}

#ifdef UNIT_TEST_CONFIG
int
main(int argc, char *argv[])
{
	FILE *logfile = NULL;
	host_info host;
	host.ipAddr = strdup("10.12.178.122");
	host.userName = strdup("admin");
	host.password = strdup("admin");
	host.auth_type = NDMP_AUTH_TEXT;

	/* Open Log file */
	logfile = fopen("unit_test_config.log", "w");
	(void) ndmp_dprintf(logfile, "main: start\n");

	/* unit test config */
	unit_test_config(&host, logfile);

	(void) ndmp_dprintf(stdout, "main: end\n");
	free(host.ipAddr);
	free(host.userName);
	free(host.password);
	fclose(logfile);
	return (1);
}
#endif
