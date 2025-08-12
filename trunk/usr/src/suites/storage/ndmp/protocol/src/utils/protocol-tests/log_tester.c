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

#pragma ident	"@(#)log_tester.c	1.4	09/03/31 SMI"

/*
 * Log Interface is used by the NDMP Server to
 * send informational and diagnostic data to the DMA.
 * This files implements all the log interfaces.
 */

#include <log_tester.h>

extern FILE *postLogFile;
extern ndmp_message postMsgFlag;
extern ndmp_message postSubMsgFlag;
extern FILE *logfile;
int check_print_test_and_sub_case(char *, char *, FILE *);
/* NDMP_LOG_MESSAGE start */

/*
 * testLogNormal() : Prints the test case result for
 * Log Normal Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testLogNormal(conn_handle *connection)
{

	(void) ndmp_dprintf(logfile, "testLogNormal: \n");

	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_MESSAGE(NDMP_LOG_NORMAL)\n");
		(void) fprintf(postLogFile,
		    "ndmp_log_type = NDMP_LOG_NORMAL\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	} else {
		(void) fprintf(postLogFile,
		    "TEST CASE : NDMP_LOG_MESSAGE(NDMP_LOG_NORMAL)\n"
		    "TEST CASE RESULT : ERROR\n");
		return (0);
	}
}

/*
 * testLogDebug() : Prints the test case result for
 * Log Debug Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testLogDebug(conn_handle *connection)
{
	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_MESSAGE(NDMP_LOG_DEBUG)\n");
		(void) fprintf(postLogFile, "ndmp_log_type = NDMP_LOG_DEBUG\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	} else {
		(void) fprintf(postLogFile,
		"TEST CASE : NDMP_LOG_MESSAGE(NDMP_LOG_DEBUG)\n"
		"TEST CASE RESULT : ERROR\n");
		return (0);
	}
	return (1);
}

/*
 * testLogError() : Prints the test case result for
 * Log Error Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testLogError(conn_handle *connection)
{
	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_MESSAGE(NDMP_LOG_ERROR)\n");
		(void) fprintf(postLogFile, "ndmp_log_type = NDMP_LOG_ERROR\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	} else {
		(void) fprintf(postLogFile,
		    "TEST CASE : NDMP_LOG_MESSAGE(NDMP_LOG_NORMAL)\n"
		    "TEST CASE RESULT : ERROR\n");
		return (0);
	}
	return (1);
}



/*
 * testLogWarning() : Prints the test case result for
 * Log Warning Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testLogWarning(conn_handle *connection)
{
	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_MESSAGE(NDMP_LOG_WARNING)\n");
		(void) fprintf(postLogFile,
		    "ndmp_log_type = NDMP_LOG_WARNING\n");
		(void) fprintf(postLogFile,
		    "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	} else {
		(void) fprintf(postLogFile,
		    "TEST CASE : NDMP_LOG_MESSAGE(NDMP_LOG_WARNING)\n"
		    "TEST CASE RESULT : ERROR\n");
		return (0);
	}
	return (1);
}


/*
 * testLogMessage() : Prints the test case result for
 * Log Message Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
int
testLogMessage(conn_handle *connection)
{
	int ret = 0;

	if (postSubMsgFlag == (ndmp_log_type)NDMP_LOG_NORMAL)
		ret = testLogNormal(connection);
	if (postSubMsgFlag == (ndmp_log_type)NDMP_LOG_DEBUG)
		ret = testLogDebug(connection);
	if (postSubMsgFlag == (ndmp_log_type)NDMP_LOG_ERROR)
		ret = testLogError(connection);
	if (postSubMsgFlag == (ndmp_log_type)NDMP_LOG_WARNING)
		ret = testLogWarning(connection);

	return (1);
}
/* NDMP_LOG_MESSAGE end */

/* NDMP_LOG_FILE start */

