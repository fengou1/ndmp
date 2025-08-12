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

#pragma ident	"@(#)ndmp_lib.c	1.3	09/03/30 SMI"

/*
 * Library methods useful for the implementation of scsi and
 * tape interfaces can be found here
 */

#include <stdio.h>
#include <string.h>

#include <ndmp.h>
#include <ndmp_lib.h>
#include <ndmp_comm_lib.h>

#include <sys/scsi/generic/inquiry.h>
#include <sys/scsi/generic/sense.h>

char *tokens[40];
int token_num;
static int cdbNum; /* This variable is used by cdb functions */
extern FILE *logfile;
extern bool_t compare_ndmp_u_quad(ndmp_u_quad, ndmp_u_quad);
ndmp_data_state get_data_state(FILE *, conn_handle *);
ndmp_mover_state get_mover_state(FILE *, conn_handle *);

/*
 * ndmpAuthTypeStrToDec() : Converts ndmp auth type string
 * to its decimal equivalent.
 *
 * Arguments :
 * 	char * - auth type string.
 * Returns :
 * 	int - Decimal equivalent of the auth type string passed.
 */
static int
ndmpAuthTypeStrToDec(char *auth_type)
{

	if (!(strcmp(auth_type, "0")))
		return (0);
	else if (!(strcmp(auth_type, "1")))
		return (1);
	else if (!(strcmp(auth_type, "2")))
		return (2);
	else
		(void) (void) printf("ndmpAuthTypeStrToDec: junk data\n");

	return (-1);
}

/* Extract functions start */

