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

#pragma ident	"@(#)ndmp_comm_lib.c	1.3	09/03/30 SMI"

/*
 * The common library functions related to data, mover can be found here.
 * Some of the methods are also used by scsi and tape interface.
 */

#include<stdio.h>
#include<strings.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ndmp.h>
#include <log.h>
#include <ndmp_comm_lib.h>
#include <ndmp_connect.h>

char *tokens[40];
int	token_num;
char	str_ndmp_mover_mode[30];
char	str_ndmp_mover_state[30];
char	str_ndmp_mover_pause_reason[30];
char	str_ndmp_mover_halt_reason[30];
char	str_ndmp_data_operation[30];
char	str_ndmp_data_state[30];
char	str_ndmp_data_halt_reason[30];
char	str_ndmp_auth_type[30];
char	str_ndmp_connection_status_reason[30];
char	str_ndmp_log_type[30];
char	str_ndmp_has_associated_message[30];
char	str_ndmp_recovery_status[30];
extern FILE *logfile;

/*
 * extract_tokens(): Tokenizes the string passed in, based on the
 * delimeter. Used to tokenize the string from the input file.
 *
 * Arguments :
 * 	char * - String to be tokenized.
 */
void
extract_tokens(char *str)
{
	char *delimeter = " ,\n";
	char *token;

	token_num = 0;
	token = strtok(str, delimeter);
	if (token != NULL)
		while ((token = strtok(NULL, delimeter)) != NULL)
			tokens[token_num++] = strdup(token);

	(void) ndmp_dprintf(logfile,
	    "extract_tokens: token_num %d \n", token_num);

}

/*
 * release_tokens() : Releases the memory held by the string token
 * pointers. This is done once the token is used.
 */
void
release_tokens(void)
{
	int	token_cntr;

	for (token_cntr = 0; token_cntr < token_num; ++token_cntr)
		free(tokens[token_cntr]);
	token_num = 0;
}

/* print functions */

/*
 * print_ndmp_u_quad() : Prints the ndmp_u_quad structure.
 */
void
print_ndmp_u_quad(FILE *outstream, ndmp_u_quad quad_t)
{
	(void) fprintf(outstream, "high: %ld; low: %ld\n",
	    quad_t.high, quad_t.low);
}

/*
 * print_ndmp_pval() : Prints ndmp_pval structure.
 */
void
print_ndmp_pval(FILE *outstream, ndmp_pval *pval)
{
	if (pval != 0 && pval->name != 0)
	(void) fprintf(outstream, "name: %s\n", pval->name);
	if (pval != 0 && pval->value != 0)
	(void) fprintf(outstream, "value: %s\n", pval->value);
}

/*
 * print_ndmp_tcp_addr() : Print ndmp_tcp_addr structure.
 */
void
print_ndmp_tcp_addr(FILE *outstream, ndmp_tcp_addr *tcp_addr)
{
		char str[100];
	(void) (void) memset(str, '\0', strlen(str));
	(void) fprintf(outstream, "ip_addr: %s\n",
	    inet_ntop(AF_INET, &(tcp_addr->ip_addr),  str, sizeof (str)));
	(void) fprintf(outstream, "port: %d\n", tcp_addr->port);
	(void) fprintf(outstream, "addr_env.addr_env_len: %d\n",
	    tcp_addr->addr_env.addr_env_len);
	int i = 0;
	for (i = 0; i < tcp_addr->addr_env.addr_env_len; i++) {
		print_ndmp_pval(outstream, tcp_addr->addr_env.addr_env_val);
		if (i < (tcp_addr->addr_env.addr_env_len - 1))
		(tcp_addr->addr_env.addr_env_val)++;
	}
}

/*
 * print_ndmp_addr_type() : Prints ndmp_addr_type structure.
 */
void
print_ndmp_addr_type(FILE *outstream, ndmp_addr_type addr)
{

	switch (addr) {
		case NDMP_ADDR_LOCAL:
			(void) fprintf(outstream, "NDMP_ADDR_LOCAL\n");
			break;
		case NDMP_ADDR_TCP:
			(void) fprintf(outstream, "NDMP_ADDR_TCP\n");
			break;
		case NDMP_ADDR_RESERVED:
			(void) fprintf(outstream, "NDMP_ADDR_RESERVED\n");
			break;
		case NDMP_ADDR_IPC:
			(void) fprintf(outstream, "NDMP_ADDR_IPC\n");
			break;
	}
}


/*
 * print_ndmp_addr() : Prints ndmp_addr structure.
 */
void
print_ndmp_addr(FILE *outstream, ndmp_addr *addr)
{
	print_ndmp_addr_type(outstream, addr->addr_type);
	switch (addr->addr_type) {
		case NDMP_ADDR_TCP:
			(void) fprintf(outstream, "tcp_addr.tcp_addr_len: %d\n",
			    addr->ndmp_addr_u.tcp_addr.tcp_addr_len);
			(void) fprintf(outstream, "tcp_addr.tcp_addr_val:\n");
			if (addr->ndmp_addr_u.tcp_addr.tcp_addr_val != 0)
				print_ndmp_tcp_addr(outstream,
				    addr->ndmp_addr_u.tcp_addr.tcp_addr_val);
			break;
		case NDMP_ADDR_IPC:
			(void) fprintf(outstream,
			    "ipc_addr.comm_data.comm_data_len: %d\n",
			    addr->ndmp_addr_u.ipc_addr.comm_data.comm_data_len);
			(void) fprintf(outstream,
			    "ipc_addr.comm_data.comm_data_val: %s\n",
			    addr->ndmp_addr_u.ipc_addr.comm_data.comm_data_val);
			break;
		default:
			break;
	}
}

/*
 * print_ndmp_data_halt_reason() : Prints ndmp_data_halt_reason structure.
 */
void
print_ndmp_data_halt_reason(FILE *outstream,
		ndmp_data_halt_reason reason)
{
	(void) fprintf(outstream, "addr_type: ");
	switch (reason) {
		case NDMP_DATA_HALT_NA:
			(void) fprintf(outstream, "NDMP_DATA_HALT_NA\n");
			break;
		case NDMP_DATA_HALT_SUCCESSFUL:
			(void) fprintf(outstream,
			    "NDMP_DATA_HALT_SUCCESSFUL\n");
			break;
		case NDMP_DATA_HALT_ABORTED:
			(void) fprintf(outstream, "NDMP_DATA_HALT_ABORTED\n");
			break;
		case NDMP_DATA_HALT_INTERNAL_ERROR:
			(void) fprintf(outstream,
			    "NDMP_DATA_HALT_INTERNAL_ERROR\n");
			break;
		case NDMP_DATA_HALT_CONNECT_ERROR:
			(void) fprintf(outstream,
			    "NDMP_DATA_HALT_CONNECT_ERROR\n");
			break;
		default:
			(void) fprintf(outstream, " No reason \n");
			break;
	}
}