/*
 * testRecoverySuccessful() : Prints the test case result for
 * Log Recovery Successful Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testRecoverySuccessful(conn_handle *connection)
{

	(void) ndmp_dprintf(logfile, "testRecoverySuccessful: \n");


	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_SUCCESSFUL)\n");
		(void) fprintf(postLogFile, "ndmp_recovery_status :"
		    " NDMP_RECOVERY_SUCCESSFUL\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	} else {
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_SUCCESSFUL)\n"
		    "TEST CASE RESULT : ERROR\n");
		return (0);
	}
}

/*
 * testRecoveryFailedPermission() : Prints the test case result for
 * Log Recovery Failed Permission Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testRecoveryFailedPermission(conn_handle *connection)
{

	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_FAILED_PERMISSION)\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	}
	return (1);
}

/*
 * testRecoveryFailedNotFound() : Prints the test case result for
 * Log Recovery Failed Not Found Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testRecoveryFailedNotFound(conn_handle *connection)
{

	(void) ndmp_dprintf(logfile, "testRecoveryFailedNotFound: \n");


	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_FAILED_NOT_FOUND)\n");
		(void) fprintf(postLogFile,
		    "ndmp_recovery_status : NDMP_RECOVERY_FAILED_NOT_FOUND\n");
		(void) fprintf(postLogFile,
		    "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	} else {
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_FAILED_NOT_FOUND)\n"
		    "TEST CASE RESULT : ERROR\n");
		return (0);
	}
}

/*
 * testRecoveryFailedNoDirectory() : Prints the test case result for
 * Log Recovery Failed No Directory Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testRecoveryFailedNoDirectory(conn_handle *connection)
{

	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_FAILED_NO_DIRECTORY)\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	}
	return (1);
}

/*
 * testRecoveryFailedOutOfMemory() : Prints the test case result for
 * Log Recovery Failed Out Of Memory Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testRecoveryFailedOutOfMemory(conn_handle *connection)
{

	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 0;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_FAILED_OUT_OF_MEMORY)\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	}
	return (1);
}

/*
 * testRecoveryFailedIoError() : Prints the test case result for
 * Log Recovery Failed IO Error Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testRecoveryFailedIoError(conn_handle *connection)
{

	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_FAILED_IO_ERROR)\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	}
	return (1);
}

/*
 * testRecoveryFailedUndefinedError() : Prints the test case result for
 * Log Recovery Failed Undefined Error Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testRecoveryFailedUndefinedError(conn_handle *connection)
{

	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_FAILED_UNDEFINED_ERROR)\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	}
	return (1);
}

/*
 * testRecoveryFailedFilePathExists() : Prints the test case result for
 * Log Recovery Failed File Path Exists Post message.
 *
 * Arguments :
 * 	Connection * - Connection object handle.
 * Returns :
 * 	int - 0 if success and 1 if failure.
 */
static int
testRecoveryFailedFilePathExists(conn_handle *connection)
{

	static int i = 0;
	if (i != 0)
		return (1);
	if (connection != 0) {
		i = 1;
		(void) fprintf(postLogFile, "TEST CASE :"
		    " NDMP_LOG_FILE(NDMP_RECOVERY_FAILED_FILE_PATH_EXISTS)\n");
		(void) fprintf(postLogFile, "TEST CASE RESULT : SUCCESS\n\n");
		return (1);
	}
	return (1);
}


/*
 * testLogFile() : Checks for the post message flag and calls
 * appropriate method to test and print the test case result.
 *
 * Arguments :
 * 	Connection * - Handle to connection object.
 *
 * Returns :
 * 	int - 0 for success and 1 for failure.
 */
