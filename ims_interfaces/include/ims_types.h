/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TELEPHONY_IMS_TYPES_H
#define TELEPHONY_IMS_TYPES_H

#include "call_manager_errors.h"
#include "call_manager_inner_type.h"

namespace OHOS {
namespace Telephony {
const int32_t kMaxNumberLength = 30;
const int32_t TELEPHONY_IMS_SYS_ABILITY_ID = 4014;

enum SrvccState {
    SRVCC_NONE = -1,
    STARTED = 0,
    COMPLETED = 1,
    FAILED = 2,
    CANCELED = 3
};

enum ImsSrvccAction {
    ACTION_DIAL,
    ACTION_HANGUP,
    ACTION_ANSWER,
    ACTION_REJECT,
    ACTION_CONFERENCE,
    ACTION_SWITCH_CALL,
    ACTION_SEND_DTMF,
    ACTION_START_DTMF,
    ACTION_STOP_DTMF,
};

struct ImsSrvccActionInfo {
    CellularCallInfo callInfo;
    char dtmfCode;
};

enum TransferState {
    VT_TRANSFER_TO_WFC = 0,
    WFC_TRANSFER_TO_VT = 1,
};

enum ImsErrType {
    IMS_SUCCESS = 0,
    IMS_FAILED = 1,
};

struct ImsResponseInfo {
    int32_t slotId;
    ImsErrType error;
};

struct ImsCallInfo {
    char phoneNum[kMaxNumberLength]; // call phone number
    int32_t slotId;
    int32_t videoState; // 0: audio 1:video
    int32_t index; // call index
};
} // namespace Telephony
} // namespace OHOS
#endif // TELEPHONY_IMS_TYPES_H