/*
 * ndmpMoverStateToStr() : Converts ndmp mover state code to ndmp mover
 * state string.
 */
char *
ndmpMoverStateToStr(ndmp_mover_state state)
{
	str_ndmp_mover_state[0] = '\0';
	switch (state) {
		case NDMP_MOVER_STATE_IDLE:
			(void) strcpy(str_ndmp_mover_state,
			    "NDMP_MOVER_STATE_IDLE");
			break;
		case NDMP_MOVER_STATE_LISTEN:
			(void) strcpy(str_ndmp_mover_state,
			    "NDMP_MOVER_STATE_LISTEN");
			break;
		case NDMP_MOVER_STATE_ACTIVE:
			(void) strcpy(str_ndmp_mover_state,
			    "NDMP_MOVER_STATE_ACTIVE");
			break;
		case NDMP_MOVER_STATE_PAUSED:
			(void) strcpy(str_ndmp_mover_state,
			    "NDMP_MOVER_STATE_PAUSED");
			break;
		case NDMP_MOVER_STATE_HALTED:
			(void) strcpy(str_ndmp_mover_state,
			    "NDMP_MOVER_STATE_HALTED");
			break;
		default:
			(void) strcpy(str_ndmp_mover_state, "ERROR");
	}
	return (str_ndmp_mover_state);
}

/*
 * ndmpMoverModeToStr() : Converts ndmp mover mode code to ndmp mover
 * mode string.
 */
char *
ndmpMoverModeToStr(ndmp_mover_mode mode)
{
	str_ndmp_mover_mode[0] = '\0';
	switch (mode) {
		case NDMP_MOVER_MODE_READ:
			(void) strcpy(str_ndmp_mover_mode,
			    "NDMP_MOVER_MODE_READ");
			break;
		case NDMP_MOVER_MODE_WRITE:
			(void) strcpy(str_ndmp_mover_mode,
			    "NDMP_MOVER_MODE_WRITE");
			break;
		case NDMP_MOVER_MODE_NOACTION:
			(void) strcpy(str_ndmp_mover_mode,
			    "NDMP_MOVER_MODE_NOACTION");
			break;
		default:
			(void) strcpy(str_ndmp_mover_mode, "ERROR");
	}
	return (str_ndmp_mover_mode);
}

/*
 * ndmpMoverPauseReasonToStr() : COnverts ndmp mover pause reason
 * code to ndmp mover pause reason string.
 */
char *
ndmpMoverPauseReasonToStr(ndmp_mover_pause_reason reason)
{
	str_ndmp_mover_pause_reason[0] = '\0';
	switch (reason) {
		case NDMP_MOVER_PAUSE_NA:
			(void) strcpy(str_ndmp_mover_pause_reason,
			    "NDMP_MOVER_PAUSE_NA");
			break;
		case NDMP_MOVER_PAUSE_EOM:
			(void) strcpy(str_ndmp_mover_pause_reason,
			    "NDMP_MOVER_PAUSE_EOM");
			break;
		case NDMP_MOVER_PAUSE_EOF:
			(void) strcpy(str_ndmp_mover_pause_reason,
			    "NDMP_MOVER_PAUSE_EOF");
			break;
		case NDMP_MOVER_PAUSE_SEEK:
			(void) strcpy(str_ndmp_mover_pause_reason,
			    "NDMP_MOVER_PAUSE_SEEK");
			break;
		case NDMP_MOVER_PAUSE_EOW:
			(void) strcpy(str_ndmp_mover_pause_reason,
			    "NDMP_MOVER_PAUSE_EOW");
			break;
	}

	return (str_ndmp_mover_pause_reason);
}

/*
 * ndmpMoverHaltReasonToStr() : Converts ndmp mover halt reason code
 * to ndmp mover halt reason string.
 */
char *
ndmpMoverHaltReasonToStr(ndmp_mover_halt_reason reason)
{
	str_ndmp_mover_halt_reason[0] = '\0';
	switch (reason) {
		case NDMP_MOVER_HALT_NA:
			(void) strcpy(str_ndmp_mover_halt_reason,
			    "NDMP_MOVER_HALT_NA");
			break;
		case NDMP_MOVER_HALT_CONNECT_CLOSED:
			(void) strcpy(str_ndmp_mover_halt_reason,
			    "NDMP_MOVER_HALT_CONNECT_CLOSED");
			break;
		case NDMP_MOVER_HALT_ABORTED:
			(void) strcpy(str_ndmp_mover_halt_reason,
			    "NDMP_MOVER_HALT_ABORTED");
			break;
		case NDMP_MOVER_HALT_INTERNAL_ERROR:
			(void) strcpy(str_ndmp_mover_halt_reason,
			    "NDMP_MOVER_HALT_INTERNAL_ERROR");
			break;
		case NDMP_MOVER_HALT_CONNECT_ERROR:
			(void) strcpy(str_ndmp_mover_halt_reason,
			    "NDMP_MOVER_HALT_CONNECT_ERROR");
			break;
		case NDMP_MOVER_HALT_MEDIA_ERROR:
			(void) strcpy(str_ndmp_mover_halt_reason,
			    "NDMP_MOVER_HALT_MEDIA_ERROR");
			break;
	}

	return (str_ndmp_mover_halt_reason);
}

/*
 * ndmpDataOperationToStr() : Converts ndmp data operation code to ndmp
 * data openration string.
 */
char *
ndmpDataOperationToStr(ndmp_data_operation operation)
{
	str_ndmp_data_operation[0] = '\0';
	switch (operation) {
		case NDMP_DATA_OP_NOACTION:
			(void) strcpy(str_ndmp_data_operation,
			    "NDMP_DATA_OP_NOACTION");
			break;
		case NDMP_DATA_OP_BACKUP:
			(void) strcpy(str_ndmp_data_operation,
			    "NDMP_DATA_OP_BACKUP");
			break;
		case NDMP_DATA_OP_RECOVER:
			(void) strcpy(str_ndmp_data_operation,
			    "NDMP_DATA_OP_RECOVER");
			break;
		case NDMP_DATA_OP_RECOVER_FILEHIST:
			(void) strcpy(str_ndmp_data_operation,
			    "NDMP_DATA_OP_RECOVER_FILEHIST");
			break;
	}
	return (str_ndmp_data_operation);
}

