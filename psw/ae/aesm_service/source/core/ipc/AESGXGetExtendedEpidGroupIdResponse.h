/*
 * Copyright (C) 2011-2019 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef __AE_SGX_GET_EXTENDED_GROUP_ID_RESPONSE_H
#define __AE_SGX_GET_EXTENDED_GROUP_ID_RESPONSE_H

#include <IAEResponse.h>
#include <stdint.h>

namespace aesm
{
    namespace message
    {
            class Response_SGXGetExtendedEpidGroupIdResponse;
    };
};

class AESGXGetExtendedEpidGroupIdResponse : public IAEResponse
{
    public:
        AESGXGetExtendedEpidGroupIdResponse();  //default ... will prepare a response that will later be inflated
        AESGXGetExtendedEpidGroupIdResponse(aesm::message::Response_SGXGetExtendedEpidGroupIdResponse& response);

        AESGXGetExtendedEpidGroupIdResponse(uint32_t errorCode, uint32_t x_group_id);
        AESGXGetExtendedEpidGroupIdResponse(const AESGXGetExtendedEpidGroupIdResponse& other);

        ~AESGXGetExtendedEpidGroupIdResponse();

        //inflater
        bool inflateWithMessage(AEMessage* message);

        AEMessage*  serialize();


        bool GetValues(uint32_t* errorCode, uint32_t* x_group_id) const;

        //operators
        AESGXGetExtendedEpidGroupIdResponse& operator=(const AESGXGetExtendedEpidGroupIdResponse &other);

        //checks
        bool check();

    protected:
        void ReleaseMemory();
        aesm::message::Response_SGXGetExtendedEpidGroupIdResponse* m_response;
};

#endif