/*
 * extract_ndmp_class_version() : Extracts and converts the
 * ndmp class version from the string to integer. The ndmp
 * class version is present in the input string present in
 * tokens array.
 *
 * Arguments :
 * 	ndmp_class_version * - Pointer to the ndmp_class_version
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_ndmp_class_version(ndmp_class_version *ndmpClassVersion,
    int *token_index)
{
	if (ndmpClassVersion != 0) {
		if (++(*token_index) < token_num)
			ndmpClassVersion->ext_class_id =
			    atoi(tokens[*token_index]);
		if (++(*token_index) < token_num)
			ndmpClassVersion->ext_version =
			    atoi(tokens[*token_index]);
	}
}

/*
 * extract_ndmp_selected_ext() : Extracts and converts the
 * ndmp selected extension from the string to integer. The ndmp
 * selected extension is present in the input string present in
 * tokens array.
 *
 * Arguments :
 * 	ndmp_selected_ext* - Pointer to the ndmp_selected_ext
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_ndmp_selected_ext(ndmp_selected_ext *ndmpSelectedExt, int *token_index)
{

	if (ndmpSelectedExt != 0) {
		ndmpSelectedExt->ndmp_selected_ext_len =
		    atoi(tokens[*token_index]);

		extract_ndmp_class_version(
		    ndmpSelectedExt->ndmp_selected_ext_val, token_index);
	}

}

/*
 * extract_ext_version() : Extracts and converts the
 * extension version from the string to integer. The ndmp
 * selected extension is present in the input string present in
 * tokens array.
 *
 * Arguments :
 * 	ext_version * - Pointer to the ext_version
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_ext_version(ext_version *extVersion, int *token_index)
{
	if (extVersion != 0) {
		if (++(*token_index) < token_num)
			extVersion->ext_version_len =
			    atoi(tokens[*token_index]);

		extVersion->ext_version_val = (ushort_t *)
		    malloc(sizeof (int) * extVersion->ext_version_len);

		if (++(*token_index) < token_num)
			*(extVersion->ext_version_val) =
			    atoi(tokens[*token_index]);
	}
}

/*
 * extract_ndmp_class_list() : Extracts and converts the
 * ndmp class list from the string to integer. The ndmp
 * selected extension is present in the input string present in
 * tokens array.
 *
 * Arguments :
 * 	ndmp_class_list * - Pointer to the ndmp_class_list
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_ndmp_class_list(ndmp_class_list *ndmpClassList, int *token_index)
{
	if (ndmpClassList != 0) {
		if (++(*token_index) < token_num)
			ndmpClassList->ext_class_id =
			    atoi(tokens[*token_index]);

		extract_ext_version(
		    (ext_version *) &(ndmpClassList->ext_version), token_index);
	}
}

/*
 * extract_class_list() : Extracts and converts the
 * class list from the string to integer. The ndmp
 * selected extension is present in the input string present in
 * tokens array.
 *
 * Arguments :
 * 	class_list * - Pointer to the class_list
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_class_list(class_list *classList, int *token_index)
{

	if (classList != 0) {
		if (++(*token_index) < token_num)
			classList->class_list_len = atoi(tokens[*token_index]);

		classList->class_list_val =
		    (ndmp_class_list*) malloc(sizeof (ndmp_class_list));
		extract_ndmp_class_list(classList->class_list_val, token_index);
	}
}

/*
 * extract_capability() : Extracts and converts the
 * capability from the string to integer. The ndmp
 * selected extension is present in the input string present in
 * tokens array.
 *
 * Arguments :
 * 	capability * - Pointer to the capability
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_capability(capability *cap, int *token_index)
{

	if (cap != 0) {
		if (++(*token_index) < token_num)
			cap->capability_len = atoi(tokens[*token_index]);

		cap->capability_val = (ndmp_pval*) malloc(sizeof (ndmp_pval));
		extract_ndmp_pval(*token_index, cap->capability_val);
	}
}

/*
 * extract_ndmp_device_capability() : Extracts and converts the
 * ndmp_device_capability from the string to integer.
 * The ndmp_device_capability is present in the input string present in
 * tokens array.
 *
 * Arguments :
 * 	ndmp_device_capability * - Pointer to the ndmp_device_capability
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_ndmp_device_capability(ndmp_device_capability *ndmpDeviceCapability,
    int *token_index)
{

	if (ndmpDeviceCapability != 0) {
		if (++(*token_index) < token_num)
			ndmpDeviceCapability->device =
			    strdup(tokens[*token_index]);

		if (++(*token_index) < token_num)
			ndmpDeviceCapability->attr = atoi(tokens[*token_index]);

		extract_capability((capability *)
		    &(ndmpDeviceCapability->capability), token_index);
	}
}

/*
 * extract_caplist() : Extracts and converts the
 * caplist from the string to integer. The caplist
 * is present in the input string, present in
 * tokens array.
 *
 * Arguments :
 * 	caplist * - Pointer to the caplist
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_caplist(caplist *capList, int *token_index)
{
	if (capList != 0) {
		if (++(*token_index) < token_num)
			capList->caplist_len = atoi(tokens[*token_index]);

		capList->caplist_val = (ndmp_device_capability*)
		    malloc(sizeof (ndmp_device_capability));
		extract_ndmp_device_capability(
		    capList->caplist_val, token_index);
	}
}

/*
 * extract_ndmp_device_info() : Extracts and converts the
 * ndmp_device_info from the string to integer. The ndmp_device_info
 * is present in the input string, present in
 * tokens array.
 *
 * Arguments :
 * 	ndmp_device_info * - Pointer to the ndmp_device_info
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_ndmp_device_info(ndmp_device_info *ndmpDeviceInfo, int *token_index)
{
	if (ndmpDeviceInfo != 0) {
		if (++(*token_index) < token_num)
			ndmpDeviceInfo->model = strdup(tokens[*token_index]);

		extract_caplist((caplist *)
		    &(ndmpDeviceInfo->caplist), token_index);
	}
}

/*
 * extract_scsi_info() : Extracts and converts the
 * scsi_info from the string to integer. The scsi_info
 * is present in the input string, present in
 * tokens array.
 *
 * Arguments :
 * 	scsi_info * - Pointer to the scsi_info
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_scsi_info(scsi_info *scsiInfo, int *token_index)
{
	if (scsiInfo != 0) {
		if (++(*token_index) < token_num)
			scsiInfo->scsi_info_len = atoi(tokens[*token_index]);

		scsiInfo->scsi_info_val =
		    (ndmp_device_info*) malloc(sizeof (ndmp_device_info));
		extract_ndmp_device_info(scsiInfo->scsi_info_val, token_index);
	}
}

/*
 * extract_tape_info() : Extracts and converts the
 * tape_info from the string to integer. The tape_info
 * is present in the input string, present in
 * tokens array.
 *
 * Arguments :
 * 	tape_info * - Pointer to the tape_info
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_tape_info(tape_info *tapeInfo, int *token_index)
{

	if (tapeInfo != 0) {
		if (++(*token_index) < token_num)
			tapeInfo->tape_info_len = atoi(tokens[*token_index]);

		tapeInfo->tape_info_val =
		    (ndmp_device_info*) malloc(sizeof (ndmp_device_info));
		extract_ndmp_device_info(tapeInfo->tape_info_val, token_index);

	}

}

/*
 * extract_ndmp_fs_info() : Extracts and converts the
 * ndmp_fs_info from the string to structure. The ndmp_fs_info
 * is present in the input string, present in
 * tokens array.
 *
 * Arguments :
 * 	ndmp_fs_info * - Pointer to the ndmp_fs_info
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_ndmp_fs_info(ndmp_fs_info *ndmpFsInfo, int *token_index)
{
	if (ndmpFsInfo != 0 && tokens != 0) {
		if (++(*token_index) < token_num)
			ndmpFsInfo->unsupported = atol(tokens[*token_index]);
		if (++(*token_index) < token_num)
			ndmpFsInfo->fs_type = strdup(tokens[*token_index]);
		if (++(*token_index) < token_num)
			ndmpFsInfo->fs_logical_device =
			    strdup(tokens[*token_index]);
		if (++(*token_index) < token_num)
			ndmpFsInfo->fs_physical_device =
			    strdup(tokens[*token_index]);

		extract_ndmp_u_quad(token_index, &(ndmpFsInfo->total_size));
		extract_ndmp_u_quad(token_index, &(ndmpFsInfo->used_size));
		extract_ndmp_u_quad(token_index, &(ndmpFsInfo->avail_size));
		extract_ndmp_u_quad(token_index, &(ndmpFsInfo->total_inodes));
		extract_ndmp_u_quad(token_index, &(ndmpFsInfo->used_inodes));

		if (++(*token_index) < token_num)
			ndmpFsInfo->fs_env.fs_env_len =
			    atoi(tokens[*token_index]);

		ndmpFsInfo->fs_env.fs_env_val = (ndmp_pval*)
		    malloc(sizeof (ndmp_pval));
		extract_ndmp_pval(*token_index, ndmpFsInfo->fs_env.fs_env_val);
		if (++(*token_index) < token_num)
			ndmpFsInfo->fs_status = strdup(tokens[*token_index]);
	}
}

/*
 * extract_fs_info() : Extracts and converts the
 * fs_info from the string to structure. The fs_info
 * is present in the input string, present in
 * tokens array.
 *
 * Arguments :
 * 	fs_info * - Pointer to the fs_info
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_fs_info(fs_info *fsInfo, int *token_index)
{

	if (fsInfo != 0) {
		if (++(*token_index) < token_num)
			fsInfo->fs_info_len = atoi(tokens[*token_index]);

		fsInfo->fs_info_val =
		    (ndmp_fs_info*) malloc(sizeof (ndmp_fs_info));
		extract_ndmp_fs_info(fsInfo->fs_info_val, token_index);
	}
}

/*
 * extract_ndmp_butype_info() : Extracts and converts the
 * ndmp_butype_info from the string to appropriate data type.
 * The ndmp_butype_info is present in the input string,
 * present in tokens array.
 *
 * Arguments :
 * 	ndmp_butype_info * - Pointer to the ndmp_butype_info
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_ndmp_butype_info(int *token_index, ndmp_butype_info *ndmpButypeInfo)
{

	if (ndmpButypeInfo != 0) {

		if (++(*token_index) < token_num)
			ndmpButypeInfo->butype_name =
			    strdup(tokens[*token_index]);

		if (++(*token_index) < token_num)
			ndmpButypeInfo->default_env.default_env_len =
			    atoi(tokens[*token_index]);

		extract_ndmp_pval((*token_index),
		    ndmpButypeInfo->default_env.default_env_val);

		if (++(*token_index) < token_num)
			ndmpButypeInfo->attrs = atol(tokens[*token_index]);
	}
}

/*
 * extract_butype_info() : Extracts and converts the
 * butype_info from the string to appropriate data type.
 * The butype_info is present in the input string,
 * present in tokens array.
 *
 * Arguments :
 * 	butype_info * - Pointer to the butype_info
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_butype_info(int *token_index, butype_info *butypeInfo)
{

	if (butypeInfo != 0) {
		if (++(*token_index) < token_num)
			butypeInfo->butype_info_len =
			    atoi(tokens[*token_index]);

		butypeInfo->butype_info_val =
		    (ndmp_butype_info*) malloc(sizeof (ndmp_butype_info));
		if (++(*token_index) < token_num)
			extract_ndmp_butype_info(
			    token_index, butypeInfo->butype_info_val);
	}
}

/*
 * extract_ndmp_auth_text() : Extracts and converts the
 * ndmp_auth_text from the string to appropriate data type.
 * The ndmp_auth_text is present in the input string,
 * present in tokens array.
 *
 * Arguments :
 * 	ndmp_auth_text * - Pointer to the ndmp_auth_text
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_ndmp_auth_text(ndmp_auth_text *auth_text, int *token_index)
{

	if (++(*token_index) < token_num)
		auth_text->auth_id = tokens[*token_index];
	if (++(*token_index) < token_num)
		auth_text->auth_password = tokens[*token_index];
}

/*
 * extract_ndmp_auth_md5() : Extracts and converts the
 * ndmp_auth_md5 from the string to appropriate data type.
 * The ndmp_auth_md5 is present in the input string,
 * present in tokens array.
 *
 * Arguments :
 * 	ndmp_auth_md5 * - Pointer to the ndmp_auth_md5
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
static void
extract_ndmp_auth_md5(ndmp_auth_md5 *auth_md5, int *token_index)
{

	if (++(*token_index) < token_num)
		auth_md5->auth_id = tokens[*token_index];

	if (++(*token_index) < token_num)
		(void) (void) strcpy(
		    auth_md5->auth_digest, tokens[*token_index]);
}

/*
 * extract_datain() : Extracts and converts the
 * datain from the string to appropriate data type.
 * The datain is present in the input string,
 * present in tokens array.
 *
 * Arguments :
 * 	datain * - Pointer to the datain
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_datain(datain *data, int *token_index)
{

	if (++(*token_index) < token_num)
		data->datain_len = atoi(tokens[*token_index]);

	if (++(*token_index) < token_num)
		data->datain_val = strdup(tokens[*token_index]);
}

/*
 * extract_ext_sense() : Extracts and converts the
 * ext_sense from the string to appropriate data type.
 * The ext_sense is present in the input string,
 * present in tokens array.
 *
 * Arguments :
 * 	ext_sense * - Pointer to the ext_sense
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_ext_sense(ext_sense *ext, int *token_index)
{

	if (++(*token_index) < token_num)
		ext->ext_sense_len = atoi(tokens[*token_index]);

	if (++(*token_index) < token_num)
		ext->ext_sense_val = strdup(tokens[*token_index]);
}

/*
 * extract_data_in() : Extracts and converts the
 * data_in from the string to appropriate data type.
 * The ext_sense is present in the input string,
 * present in tokens array.
 *
 * Arguments :
 * 	data_in * - Pointer to the data_in
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_data_in(data_in *data, int *token_index)
{

	if (++(*token_index) < token_num)
		data->data_in_len = atol(tokens[*token_index]);

	if (++(*token_index) < token_num)
		data->data_in_val = tokens[*token_index];
}

/*
 * getCdbNum() : Converts and returns the appropriate cdb
 * number associated with the cdb string passsed in.
 */