/*
 * ndmpDataStateToStr() : Converts ndmp data state code to
 * ndmp data state sting.
 */
char *
ndmpDataStateToStr(ndmp_data_state state)
{
	str_ndmp_data_state[0] = '\0';
	switch (state) {
		case NDMP_DATA_STATE_IDLE:
			(void) strcpy(str_ndmp_data_state,
			    "NDMP_DATA_STATE_IDLE");
			break;
		case NDMP_DATA_STATE_ACTIVE:
			(void) strcpy(str_ndmp_data_state,
			    "NDMP_DATA_STATE_ACTIVE");
			break;
		case NDMP_DATA_STATE_HALTED:
			(void) strcpy(str_ndmp_data_state,
			    "NDMP_DATA_STATE_HALTED");
			break;
		case NDMP_DATA_STATE_LISTEN:
			(void) strcpy(str_ndmp_data_state,
			    "NDMP_DATA_STATE_LISTEN");
			break;
		case NDMP_DATA_STATE_CONNECTED:
			(void) strcpy(str_ndmp_data_state,
			    "NDMP_DATA_STATE_CONNECTED");
			break;
	}
	return (str_ndmp_data_state);
}

/*
 * ndmpDataHaltReasonToStr() : Converts ndmp data halt reason code to
 * ndmp data halt reason string.
 */
char *
ndmpDataHaltReasonToStr(ndmp_data_halt_reason reason)
{
	str_ndmp_data_halt_reason[0] = '\0';
	switch (reason) {
		case NDMP_DATA_HALT_NA:
			(void) strcpy(str_ndmp_data_halt_reason,
			    "NDMP_DATA_HALT_NA");
			break;
		case NDMP_DATA_HALT_SUCCESSFUL:
			(void) strcpy(str_ndmp_data_halt_reason,
			    "NDMP_DATA_HALT_SUCCESSFUL");
			break;
		case NDMP_DATA_HALT_ABORTED:
			(void) strcpy(str_ndmp_data_halt_reason,
			    "NDMP_DATA_HALT_ABORTED");
			break;
		case NDMP_DATA_HALT_INTERNAL_ERROR:
			(void) strcpy(str_ndmp_data_halt_reason,
			    "NDMP_DATA_HALT_INTERNAL_ERROR");
			break;
		case NDMP_DATA_HALT_CONNECT_ERROR:
			(void) strcpy(str_ndmp_data_halt_reason,
			    "NDMP_DATA_HALT_CONNECT_ERROR");
			break;
	}
	return (str_ndmp_data_halt_reason);
}

/*
 * ndmpConnectionStatusReasonToStr() : Converts ndmp connection status
 * reason code to ndmp connection status reason string.
 */
char *
ndmpConnectionStatusReasonToStr(ndmp_connection_status_reason reason)
{
	str_ndmp_connection_status_reason[0] = '\0';
	switch (reason) {
		case NDMP_CONNECTED:
			(void) strcpy(str_ndmp_connection_status_reason,
			    "NDMP_CONNECTED");
			break;
		case NDMP_SHUTDOWN:
			(void) strcpy(str_ndmp_connection_status_reason,
			    "NDMP_SHUTDOWN");
			break;
		case NDMP_REFUSED:
			(void) strcpy(str_ndmp_connection_status_reason,
			    "NDMP_REFUSED");
			break;
	}
	return (str_ndmp_data_halt_reason);
}

/*
 * ndmpAuthTypeToStr() : Converts ndmp auth type code to ndmp auth type
 * string.
 */
char *
ndmpAuthTypeToStr(ndmp_auth_type auth_type)
{
	str_ndmp_auth_type[0] = '\0';
	switch (auth_type) {
		case NDMP_AUTH_NONE:
			(void) strcpy(str_ndmp_auth_type, "NDMP_AUTH_NONE");
			break;
		case NDMP_AUTH_TEXT:
			(void) strcpy(str_ndmp_auth_type, "NDMP_AUTH_TEXT");
			break;
		case NDMP_AUTH_MD5:
			(void) strcpy(str_ndmp_auth_type, "NDMP_AUTH_MD5");
			break;
	}
	return (str_ndmp_auth_type);
}

/*
 * ndmpLogTypeToStr() : Converts ndmp log type code to ndmp log type string.
 */
char *
ndmpLogTypeToStr(ndmp_log_type log_type)
{
	str_ndmp_log_type[0] = '\0';
	switch (log_type) {
		case NDMP_LOG_NORMAL:
			(void) strcpy(str_ndmp_log_type, "NDMP_LOG_NORMAL");
			break;
		case NDMP_LOG_DEBUG:
			(void) strcpy(str_ndmp_log_type, "NDMP_LOG_DEBUG");
			break;
		case NDMP_LOG_ERROR:
			(void) strcpy(str_ndmp_log_type, "NDMP_LOG_ERROR");
			break;
		case NDMP_LOG_WARNING:
			(void) strcpy(str_ndmp_log_type, "NDMP_LOG_WARNING");
			break;
	}
	return (str_ndmp_log_type);
}

/*
 * ndmpHasAssociatedMsgToStr() : COnverts ndmp associated message to
 * ndmp associated message string.
 */
char *
ndmpHasAssociatedMsgToStr(ndmp_has_associated_message has_associated_message)
{
	str_ndmp_has_associated_message[0] = '\0';
	switch (has_associated_message) {
		case NDMP_NO_ASSOCIATED_MESSAGE:
			(void) strcpy(str_ndmp_has_associated_message,
			    "NDMP_NO_ASSOCIATED_MESSAGE");
			break;
		case NDMP_HAS_ASSOCIATED_MESSAGE:
			(void) strcpy(str_ndmp_has_associated_message,
			    "NDMP_HAS_ASSOCIATED_MESSAGE");
			break;
	}
	return (str_ndmp_has_associated_message);
}

/*
 * ndmpRecoveryStatusToStr() : Converts ndmp Recovery Status code to
 * ndmp Recovery Status string.
 */
