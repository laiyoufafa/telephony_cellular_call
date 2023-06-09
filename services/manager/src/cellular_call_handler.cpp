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

#include "cellular_call_handler.h"

#include "hril_call_parcel.h"

#include "cellular_call_config.h"
#include "cellular_call_service.h"
#include "radio_event.h"

namespace OHOS {
namespace Telephony {
CellularCallHandler::CellularCallHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner)
    : AppExecFwk::EventHandler(runner)
{
    InitBasicFuncMap();
    InitConfigFuncMap();
    InitSupplementFuncMap();
    InitActiveReportFuncMap();
}

void CellularCallHandler::InitBasicFuncMap()
{
    requestFuncMap_[RadioEvent::RADIO_DIAL] = &CellularCallHandler::DialResponse;
    requestFuncMap_[RadioEvent::RADIO_HANGUP_CONNECT] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[RadioEvent::RADIO_REJECT_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[RadioEvent::RADIO_ACCEPT_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[RadioEvent::RADIO_HOLD_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[RadioEvent::RADIO_ACTIVE_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[RadioEvent::RADIO_SWAP_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[RadioEvent::RADIO_JOIN_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[RadioEvent::RADIO_SPLIT_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[RadioEvent::RADIO_CALL_SUPPLEMENT] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[RadioEvent::RADIO_SEND_DTMF] = &CellularCallHandler::SendDtmfResponse;
    requestFuncMap_[RadioEvent::RADIO_START_DTMF] = &CellularCallHandler::StartDtmfResponse;
    requestFuncMap_[RadioEvent::RADIO_STOP_DTMF] = &CellularCallHandler::StopDtmfResponse;
    requestFuncMap_[RadioEvent::RADIO_CURRENT_CALLS] = &CellularCallHandler::GetCsCallsDataResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_IMS_CALL_LIST] = &CellularCallHandler::GetImsCallsDataResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_CALL_FAIL_REASON] = &CellularCallHandler::GetCallFailReasonResponse;

    requestFuncMap_[GET_CS_CALL_DATA_ID] = &CellularCallHandler::GetCsCallsDataRequest;
    requestFuncMap_[GET_IMS_CALL_DATA_ID] = &CellularCallHandler::GetImsCallsDataRequest;
    requestFuncMap_[REGISTER_HANDLER_ID] = &CellularCallHandler::RegisterHandler;
    requestFuncMap_[MMIHandlerId::EVENT_MMI_Id] = &CellularCallHandler::GetMMIResponse;
}

void CellularCallHandler::InitConfigFuncMap()
{
    requestFuncMap_[RadioEvent::RADIO_SET_CMUT] = &CellularCallHandler::SetMuteResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_CMUT] = &CellularCallHandler::GetMuteResponse;
    requestFuncMap_[RadioEvent::RADIO_SET_CALL_PREFERENCE_MODE] = &CellularCallHandler::SetDomainPreferenceModeResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_CALL_PREFERENCE_MODE] = &CellularCallHandler::GetDomainPreferenceModeResponse;
    requestFuncMap_[RadioEvent::RADIO_SET_LTE_IMS_SWITCH_STATUS] = &CellularCallHandler::SetLteImsSwitchStatusResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_LTE_IMS_SWITCH_STATUS] = &CellularCallHandler::GetLteImsSwitchStatusResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_EMERGENCY_CALL_LIST] = &CellularCallHandler::GetEmergencyCallListResponse;
}

void CellularCallHandler::InitSupplementFuncMap()
{
    requestFuncMap_[RadioEvent::RADIO_GET_CALL_WAIT] = &CellularCallHandler::GetCallWaitingResponse;
    requestFuncMap_[RadioEvent::RADIO_SET_CALL_WAIT] = &CellularCallHandler::SetCallWaitingResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_CALL_FORWARD] = &CellularCallHandler::GetCallTransferResponse;
    requestFuncMap_[RadioEvent::RADIO_SET_CALL_FORWARD] = &CellularCallHandler::SetCallTransferInfoResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_CALL_CLIP] = &CellularCallHandler::GetClipResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_CALL_CLIR] = &CellularCallHandler::GetClirResponse;
    requestFuncMap_[RadioEvent::RADIO_SET_CALL_CLIR] = &CellularCallHandler::SetClirResponse;
    requestFuncMap_[RadioEvent::RADIO_GET_CALL_RESTRICTION] = &CellularCallHandler::GetCallRestrictionResponse;
    requestFuncMap_[RadioEvent::RADIO_SET_CALL_RESTRICTION] = &CellularCallHandler::SetCallRestrictionResponse;
    requestFuncMap_[RadioEvent::RADIO_SET_USSD] = &CellularCallHandler::SendUssdResponse;
}