int
getCdbNum(char *cdbStr)
{
	if (cdbStr == NULL)
		return (-1);
	if (!(strcmp("INQUIRY", cdbStr)))
		return (INQUIRYCDB);
	if (!(strcmp("TESTUNITREADY", cdbStr)))
		return (TESTUNITREADYCDB);
	if (!(strcmp("LOAD", cdbStr)))
		return (LOADCDB);
	if (!(strcmp("UNLOAD", cdbStr)))
		return (UNLOADCDB);
	if (!(strcmp("REQUESTSENSE", cdbStr)))
		return (REQUESTSENSECDB);
	if (!(strcmp("MODESELECT", cdbStr)))
		return (MODESELECTCDB);
	if (!(strcmp("MODESENSE", cdbStr)))
		return (MODESENSECDB);
	if (!(strcmp("READ", cdbStr)))
		return (READCDB);
	if (!(strcmp("READBLOCKLIMITS", cdbStr)))
		return (READBLOCKLIMITSCDB);
	if (!(strcmp("REWIND", cdbStr)))
		return (REWINDCDB);
	if (!(strcmp("SPACE", cdbStr)))
		return (SPACECDB);
	if (!(strcmp("WRITE", cdbStr)))
		return (WRITECDB);
	if (!(strcmp("WRITEFILEMARKS", cdbStr)))
		return (WRITEFILEMARKSCDB);
	if (!(strcmp("MOVEMEDIUM", cdbStr)))
		return (MOVEMEDIUMCDB);
	if (!(strcmp("SETTARGETPORTGROUPS", cdbStr)))
		return (SETTARGETPORTGROUPSCDB);
	if (!(strcmp("READELEMENTSTATUS", cdbStr)))
		return (READELEMENTSTATUSCDB);
	else
		return (-1);
}

/*
 * create_cdb()
 * Helper method to create a cdb
 */
int
create_cdb(cdb *pcdb, int cdb_num)
{
	switch (cdb_num) {
		case INQUIRYCDB:
			pcdb->cdb_val[0] = 0x12;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0x50;
			pcdb->cdb_val[5] = 0;
			break;
		case TESTUNITREADYCDB:
			pcdb->cdb_val[0] = 0x00;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0;
			pcdb->cdb_val[5] = 0;
			break;
		case UNLOADCDB:
			pcdb->cdb_val[0] = 0x1B;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0;
			pcdb->cdb_val[5] = 0;
			break;
		case LOADCDB:
			pcdb->cdb_val[0] = 0x1B;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 1;
			pcdb->cdb_val[5] = 0;
			break;
		case MODESELECTCDB:
			free(pcdb->cdb_val);
			pcdb->cdb_val = (char *)malloc(10);
			pcdb->cdb_val[0] = 0x15;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0;
			pcdb->cdb_val[5] = 0;
			break;
		case MODESENSECDB:
			pcdb->cdb_val[0] = 0x1A;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 80;
			pcdb->cdb_val[5] = 0;
			break;
		case READCDB:
			pcdb->cdb_val[0] = 0x08;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 127;
			pcdb->cdb_val[5] = 0;
			break;
		case READBLOCKLIMITSCDB:
			pcdb->cdb_val[0] = 0x05;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0;
			pcdb->cdb_val[5] = 0;
			break;
		case REWINDCDB:
			pcdb->cdb_val[0] = 0x01;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0;
			pcdb->cdb_val[5] = 0;
			break;
		case SPACECDB:
			pcdb->cdb_val[0] = 0x11;
			pcdb->cdb_val[1] = 1;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 1;
			pcdb->cdb_val[5] = 0;
			break;
		case WRITECDB:
			pcdb->cdb_val[0] = 0x0A;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0;
			pcdb->cdb_val[5] = 0;
			break;
		case WRITEFILEMARKSCDB:
			pcdb->cdb_val[0] = 0x10;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 1;
			pcdb->cdb_val[5] = 0;
			break;
		case MOVEMEDIUMCDB:
			pcdb->cdb_val[0] = 0;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0;
			pcdb->cdb_val[5] = 0;
			break;
		case REQUESTSENSECDB:
			pcdb->cdb_val[0] = 0x03;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 80;
			pcdb->cdb_val[5] = 0;
			break;
		case SETTARGETPORTGROUPSCDB:
			pcdb->cdb_val[0] = 0;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0;
			pcdb->cdb_val[5] = 0;
			break;
		case READELEMENTSTATUSCDB:
			pcdb->cdb_val[0] = 0;
			pcdb->cdb_val[1] = 0;
			pcdb->cdb_val[2] = 0;
			pcdb->cdb_val[3] = 0;
			pcdb->cdb_val[4] = 0;
			pcdb->cdb_val[5] = 0;
			pcdb->cdb_val[6] = 0;
			pcdb->cdb_val[7] = 0;
			pcdb->cdb_val[8] = 0;
			pcdb->cdb_val[9] = 80;
			pcdb->cdb_val[10] = 0;
			pcdb->cdb_val[11] = 0;
			break;
		default:
			pcdb->cdb_val[0] = -1;
			pcdb->cdb_val[1] = -1;
			pcdb->cdb_val[2] = -1;
			pcdb->cdb_val[3] = -1;
			pcdb->cdb_val[4] = -1;
			pcdb->cdb_val[5] = -1;
	}
	return (0);
}
/*
 * extract_cdb() : Creates a cdb packet, based on the
 * cdb value in the input file. Only this many cdb's can be
 * tested.
 */
void
extract_cdb(cdb *pcdb, int *token_index)
{

	if (++(*token_index) < token_num)
		pcdb->cdb_len = atol(tokens[*token_index]);

	pcdb->cdb_val = (char *)malloc(6);
	if (++(*token_index) < token_num) {
		pcdb->cdb_val = strdup(tokens[*token_index]);
		cdbNum = getCdbNum(pcdb->cdb_val);
		(void) create_cdb(pcdb, cdbNum);
	}
}

/*
 * extract_dataout() : Extracts and converts the
 * dataout from the string to appropriate data type.
 * The dataout is present in the input string,
 * present in tokens array.
 *
 * Arguments :
 * 	dataout * - Pointer to the dataout
 * 	structure. The integer is stored here.
 * 	int * - Token index of the tokens array.
 *
 */
void
extract_dataout(dataout *data, int *token_index)
{

	if (++(*token_index) < token_num)
		data->dataout_len = atol(tokens[*token_index]);

	if (++(*token_index) < token_num)
		data->dataout_val = strdup(tokens[*token_index]);
}

void
extract_ndmp_auth_data(ndmp_auth_data *auth_data, int *token_index)
{

	if (++(*token_index) < token_num)
		auth_data->auth_type =
		    ndmpAuthTypeStrToDec(tokens[*token_index]);

	if ((!(strcmp(tokens[*token_index], "NDMP_AUTH_TEXT")) &&
	    ++(*token_index) < token_num))
		extract_ndmp_auth_text(&(auth_data->ndmp_auth_data_u.auth_text),
		    token_index);

	if ((!(strcmp(tokens[*token_index], "NDMP_AUTH_MD5")) &&
	    ++(*token_index) < token_num))
		extract_ndmp_auth_md5(&(auth_data->ndmp_auth_data_u.auth_md5),
		    token_index);
}

void
extract_ndmp_auth_attr(ndmp_auth_attr *auth_attr, int *token_index)
{
	if (++(*token_index) < token_num)
		auth_attr->auth_type =
		    ndmpAuthTypeStrToDec(tokens[*token_index]);

	if (++(*token_index) < token_num)
		(void) strcpy(auth_attr->ndmp_auth_attr_u.challenge,
		    tokens[*token_index]);
}