char *
ndmpRecoveryStatusToStr(ndmp_recovery_status recovery_status)
{
	str_ndmp_recovery_status[0] = '\0';
	switch (recovery_status) {
		case NDMP_RECOVERY_SUCCESSFUL:
			(void) strcpy(str_ndmp_recovery_status,
			    "NDMP_RECOVERY_SUCCESSFUL");
			break;
		case NDMP_RECOVERY_FAILED_PERMISSION:
			(void) strcpy(str_ndmp_recovery_status,
			    "NDMP_RECOVERY_FAILED_PERMISSION");
			break;
		case NDMP_RECOVERY_FAILED_NOT_FOUND:
			(void) strcpy(str_ndmp_recovery_status,
			    "NDMP_RECOVERY_FAILED_NOT_FOUND");
			break;
		case NDMP_RECOVERY_FAILED_NO_DIRECTORY:
			(void) strcpy(str_ndmp_recovery_status,
			    "NDMP_RECOVERY_FAILED_NO_DIRECTORY");
			break;
		case NDMP_RECOVERY_FAILED_OUT_OF_MEMORY:
			(void) strcpy(str_ndmp_recovery_status,
			    "NDMP_RECOVERY_FAILED_OUT_OF_MEMORY");
			break;
		case NDMP_RECOVERY_FAILED_IO_ERROR:
			(void) strcpy(str_ndmp_recovery_status,
			    "NDMP_RECOVERY_FAILED_IO_ERROR");
			break;
		case NDMP_RECOVERY_FAILED_UNDEFINED_ERROR:
			(void) strcpy(str_ndmp_recovery_status,
			    "NDMP_RECOVERY_FAILED_UNDEFINED_ERROR");
			break;
		case NDMP_RECOVERY_FAILED_FILE_PATH_EXISTS:
			(void) strcpy(str_ndmp_recovery_status,
			    "NDMP_RECOVERY_FAILED_FILE_PATH_EXISTS");
			break;
	}
	return (str_ndmp_recovery_status);
}

/* compare functions */

/*
 * compare_ndmp_u_quad() : Compares ndmp_u_quad structure.
 */
bool_t
compare_ndmp_u_quad(ndmp_u_quad a, ndmp_u_quad b)
{
	return (a.high == b.high && a.low == b.low);
}

/*
 * compare_ndmp_pval() : Compares ndmp_pval structure.
 */
bool_t
compare_ndmp_pval(ndmp_pval *a, ndmp_pval *b)
{
	if (strcmp(a->name, b->name))
		return (FALSE);
	if (strcmp(a->value, b->value))
		return (FALSE);
	return (TRUE);
}

/*
 * compare_ndmp_tcp_addr() : Compares ndmp_tcp_addr structure.
 */
bool_t
compare_ndmp_tcp_addr(ndmp_tcp_addr *a, ndmp_tcp_addr *b)
{
	if (a->ip_addr != b->ip_addr)
		return (FALSE);
	if (a->port != b->port)
		return (FALSE);
	if (a->addr_env.addr_env_len != b->addr_env.addr_env_len)
		return (FALSE);
	if (! compare_ndmp_pval(a->addr_env.addr_env_val,
	    b->addr_env.addr_env_val))
		return (FALSE);
	return (TRUE);
}

/*
 * compare_ndmp_ipc_addr() : Compares ndmp_ipc_addr structure.
 */
bool_t
compare_ndmp_ipc_addr(ndmp_ipc_addr a, ndmp_ipc_addr b)
{
	if (a.comm_data.comm_data_len != b.comm_data.comm_data_len)
		return (FALSE);
	if (strcmp(a.comm_data.comm_data_val, b.comm_data.comm_data_val))
		return (FALSE);
	return (TRUE);
}

/*
 * compare_ndmp_addr() : Compares ndmp_addr structure.
 */
bool_t
compare_ndmp_addr(ndmp_addr *a, ndmp_addr *b)
{
	if (a->addr_type != b->addr_type)
		return (FALSE);
	switch (a->addr_type) {
		case NDMP_ADDR_TCP:
			if (a->ndmp_addr_u.tcp_addr.tcp_addr_len !=
			    b->ndmp_addr_u.tcp_addr.tcp_addr_len)
				return (FALSE);
			if (! compare_ndmp_tcp_addr
			    (a->ndmp_addr_u.tcp_addr.tcp_addr_val,
			    b->ndmp_addr_u.tcp_addr.tcp_addr_val))
				return (FALSE);
			break;
		case NDMP_ADDR_IPC:
			if (! compare_ndmp_ipc_addr
			    (a->ndmp_addr_u.ipc_addr,
			    b->ndmp_addr_u.ipc_addr))
				return (FALSE);
			break;
		default:
			return (FALSE);
	}
	return (TRUE);
}

/* extract functions */

/*
 * extract_ndmp_data_halt_reason() : Checks the token with ndmp
 * data halt reason string and returns the appropriate code
 * associated with it.
 *
 * Returns :
 * 	ndmp_data_halt_reason - Ndmp data halt reason code.
 */
ndmp_data_halt_reason
extract_ndmp_data_halt_reason(int token_index)
{
	if (! (strcmp(tokens[token_index], "NDMP_DATA_HALT_NA")))
		return (NDMP_DATA_HALT_NA);
	if (! (strcmp(tokens[token_index], "NDMP_DATA_HALT_SUCCESSFUL")))
		return (NDMP_DATA_HALT_SUCCESSFUL);
	if (! (strcmp(tokens[token_index], "NDMP_DATA_HALT_ABORTED")))
		return (NDMP_DATA_HALT_ABORTED);
	if (! (strcmp(tokens[token_index], "NDMP_DATA_HALT_INTERNAL_ERROR")))
		return (NDMP_DATA_HALT_INTERNAL_ERROR);
	if (! (strcmp(tokens[token_index], "NDMP_DATA_HALT_CONNECT_ERROR")))
		return (NDMP_DATA_HALT_CONNECT_ERROR);
	return (NDMP_DATA_HALT_NA);
}

void
extract_ndmp_u_quad(int *token_index, ndmp_u_quad *a)
{
	(void) memset(a, '\0', sizeof (ndmp_u_quad));

	if (*token_index < token_num)
		a->high = atol(tokens[(*token_index)++]);

	if (*token_index < token_num)
		a->low = atol(tokens[(*token_index)++]);
}

/*
 * extract_ndmp_pval() : Extracts the ndmp pval stucture values from the
 * tokens array, using the token index. Puts the caluse extracted in the
 * ndmp pval pointer.
 *
 * Returns :
 * 	int - The next token index.
 */
