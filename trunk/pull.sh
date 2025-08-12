#!/usr/bin/bash
#
# BSD 3 Clause License
#
# Copyright (c) 2007, The Storage Networking Industry Association.
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
#       - Neither the name of The Storage Networking Industry Association (SNIA)
#         nor the names of its contributors may be used to endorse or promote
#         products derived from this software without specific prior written
#         permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

# Get local copy of OpenSolaris source via mercurial
echo Pulling the changes over, this might take a few minutes
hg clone ssh://anon@hg.opensolaris.org/hg/onnv/onnv-gate my-opensolaris

# Copy files
echo Copying necessary files...
echo usr/src; mkdir -p usr/src
echo usr/src/Makefile.master; cp my-opensolaris/usr/src/Makefile.master usr/src/Makefile.master
echo usr/src/Makefile.master.64; cp my-opensolaris/usr/src/Makefile.master.64 usr/src/Makefile.master.64
echo usr/src/Makefile.msg.targ; cp my-opensolaris/usr/src/Makefile.msg.targ usr/src/Makefile.msg.targ
echo usr/src/Makefile.noget; cp my-opensolaris/usr/src/Makefile.noget usr/src/Makefile.noget
echo usr/src/cmd; mkdir usr/src/cmd
echo usr/src/cmd/Makefile.cmd; cp my-opensolaris/usr/src/cmd/Makefile.cmd usr/src/cmd/Makefile.cmd
echo usr/src/cmd/Makefile.targ; cp my-opensolaris/usr/src/cmd/Makefile.targ usr/src/cmd/Makefile.targ
echo usr/src/common; mkdir usr/src/common
echo usr/src/common/mapfiles; mkdir usr/src/common/mapfiles
echo usr/src/common/mapfiles/common; mkdir usr/src/common/mapfiles/common
echo usr/src/common/mapfiles/common/map.noexstk; cp my-opensolaris/usr/src/common/mapfiles/common/map.noexstk usr/src/common/mapfiles/common/map.noexstk
echo usr/src/common/mapfiles/i386; mkdir usr/src/common/mapfiles/i386
echo usr/src/common/mapfiles/i386/map.noexdata; cp my-opensolaris/usr/src/common/mapfiles/i386/map.noexdata usr/src/common/mapfiles/i386/map.noexdata
echo usr/src/common/mapfiles/i386/map.pagealign; cp my-opensolaris/usr/src/common/mapfiles/i386/map.pagealign usr/src/common/mapfiles/i386/map.pagealign
echo usr/src/lib; mkdir usr/src/lib
echo usr/src/lib/Makefile.lib; cp my-opensolaris/usr/src/lib/Makefile.lib usr/src/lib/Makefile.lib
echo usr/src/lib/Makefile.lib.64; cp my-opensolaris/usr/src/lib/Makefile.lib.64 usr/src/lib/Makefile.lib.64
echo usr/src/lib/Makefile.targ; cp my-opensolaris/usr/src/lib/Makefile.targ usr/src/lib/Makefile.targ
echo usr/src/pkgdefs; mkdir usr/src/pkgdefs
echo usr/src/pkgdefs/Makefile.com; cp my-opensolaris/usr/src/pkgdefs/Makefile.com usr/src/pkgdefs/Makefile.com
echo usr/src/pkgdefs/Makefile.targ; cp my-opensolaris/usr/src/pkgdefs/Makefile.targ usr/src/pkgdefs/Makefile.targ
echo usr/src/pkgdefs/awk_pkginfo; #cp my-opensolaris/usr/src/pkgdefs/awk_pkginfo usr/src/pkgdefs/awk_pkginfo
echo usr/src/pkgdefs/common_files; mkdir usr/src/pkgdefs/common_files
echo usr/src/pkgdefs/common_files/copyright; #cp my-opensolaris/usr/src/pkgdefs/common_files/copyright usr/src/pkgdefs/common_files/copyright
echo usr/src/pkgdefs/common_files/depend; cp my-opensolaris/usr/src/pkgdefs/common_files/depend usr/src/pkgdefs/common_files/depend
echo usr/src/pkgdefs/common_files/i.manifest; cp my-opensolaris/usr/src/pkgdefs/common_files/i.manifest usr/src/pkgdefs/common_files/i.manifest
echo usr/src/pkgdefs/common_files/r.manifest; cp my-opensolaris/usr/src/pkgdefs/common_files/r.manifest usr/src/pkgdefs/common_files/r.manifest