void
extract_addr_types(addr_types *addrType, int *token_index)
{
	if (++(*token_index) < token_num)
		addrType->addr_types_len = atoi(tokens[*token_index]);

	addrType->addr_types_val =
	    (ndmp_addr_type*) malloc(sizeof (ndmp_addr_type));
	if (++(*token_index) < token_num)
		extract_ndmp_addr_type(*token_index, addrType->addr_types_val);
}

/*
 * compare_ndmp_class_list() : Compares the ndmp_class_list structure.
 *
 * Arguments :
 * 	ndmp_class_list * - Pointer to the expected ndmp_class_list object.
 * 	ndmp_class_list * - Pointer to the reply ndmp_class_list object.
 *
 * Returns :
 * 	bool_t - TRUE if success and FALSE if failure.
 */
static bool_t
compare_ndmp_class_list(ndmp_class_list *exp_class_list,
			ndmp_class_list *rep_class_list)
{
	if (exp_class_list != 0 && rep_class_list != 0) {

		if (exp_class_list->ext_class_id !=
		    rep_class_list->ext_class_id)
			return (FALSE);

		if (exp_class_list->ext_version.ext_version_len !=
		    rep_class_list->ext_version.ext_version_len)
			return (FALSE);

		if (*(exp_class_list->ext_version.ext_version_val) !=
		    *(rep_class_list->ext_version.ext_version_val))
			return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}
}

bool_t
compare_class_list(class_list *exp_class_list, class_list *rep_class_list)
{
	if (exp_class_list != 0 && rep_class_list != 0) {
		if (exp_class_list->class_list_len !=
		    rep_class_list->class_list_len)
			return (FALSE);

		if (!compare_ndmp_class_list(
		    exp_class_list->class_list_val,
		    rep_class_list->class_list_val))
			return (FALSE);
		return (TRUE);
	} else {
		return (FALSE);
	}
}

/*
 * compare_ndmp_device_capability() : Compares the ndmp_device_capability
 * structure.
 *
 * Arguments :
 * 	ndmp_device_capability * - Pointer to the expected
 * 	ndmp_device_capability object.
 * 	ndmp_device_capability * - Pointer to the reply
 * 	ndmp_device_capability object.
 *
 * Returns :
 * 	bool_t - TRUE if success and FALSE if failure.
 */
static bool_t
compare_ndmp_device_capability(ndmp_device_capability *expDevCap,
    ndmp_device_capability *repDevCap)
{
	if (expDevCap != 0 && repDevCap != 0) {

		if (!(strcmp(expDevCap->device, repDevCap->device)))
			return (FALSE);
		if (expDevCap->attr != repDevCap->attr)
			return (FALSE);
		if (expDevCap->capability.capability_len !=
		    repDevCap->capability.capability_len)
			return (FALSE);
		if (compare_ndmp_pval(expDevCap->capability.capability_val,
		    repDevCap->capability.capability_val))
			return (FALSE);
		return (TRUE);
	} else {
		return (FALSE);
	}
}

static bool_t
compare_ndmp_device_info(ndmp_device_info *expDevInfo,
    ndmp_device_info *repDevInfo)
{
	if (expDevInfo != 0 && repDevInfo != 0) {
		if (!(strcmp(expDevInfo->model, repDevInfo->model)))
			return (FALSE);

		if (expDevInfo->caplist.caplist_len !=
		    repDevInfo->caplist.caplist_len)
			return (FALSE);

		if (compare_ndmp_device_capability(
		    expDevInfo->caplist.caplist_val,
		    repDevInfo->caplist.caplist_val))
			return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}
}

bool_t
compare_scsi_info(scsi_info *exp_scsi_info, scsi_info *rep_scsi_info)
{
	if (exp_scsi_info != rep_scsi_info) {

		if (exp_scsi_info->scsi_info_len !=
		    rep_scsi_info->scsi_info_len)
			return (FALSE);

		if (!compare_ndmp_device_info(exp_scsi_info->scsi_info_val,
		    rep_scsi_info->scsi_info_val))
			return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}
}

bool_t
compare_tape_info(tape_info *exp_tape_info, tape_info *rep_tape_info)
{

	if (exp_tape_info != 0 && rep_tape_info != 0) {

		if (exp_tape_info->tape_info_len !=
		    rep_tape_info->tape_info_len)
			return (FALSE);

		if (compare_ndmp_device_info(exp_tape_info->tape_info_val,
		    rep_tape_info->tape_info_val))
			return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}
}

/*
 * compare_ndmp_fs_info() : Compares the ndmp_fs_info
 * structure.
 *
 * Arguments :
 * 	ndmp_fs_info * - Pointer to the expected ndmp_fs_info
 * 	object.
 * 	ndmp_fs_info * - Pointer to the reply ndmp_fs_info object.
 *
 * Returns :
 * 	bool_t - TRUE if success and FALSE if failure.
 */
static bool_t
compare_ndmp_fs_info(ndmp_fs_info *expFsInfo, ndmp_fs_info *repFsInfo)
{

	if (expFsInfo != 0 && repFsInfo != 0) {

		if (!(strcmp(expFsInfo->fs_type, repFsInfo->fs_type)))
			return (FALSE);

		if (!(strcmp(expFsInfo->fs_logical_device,
		    repFsInfo->fs_logical_device)))
			return (FALSE);

		if (!(strcmp(expFsInfo->fs_physical_device,
		    repFsInfo->fs_physical_device)))
			return (FALSE);

		if (!compare_ndmp_u_quad(expFsInfo->total_size,
		    repFsInfo->total_size))
			return (FALSE);

		if (!compare_ndmp_u_quad(
		    expFsInfo->used_size, repFsInfo->used_size))
			return (FALSE);

		if (!compare_ndmp_u_quad(
		    expFsInfo->avail_size, repFsInfo->avail_size))
			return (FALSE);

		if (!compare_ndmp_u_quad(expFsInfo->total_inodes,
		    repFsInfo->total_inodes))
			return (FALSE);

		if (!compare_ndmp_u_quad(expFsInfo->used_inodes,
		    repFsInfo->used_inodes))
			return (FALSE);

		if (expFsInfo->fs_env.fs_env_len !=
		    repFsInfo->fs_env.fs_env_len)
			return (FALSE);

		if (!compare_ndmp_pval(expFsInfo->fs_env.fs_env_val,
		    repFsInfo->fs_env.fs_env_val))
			return (FALSE);

		if (!(strcmp(expFsInfo->fs_status, repFsInfo->fs_status)))
			return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}
}

/*
 * compare_fs_info() : Compares fs_info structures and returns boolean
 * value, true of false.
 */
bool_t
compare_fs_info(fs_info *exp_fs_info, fs_info *rep_fs_info)
{

	if (exp_fs_info != 0 && rep_fs_info != 0) {

		if (exp_fs_info->fs_info_len != rep_fs_info->fs_info_len)
			return (FALSE);

		if (compare_ndmp_fs_info(exp_fs_info->fs_info_val,
		    rep_fs_info->fs_info_val))
			return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}
}

/*
 * compare_ndmp_butype_info() : Compares ndmp_butype_info
 * structures and returns boolean
 * value, true of false.
 */
bool_t
compare_ndmp_butype_info(ndmp_butype_info *exp_ndmp_butype_info,
    ndmp_butype_info *rep_ndmp_butype_info)
{

	if (exp_ndmp_butype_info != 0 && rep_ndmp_butype_info != 0) {

		if (!(strcmp(exp_ndmp_butype_info->butype_name,
		    rep_ndmp_butype_info->butype_name)))
			return (FALSE);

		if (exp_ndmp_butype_info->default_env.default_env_len !=
		    rep_ndmp_butype_info->default_env.default_env_len)
			return (FALSE);

		if (!compare_ndmp_pval(
		    exp_ndmp_butype_info->default_env.default_env_val,
		    rep_ndmp_butype_info->default_env.default_env_val))
			return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}

}