int
extract_ndmp_pval(int token_index, ndmp_pval *a)
{
	int	original_token_index = token_index;
	(void) memset(a, '\0', sizeof (ndmp_pval));
	if (token_index < token_num) {
		a->name = strdup(tokens[token_index++]);
	} else {
		return (token_index - original_token_index);
	}

	if (token_index < token_num)
		a->value = strdup(tokens[token_index++]);
	else
		return (token_index - original_token_index);
	(void) ndmp_dprintf(logfile,
	    "extract_ndmp_pval: a->name %s \n", a->name);
	(void) ndmp_dprintf(logfile,
	    "extract_ndmp_pval: a->value %s \n", a->value);
	return (0);
}

/*
 * extract_ndmp_tcp_addr() : Extracts ndmp_tcp_addr structure from
 * the tokens array and puts it in ndmp_tcp_addr structure pointer.
 *
 * Returns :
 * 	int - The next token index.
 */
int
extract_ndmp_tcp_addr(int token_index,	ndmp_tcp_addr *a)
{
	int	initial_token_index = token_index;
	(void) memset(a, '\0', sizeof (ndmp_tcp_addr));
	if (token_index < token_num) {
		char *str1;
		str1 = strdup(tokens[token_index++]);

		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_tcp_addr: b4 ip %s\n", str1);

		a->ip_addr = inet_addr(str1);
		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_tcp_addr: ip 0x%x\n", a->ip_addr);


	} else
		return (token_index - initial_token_index);

	if (token_index < token_num) {
		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_tcp_addr: b4 port  \n");

		a->port = htonl(atol(tokens[token_index++]));
		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_tcp_addr:port -> %d \n", a->port);

	} else
		return (token_index - initial_token_index);

	if (token_index < token_num)
		a->addr_env.addr_env_len = atoi(tokens[token_index++]);
	else
		return (token_index - initial_token_index);

	if (token_index < token_num) {
		a->addr_env.addr_env_val = (ndmp_pval*)malloc
		    (sizeof (ndmp_pval));
		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_tcp_addr: token_index %d \n", token_index);

		token_index += extract_ndmp_pval
		    (token_index, a->addr_env.addr_env_val);

		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_tcp_addr: token_index %d \n", token_index);

	} else
		return (token_index - initial_token_index);
	return (0);
}

/*
 * extract_ndmp_addr_type() : Extracts ndmp_addr_type structure from
 * the tokens array and puts it in the ndmp_addr_type structure pointer.
 */
void
extract_ndmp_addr_type(int token_index, ndmp_addr_type* addr_type)
{

	(void) ndmp_dprintf(logfile, "extract_ndmp_addr_type: start \n");

	(void) memset(addr_type, '\0', sizeof (ndmp_addr_type));
	if (token_index >= token_num)
		return;
	if (! (strcmp(tokens[token_index], "NDMP_ADDR_LOCAL"))) {

		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_addr_type:NDMP_ADDR_LOCAL \n");

		*addr_type = NDMP_ADDR_LOCAL;
	} else if (! (strcmp(tokens[token_index], "NDMP_ADDR_TCP"))) {
		*addr_type = NDMP_ADDR_TCP;

		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_addr_type: NDMP_ADDR_TCP\n");

	} else if (! (strcmp(tokens[token_index], "NDMP_ADDR_RESERVED"))) {
		*addr_type = NDMP_ADDR_RESERVED;

		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_addr_type:NDMP_ADDR_RESERVED \n");

	} else if (! (strcmp(tokens[token_index], "NDMP_ADDR_IPC"))) {
		*addr_type = NDMP_ADDR_IPC;

		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_addr_type:NDMP_ADDR_IPC \n");

	} else
		*addr_type = 2;
}

/*
 * extract_ndmp_addr() : Extracts ndmp_addr structure from the tokens
 * array and puts it in the ndmp_addr structure pointer.
 */
int
extract_ndmp_addr(int token_index, ndmp_addr *a)
{
	int	initial_token_index = token_index;
	(void) memset(a, '\0', sizeof (ndmp_addr));

	extract_ndmp_addr_type(token_index++, &(a->addr_type));
	if (token_index < token_num) {


		(void) ndmp_dprintf(logfile,
		    "extract_ndmp_addr: in if () a->addr_type is %d \n",
		    a->addr_type);

		switch (a->addr_type) {
			case NDMP_ADDR_IPC:
				a->ndmp_addr_u.ipc_addr.comm_data.comm_data_len
				    = atoi(tokens[token_index++]);
				if (token_index < token_num)
				a->ndmp_addr_u.ipc_addr.comm_data.comm_data_val
				    = strdup(tokens[token_index++]);
				break;
			case NDMP_ADDR_TCP:

	(void) ndmp_dprintf(logfile,
	    "extract_ndmp_addr: NDMP_ADDR_TCP \n");

				a->ndmp_addr_u.tcp_addr.tcp_addr_len =
				    atoi(tokens[token_index++]);
				a->ndmp_addr_u.tcp_addr.tcp_addr_val =
				    (ndmp_tcp_addr*)malloc
				    (sizeof (ndmp_tcp_addr));
				if (token_index < token_num)
					token_index += extract_ndmp_tcp_addr(
					    token_index, a->
					    ndmp_addr_u.tcp_addr.tcp_addr_val);
				break;
			case NDMP_ADDR_LOCAL:
				break;
			default:

	(void) ndmp_dprintf(logfile,
	    "extract_ndmp_addr: NDMP_ADDR_LOCAL\n");

				break;
		}
	}

	(void) ndmp_dprintf(logfile, "extract_ndmp_addr: end \n");

	return (token_index - initial_token_index);
}

/*
 * strToNdmpLogType() : Converts ndmp_log_type string in to ndmp_log_type
 * code.
 *
 * Returns :
 * 	ndmp_log_type - The ndmp_log_type code associated with the string.
 */
ndmp_log_type
strToNdmpLogType(int token_index)
{
	if (! (strcmp(tokens[token_index], "NDMP_LOG_NORMAL")))
		return (NDMP_LOG_NORMAL);
	if (! (strcmp(tokens[token_index], "NDMP_LOG_DEBUG")))
		return (NDMP_LOG_DEBUG);
	if (! (strcmp(tokens[token_index], "NDMP_LOG_ERROR")))
		return (NDMP_LOG_ERROR);
	if (! (strcmp(tokens[token_index], "NDMP_LOG_WARNING")))
		return (NDMP_LOG_WARNING);
	return (NDMP_LOG_NORMAL);
}