void CellularCallHandler::InitActiveReportFuncMap()
{
    requestFuncMap_[RadioEvent::RADIO_CALL_STATUS_INFO] = &CellularCallHandler::CallStatusInfoResponse;
    requestFuncMap_[RadioEvent::RADIO_CALL_IMS_SERVICE_STATUS] = &CellularCallHandler::CallImsServiceStatusResponse;
    requestFuncMap_[RadioEvent::RADIO_AVAIL] = &CellularCallHandler::GetCsCallData;
    requestFuncMap_[RadioEvent::RADIO_NOT_AVAIL] = &CellularCallHandler::GetCsCallData;
    requestFuncMap_[RadioEvent::RADIO_CALL_USSD_NOTICE] = &CellularCallHandler::UssdNotifyResponse;
    requestFuncMap_[RadioEvent::RADIO_CALL_RINGBACK_VOICE] = &CellularCallHandler::CallRingBackVoiceResponse;
    requestFuncMap_[RadioEvent::RADIO_CALL_SRVCC_STATUS] = &CellularCallHandler::UpdateSrvccStateReport;
}

void CellularCallHandler::ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CellularCallHandler::ProcessEvent, event is nullptr");
        return;
    }
    auto itFunc = requestFuncMap_.find(event->GetInnerEventId());
    if (itFunc != requestFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(event);
        }
    }
    TELEPHONY_LOGI("CellularCallHandler::ProcessEvent, default case, need check.");
}

void CellularCallHandler::GetCsCallData(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCsCallData return, event is nullptr");
        return;
    }
    TELEPHONY_LOGI("GetCsCallData event id: %{public}d", event->GetInnerEventId());
    this->SendEvent(GET_CS_CALL_DATA_ID, delayTime_, Priority::HIGH);
}

void CellularCallHandler::GetImsCallData(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsCallData return, event is nullptr");
        return;
    }
    TELEPHONY_LOGI("GetImsCallData event id: %{public}d", event->GetInnerEventId());
    this->SendEvent(GET_IMS_CALL_DATA_ID, delayTime_, Priority::HIGH);
}

void CellularCallHandler::ReportCsCallsData(const CallInfoList &callInfoList)
{
    auto serviceInstance_ = DelayedSingleton<CellularCallService>::GetInstance();
    if (serviceInstance_ == nullptr) {
        TELEPHONY_LOGE("ReportCsCallsData return, GetInstance is nullptr");
        return;
    }
    auto csControl = serviceInstance_->GetCsControl(slotId_);
    if (callInfoList.callSize == 0) {
        callType_ = CallType::TYPE_ERR_CALL;
        if (csControl == nullptr) {
            TELEPHONY_LOGE("ReportCsCallsData return, cs_control is nullptr");
            return;
        }
        csControl->ReportCallsData(slotId_, callInfoList);
        serviceInstance_->CleanControlMap();
        return;
    }
    if (callInfoList.callSize == 1) {
        if (csControl == nullptr) {
            csControl = std::make_shared<CSControl>();
            serviceInstance_->SetCsControl(slotId_, csControl);
        }
    }
    if (csControl == nullptr) {
        TELEPHONY_LOGE("ReportCsCallsData return, cs_control is nullptr");
        return;
    }
    csControl->ReportCallsData(slotId_, callInfoList);
}