bool_t
compare_ndmp_auth_attr(ndmp_auth_attr *exp_auth_attr,
    ndmp_auth_attr *rep_auth_attr)
{

	if (exp_auth_attr != 0 && rep_auth_attr != 0) {

		if (exp_auth_attr->auth_type != rep_auth_attr->auth_type)
			return (FALSE);

		if (!(strcmp(exp_auth_attr->ndmp_auth_attr_u.challenge,
		    rep_auth_attr->ndmp_auth_attr_u.challenge)))
			return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}
}

static bool_t
compare_ndmp_auth_text(ndmp_auth_text *exp_auth_text,
    ndmp_auth_text *rep_auth_text)
{

	if (!(strcmp(exp_auth_text->auth_id, rep_auth_text->auth_id)))
		return (FALSE);

	if (!(strcmp(exp_auth_text->auth_password,
	    rep_auth_text->auth_password)))
		return (FALSE);

	return (TRUE);
}

/*
 * compare_ndmp_auth_md5() : Compares ndmp_auth_md5
 * structures and returns boolean
 * value, true of false.
 */
static bool_t
compare_ndmp_auth_md5(ndmp_auth_md5 *exp_auth_md5,
    ndmp_auth_md5 *rep_auth_md5)
{

	if (!(strcmp(exp_auth_md5->auth_id, rep_auth_md5->auth_id)))
		return (FALSE);

	if (!(strcmp(exp_auth_md5->auth_digest, rep_auth_md5->auth_digest)))
		return (FALSE);

	return (TRUE);

}

bool_t
compare_datain(void *exp, void *rep)
{

	if (((datain *) exp) == 0 || ((datain *) rep) == 0)
		return (FALSE);
	if (((datain *) exp)->datain_len != ((datain *) rep)->datain_len)
		return (FALSE);
	if (!(strcmp(((datain *) exp)->datain_val,
	    ((datain *) rep)->datain_val)))
		return (FALSE);

	return (TRUE);
}

bool_t
compare_ext_sense(void *exp, void *rep)
{

	if (((ext_sense *) exp) == 0 || ((ext_sense *) rep) == 0)
		return (FALSE);
	if (((ext_sense *) exp)->ext_sense_len !=
	    ((ext_sense *) rep)->ext_sense_len)
		return (FALSE);
	if (!(strcmp(((ext_sense *) exp)->ext_sense_val,
	    ((ext_sense *) rep)->ext_sense_val)))
		return (FALSE);

	return (TRUE);
}

bool_t
compare_data_in(ndmp_tape_read_reply *exp, ndmp_tape_read_reply *rep)
{

	if (exp->data_in.data_in_len != rep->data_in.data_in_len)
		return (FALSE);

	if (!(strcmp(exp->data_in.data_in_val, rep->data_in.data_in_val)))
		return (FALSE);

	return (TRUE);

}

/*
 * compare_ndmp_auth_data() : Compares ndmp_auth_data
 * structures and returns boolean
 * value, true of false.
 */
bool_t
compare_ndmp_auth_data(ndmp_auth_data *exp_auth_data,
    ndmp_auth_data *rep_auth_data)
{

	if (exp_auth_data != 0 && rep_auth_data != 0) {
		if (exp_auth_data->auth_type != rep_auth_data->auth_type)
			return (FALSE);

		if (exp_auth_data->auth_type == 1 &&
		    rep_auth_data->auth_type == 1)
			if (!compare_ndmp_auth_text(
			    &(exp_auth_data->ndmp_auth_data_u.auth_text),
			    &(rep_auth_data->ndmp_auth_data_u.auth_text)))
				return (FALSE);

		if (exp_auth_data->auth_type == 2 &&
		    rep_auth_data->auth_type == 2)
			if (!compare_ndmp_auth_md5(
			    &(exp_auth_data->ndmp_auth_data_u.auth_md5),
			    &(rep_auth_data->ndmp_auth_data_u.auth_md5)))
				return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}
}

bool_t
compare_addr_types(addr_types *exp_addr_types, addr_types *rep_addr_types)
{

	if (exp_addr_types != 0 && rep_addr_types != 0) {

		if (exp_addr_types->addr_types_len !=
		    rep_addr_types->addr_types_len)
			return (FALSE);

		if (exp_addr_types->addr_types_val !=
		    rep_addr_types->addr_types_val)
			return (FALSE);

		return (TRUE);

	} else {
		return (FALSE);
	}

}

/*
 * print_ndmp_class_list() : Prints ndmp_class_list
 * structure.
 */
static void
print_ndmp_class_list(FILE *out, ndmp_class_list *classList)
{

	if (classList != 0) {
		(void) ndmp_lprintf(out, "ext_class_id %d \n",
		    classList->ext_class_id);
		(void) ndmp_lprintf(out, "ext_version.ext_version_len %d \n",
		    classList->ext_version.ext_version_len);
		(void) ndmp_lprintf(out, "ext_version.ext_version_val %d \n",
		    *(classList->ext_version.ext_version_val));

	}
}

void
print_class_list(FILE *out, class_list *classList)
{

	if (classList != 0) {
		(void) ndmp_lprintf(out, "class_list_len %d \n",
		    classList->class_list_len);
		print_ndmp_class_list(out, classList->class_list_val);
	}
}

/*
 * print_ndmp_device_capability() : Prints ndmp_device_capability
 * structure.
 */
static void
print_ndmp_device_capability(FILE *out, ndmp_device_capability *caplist_val)
{

	if (caplist_val == 0)
		return;

	(void) ndmp_lprintf(out, "caplist_val->device %s \n",
	    caplist_val->device);
	(void) ndmp_lprintf(out, "caplist_val->attr %d \n",
	    (int)caplist_val->attr);
	(void) ndmp_lprintf(out, "caplist_val->capability.capability_len %d \n",
	    caplist_val->capability.capability_len);
	int i = 0;
	for (i = 0; i < caplist_val->capability.capability_len; i++) {
		print_ndmp_pval(out, caplist_val->capability.capability_val);
		if (i < (caplist_val->capability.capability_len - 1))
			(caplist_val->capability.capability_val)++;
	}
}

static void
print_ndmp_device_info(FILE *out, ndmp_device_info *ndmpDevInfo)
{

	if (ndmpDevInfo != 0) {

		(void) ndmp_lprintf(
		    out, "ndmpDevInfo->model %s \n", ndmpDevInfo->model);
		(void) ndmp_lprintf(out,
		    "ndmpDevInfo->caplist.caplist_len %d \n",
		    ndmpDevInfo->caplist.caplist_len);
		print_ndmp_device_capability(
		    out, ndmpDevInfo->caplist.caplist_val);

	}

}

/*
 * print_scsi_info() : Prints scsi_info
 * structure.
 */
void
print_scsi_info(FILE *out, scsi_info *scsiInfo)
{

	if (scsiInfo != 0) {

		(void) ndmp_lprintf(out, "scsi_info.scsi_info_len %d \n",
		    scsiInfo->scsi_info_len);
		print_ndmp_device_info(out, scsiInfo->scsi_info_val);
	}
}

void
print_tape_info(FILE *out, tape_info *tapeInfo)
{

	if (tapeInfo != 0) {

		(void) ndmp_lprintf(
		    out, "tape_info_len %d \n", tapeInfo->tape_info_len);
		print_ndmp_device_info(out, tapeInfo->tape_info_val);

	}
}

/*
 * print_ndmp_fs_info() : Prints ndmp_fs_info
 * structure.
 */