/*
 * strToNdmpHasAssociatedMsg() : Converts ndmp associated message string to
 * ndmp associated message code.
 *
 * Returns :
 * 	ndmp_has_associated_message - ndmp associated message code.
 */
ndmp_has_associated_message
strToNdmpHasAssociatedMsg(int token_index)
{
	if (! (strcmp(tokens[token_index], "NDMP_NO_ASSOCIATED_MESSAGE")))
		return (NDMP_NO_ASSOCIATED_MESSAGE);
	if (! (strcmp(tokens[token_index], "NDMP_HAS_ASSOCIATED_MESSAGE")))
		return (NDMP_HAS_ASSOCIATED_MESSAGE);
	return (NDMP_NO_ASSOCIATED_MESSAGE);
}

/*
 * strToNdmpRecoveryStatus() : Converts ndmp recovery status string to
 * ndmp recovery status code.
 */
ndmp_recovery_status
strToNdmpRecoveryStatus(int token_index)
{
	if (! (strcmp(tokens[token_index], "NDMP_RECOVERY_SUCCESSFUL")))
		return (NDMP_RECOVERY_SUCCESSFUL);
	if (! (strcmp(tokens[token_index], "NDMP_RECOVERY_FAILED_PERMISSION")))
		return (NDMP_RECOVERY_FAILED_PERMISSION);
	if (! (strcmp(tokens[token_index], "NDMP_RECOVERY_FAILED_NOT_FOUND")))
		return (NDMP_RECOVERY_FAILED_NOT_FOUND);
	if (! (strcmp(tokens[token_index],
	    "NDMP_RECOVERY_FAILED_NO_DIRECTORY")))
		return (NDMP_RECOVERY_FAILED_NO_DIRECTORY);
	if (! (strcmp(tokens[token_index],
	    "NDMP_RECOVERY_FAILED_OUT_OF_MEMORY")))
		return (NDMP_RECOVERY_FAILED_OUT_OF_MEMORY);
	if (! (strcmp(tokens[token_index], "NDMP_RECOVERY_FAILED_IO_ERROR")))
		return (NDMP_RECOVERY_FAILED_IO_ERROR);
	if (! (strcmp(tokens[token_index],
	    "NDMP_RECOVERY_FAILED_UNDEFINED_ERROR")))
		return (NDMP_RECOVERY_FAILED_UNDEFINED_ERROR);
	if (! (strcmp(tokens[token_index],
	    "NDMP_RECOVERY_FAILED_FILE_PATH_EXISTS")))
		return (NDMP_RECOVERY_FAILED_FILE_PATH_EXISTS);
	return (NDMP_RECOVERY_SUCCESSFUL);
}

/*
 * strToNdmpMoverMode() : Converts ndmp mover mode string from the tokens
 * array to ndmp mover mode code.
 *
 * Returns :
 * 	ndmp_mover_mode - ndmp_mover_mode code.
 */
ndmp_mover_mode
strToNdmpMoverMode(char *str)
{
	if (! (strcmp(str, "NDMP_MOVER_MODE_READ")))
		return (NDMP_MOVER_MODE_READ);
	else if (! (strcmp(str, "NDMP_MOVER_MODE_WRITE")))
		return (NDMP_MOVER_MODE_WRITE);
	else if (! (strcmp(str, "NDMP_MOVER_MODE_NOACTION")))
		return (NDMP_MOVER_MODE_NOACTION);
	else
		return (0);
}

/*
 * strToNdmpMoverState() : Converts ndmp_mover_state string from the tokens
 * array to ndmp_mover_state code.
 *
 * Returns :
 * 	ndmp_mover_state - ndmp_mover_state code.
 */
ndmp_mover_state
strToNdmpMoverState(char *str)
{
	if (! (strcmp(str, "NDMP_MOVER_STATE_IDLE")))
		return (NDMP_MOVER_STATE_IDLE);
	else if (! (strcmp(str, "NDMP_MOVER_STATE_LISTEN")))
		return (NDMP_MOVER_STATE_LISTEN);
	else if (! (strcmp(str, "NDMP_MOVER_STATE_ACTIVE")))
		return (NDMP_MOVER_STATE_ACTIVE);
	else if (! (strcmp(str, "NDMP_MOVER_STATE_PAUSED")))
		return (NDMP_MOVER_STATE_PAUSED);
	else if (! (strcmp(str, "NDMP_MOVER_STATE_HALTED")))
		return (NDMP_MOVER_STATE_HALTED);
	else
		return (0);
}

/*
 * strToNdmpMoverPauseReason() : Converts ndmp_mover_pause_reason
 * string from the tokens array to ndmp_mover_pause_reason code.
 *
 * Returns :
 * 	ndmp_mover_pause_reason - ndmp_mover_pause_reason code.
 */
ndmp_mover_pause_reason
strToNdmpMoverPauseReason(char *str)
{
	if (! (strcmp(str, "NDMP_MOVER_PAUSE_NA")))
		return (NDMP_MOVER_PAUSE_NA);
	else if (! (strcmp(str, "NDMP_MOVER_PAUSE_EOM")))
		return (NDMP_MOVER_PAUSE_EOM);
	else if (! (strcmp(str, "NDMP_MOVER_PAUSE_EOF")))
		return (NDMP_MOVER_PAUSE_EOF);
	else if (! (strcmp(str, "NDMP_MOVER_PAUSE_SEEK")))
		return (NDMP_MOVER_PAUSE_SEEK);
	else if (! (strcmp(str, "NDMP_MOVER_PAUSE_EOW")))
		return (NDMP_MOVER_PAUSE_EOW);
	else
		return (0);
}

/*
 * strToNdmpMoverHaltReason() : Converts ndmp_mover_halt_reason string from
 * the tokens array to ndmp_mover_halt_reason code.
 *
 * Returns :
 * 	ndmp_mover_halt_reason - ndmp_mover_halt_reason code.
 */