void CellularCallHandler::ReportImsCallsData(const CallInfoList &imsCallInfoList)
{
    auto serviceInstance_ = DelayedSingleton<CellularCallService>::GetInstance();
    if (serviceInstance_ == nullptr) {
        TELEPHONY_LOGE("ReportImsCallsData return, serviceInstance_ is nullptr");
        return;
    }
    TELEPHONY_LOGI("ReportImsCallsData, imsCallInfoList.callSize:%{public}d", imsCallInfoList.callSize);
    auto imsControl = serviceInstance_->GetImsControl(slotId_);
    if (imsCallInfoList.callSize == 0) {
        callType_ = CallType::TYPE_ERR_CALL;
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("ReportImsCallsData return, ims_control is nullptr");
            return;
        }
        imsControl->ReportCallsData(slotId_, imsCallInfoList);
        serviceInstance_->CleanControlMap();
        return;
    }
    if (imsCallInfoList.callSize == 1) {
        if (imsControl == nullptr) {
            imsControl = std::make_shared<IMSControl>();
            TELEPHONY_LOGI("ReportImsCallsData, make control");
            serviceInstance_->SetImsControl(slotId_, imsControl);
        }
    }
    if (imsControl == nullptr) {
        TELEPHONY_LOGE("ReportImsCallsData return, ims_control is nullptr");
        return;
    }
    imsControl->ReportCallsData(slotId_, imsCallInfoList);
}

void CellularCallHandler::GetCsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCsCallsDataResponse return, event is nullptr");
        return;
    }
    // Returns list of current calls of ME. If command succeeds but no calls are available,
    // no information response is sent to TE. Refer subclause 9.2 for possible <err> values.
    auto callInfoList = event->GetSharedObject<CallInfoList>();
    if (callInfoList == nullptr) {
        TELEPHONY_LOGE("GetCsCallsDataResponse, Cannot get the callInfoList, need to get rilResponseInfo");
        auto rilResponseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (rilResponseInfo == nullptr) {
            TELEPHONY_LOGE("GetCsCallsDataResponse return, callInfoList and rilResponseInfo is nullptr");
            return;
        }
        if (rilResponseInfo->error == HRilErrType::NONE) {
            TELEPHONY_LOGE("GetCsCallsDataResponse return, failed to query the call list but no reason!");
            return;
        }
        TELEPHONY_LOGE("GetCsCallsDataResponse error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_GET_CURRENT_CALLS_FAILED;
        if (registerInstance_ == nullptr) {
            TELEPHONY_LOGE("GetCsCallsDataResponse return, GetInstance is nullptr");
            return;
        }
        registerInstance_->ReportEventResultInfo(eventInfo);
        return;
    }
    ReportCsCallsData(*callInfoList);
}

void CellularCallHandler::GetImsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataResponse return, event is nullptr");
        return;
    }
    // Returns list of current calls of ME. If command succeeds but no calls are available,
    // no information response is sent to TE. Refer subclause 9.2 for possible <err> values.
    auto imsCallInfoList = event->GetSharedObject<CallInfoList>();
    if (imsCallInfoList == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataResponse, Cannot get the imsCallInfoList, need to get rilResponseInfo");
        auto rilResponseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (rilResponseInfo == nullptr) {
            TELEPHONY_LOGE("GetImsCallsDataResponse return, callInfoList and rilResponseInfo is nullptr");
            return;
        }
        if (rilResponseInfo->error == HRilErrType::NONE) {
            TELEPHONY_LOGE("GetImsCallsDataResponse return, failed to query the call list but no reason!");
            return;
        }
        TELEPHONY_LOGE("GetImsCallsDataResponse error, report to call_manager");
        if (registerInstance_ == nullptr) {
            TELEPHONY_LOGE("GetImsCallsDataResponse return, GetInstance is nullptr");
            return;
        }
        registerInstance_->ReportGetCallDataResult(static_cast<int32_t>(rilResponseInfo->error));
        return;
    }
    ReportImsCallsData(*imsCallInfoList);
}