static void
print_ndmp_fs_info(FILE *out, ndmp_fs_info *fs_info)
{

	if (fs_info != NULL) {
		if (fs_info->fs_type != NULL) {
			(void) ndmp_lprintf(out, "fs_type %s \n",
			    fs_info->fs_type);
			(void) ndmp_lprintf(out, "fs_logical_device %s \n",
			    fs_info->fs_logical_device);
			(void) ndmp_lprintf(out, "fs_physical_device %s\n",
			    fs_info->fs_physical_device);

			print_ndmp_u_quad(out, fs_info->total_size);
			print_ndmp_u_quad(out, fs_info->used_size);
			print_ndmp_u_quad(out, fs_info->avail_size);
			print_ndmp_u_quad(out, fs_info->total_inodes);
			print_ndmp_u_quad(out, fs_info->used_inodes);

			(void) ndmp_lprintf(out,
			    "fs_env_len %d \n", fs_info->fs_env.fs_env_len);

			int i = 0;
			for (i = 0; i < fs_info->fs_env.fs_env_len; i++) {
				print_ndmp_pval(out,
				    fs_info->fs_env.fs_env_val);
				if (i < (fs_info->fs_env.fs_env_len - 1))
					(fs_info->fs_env.fs_env_val)++;
			}
			(void) ndmp_lprintf(out,
			    "fs_status %s \n", fs_info->fs_status);
		}

	}
}

void
print_fs_info(FILE *out, fs_info *fsInfo)
{
	if (fsInfo != NULL) {
		(void) ndmp_lprintf(
		    out, "fsInfo->fs_info_len %d \n", fsInfo->fs_info_len);
		print_ndmp_fs_info(out, fsInfo->fs_info_val);
	}
}

static void
print_ndmp_butype_info(FILE *out, ndmp_butype_info *butype_info_val)
{

	if (butype_info_val == 0)
		return;

	if (butype_info_val->butype_name != 0)
		(void) ndmp_lprintf(out, "butype_name %s\n",
		    butype_info_val->butype_name);
	(void) ndmp_lprintf(out, "default_env_len %d\n",
	    butype_info_val->default_env.default_env_len);

	int i = 0;
	for (i = 0; i < butype_info_val->default_env.default_env_len; i++) {
		print_ndmp_pval(out,
		    butype_info_val->default_env.default_env_val);
		if (i < (butype_info_val->default_env.default_env_len - 1))
			(butype_info_val->default_env.default_env_val)++;
	}
	(void) ndmp_lprintf(out, "attrs %d \n", (int)butype_info_val->attrs);


}

/*
 * print_butype_info() : Prints butype_info
 * structure.
 */
void
print_butype_info(FILE *out, butype_info *butypeInfo)
{
	if (butypeInfo != 0) {

		(void) ndmp_lprintf(out, "butype_info_len %d \n",
		    butypeInfo->butype_info_len);

		print_ndmp_butype_info(out, butypeInfo->butype_info_val);
	}
}

static void
print_ndmp_auth_text(FILE *out, ndmp_auth_text *auth_text)
{
	if (auth_text != 0) {
		(void) ndmp_lprintf(out, "auth_id %c \n",
		    *(auth_text->auth_id));
		(void) ndmp_lprintf(
		    out, "auth_password %s \n", (auth_text->auth_password));
	} else {
		(void) ndmp_lprintf(
		    out, "print_ndmp_auth_text: auth_text is null\n");
	}
}

static void
print_ndmp_auth_md5(FILE *out, ndmp_auth_md5 *auth_md5)
{
	if (auth_md5 != 0) {
		(void) ndmp_lprintf(out, "auth_id %c \n", *(auth_md5->auth_id));
		(void) ndmp_lprintf(
		    out, "auth_digest %s \n", (auth_md5->auth_digest));
	} else {
		(void) ndmp_lprintf(out,
		    "print_ndmp_auth_md5: auth_md5is null\n");
	}
}

static void
print_scsi_status(void *rep)
{

	ndmp_execute_cdb_reply *reply;
	reply = (ndmp_execute_cdb_reply*) rep;
	if (!reply->status)
		(void) ndmp_dprintf(logfile,
		    "print_scsi_status: Status GOOD \n");
	else
		(void) ndmp_dprintf(logfile,
		    "print_scsi_status: Status BAD \n");

}

/*
 * print_sense_data() : Prints scsi_extended_sense
 * structure.
 */
static void
print_sense_data(void *rep)
{

	ndmp_execute_cdb_reply *reply;
	reply = (ndmp_execute_cdb_reply*) rep;
	struct scsi_extended_sense *sense;

	sense = (struct scsi_extended_sense *)reply->ext_sense.ext_sense_val;
	if (sense != 0 && sense->es_add_code != 0)
		(void) ndmp_dprintf(logfile,
		    "Additional Sense Code is 0x%x \n", sense->es_add_code);
	if (sense != 0 && sense->es_qual_code != 0)
		(void) ndmp_dprintf(
		    logfile, "Additional Sense Code Qualifier is 0x%x \n",
		    sense->es_qual_code);
}

/*
 * print_datain() : Prints the cdb based on the cdb number.
 * Calls appropriate method to print the data.
 *
 * Arguments :
 * 	FILE * - Handle to log file.
 * 	void *rep - Reply object from teh ndmp server.
 */
void
print_datain(FILE *out, void *rep)
{

	if (rep != 0) {
		switch (cdbNum) {
		case INQUIRYCDB:
			(void) ndmp_dprintf(out, "INQUIRYCDB\n");
			ndmp_execute_cdb_reply *reply =
			    (ndmp_execute_cdb_reply*) rep;
			struct scsi_inquiry *inq_data;
			inq_data = (struct scsi_inquiry *)
			    (reply->datain.datain_val);
			if (inq_data != 0 && inq_data->inq_vid != 0)
				(void) ndmp_lprintf(out,
				    "print_datain: Vendor  %s\n"
				    "Product %s\n", inq_data->inq_vid,
				    inq_data->inq_pid);
			break;
		case TESTUNITREADYCDB:
			print_scsi_status(rep);
			print_sense_data(rep);
			break;
		case LOADCDB:
			print_scsi_status(rep);
			break;
		case UNLOADCDB:
			print_scsi_status(rep);
			break;
		case MODESELECTCDB:
			print_scsi_status(rep);
			break;
		case MODESENSECDB:
			print_scsi_status(rep);
			break;
		case READCDB:
			print_scsi_status(rep);
			break;
		case READBLOCKLIMITSCDB:
			print_scsi_status(rep);
			break;
		case REWINDCDB:
			print_scsi_status(rep);
			break;
		case SPACECDB:
			print_scsi_status(rep);
			break;
		case WRITECDB:
			print_scsi_status(rep);
			break;
		case WRITEFILEMARKSCDB:
			print_scsi_status(rep);
			break;
		case MOVEMEDIUMCDB:
			print_scsi_status(rep);
			break;
		case REQUESTSENSECDB:
			print_scsi_status(rep);
			break;
		case SETTARGETPORTGROUPSCDB:
			print_scsi_status(rep);
			break;
		case READELEMENTSTATUSCDB:
			print_scsi_status(rep);
			break;
		default:
			(void) printf(" ");
		}
	}
}

void
print_ext_sense(FILE *out, void *rep)
{
	if (rep != 0) {
		if (((ext_sense*) rep)->ext_sense_len != 0) {
			(void) ndmp_lprintf(out, "ext_sense_len %d \n",
			    ((ext_sense*) rep)->ext_sense_len);
			(void) ndmp_lprintf(out, "ext_sense_val %s \n",
			    ((ext_sense*) rep)->ext_sense_val);
		}
	}
}

void
print_data_in(FILE *out, ndmp_tape_read_reply *rep)
{

	if (rep != 0) {
		(void) ndmp_lprintf(
		    out, "data_in_len %d \n", rep->data_in.data_in_len);

		if (rep->data_in.data_in_val != 0) {
			(void) ndmp_lprintf(out, "data_in_val %s \n",
			    rep->data_in.data_in_val);
		}
	}
}

