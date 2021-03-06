#
# Copyright (C) 2011-2019 Intel Corporation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in
#     the documentation and/or other materials provided with the
#     distribution.
#   * Neither the name of Intel Corporation nor the names of its
#     contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#

TOP_DIR := ../../../..
include ../../buildenv.mk

CFLAGS   += -Werror
#CXXFLAGS += -Werror
DEFINES  += -DPSE_PR_20

EPID_SDK_DIR := $(TOP_DIR)/external/epid-sdk/

INCLUDE += -I.                                   \
           -I../pse_pr                           \
           -I../pse_pr/include                   \
           -I$(TOP_DIR)/sdk/tlibcxx/include      \
           -I$(LINUX_PSW_DIR)/ae/common          \
           -I$(SGX_IPP_INC)/                     \
           -I$(LINUX_SDK_DIR)/tseal              \
           -I$(EPID_SDK_DIR)                     \
           -I$(TOP_DIR)/common/inc               \
           -I$(LINUX_PSW_DIR)/ae/inc/internal    \
           -I$(LINUX_PSW_DIR)/ae/data/constants/linux

EXTERNAL_LIB += -lsgx_tcxx -lsgx_tcrypto                \
                -L$(EPID_SDK_DIR)/epid/verifier -lverifier \
                -L$(EPID_SDK_DIR)/epid/common -lcommon

VPATH = src:../pse_pr ../pse_pr/X509_Parser
EDLFILE := ../pse_pr/pse_pr.edl
SRC := Keys.cpp prepare_hash_sha1.cpp prepare_hash_sha256.cpp prepare_hmac_sha256.cpp pse_pr.cpp sigma_crypto_layer.cpp sigma_crypto_layer_20.cpp sign_csr.cpp t_certificate_provisioning.cpp t_long_term_pairing.cpp X509Parser.cpp t_pairing_blob.cpp pse_pr_common.cpp version.cpp X509_Parser.cpp sgx_sha256_128.cpp

OBJ := $(SRC:.cpp=.o)
OBJS := $(sort $(OBJ) version.o)

.PHONY: all
all: $(SONAME) 

.PHONY: EPID
EPID:
	cd $(EPID_SDK_DIR) && ./configure prefix=/usr/local
	$(MAKE) -C $(EPID_SDK_DIR) 2> /dev/null

$(SONAME): $(OBJS) EPID
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -nostdlib -nodefaultlibs -nostartfiles $(LDTFLAGS)
	$(STRIP)  --strip-unneeded $(SONAME)

$(OBJ): $(AENAME)_t.c
$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -fno-exceptions -fno-rtti $(INCLUDE) $(DEFINES) -c $< -o $@

$(AENAME)_t.c: $(EDLFILE)
	@$(EDGER8R) --search-path ../../../../common/inc/ --trusted $<

.PHONY: clean
clean:
	@$(RM) *.o
	@$(RM) *.so
	@$(RM) *.map
	@$(RM) *_t.*
ifeq ("$(shell test -f $(EPID_SDK_DIR)/Makefile && echo Makefile exists)", "Makefile exists")
	-$(MAKE) -C $(EPID_SDK_DIR) clean
endif
	@$(RM) -r $(EPID_SDK_DIR)/Makefile $(EPID_SDK_DIR)/config.log $(EPID_SDK_DIR)/config.status

.PHONY: rebuild
rebuild:
	$(MAKE) clean
	$(MAKE) all
