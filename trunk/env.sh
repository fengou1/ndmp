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

# Set SRC and ROOT
export MACH=$1
export SRC=$2/usr/src
export ROOT=$2/proto

# Create the directories
mkdir $ROOT
mkdir $ROOT/lib
mkdir $ROOT/lib/svc
mkdir $ROOT/lib/svc/method
mkdir $ROOT/usr
mkdir $ROOT/usr/include
mkdir $ROOT/usr/lib
mkdir $ROOT/usr/lib/sparc
mkdir $ROOT/usr/lib/amd64
mkdir $ROOT/usr/sbin
mkdir $ROOT/var
mkdir $ROOT/var/src
mkdir $ROOT/var/src/manifest
mkdir $ROOT/var/src/manifest/system

/usr/bin/bash
