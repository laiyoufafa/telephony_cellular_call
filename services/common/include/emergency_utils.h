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

#ifndef TELEPHONY_CELLULAR_CALL_EMERGENCY_UTILS_H
#define TELEPHONY_CELLULAR_CALL_EMERGENCY_UTILS_H

#include <string>

#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
class EmergencyUtils {
public:
    /**
     *  EmergencyUtils constructor
     */
    EmergencyUtils() = default;

    /**
     *  ~EmergencyUtils destructor
     */
    ~EmergencyUtils() = default;

    /**
     * @brief Is it an emergency call
     *
     * @param slotId
     * @param phoneNum
     * @return bool
     */
    bool IsEmergencyCall(int32_t slotId, const std::string &phoneNum);

private:
    /**
     * determine the handling of urgent calls
     *
     * @param slotId
     * @param formatString
     * @return bool
     */
    bool IsEmergencyCallProcessing(int32_t slotId, const std::string &formatString);
};
} // namespace Telephony
} // namespace OHOS
#endif // TELEPHONY_CELLULAR_CALL_EMERGENCY_UTILS_H
