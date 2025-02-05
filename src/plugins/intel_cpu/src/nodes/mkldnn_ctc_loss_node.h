// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <ie_common.h>
#include <mkldnn_node.h>

namespace MKLDNNPlugin {

class MKLDNNCTCLossNode : public MKLDNNNode {
public:
    MKLDNNCTCLossNode(const std::shared_ptr<ngraph::Node>& op, const mkldnn::engine& eng, MKLDNNWeightsSharing::Ptr &cache);

    void getSupportedDescriptors() override {};
    void initSupportedPrimitiveDescriptors() override;
    void execute(mkldnn::stream strm) override;
    bool created() const override;

    static bool isSupportedOperation(const std::shared_ptr<const ngraph::Node>& op, std::string& errorMessage) noexcept;

    void executeDynamicImpl(mkldnn::stream strm) override;
    bool needPrepareParams() const override { return false; };

private:
    bool ctcMergeRepeated;
    bool preprocessCollapseRepeated;
    bool unique;

    std::string errorPrefix;
};

}  // namespace MKLDNNPlugin
