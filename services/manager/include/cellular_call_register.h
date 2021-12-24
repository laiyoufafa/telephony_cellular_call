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

#ifndef CELLULAR_CALL_REGISTER_H
#define CELLULAR_CALL_REGISTER_H

#include <map>

#include "cellular_call_connection_cs.h"
#include "i_call_status_callback.h"
#include "singleton.h"

namespace OHOS {
namespace Telephony {
class CellularCallRegister {
    DECLARE_DELAYED_SINGLETON(CellularCallRegister);

public:
    /**
     * ReportCallsInfo.
     *
     * @param callsReportInfo data list
     */
    void ReportCallsInfo(const CallsReportInfo &callsReportInfo);

    /**
     * ReportSingleCallInfo.
     *
     * @param CallReportInfo
     * @param TelCallState
     */
    void ReportSingleCallInfo(CallReportInfo &reportInfo, TelCallState callState);

    /**
     * ReportEventResultInfo.
     *
     * @param CellularCallEventInfo
     */
    void ReportEventResultInfo(const CellularCallEventInfo &info);

    /**
     * ReportGetWaitingResult.
     *
     * @param CallWaitResponse
     */
    void ReportGetWaitingResult(const CallWaitResponse &response);

    /**
     * ReportSetWaitingResult.
     *
     * @param CallWaitResponse
     */
    void ReportSetWaitingResult(const CallWaitResponse &response);

    /**
     * ReportGetRestrictionResult.
     *
     * @param CallRestrictionResponse
     */
    void ReportGetRestrictionResult(const CallRestrictionResponse &response);

    /**
     * ReportSetRestrictionResult.
     *
     * @param result
     */
    void ReportSetRestrictionResult(int32_t result);

    /**
     * ReportGetTransferResult.
     *
     * @param CallTransferResponse
     */
    void ReportGetTransferResult(const CallTransferResponse &response);

    /**
     * ReportSetTransferResult.
     *
     * @param result
     */
    void ReportSetTransferResult(int32_t result);

    /**
     * ReportGetClipResult.
     *
     * @param ClipResponse
     */
    void ReportGetClipResult(const ClipResponse &clipResponse);

    /**
     * ReportGetClirResult.
     *
     * @param ClirResponse
     */
    void ReportGetClirResult(const ClirResponse &clirResponse);

    /**
     * ReportSetClirResult.
     *
     * @param ClirResponse
     */
    void ReportSetClirResult(const ClirResponse &clirResponses);

    /**
     * ReportGetCallPreferenceResult.
     *
     * @param CallPreferenceResponse
     */
    void ReportGetCallPreferenceResult(const CallPreferenceResponse &callPreference);

    /**
     * ReportGetLteImsSwitchResult.
     *
     * @param active
     */
    void ReportGetLteImsSwitchResult(const LteImsSwitchResponse &lteImsSwitch);

    /**
     * Register CallManagerCallBack
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t RegisterCallManagerCallBack(const sptr<ICallStatusCallback> &callback);

    /**
     * UnRegister CallManagerCallBack
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UnRegisterCallManagerCallBack();

private:
    sptr<ICallStatusCallback> callManagerCallBack_;
    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallRegister"};
};
} // namespace Telephony
} // namespace OHOS

#endif // CELLULAR_CALL_REGISTER_H
