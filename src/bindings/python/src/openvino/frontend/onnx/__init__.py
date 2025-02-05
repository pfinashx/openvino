# Copyright (C) 2018-2021 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

"""
Package: openvino
Low level wrappers for the FrontEnd c++ api.
"""

# flake8: noqa

from openvino.utils import add_openvino_libs_to_path

add_openvino_libs_to_path()

try:
    from openvino.frontend.onnx.py_onnx_frontend import ConversionExtensionONNX as ConversionExtension
except ImportError as err:
    raise ImportError("OpenVINO ONNX frontend is not available, please make sure the frontend is built. "
                      "{}".format(err))
