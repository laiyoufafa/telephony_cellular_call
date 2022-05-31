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

#include "supplement_request.h"

#include "cellular_call_service.h"
#include "radio_event.h"
#include "telephony_log_wrapper.h"
#include "telephony_types.h"
#include "ims_call_client.h"

namespace OHOS {
namespace Telephony {
int32_t SupplementRequest::InquireClipRequest(int32_t slotId)
{
    TELEPHONY_LOGI("InquireClipRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("InquireClipRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->GetClip(slotId);
    }
    CoreManagerInner::GetInstance().GetClip(slotId, RadioEvent::RADIO_GET_CALL_CLIP, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetClirRequest(int32_t slotId, int32_t action)
{
    TELEPHONY_LOGI("SetClirRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetClirRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetClir(slotId, action);
    }
    CoreManagerInner::GetInstance().SetClir(slotId, RadioEvent::RADIO_SET_CALL_CLIR, action, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::InquireClirRequest(int32_t slotId)
{
    TELEPHONY_LOGI("InquireClirRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("InquireClirRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->GetClir(slotId);
    }
    CoreManagerInner::GetInstance().GetClir(slotId, RadioEvent::RADIO_GET_CALL_CLIR, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallTransferRequest(int32_t slotId, int32_t reason)
{
    TELEPHONY_LOGI("GetCallTransferRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallTransferRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->GetCallTransfer(slotId, reason);
    }
    CoreManagerInner::GetInstance().GetCallTransferInfo(
        slotId, RadioEvent::RADIO_GET_CALL_FORWARD, reason, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallTransferRequest(
    int32_t slotId, int32_t action, int32_t reason, const std::string &transferNum, int32_t classType)
{
    TELEPHONY_LOGI("SetCallTransferRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCallTransferRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetCallTransfer(
            slotId, reason, action, transferNum, classType);
    }
    CallTransferParam callTransferParam;
    callTransferParam.mode = action;
    callTransferParam.reason = reason;
    callTransferParam.number = transferNum;
    callTransferParam.classx = classType;
    CoreManagerInner::GetInstance().SetCallTransferInfo(
        slotId, RadioEvent::RADIO_SET_CALL_FORWARD, callTransferParam, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallRestrictionRequest(int32_t slotId, const std::string &fac)
{
    TELEPHONY_LOGI("GetCallRestrictionRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallRestrictionRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->GetCallRestriction(slotId, fac);
    }
    CoreManagerInner::GetInstance().GetCallRestriction(
        slotId, RadioEvent::RADIO_GET_CALL_RESTRICTION, fac, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallRestrictionRequest(int32_t slotId, std::string &fac, int32_t mode, std::string &pw)
{
    TELEPHONY_LOGI("SetCallRestrictionRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCallRestrictionRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetCallRestriction(slotId, fac, mode, pw);
    }
    CallRestrictionParam callRestrictionParam;
    callRestrictionParam.mode = mode;
    callRestrictionParam.fac = fac;
    callRestrictionParam.password = pw;
    CoreManagerInner::GetInstance().SetCallRestriction(
        slotId, RadioEvent::RADIO_SET_CALL_RESTRICTION, callRestrictionParam, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallWaitingRequest(int32_t slotId, bool activate)
{
    TELEPHONY_LOGI("SetCallWaitingRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCallWaitingRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetCallWaiting(slotId, activate);
    }
    CoreManagerInner::GetInstance().SetCallWaiting(
        slotId, RadioEvent::RADIO_SET_CALL_WAIT, activate, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallWaitingRequest(int32_t slotId)
{
    TELEPHONY_LOGI("GetCallWaitingRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallWaitingRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->GetCallWaiting(slotId);
    }
    CoreManagerInner::GetInstance().GetCallWaiting(slotId, RadioEvent::RADIO_GET_CALL_WAIT, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

std::shared_ptr<CellularCallHandler> SupplementRequest::GetMMIHandler(int32_t slotId) const
{
    auto callService = DelayedSingleton<CellularCallService>::GetInstance();
    if (callService == nullptr) {
        TELEPHONY_LOGE("GetMMIHandler return, error type: callService is nullptr.");
        return nullptr;
    }
    return callService->GetHandler(slotId);
}

int32_t SupplementRequest::SendUssdRequest(int32_t slotId, const std::string &msg)
{
    TELEPHONY_LOGI("SendUssdRequest entry");
    CoreManagerInner::GetInstance().SetUssd(slotId, RadioEvent::RADIO_SET_USSD, msg, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::AlterPinPassword(int32_t slotId, std::string newPin, std::string oldPin)
{
    TELEPHONY_LOGI("SupplementRequest::AlterPinPassword entry");
    LockStatusResponse response = {0};
    bool result = CoreManagerInner::GetInstance().AlterPin(slotId, newPin, oldPin, response);
    TELEPHONY_LOGI("SupplementRequest::AlterPinPassword result: %{public}d, remain: %{public}d",
        response.result, response.remain);
    if (result) {
        std::shared_ptr<CellularCallHandler> ccHandler = GetMMIHandler(slotId);
        std::shared_ptr<PinPukResponse> pinResData = std::make_shared<PinPukResponse>();
        pinResData->result = response.result;
        pinResData->remain = response.remain;
        AppExecFwk::InnerEvent::Pointer msgEvent = AppExecFwk::InnerEvent::Get(
            MMIHandlerId::EVENT_SET_UNLOCK_PIN_PUK_ID, pinResData, 0);
        ccHandler->SendEvent(msgEvent, 0, AppExecFwk::EventQueue::Priority::IMMEDIATE);
        return TELEPHONY_SUCCESS;
    }
    return TELEPHONY_ERROR;
}

int32_t SupplementRequest::UnlockPuk(int32_t slotId, std::string newPin, std::string puk)
{
    TELEPHONY_LOGI("SupplementRequest::UnlockPuk entry");
    LockStatusResponse response = {0};
    bool result = CoreManagerInner::GetInstance().UnlockPuk(slotId, newPin, puk, response);
    TELEPHONY_LOGI("SupplementRequest::UnlockPuk result: %{public}d, remain: %{public}d",
        response.result, response.remain);
    if (result) {
        std::shared_ptr<CellularCallHandler> ccHandler = GetMMIHandler(slotId);
        std::shared_ptr<PinPukResponse> pinResData = std::make_shared<PinPukResponse>();
        pinResData->result = response.result;
        pinResData->remain = response.remain;
        AppExecFwk::InnerEvent::Pointer msgEvent = AppExecFwk::InnerEvent::Get(
            MMIHandlerId::EVENT_SET_UNLOCK_PIN_PUK_ID, pinResData, 0);
        ccHandler->SendEvent(msgEvent, 0, AppExecFwk::EventQueue::Priority::IMMEDIATE);
        return TELEPHONY_SUCCESS;
    }
    return TELEPHONY_ERROR;
}

int32_t SupplementRequest::AlterPin2Password(int32_t slotId, std::string newPin2, std::string oldPin2)
{
    TELEPHONY_LOGI("SupplementRequest::AlterPin2Password entry");
    LockStatusResponse response = {0};
    bool result = CoreManagerInner::GetInstance().AlterPin2(slotId, newPin2, oldPin2, response);
    TELEPHONY_LOGI("SupplementRequest::AlterPin2Password result: %{public}d, remain: %{public}d",
        response.result, response.remain);
    if (result) {
        std::shared_ptr<CellularCallHandler> ccHandler = GetMMIHandler(slotId);
        std::shared_ptr<PinPukResponse> pinResData = std::make_shared<PinPukResponse>();
        pinResData->result = response.result;
        pinResData->remain = response.remain;
        AppExecFwk::InnerEvent::Pointer msgEvent = AppExecFwk::InnerEvent::Get(
            MMIHandlerId::EVENT_SET_UNLOCK_PIN_PUK_ID, pinResData, 0);
        ccHandler->SendEvent(msgEvent, 0, AppExecFwk::EventQueue::Priority::IMMEDIATE);
        return TELEPHONY_SUCCESS;
    }
    return TELEPHONY_ERROR;
}

int32_t SupplementRequest::UnlockPuk2(int32_t slotId, std::string newPin2, std::string puk2)
{
    TELEPHONY_LOGI("SupplementRequest::UnlockPuk2 entry");
    LockStatusResponse response = {0};
    bool result = CoreManagerInner::GetInstance().UnlockPuk2(slotId, newPin2, puk2, response);
    TELEPHONY_LOGI("SupplementRequest::UnlockPuk2 result: %{public}d, remain: %{public}d",
        response.result, response.remain);
    if (result) {
        std::shared_ptr<CellularCallHandler> ccHandler = GetMMIHandler(slotId);
        std::shared_ptr<PinPukResponse> pinResData = std::make_shared<PinPukResponse>();
        pinResData->result = response.result;
        pinResData->remain = response.remain;
        AppExecFwk::InnerEvent::Pointer msgEvent = AppExecFwk::InnerEvent::Get(
            MMIHandlerId::EVENT_SET_UNLOCK_PIN_PUK_ID, pinResData, 0);
        ccHandler->SendEvent(msgEvent, 0, AppExecFwk::EventQueue::Priority::IMMEDIATE);
        return TELEPHONY_SUCCESS;
    }
    return TELEPHONY_ERROR;
}
} // namespace Telephony
} // namespace OHOS