void
print_ndmp_auth_data(FILE *out, ndmp_auth_data *auth_data)
{
	if (auth_data != 0) {
		if (auth_data->auth_type == 0) {
			(void) ndmp_lprintf(out,
			    "auth_type = NDMP_AUTH_NONE \n");
		} else if (auth_data->auth_type == 1) {
			(void) ndmp_lprintf(out,
			    "auth_type = NDMP_AUTH_TEXT\n");
			print_ndmp_auth_text(
			    out, &(auth_data->ndmp_auth_data_u.auth_text));
		} else if (auth_data->auth_type == 2) {
			(void) ndmp_lprintf(out, "auth_type = NDMP_AUTH_MD5\n");
			print_ndmp_auth_md5(
			    out, &(auth_data->ndmp_auth_data_u.auth_md5));
		} else
			(void) ndmp_lprintf(out,
			    "auth_type != any auth type \n");
	} else {
		(void) ndmp_lprintf(out, "auth_data is null\n");
	}
}

void
print_addr_types(FILE *out, addr_types *addrType)
{

	if (addrType != 0) {
		if (addrType->addr_types_len != NULL)
			(void) ndmp_lprintf(out, "addr_types_len %d \n",
			    addrType->addr_types_len);
		print_ndmp_addr_type(out, *(addrType->addr_types_val));

	}
}

static void
print_ndmp_auth_type(FILE *out, ndmp_auth_type *auth_type)
{

	if (*auth_type == 0)
		(void) ndmp_lprintf(out, "ndmp_auth_type NDMP_AUTH_NONE\n");
	else if (*auth_type == 1)
		(void) ndmp_lprintf(out, "ndmp_auth_type NDMP_AUTH_TEXT\n");
	else
		(void) ndmp_lprintf(out, "ndmp_auth_type NDMP_AUTH_MD5\n");
}

void
print_ndmp_auth_attr(FILE *out, ndmp_auth_attr *auth_attr)
{

	if (auth_attr != 0) {

		print_ndmp_auth_type(out, &(auth_attr->auth_type));
		(void) ndmp_lprintf(
		    out, "ndmp_auth_attr->ndmp_auth_attr_u.challenge %s\n",
		    auth_attr->ndmp_auth_attr_u.challenge);

	}

}
/* Print functions end============= */

/* Memory cleaning functions start */

/*
 * clear_mover_connect_request() : Cleans up the memory for
 * ndmp_mover_connect_request structure.
 *
 * Arguments :
 * 	void *request - Pointer to ndmp_mover_connect_request structure.
 */
void
clear_mover_connect_request(void *request)
{
	ndmp_mover_connect_request *req;
	ndmp_tcp_addr *tcp_addr_val;
	ndmp_pval *addr_env_val;

	req = (ndmp_mover_connect_request*) request;
	if (req->addr.addr_type == NDMP_ADDR_TCP) {
		if (req != 0)
			tcp_addr_val =
			    req->addr.ndmp_addr_u.tcp_addr.tcp_addr_val;
		if (tcp_addr_val != 0)
			addr_env_val = tcp_addr_val->addr_env.addr_env_val;

		if (addr_env_val != 0) {
			if (addr_env_val->name != 0)
				free(addr_env_val->name);
			if (addr_env_val->value != 0) {
				free(addr_env_val->value);
				free(addr_env_val);
			}
			free(tcp_addr_val);
		}
	}
}

void
clear_data_start_recover_request(void *request)
{
	ndmp_data_start_recover_request *req;

	req = (ndmp_data_start_recover_request*) request;

	if (req->butype_name != 0)
		free(req->butype_name);
	if (req->env.env_val != 0 && req->env.env_val->name != 0)
		free(req->env.env_val->name);
	if (req->env.env_val != 0 && req->env.env_val->value != 0)
		free(req->env.env_val->value);
	if (req->env.env_val != 0)
		free(req->env.env_val);

	if (req->nlist.nlist_val != 0 &&
	    req->nlist.nlist_val->original_path != 0)
		free(req->nlist.nlist_val->original_path);
	if (req->nlist.nlist_val != 0 &&
	    req->nlist.nlist_val->destination_dir != 0)
		free(req->nlist.nlist_val->destination_dir);
	if (req->nlist.nlist_val != 0 && req->nlist.nlist_val->name != 0)
		free(req->nlist.nlist_val->name);

}

void
clear_data_start_backup_request(void *request)
{
	ndmp_data_start_backup_request *req;

	req = (ndmp_data_start_backup_request*) request;

	if (req->butype_name != 0)
		free(req->butype_name);
	if (req->env.env_val != 0 && req->env.env_val->name != 0)
		free(req->env.env_val->name);
	if (req->env.env_val != 0 && req->env.env_val->value != 0)
		free(req->env.env_val->value);
	if (req->env.env_val != 0)
		free(req->env.env_val);

}

/*
 * clear_connect_client_auth_request() : Cleans up the memory for
 * ndmp_connect_client_auth_request structure.
 *
 * Arguments :
 * 	void *request - Pointer to ndmp_connect_client_auth_request structure.
 */
void
clear_connect_client_auth_request(void *request)
{

	ndmp_connect_client_auth_request *req = NULL;
	ndmp_auth_data *p_auth_data = NULL;
	ndmp_auth_text *p_auth_text = NULL;
	ndmp_auth_md5 *p_auth_md5 = NULL;

	req = (ndmp_connect_client_auth_request*) request;
	p_auth_data = &(req->auth_data);

	*p_auth_text = p_auth_data->ndmp_auth_data_u.auth_text;
	if (p_auth_text->auth_id != 0)
		free(p_auth_text->auth_id);
	if (p_auth_text->auth_password)
		free(p_auth_text->auth_password);

	*p_auth_md5 = p_auth_data->ndmp_auth_data_u.auth_md5;
	if (p_auth_md5->auth_id != 0)
		free(p_auth_md5->auth_id);

}

void
clear_config_get_host_info(void *reply)
{

	ndmp_config_get_host_info_reply *rep;

	rep = (ndmp_config_get_host_info_reply*) reply;

	if (rep != 0) {
		free(rep->hostname);
		free(rep->os_type);
		free(rep->os_vers);
		free(rep->hostid);
	}
}

void
clear_config_get_server_info(void *reply)
{

	ndmp_config_get_server_info_reply *rep;

	rep = (ndmp_config_get_server_info_reply*) reply;

	if (rep != 0) {
		free(rep->vendor_name);
		free(rep->product_name);
		free(rep->revision_number);
		if (rep->auth_type.auth_type_val != 0)
			free(rep->auth_type.auth_type_val);
	}
}

void
clear_config_get_fs_info(void *reply)
{

	ndmp_config_get_fs_info_reply *rep;
	ndmp_fs_info *fs_info_val;

	rep = (ndmp_config_get_fs_info_reply*) reply;
	fs_info_val = rep->fs_info.fs_info_val;

	if (fs_info_val != 0) {
		if (fs_info_val->fs_type != 0)
			free(fs_info_val->fs_type);
		if (fs_info_val->fs_logical_device != 0)
			free(fs_info_val->fs_logical_device);
		if (fs_info_val->fs_physical_device != 0)
			free(fs_info_val->fs_physical_device);
		if (fs_info_val->fs_env.fs_env_val != 0)
			free(fs_info_val->fs_env.fs_env_val);
		if (fs_info_val->fs_status != 0)
			free(fs_info_val->fs_status);
	}
}

/*
 * clear_config_get_tape_info() : Cleans up the memory for
 * ndmp_config_get_tape_info_reply structure.
 *
 * Arguments :
 * 	void *request - Pointer to ndmp_config_get_tape_info_reply
 * 	structure.
 */