ndmp_mover_halt_reason
strToNdmpMoverHaltReason(char *str)
{
	if (! (strcmp(str, "NDMP_MOVER_HALT_NA")))
		return (NDMP_MOVER_HALT_NA);
	else if (! (strcmp(str, "NDMP_MOVER_HALT_CONNECT_CLOSED")))
		return (NDMP_MOVER_HALT_CONNECT_CLOSED);
	else if (! (strcmp(str, "NDMP_MOVER_HALT_ABORTED")))
		return (NDMP_MOVER_HALT_ABORTED);
	else if (! (strcmp(str, "NDMP_MOVER_HALT_INTERNAL_ERROR")))
		return (NDMP_MOVER_HALT_INTERNAL_ERROR);
	else if (! (strcmp(str, "NDMP_MOVER_HALT_CONNECT_ERROR")))
		return (NDMP_MOVER_HALT_CONNECT_ERROR);
	else if (! (strcmp(str, "NDMP_MOVER_HALT_MEDIA_ERROR")))
		return (NDMP_MOVER_HALT_MEDIA_ERROR);
	else
		return (0);
}

/*
 * strToNdmpAuthType() : Converts ndmp_auth_type string from the tokens
 * array to ndmp_auth_type code.
 *
 * Returns :
 * 	ndmp_auth_type - ndmp_auth_type code.
 */
ndmp_auth_type
strToNdmpAuthType(char *str)
{
	if (! (strcmp(str, "NDMP_AUTH_NONE")))
		return (NDMP_AUTH_NONE);
	else if (! (strcmp(str, "NDMP_AUTH_TEXT")))
		return (NDMP_AUTH_TEXT);
	else if (! (strcmp(str, "NDMP_AUTH_MD5")))
		return (NDMP_AUTH_MD5);

	return (NDMP_AUTH_NONE);
}

/*
 * convert_mover_mode :
 *  Converts the mover mode from a string to a enum.
 * Return :
 *  ndmp_mover_mode
 */
ndmp_mover_mode
convert_mover_mode(char *mover_mode)
{
	if (mover_mode == NULL) {
		return (NDMP_MOVER_MODE_READ);
	}
	if (!(strcmp(mover_mode, "NDMP_MOVER_MODE_READ")))
		return (NDMP_MOVER_MODE_READ);
	else if (!(strcmp(mover_mode, "NDMP_MOVER_MODE_WRITE")))
		return (NDMP_MOVER_MODE_WRITE);
	else
		return (NDMP_MOVER_MODE_READ);
}
/*
 * convert_mover_mode :
 *  Converts the mover mode from a string to a enum.
 * Return :
 *  ndmp_mover_mode
 */
ndmp_addr_type
convert_addr_type(char *addr_type)
{
	if (addr_type == NULL) {
		return (NDMP_ADDR_LOCAL);
	}
	if (!(strcmp(addr_type, "NDMP_ADDR_LOCAL")))
		return (NDMP_ADDR_LOCAL);
	else if (!(strcmp(addr_type, "NDMP_ADDR_TCP")))
		return (NDMP_ADDR_TCP);
	else if (!(strcmp(addr_type, "NDMP_ADDR_IPC")))
		return (NDMP_ADDR_IPC);
	else if (!(strcmp(addr_type, "NDMP_ADDR_RESERVED")))
		return (NDMP_ADDR_RESERVED);
	else
		return (NDMP_ADDR_IPC);
}

/*
 * convert_butype :
 *  Converts the backup type from a string to a int.
 * Return :
 *  ndmp_mover_mode
 */
int
convert_butype(char *backup_type)
{
	if (backup_type != NULL) {
		if (!(strcmp(backup_type, "tar")))
			return (STD_BACKUP_TYPE_TAR);
		else if (!(strcmp(backup_type, "dump")))
			return (STD_BACKUP_TYPE_DUMP);
		else
			return (-1);
	} else
		return (STD_BACKUP_TYPE_DUMP);
}

/*
 * convert_tape_op :
 *  Converts the ndmp_tape_mtio_op from a string to a enum.
 * Return :
 *  ndmp_tape_mtio_op
 */
ndmp_tape_mtio_op
convert_tape_mtio_op(char *tape_mtio_op)
{
	if (tape_mtio_op == NULL) {
		return (NDMP_MTIO_TUR);
	}
	if (!(strcmp(tape_mtio_op, "NDMP_MTIO_FSF")))
		return (NDMP_MTIO_FSF);
	else if (!(strcmp(tape_mtio_op, "NDMP_MTIO_BSF")))
		return (NDMP_MTIO_BSF);
	else if (!(strcmp(tape_mtio_op, "NDMP_MTIO_REW")))
		return (NDMP_MTIO_REW);
	else if (!(strcmp(tape_mtio_op, "NDMP_MTIO_OFF")))
		return (NDMP_MTIO_OFF);
	else if (!(strcmp(tape_mtio_op, "NDMP_MTIO_EOF")))
		return (NDMP_MTIO_EOF);
	else if (!(strcmp(tape_mtio_op, "NDMP_MTIO_TUR")))
		return (NDMP_MTIO_TUR);
	else
		return (-1);
}

/*
 * print_reply()
 * Method to print the reply struct for tape module
 */
int
print_reply(ndmp_error reply_err, ndmp_error exp_err,
    ProcessMsgHandler *process_hdlr, void *reply_mem, FILE *outfile)
{

	ndmp_lprintf(outfile, "NDMP REPLY MESSAGE :\n");
	if (reply_err == exp_err) {
		(process_hdlr->printReplyMsg)(outfile, reply_mem);
		return (0);
	} else {
		(process_hdlr->printReplyMsg)(outfile, reply_mem);
		return (1);
	}
}

/*
 * print_test_result()
 * Helper method to print the test case result.
 */
int
print_test_result(int result, FILE *outfile)
{
	if (result == 0) {
		(void) ndmp_fprintf(outfile,
		    "Test case result : Pass\n");
		return (0);
	} else {
		(void) ndmp_fprintf(outfile,
		    "Test case result : Fail\n");
		return (1);
	}
}

/*
 * print_cleanup_result()
 * Helper method to print the test cleanup result.
 */
int
print_cleanup_result(int result, FILE *outfile)
{
	if (result == 0) {
		(void) ndmp_fprintf(outfile,
		    "Cleanup Passed ...\n");
		return (0);
	} else {
		(void) ndmp_fprintf(outfile,
		    "Cleanup Failed ...\n");
		return (1);
	}
}

/*
 * print_intl_result()
 * Helper method to print the test Initialization result.
 */
int
print_intl_result(int result, FILE *outfile)
{
	if (result == 0) {
		(void) ndmp_fprintf(outfile,
		    "Initialization Passed ...\n");
		return (0);
	} else {
		(void) ndmp_fprintf(outfile,
		    "Initialization Failed ...\n");
		return (1);
	}
}