int
testLogFile(conn_handle *connection)
{
	int ret = 0;

	if (postSubMsgFlag == (ndmp_message)NDMP_RECOVERY_SUCCESSFUL)
		ret = testRecoverySuccessful(connection);
	if (postSubMsgFlag == (ndmp_message)NDMP_RECOVERY_FAILED_PERMISSION)
		ret = testRecoveryFailedPermission(connection);
	if (postSubMsgFlag == (ndmp_message)NDMP_RECOVERY_FAILED_NOT_FOUND)
		ret = testRecoveryFailedNotFound(connection);
	if (postSubMsgFlag == (ndmp_message)NDMP_RECOVERY_FAILED_NO_DIRECTORY)
		ret = testRecoveryFailedNoDirectory(connection);
	if (postSubMsgFlag == (ndmp_message)NDMP_RECOVERY_FAILED_OUT_OF_MEMORY)
		ret = testRecoveryFailedOutOfMemory(connection);
	if (postSubMsgFlag == (ndmp_message)NDMP_RECOVERY_FAILED_IO_ERROR)
		ret = testRecoveryFailedIoError(connection);
	if (postSubMsgFlag ==
	    (ndmp_message)NDMP_RECOVERY_FAILED_UNDEFINED_ERROR)
		ret = testRecoveryFailedUndefinedError(connection);
	if (postSubMsgFlag ==
	    (ndmp_message)NDMP_RECOVERY_FAILED_FILE_PATH_EXISTS)
		ret = testRecoveryFailedFilePathExists(connection);
	else
		return (ret);

	return (ret);
}
/* NDMP_LOG_FILE end */


/*
 * test_log_file() :
 * Test NDMP_RECOVERY_SUCCESSFUL, NDMP_RECOVERY_FAILED_PERMISSION,
 * NDMP_RECOVERY_FAILED_NOT_FOUND and NDMP_RECOVERY_FAILED_NO_DIRECTORY
 * post messages.
 * This post sends a file recovered message to the DMA. It is used
 * during recovery to notify the DMA that a file/directory specified in
 * the recovery list sent in the NDMP_DATA_START_RECOVER request has or
 * has not been recovered.
 *
 * Arguments :
 * test_case - Test case name.
 * abcBckDirPath - Backup directory path.
 *
 * Returns :
 * SUCCESS - Sucess.
 * Error - Failure.
 */
int
test_log_file(char *test_case, char *sub_case, char *tape_dev,
    char *abcBckDirPath, FILE *outfile, conn_handle *conn)
{
	int ret = 0, sub_msg = strToNdmpSubMessageCode(sub_case);
	ndmp_message msg = strToNdmpMessageCode(test_case);
	FILE *dev_null = fopen("/dev/null", "w");
	char backup_dir[50];
	memset(backup_dir, '\0', 50);

	char *backup_type = "dump";
	if (check_print_test_and_sub_case(test_case, sub_case, outfile)
	    == ERROR) {
		return (ERROR);
	}
	ret = inf_data_start_backup(NDMP_NO_ERR, tape_dev, abcBckDirPath,
	    backup_type, dev_null, conn);
	if (sub_msg == NDMP_RECOVERY_FAILED_NOT_FOUND) {
		ret += data_start_recover_intl(NDMP_NOT_AUTHORIZED_ERR,
		    tape_dev, outfile, conn);
	} else {
		ret += data_start_recover_intl(NDMP_NO_ERR, tape_dev, outfile,
		    conn);
	}
	if (sub_msg == NDMP_RECOVERY_FAILED_NO_DIRECTORY) {
		strcpy(backup_dir, abcBckDirPath);
		abcBckDirPath = strcat(backup_dir, "/xzy");
	}
	if (sub_msg == NDMP_RECOVERY_FAILED_PERMISSION)
		abcBckDirPath = strcpy(backup_dir, "/home");
	ret += data_start_recover_core(NDMP_NO_ERR, NDMP_DATA_START_RECOVER,
	    abcBckDirPath, backup_type, outfile, conn);
	print_intl_result(ret, outfile);
	if (ret == ERROR)
		return (ERROR);
	print_test_result(process_post(msg, sub_msg, outfile, conn), outfile);
	print_cleanup_result(data_start_recover_cleanup(NDMP_NO_ERR, outfile,
	    conn), outfile);
	fclose(dev_null);
	/* Now check and process for the post message */
	return (SUCCESS);
}