void
clear_config_get_tape_info(void *reply)
{

	ndmp_config_get_tape_info_reply *rep = 0;
	ndmp_device_info *dev_info = 0;
	ndmp_device_capability *caplist_val = 0;

	rep = (ndmp_config_get_tape_info_reply*) reply;

	if (rep == 0)
		return;
	if (rep->tape_info.tape_info_val != 0)
		dev_info = rep->tape_info.tape_info_val;
	if (dev_info != 0 && dev_info->model != 0) {
		free(dev_info->model);
		caplist_val = dev_info->caplist.caplist_val;
		if (caplist_val == 0)
			return;
		free(caplist_val->device);
		if (caplist_val->capability.capability_val->name != 0) {
			free(caplist_val->capability.capability_val->name);
			free(caplist_val->capability.capability_val->value);
		}
	}
}

void
clear_config_get_scsi_info(void *reply)
{

	ndmp_config_get_scsi_info_reply *rep = 0;
	ndmp_device_info *dev_info = 0;
	ndmp_device_capability *caplist_val = 0;

	rep = (ndmp_config_get_scsi_info_reply*) reply;

	if (rep == 0)
		return;
	if (rep->scsi_info.scsi_info_val != 0)
		dev_info = rep->scsi_info.scsi_info_val;
	if (dev_info != 0 && dev_info->model != 0) {
		free(dev_info->model);
		if (dev_info->caplist.caplist_val != 0)
			caplist_val = dev_info->caplist.caplist_val;
		if (caplist_val->device == 0)
			return;

		free(caplist_val->device);
		if (caplist_val->capability.capability_val == 0)
			return;
		if (caplist_val->capability.capability_val->name != 0)
			free(caplist_val->capability.capability_val->name);
		if (caplist_val->capability.capability_val->value != 0)
			free(caplist_val->capability.capability_val->value);
	}
}

void
clear_mover_get_state(void *reply)
{
	ndmp_mover_get_state_reply *rep = 0;
	ndmp_tcp_addr *tcp_addr_val = 0;
	ndmp_pval *addr_env_val = 0;

	rep = (ndmp_mover_get_state_reply*) reply;
	if (rep != 0) {
		tcp_addr_val =
		    rep->data_connection_addr.ndmp_addr_u.tcp_addr.tcp_addr_val;
		if (tcp_addr_val != 0) {
			addr_env_val = tcp_addr_val->addr_env.addr_env_val;
			if (addr_env_val != 0 && addr_env_val->name != 0)
				free(addr_env_val->name);
			if (addr_env_val != 0 && addr_env_val->value != 0) {
				free(addr_env_val->value);
				free(addr_env_val);
			}
			free(tcp_addr_val);
		}
	}
}

void
clear_mover_listen(void *reply)
{
	ndmp_mover_listen_reply *rep = 0;
	ndmp_tcp_addr *tcp_addr_val = 0;
	ndmp_pval *addr_env_val = 0;

	rep = (ndmp_mover_listen_reply*) reply;
	if (rep == 0)
		return;
	tcp_addr_val = rep->connect_addr.ndmp_addr_u.tcp_addr.tcp_addr_val;
	if (tcp_addr_val != 0) {
		addr_env_val = tcp_addr_val->addr_env.addr_env_val;
		if (addr_env_val != 0 && addr_env_val->name != 0)
			free(addr_env_val->name);
		if (addr_env_val != 0 && addr_env_val->value != 0) {
			free(addr_env_val->value);
			free(addr_env_val);
		}
		free(tcp_addr_val);
	}
}

/*
 * clear_data_get_env() : Cleans up the memory for
 * ndmp_data_get_env_reply structure.
 *
 * Arguments :
 * 	void *reply - Pointer to ndmp_data_get_env_reply
 * 	structure.
 */
void
clear_data_get_env(void *reply)
{
	ndmp_data_get_env_reply *rep = 0;
	ndmp_pval *addr_env_val = 0;

	rep = (ndmp_data_get_env_reply*) reply;

	if (rep != 0) {
		addr_env_val = rep->env.env_val;
		if (addr_env_val != 0 && addr_env_val->name != 0)
			free(addr_env_val->name);
		if (addr_env_val != 0 && addr_env_val->value != 0) {
			free(addr_env_val->value);
			free(addr_env_val);
		}
	}
}

void
clear_data_get_state(void *reply)
{
	ndmp_data_get_state_reply *rep = 0;
	ndmp_tcp_addr *tcp_addr_val = 0;
	ndmp_pval *addr_env_val = 0;

	rep = (ndmp_data_get_state_reply*) reply;
	if (rep == 0)
		return;
	tcp_addr_val =
	    rep->data_connection_addr.ndmp_addr_u.tcp_addr.tcp_addr_val;
	if (tcp_addr_val != 0) {
		addr_env_val = tcp_addr_val->addr_env.addr_env_val;
		if (addr_env_val != 0 && addr_env_val->name != 0)
			free(addr_env_val->name);
		if (addr_env_val != 0 && addr_env_val->value != 0) {
			free(addr_env_val->value);
			free(addr_env_val);
		}
		free(tcp_addr_val);
	}
}

/*
 * clear_data_listen() : Cleans up the memory for
 * ndmp_data_listen_reply structure.
 *
 * Arguments :
 * 	void *reply - Pointer to ndmp_data_listen_reply
 * 	structure.
 */
void
clear_data_listen(void *reply)
{
	ndmp_data_listen_reply *rep = 0;
	ndmp_tcp_addr *tcp_addr_val = 0;
	ndmp_pval *addr_env_val = 0;

	rep = (ndmp_data_listen_reply*) reply;
	if (rep == 0)
		return;

	tcp_addr_val = rep->connect_addr.ndmp_addr_u.tcp_addr.tcp_addr_val;
	if (tcp_addr_val != 0) {
		addr_env_val = tcp_addr_val->addr_env.addr_env_val;
		if (addr_env_val != 0 && addr_env_val->name != 0)
			free(addr_env_val->name);
		if (addr_env_val != 0 && addr_env_val->value != 0) {
			free(addr_env_val->value);
			free(addr_env_val);
		}
		free(tcp_addr_val);
	}
}

void
clear_connect_server_auth(void *reply)
{
	if (reply != NULL)
		(void) ndmp_lprintf(logfile,
		    "clear_connect_server_auth: reply %p",
		    reply);
}

/*
 * stop_mover()
 * This method checks what is the state of ndmp server and based on the state
 * sends abort or stop request.
 *
 * Arguments :
 * outfile - Log file
 * conn - connection handle
 *
 * Return :
 * 0 - Successful
 * 1 - Failure
 */
int
stop_mover(FILE *outfile, conn_handle *conn)
{
	int state, ret;
	state = get_data_state(outfile, conn);
	if (state == NDMP_DATA_STATE_HALTED)
		ret = data_stop_core(NDMP_NO_ERR, outfile, conn);
	else {
		ret = data_abort_core(NDMP_NO_ERR, outfile, conn);
		ret += data_stop_core(NDMP_NO_ERR, outfile, conn);
	}
	return (ret);
}

/*
 * stop_data()
 * This method checks what is the state of ndmp server and based on the state
 * sends abort or stop request.
 *
 * Arguments :
 * outfile - Log file
 * conn - connection handle
 *
 * Return :
 * 0 - Successful
 * 1 - Failure
 */
int
stop_data(FILE *outfile, conn_handle *conn)
{
	int state, ret;
	state = get_data_state(outfile, conn);
	if (state == NDMP_DATA_STATE_HALTED)
		ret = data_stop_core(NDMP_NO_ERR, outfile, conn);
	else {
		ret = data_abort_core(NDMP_NO_ERR, outfile, conn);
		ret += data_stop_core(NDMP_NO_ERR, outfile, conn);
	}
	return (ret);
}