/*
 * ndmp_err_to_string()
 *  Takes the error code as argument and return the string.
 *
 * Argument : ndmp error code
 * Returns :
 *  char * - Pointer to the string.
 */
char *
ndmp_err_to_string(ndmp_error error)
{
	if (error == NDMP_NO_ERR)
		return ("NDMP_NO_ERR");
	else if (error == NDMP_NOT_SUPPORTED_ERR)
		return ("NDMP_NOT_SUPPORTED_ERR");
	else if (error == NDMP_DEVICE_BUSY_ERR)
		return ("NDMP_DEVICE_BUSY_ERR");
	else if (error == NDMP_DEVICE_OPENED_ERR)
		return ("NDMP_DEVICE_OPENED_ERR");
	else if (error == NDMP_NOT_AUTHORIZED_ERR)
		return ("NDMP_NOT_AUTHORIZED_ERR");
	else if (error == NDMP_PERMISSION_ERR)
		return ("NDMP_PERMISSION_ERR");
	else if (error == NDMP_DEV_NOT_OPEN_ERR)
		return ("NDMP_DEV_NOT_OPEN_ERR");
	else if (error == NDMP_IO_ERR)
		return ("NDMP_IO_ERR");
	else if (error == NDMP_TIMEOUT_ERR)
		return ("NDMP_TIMEOUT_ERR");
	else if (error == NDMP_ILLEGAL_ARGS_ERR)
		return ("NDMP_ILLEGAL_ARGS_ERR");
	else if (error == NDMP_NO_TAPE_LOADED_ERR)
		return ("NDMP_NO_TAPE_LOADED_ERR");
	else if (error == NDMP_WRITE_PROTECT_ERR)
		return ("NDMP_WRITE_PROTECT_ERR");
	else if (error == NDMP_EOF_ERR)
		return ("NDMP_EOF_ERR");
	else if (error == NDMP_EOM_ERR)
		return ("NDMP_EOM_ERR");
	else if (error == NDMP_FILE_NOT_FOUND_ERR)
		return ("NDMP_FILE_NOT_FOUND_ERR");
	else if (error == NDMP_BAD_FILE_ERR)
		return ("NDMP_BAD_FILE_ERR");
	else if (error == NDMP_NO_DEVICE_ERR)
		return ("NDMP_NO_DEVICE_ERR");
	else if (error == NDMP_NO_BUS_ERR)
		return ("NDMP_NO_BUS_ERR");
	else if (error == NDMP_XDR_DECODE_ERR)
		return ("NDMP_XDR_DECODE_ERR");
	else if (error == NDMP_ILLEGAL_STATE_ERR)
		return ("NDMP_ILLEGAL_STATE_ERR");
	else if (error == NDMP_UNDEFINED_ERR)
		return ("NDMP_UNDEFINED_ERR");
	else if (error == NDMP_XDR_ENCODE_ERR)
		return ("NDMP_XDR_ENCODE_ERR");
	else if (error == NDMP_NO_MEM_ERR)
		return ("NDMP_NO_MEM_ERR");
	else if (error == NDMP_CONNECT_ERR)
		return ("NDMP_CONNECT_ERR");
	else if (error == NDMP_SEQUENCE_NUM_ERR)
		return ("NDMP_SEQUENCE_NUM_ERR");
	else if (error == NDMP_READ_IN_PROGRESS_ERR)
		return ("NDMP_READ_IN_PROGRESS_ERR");
	else if (error == NDMP_PRECONDITION_ERR)
		return ("NDMP_PRECONDITION_ERR");
	else if (error == NDMP_VERSION_NOT_SUPPORTED_ERR)
		return ("NDMP_VERSION_NOT_SUPPORTED_ERR");
	else if (error == NDMP_EXT_DUPL_CLASSES_ERR)
		return ("NDMP_EXT_DUPL_CLASSES_ERR");
	else if (error == NDMP_EXT_DANDN_ILLEGAL_ERR)
		return ("NDMP_EXT_DANDN_ILLEGAL_ERR");
	else
		return ("Unknown Error");
}

/*
 * create_host_info():
 * Helper method to fill to create host_info structure.
 *
 * Arguments :
 * host - Address of host structure.
 * list - Command line parameter list.
 * logfile - Log file.
 *
 * Return :
 * SUCCESS - If Successful.
 * ERROR - If Failure.
 */
int
create_host_info(host_info *host, char **list, FILE *logfile) {
	if (list[NDMPAUTH] == NULL)
		host->auth_type = NDMP_AUTH_TEXT;
	else if (!(strcmp(list[NDMPAUTH], "NDMP_AUTH_NONE")))
		host->auth_type = NDMP_AUTH_NONE;
	else if (!(strcmp(list[NDMPAUTH], "NDMP_AUTH_TEXT")))
		host->auth_type = NDMP_AUTH_TEXT;
	else if (!(strcmp(list[NDMPAUTH], "NDMP_AUTH_MD5")))
		host->auth_type = NDMP_AUTH_MD5;
	else
		host->auth_type = NDMP_AUTH_TEXT;

	if (list[SRC_MC] == NULL) {
		ndmp_dprintf(logfile,
		    "connect_switcher: source name/IP is null\n");
		return (ERROR);
	} else {
		host->ipAddr = list[SRC_MC];
	}
	if (list[SRCUSER] == NULL) {
		ndmp_dprintf(logfile,
		    "connect_switcher: source user/pass is null\n");
		return (ERROR);
	} else {
		host->password = list[SRCPSWD];
		host->userName = list[SRCUSER];
	}
	if (list[NDMPVERSION] != NULL) {
		host->protocol_version = atoi(list[NDMPVERSION]);
	} else {
		host->protocol_version = 4;
	}
	return (SUCCESS);
}

/*
 * check_test_and_sub_case() :
 * Check the test case and sub case string.
 *
 * Returns :
 * SUCCESS - Sucess.
 * Error - Failure.
 */
int
check_print_test_and_sub_case(char *test_case, char *sub_case, FILE *outfile)
{
	if (test_case == NULL && sub_case == NULL) {
		(void) ndmp_fprintf(outfile,
		    "Test case name : NULL\n");
		print_test_result(ERROR, outfile);
		return (ERROR);
	} else {
		if (test_case != NULL) {
			(void) ndmp_fprintf(outfile,
			    "Test case name : %s - ", test_case);
			if (sub_case != NULL) {
				(void) ndmp_fprintf(outfile,
				    "%s\n", sub_case);
			}
		}
		return (SUCCESS);
	}
}