void CellularCallHandler::DialResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("DialResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("DialResponse return, result is nullptr");
        return;
    }
    if (result->error != HRilErrType::NONE) {
        TELEPHONY_LOGI("DialResponse, dial return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;

        /*
         * 3GPP TS 27.007 V3.9.0 (2001-06)
         * If ME has succeeded in establishing a logical link between application protocols and external interface,
         * it will send CONNECT message to the TE. Otherwise, the NO CARRIER response will be returned.
         */
        if (result->error == HRilErrType::HRIL_ERR_CMD_NO_CARRIER) {
            eventInfo.eventId = RequestResultEventId::RESULT_DIAL_NO_CARRIER;
        } else {
            eventInfo.eventId = RequestResultEventId::RESULT_DIAL_SEND_FAILED;
        }
        if (registerInstance_ == nullptr) {
            TELEPHONY_LOGE("DialResponse return, GetInstance is nullptr");
            return;
        }
        registerInstance_->ReportEventResultInfo(eventInfo);
    }
}

void CellularCallHandler::CommonResultResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CommonResultResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("CommonResultResponse return, result is nullptr");
        return;
    }
    if (result->error != HRilErrType::NONE) {
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        switch (event->GetInnerEventId()) {
            case RadioEvent::RADIO_HANGUP_CONNECT:
                eventInfo.eventId = RequestResultEventId::RESULT_END_SEND_FAILED;
                break;
            case RadioEvent::RADIO_REJECT_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_REJECT_SEND_FAILED;
                break;
            case RadioEvent::RADIO_ACCEPT_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_ACCEPT_SEND_FAILED;
                break;
            case RadioEvent::RADIO_HOLD_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_HOLD_SEND_FAILED;
                break;
            case RadioEvent::RADIO_ACTIVE_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_ACTIVE_SEND_FAILED;
                break;
            case RadioEvent::RADIO_SWAP_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_SWAP_SEND_FAILED;
                break;
            case RadioEvent::RADIO_JOIN_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_JOIN_SEND_FAILED;
                break;
            case RadioEvent::RADIO_SPLIT_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_SPLIT_SEND_FAILED;
                break;
            case RadioEvent::RADIO_CALL_SUPPLEMENT:
                eventInfo.eventId = RequestResultEventId::RESULT_SUPPLEMENT_SEND_FAILED;
                break;
            default:
                break;
        }
        if (registerInstance_ == nullptr) {
            TELEPHONY_LOGE("CommonResultResponse return, registerInstance_ is nullptr");
            return;
        }
        registerInstance_->ReportEventResultInfo(eventInfo);
        return;
    }
}

void CellularCallHandler::SendDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse return, result is nullptr");
        return;
    }
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (result->error != HRilErrType::NONE) {
        eventInfo.eventId = RequestResultEventId::RESULT_SEND_DTMF_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SEND_DTMF_SUCCESS;
    }
    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse return, GetInstance is nullptr");
        return;
    }
    TELEPHONY_LOGI("SendDtmfResponse: report to call manager");
    registerInstance_->ReportEventResultInfo(eventInfo);
}

void CellularCallHandler::StartDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse return, result is nullptr");
        return;
    }

    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse return, GetInstance is nullptr");
        return;
    }
    TELEPHONY_LOGI("StartDtmfResponse: report to call manager");
    registerInstance_->ReportStartDtmfResult(static_cast<int32_t>(result->error));
}

void CellularCallHandler::StopDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse return, result is nullptr");
        return;
    }

    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse return, GetInstance is nullptr");
        return;
    }
    TELEPHONY_LOGI("StopDtmfResponse: report to call manager");
    registerInstance_->ReportStopDtmfResult(static_cast<int32_t>(result->error));
}

void CellularCallHandler::SetSlotId(int32_t id)
{
    slotId_ = id;
}

int32_t CellularCallHandler::GetSlotId()
{
    return slotId_;
}

int64_t CellularCallHandler::CurrentTimeMillis()
{
    int64_t timems =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    return timems;
}

bool CellularCallHandler::IsCanRequestCallsData()
{
    int64_t timems = CurrentTimeMillis();
    if ((timems - lastTime_) < FAST_DELAY_TIME) {
        return false;
    }
    lastTime_ = timems;
    return true;
}

