/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "textclassifier_jni.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace libtextclassifier {
namespace {

TEST(TextClassifier, ConvertIndicesBMPUTF8) {
  EXPECT_EQ(ConvertIndicesBMPToUTF8("hello", {0, 5}),
            ConvertIndicesUTF8ToBMP("hello", {0, 5}));

  // Simple example where the longer character is before the selection.
  //  character 😁 is 0x1f601
  EXPECT_EQ(ConvertIndicesBMPToUTF8("😁 Hello World.", {3, 8}),
            std::make_pair(2, 7));

  EXPECT_EQ(ConvertIndicesUTF8ToBMP("😁 Hello World.", {2, 7}),
            std::make_pair(3, 8));

  // Longer character is before and in selection.
  EXPECT_EQ(ConvertIndicesBMPToUTF8("😁 Hell😁 World.", {3, 9}),
            std::make_pair(2, 7));

  EXPECT_EQ(ConvertIndicesUTF8ToBMP("😁 Hell😁 World.", {2, 7}),
            std::make_pair(3, 9));

  // Longer character is before and after selection.
  EXPECT_EQ(ConvertIndicesBMPToUTF8("😁 Hello😁World.", {3, 8}),
            std::make_pair(2, 7));

  EXPECT_EQ(ConvertIndicesUTF8ToBMP("😁 Hello😁World.", {2, 7}),
            std::make_pair(3, 8));

  // Longer character is before in after selection.
  EXPECT_EQ(ConvertIndicesBMPToUTF8("😁 Hell😁😁World.", {3, 9}),
            std::make_pair(2, 7));

  EXPECT_EQ(ConvertIndicesUTF8ToBMP("😁 Hell😁😁World.", {2, 7}),
            std::make_pair(3, 9));
}

}  // namespace
}  // namespace libtextclassifier