echo usr/src/cmd/Makefile; cp my-opensolaris/usr/src/cmd/Makefile usr/src/cmd/Makefile
echo usr/src/pkgdefs/; cp my-opensolaris/usr/src/pkgdefs/build_copyright.sh usr/src/pkgdefs/
echo usr/src/pkgdefs/; cp my-opensolaris/usr/src/pkgdefs/bld_awk_pkginfo.ksh usr/src/pkgdefs/
echo usr/src/pkgdefs/SUNWndmpu; cp -r my-opensolaris/usr/src/pkgdefs/SUNWndmpu usr/src/pkgdefs/SUNWndmpu
echo usr/src/pkgdefs/SUNWndmpr; cp -r my-opensolaris/usr/src/pkgdefs/SUNWndmpr usr/src/pkgdefs/SUNWndmpr
echo usr/src/pkgdefs/SUNW0on; mkdir usr/src/pkgdefs/SUNW0on
echo usr/src/pkgdefs/SUNW0on/prototype_com; cp -r my-opensolaris/usr/src/pkgdefs/SUNW0on/prototype_com usr/src/pkgdefs/SUNW0on/prototype_com
echo usr/src/pkgdefs/Makefile; cp my-opensolaris/usr/src/pkgdefs/Makefile usr/src/pkgdefs/Makefile
echo usr/src/pkgdefs/SUNWcsu; mkdir usr/src/pkgdefs/SUNWcsu
echo usr/src/pkgdefs/SUNWcsu/prototype_com; cp -r my-opensolaris/usr/src/pkgdefs/SUNWcsu/prototype_com usr/src/pkgdefs/SUNWcsu/prototype_com
echo usr/src/lib/libsecdb; mkdir usr/src/lib/libsecdb
echo usr/src/lib/libsecdb/prof_attr.txt; cp my-opensolaris/usr/src/lib/libsecdb/prof_attr.txt usr/src/lib/libsecdb/prof_attr.txt
echo usr/src/lib/libsecdb/help; mkdir usr/src/lib/libsecdb/help
echo usr/src/lib/libsecdb/help/auths; mkdir usr/src/lib/libsecdb/help/auths
echo usr/src/lib/libsecdb/help/auths/Makefile; cp my-opensolaris/usr/src/lib/libsecdb/help/auths/Makefile usr/src/lib/libsecdb/help/auths/Makefile
echo usr/src/lib/libsecdb/help/auths/AuthReadNDMP.html; cp my-opensolaris/usr/src/lib/libsecdb/help/auths/AuthReadNDMP.html usr/src/lib/libsecdb/help/auths/AuthReadNDMP.html
echo usr/src/lib/libsecdb/help/auths/SmfValueNDMP.html; cp my-opensolaris/usr/src/lib/libsecdb/help/auths/SmfValueNDMP.html usr/src/lib/libsecdb/help/auths/SmfValueNDMP.html
echo usr/src/lib/libsecdb/help/auths/SmfNDMPStates.html; cp my-opensolaris/usr/src/lib/libsecdb/help/auths/SmfNDMPStates.html usr/src/lib/libsecdb/help/auths/SmfNDMPStates.html
echo usr/src/lib/libsecdb/help/profiles; mkdir usr/src/lib/libsecdb/help/profiles
echo usr/src/lib/libsecdb/help/profiles/Makefile; cp my-opensolaris/usr/src/lib/libsecdb/help/profiles/Makefile usr/src/lib/libsecdb/help/profiles/Makefile
echo usr/src/lib/libsecdb/help/profiles/RtNDMPMngmnt.html; cp my-opensolaris/usr/src/lib/libsecdb/help/profiles/RtNDMPMngmnt.html usr/src/lib/libsecdb/help/profiles/RtNDMPMngmnt.html
echo usr/src/lib/libsecdb/auth_attr.txt; cp my-opensolaris/usr/src/lib/libsecdb/auth_attr.txt usr/src/lib/libsecdb/auth_attr.txt
echo usr/src/lib/Makefile; cp my-opensolaris/usr/src/lib/Makefile usr/src/lib/Makefile
echo usr/src/Makefile.lint; cp my-opensolaris/usr/src/Makefile.lint usr/src/Makefile.lint

echo usr/src/pkgdefs/license_files; mkdir usr/src/pkgdefs/license_files
echo usr/src/pkgdefs/license_files/cr_Sun; cp my-opensolaris/usr/src/pkgdefs/license_files/cr_Sun usr/src/pkgdefs/license_files
echo usr/src/pkgdefs/license_files/lic_OSBL_preamble; cp my-opensolaris/usr/src/pkgdefs/license_files/lic_OSBL_preamble usr/src/pkgdefs/license_files
echo usr/src/tools; mkdir usr/src/tools
echo usr/src/tools/opensolaris; mkdir usr/src/tools/opensolaris
echo usr/src/tools/opensolaris/BINARYLICENSE.txt; cp my-opensolaris/usr/src/tools/opensolaris/BINARYLICENSE.txt usr/src/tools/opensolaris
echo Finished.