void CellularCallHandler::GetCsCallsDataRequest(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (!IsCanRequestCallsData()) {
        TELEPHONY_LOGE("GetCsCallsDataRequest return, IsCanRequestCallsData false");
    }
    lastCallsDataFlag_ = CurrentTimeMillis();
    CellularCallConnectionCS connectionCs;
    connectionCs.GetCsCallsDataRequest(slotId_, lastCallsDataFlag_);
}

void CellularCallHandler::GetImsCallsDataRequest(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (!IsCanRequestCallsData()) {
        TELEPHONY_LOGE("GetImsCallsDataRequest return, IsCanRequestCallsData false");
    }
    lastCallsDataFlag_ = CurrentTimeMillis();
    CellularCallConnectionIMS connectionIms;
    connectionIms.GetImsCallsDataRequest(slotId_, lastCallsDataFlag_);
}

void CellularCallHandler::RegisterHandler(const AppExecFwk::InnerEvent::Pointer &event)
{
    CellularCallConnectionCS connectionCs;
    connectionCs.RegisterHandler();
}

void CellularCallHandler::SetDomainPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("SetDomainPreferenceModeResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetDomainPreferenceModeResponse return, event is nullptr");
        return;
    }
    auto info = event->GetSharedObject<HRilRadioResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetDomainPreferenceModeResponse return, info is nullptr");
        return;
    }
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info->error != HRilErrType::NONE) {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_CALL_PREFERENCE_MODE_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_CALL_PREFERENCE_MODE_SUCCESS;

        CellularCallConfig config;
        config.SetTempMode(slotId_);
    }
    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("SetDomainPreferenceModeResponse return, GetInstance is nullptr");
        return;
    }
    registerInstance_->ReportEventResultInfo(eventInfo);
}

void CellularCallHandler::GetDomainPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGE("GetDomainPreferenceModeResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetDomainPreferenceModeResponse return, event is nullptr");
        return;
    }
    auto mode = event->GetSharedObject<int32_t>();
    if (mode == nullptr) {
        TELEPHONY_LOGI("GetDomainPreferenceModeResponse return, mode is nullptr");
        return;
    }
    CellularCallConfig config;
    config.GetDomainPreferenceModeResponse(slotId_, *mode);
}

void CellularCallHandler::SetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("SetLteImsSwitchStatusResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetLteImsSwitchStatusResponse return, event is nullptr");
        return;
    }
    auto info = event->GetSharedObject<HRilRadioResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetLteImsSwitchStatusResponse return, info is nullptr");
        return;
    }
    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("SetLteImsSwitchStatusResponse return, GetInstance is nullptr");
        return;
    }
    registerInstance_->ReportSetLteImsSwitchResult(static_cast<int32_t>(info->error));
}

void CellularCallHandler::GetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("GetLteImsSwitchStatusResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetLteImsSwitchStatusResponse return, event is nullptr");
        return;
    }
    LteImsSwitchResponse lteImsSwitch;
    auto active = event->GetSharedObject<int32_t>();
    if (active == nullptr) {
        TELEPHONY_LOGI("GetLteImsSwitchStatusResponse, Cannot get the active, need to get rilResponseInfo");
        auto info = event->GetSharedObject<HRilRadioResponseInfo>();
        if (info == nullptr) {
            TELEPHONY_LOGE("GetLteImsSwitchStatusResponse return, info is nullptr");
            return;
        }
        lteImsSwitch.result = static_cast<int32_t>(info->error);
    } else {
        CellularCallConfig config;
        config.GetLteImsSwitchStatusResponse(slotId_, *active);
        lteImsSwitch.result = static_cast<int32_t>(HRilErrType::NONE);
        lteImsSwitch.active = *active;
    }
    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("GetLteImsSwitchStatusResponse return, GetInstance is nullptr");
        return;
    }
    registerInstance_->ReportGetLteImsSwitchResult(lteImsSwitch);
}

