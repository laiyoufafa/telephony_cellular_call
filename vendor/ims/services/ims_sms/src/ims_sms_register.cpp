/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#include "ims_sms_register.h"
#include "telephony_errors.h"

namespace OHOS {
namespace Telephony {
ImsSmsRegister::ImsSmsRegister() {}

ImsSmsRegister::~ImsSmsRegister() {}

int32_t ImsSmsRegister::UpdateImsSendMessageResponse(const ImsResponseInfo &info, const SendSmsResultInfo &result)
{
    TELEPHONY_LOGI("ImsSendMessageResponse");
    if (imsSmsCallback_ == nullptr) {
        TELEPHONY_LOGE("imsSmsCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsSmsCallback_->ImsSendMessageResponse(info, result);
    return TELEPHONY_SUCCESS;
}

int32_t ImsSmsRegister::UpdateImsSetSmsConfigResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsSetSmsConfigResponse");
    if (imsSmsCallback_ == nullptr) {
        TELEPHONY_LOGE("imsSmsCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsSmsCallback_->ImsSetSmsConfigResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsSmsRegister::UpdateImsGetSmsConfigResponse(const ImsResponseInfo &info, int32_t imsSmsConfig)
{
    TELEPHONY_LOGI("ImsGetSmsConfigResponse");
    if (imsSmsCallback_ == nullptr) {
        TELEPHONY_LOGE("imsSmsCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsSmsCallback_->ImsGetSmsConfigResponse(info, imsSmsConfig);
    return TELEPHONY_SUCCESS;
}

int32_t ImsSmsRegister::RegisterImsSmsCallBack(const sptr<ImsSmsCallbackInterface> &callback)
{
    imsSmsCallback_ = callback;
    return TELEPHONY_SUCCESS;
}

bool ImsSmsRegister::IsCallBackExists()
{
    return imsSmsCallback_ != nullptr;
}
} // namespace Telephony
} // namespace OHOS
