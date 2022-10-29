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

#ifndef TELEPHONY_IMS_CALL_CALLBACK_STUB_H
#define TELEPHONY_IMS_CALL_CALLBACK_STUB_H

#include <map>
#include "iremote_stub.h"
#include "ims_call_callback_interface.h"

namespace OHOS {
namespace Telephony {
class ImsCallCallbackStub : public IRemoteStub<ImsCallCallbackInterface> {
public:
    ImsCallCallbackStub();
    virtual ~ImsCallCallbackStub();
    int OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;

    /****************** call basic ******************/
    int32_t DialResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t HangUpResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t RejectWithReasonResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t AnswerResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t HoldCallResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t UnHoldCallResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SwitchCallResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t CombineConferenceResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t InviteToConferenceResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t KickOutFromConferenceResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t CallMediaModeResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t CallStateChangeReport(int32_t slotId) override;
    int32_t GetImsCallsDataResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetImsCallsDataResponse(int32_t slotId, const ImsCurrentCallList &callList) override;
    int32_t LastCallFailReasonResponse(int32_t slotId, const DisconnectedDetails &details) override;
    int32_t SrvccStateReport(int32_t slotId, SrvccState srvccState) override;
    int32_t VtWfcReport(int32_t slotId, TransferState transferState) override;
    int32_t CallRingBackReport(int32_t slotId, const RingbackVoice &info) override;

    /****************** dtmf rtt ******************/
    int32_t StartDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SendDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t StopDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t StartRttResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t StopRttResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;

    /****************** ims config ******************/
    int32_t SetPreModeResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetPreModeResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetPreModeResponse(int32_t slotId, int32_t mode) override;
    int32_t SetImsSwitchResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetImsSwitchResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetImsSwitchResponse(int32_t slotId, int32_t active) override;
    int32_t SetImsConfigResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetImsConfigResponse(int32_t slotId, int32_t value) override;
    int32_t GetImsConfigResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SetImsFeatureValueResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetImsFeatureValueResponse(int32_t slotId, int32_t value) override;
    int32_t GetImsFeatureValueResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SetMuteResponse(int32_t slotId, const MuteControlResponse &response) override;
    int32_t GetMuteResponse(int32_t slotId, const MuteControlResponse &response) override;

    /****************** video settings ******************/
    int32_t CtrlCameraResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SetPreviewWindowResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SetDisplayWindowResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SetCameraZoomResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SetPauseImageResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SetDeviceDirectionResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;

    /****************** supplement ******************/
    int32_t SetClipResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetClipResponse(int32_t slotId, const ClipResponse &response) override;
    int32_t GetClirResponse(int32_t slotId, const ClirResponse &response) override;
    int32_t SetClirResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetCallTransferResponse(int32_t slotId, const CallTransferResponse &response) override;
    int32_t SetCallTransferResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetCallRestrictionResponse(int32_t slotId, const CallRestrictionResponse &response) override;
    int32_t SetCallRestrictionResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetCallWaitingResponse(int32_t slotId, const CallWaitResponse &response) override;
    int32_t SetCallWaitingResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SetColrResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetColrResponse(int32_t slotId, const ColrResponse &response) override;
    int32_t SetColpResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetColpResponse(int32_t slotId, const ColpResponse &response) override;

private:
    void InitFuncMap();
    void InitCallBasicFuncMap();
    void InitConfigFuncMap();
    void InitVedioFuncMap();
    void InitSupplementFuncMap();

    /****************** call basic ******************/
    int32_t OnDialResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnHangUpResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnRejectResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnAnswerResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnHoldCallResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnUnHoldCallResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSwitchCallResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnCombineConferenceResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnInviteToConferenceResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnKickOutFromConferenceResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnCallMediaModeResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnCallStateChangeReportInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetImsCallsDataResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSrvccStateReportInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnVtWfcReportInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnCallRingBackReportInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnLastCallFailReasonResponseInner(MessageParcel &data, MessageParcel &reply);

    /****************** dtmf rtt ******************/
    int32_t OnStartDtmfResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSendDtmfResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnStopDtmfResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnStartRttResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnStopRttResponseInner(MessageParcel &data, MessageParcel &reply);

    /****************** ims config ******************/
    int32_t OnSetPreModeResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetPreModeResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetImsSwitchEnhanceModeResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetImsSwitchEnhanceModeResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetMuteResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetMuteResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetEccListResponseInner(MessageParcel &data, MessageParcel &reply);

    /****************** video settings ******************/
    int32_t OnCtrlCameraResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetPreviewWindowResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetDisplayWindowResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetCameraZoomResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetPauseImageResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetDeviceDirectionResponseInner(MessageParcel &data, MessageParcel &reply);

    /****************** supplement ******************/
    int32_t OnSetClipResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetClipResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetClirResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetClirResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetColrResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetColrResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnSetColpResponseInner(MessageParcel &data, MessageParcel &reply);
    int32_t OnGetColpResponseInner(MessageParcel &data, MessageParcel &reply);

    int32_t SendEvent(int32_t slotId, int32_t eventId, const HRilRadioResponseInfo &info);

private:
    using RequestFuncType = int32_t (ImsCallCallbackStub::*)(MessageParcel &data, MessageParcel &reply);
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_CALL_CALLBACK_STUB_H