void CellularCallHandler::CallStatusInfoResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CallStatusInfoResponse return, event is nullptr");
        return;
    }
    auto serviceInstance_ = DelayedSingleton<CellularCallService>::GetInstance();
    if (serviceInstance_ == nullptr) {
        TELEPHONY_LOGE("CallStatusInfoResponse return, GetInstance is nullptr");
        return;
    }
    if (callType_ == CallType::TYPE_ERR_CALL) {
        TELEPHONY_LOGI("CallStatusInfoResponse, default call type");
        if (serviceInstance_->IsNeedIms(slotId_)) {
            GetImsCallData(event);
        } else {
            GetCsCallData(event);
        }
    } else if (callType_ == CallType::TYPE_CS) {
        GetCsCallData(event);
    } else if (callType_ == CallType::TYPE_IMS) {
        GetImsCallData(event);
    }
}

void CellularCallHandler::CallImsServiceStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CellularCallHandler::CallImsServiceStatusResponse entry");
}

void CellularCallHandler::SetCallType(CallType callType)
{
    callType_ = callType;
}

void CellularCallHandler::UssdNotifyResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CellularCallHandler::UssdNotifyResponse entry");
}

void CellularCallHandler::SetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CellularCallHandler::SetMuteResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetMuteResponse return, event is nullptr");
        return;
    }
    auto info = event->GetSharedObject<HRilRadioResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetMuteResponse return, info is nullptr");
        return;
    }
    MuteControlResponse response;
    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("SetMuteResponse return, registerInstance_ is nullptr");
        return;
    }
    response.result = static_cast<int32_t>(info->error);
    TELEPHONY_LOGI("SetMuteResponse: report to call manager");
    registerInstance_->ReportSetMuteResult(response);
}

void CellularCallHandler::GetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CellularCallHandler::GetMuteResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetMuteResponse return, event is nullptr");
        return;
    }
    MuteControlResponse response;
    auto mute = event->GetSharedObject<int32_t>();
    if (mute == nullptr) {
        TELEPHONY_LOGI("GetMuteResponse, mute is nullptr");
        auto info = event->GetSharedObject<HRilRadioResponseInfo>();
        if (info == nullptr) {
            TELEPHONY_LOGE("GetMuteResponse return, info is nullptr");
            return;
        }
        response.result = static_cast<int32_t>(info->error);
    } else {
        response.result = static_cast<int32_t>(HRilErrType::NONE);
        response.value = *mute;
    }
    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("GetMuteResponse return, registerInstance_ is nullptr");
        return;
    }
    TELEPHONY_LOGI("GetMuteResponse: report to call manager");
    registerInstance_->ReportGetMuteResult(response);
}

void CellularCallHandler::GetEmergencyCallListResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CellularCallHandler::GetEmergencyCallListResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetEmergencyCallListResponse return, event is nullptr");
        return;
    }
    auto eccList = event->GetSharedObject<EmergencyInfoList>();
    if (eccList == nullptr) {
        TELEPHONY_LOGE("GetEmergencyCallListResponse return, eccList is nullptr");
        return;
    }
    CellularCallConfig config;
    config.GetEmergencyCallListResponse(slotId_, *eccList);
}

void CellularCallHandler::CallRingBackVoiceResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CellularCallHandler::CallRingBackVoiceResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallRingBackVoiceResponse return, event is nullptr");
        return;
    }
    auto ringBackVoice = event->GetSharedObject<RingbackVoice>();
    if (ringBackVoice == nullptr) {
        TELEPHONY_LOGE("CallRingBackVoiceResponse return, ringBackVoice is nullptr");
        return;
    }
    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("CallRingBackVoiceResponse return, registerInstance_ is nullptr");
        return;
    }
    TELEPHONY_LOGI("CallRingBackVoiceResponse: report to call manager");
    registerInstance_->ReportCallRingBackResult(ringBackVoice->status);
}

void CellularCallHandler::GetCallFailReasonResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CellularCallHandler::GetCallFailReasonResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonResponse return, event is nullptr");
        return;
    }
    auto reason = event->GetSharedObject<int32_t>();
    if (reason == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonResponse return, reason is nullptr");
        return;
    }
    if (registerInstance_ == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonResponse return, registerInstance_ is nullptr");
        return;
    }
    TELEPHONY_LOGI("GetCallFailReasonResponse: %{public}d, report to call manager", *reason);
    registerInstance_->ReportCallFailReason(*reason);
}

void CellularCallHandler::UpdateSrvccStateReport(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CellularCallHandler::UpdateSrvccStateReport entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("UpdateSrvccStateReport return, event is nullptr");
        return;
    }
    auto srvccStatus = event->GetSharedObject<HRilCallSrvccStatus>();
    if (srvccStatus == nullptr) {
        TELEPHONY_LOGE("UpdateSrvccStateReport return, srvccStatus is nullptr");
        return;
    }
    srvccState_ = srvccStatus->status;
    if (srvccState_ != SrvccState::COMPLETED) {
        TELEPHONY_LOGE("UpdateSrvccStateReport return, srvccState_ != SrvccState::COMPLETED");
        return;
    }
    SrvccStateCompleted();
}

void CellularCallHandler::SrvccStateCompleted()
{
    if (srvccState_ != SrvccState::COMPLETED) {
        TELEPHONY_LOGE("SrvccStateCompleted return, srvccState_ != SrvccState::COMPLETED");
        return;
    }
    auto event = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_CALL_STATUS_INFO);
    CallStatusInfoResponse(event);
    srvccState_ = SrvccState::SRVCC_NONE;
}

void CellularCallHandler::GetMMIResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetMMIResponse, event is nullptr");
        return;
    }
    std::unique_ptr<MMICodeUtils> mmiCodeUtils = event->GetUniqueObject<MMICodeUtils>();
    if (mmiCodeUtils == nullptr) {
        TELEPHONY_LOGE("CellularCallHandler::GetMMIResponse, mmiCodeUtils is nullptr");
        return;
    }
    mmiCodeUtils->ExecuteMmiCode(slotId_);
}

void CellularCallHandler::GetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CellularCallHandler::GetCallWaitingResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingResponse, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<CallWaitResult>();
    if (result == nullptr) {
        TELEPHONY_LOGE("CellularCallHandler::GetCallWaitingResponse, result is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventGetCallWaiting(*result);
}

void CellularCallHandler::SetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("SetCallWaitingResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingResponse, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingResponse, result is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventSetCallWaiting(*result);
}

void CellularCallHandler::GetClirResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("GetClirResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetClirResponse, event is nullptr");
        return;
    }
    auto getClirResult = event->GetSharedObject<GetClirResult>();
    if (getClirResult == nullptr) {
        TELEPHONY_LOGE("GetClirResponse, getClirResult is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventGetClir(*getClirResult);
}

void CellularCallHandler::SetClirResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("SetClirResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetClirResponse, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SetClirResponse, result is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventSetClir(*result);
}

void CellularCallHandler::GetClipResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("GetClipResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetClipResponse, event is nullptr");
        return;
    }
    auto getClipResult = event->GetSharedObject<GetClipResult>();
    if (getClipResult == nullptr) {
        TELEPHONY_LOGE("GetClipResponse, getClipResult is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventGetClip(*getClipResult);
}

void CellularCallHandler::GetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("GetCallTransferResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallTransferResponse, event is nullptr");
        return;
    }
    auto cFQueryResult = event->GetSharedObject<CallForwardQueryResult>();
    if (cFQueryResult == nullptr) {
        TELEPHONY_LOGE("GetCallTransferResponse, cFQueryResult is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventGetCallTransferInfo(*cFQueryResult);
}

void CellularCallHandler::SetCallTransferInfoResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("SetCallTransferInfoResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallTransferInfoResponse, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SetCallTransferInfoResponse, result is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventSetCallTransferInfo(*result);
}

void CellularCallHandler::GetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("GetCallRestrictionResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionResponse, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<CallRestrictionResult>();
    if (result == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionResponse, result is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventGetCallRestriction(*result);
}

void CellularCallHandler::SetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("SetCallRestrictionResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionResponse, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionResponse, result is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventSetCallRestriction(*result);
}

void CellularCallHandler::SendUssdResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SendUssdResponse, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SendUssdResponse, result is nullptr");
        return;
    }
    CellularCallSupplement supplement;
    supplement.EventSendUssd(*result);
}
} // namespace Telephony
} // namespace OHOS