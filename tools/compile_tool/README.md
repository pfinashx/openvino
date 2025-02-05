# Compile Tool {#openvino_inference_engine_tools_compile_tool_README}

Compile tool is a C++ application that enables you to compile a network for inference on a specific device and export it to a binary file.
With the Compile Tool, you can compile a network using supported Inference Engine plugins on a machine that doesn't have the physical device connected and then transfer a generated file to any machine with the target inference device available.

The tool compiles networks for the following target devices using corresponding Inference Engine plugins:
* Intel® Neural Compute Stick 2 (MYRIAD plugin)


The tool is delivered as an executable file that can be run on both Linux* and Windows*.
The tool is located in the `<INSTALLROOT>/tools/compile_tool` directory.

The workflow of the Compile tool is as follows:

1. First, the application reads command-line parameters and loads a network to the Inference Engine device.
2. The application exports a blob with the compiled network and writes it to the output file.

## Run the Compile Tool

Running the application with the `-h` option yields the following usage message:

```sh
./compile_tool -h
OpenVINO Runtime version ......... 2022.1.0
Build ........... custom_changed_compile_tool_183a1adfcd7a001974fe1c5cfa21ec859b70ca2c

compile_tool [OPTIONS]

 Common options:
    -h                                       Optional. Print the usage message.
    -m                           <value>     Required. Path to the XML model.
    -d                           <value>     Required. Specify a target device for which executable network will be compiled.
                                             Use "-d HETERO:<comma-separated_devices_list>" format to specify HETERO plugin.
                                             Use "-d MULTI:<comma-separated_devices_list>" format to specify MULTI plugin.
                                             The application looks for a suitable plugin for the specified device.
    -o                           <value>     Optional. Path to the output file. Default value: "<model_xml_file>.blob".
    -c                           <value>     Optional. Path to the configuration file.
    -ip                          <value>     Optional. Specifies precision for all input layers of the network.
    -op                          <value>     Optional. Specifies precision for all output layers of the network.
    -iop                        "<value>"    Optional. Specifies precision for input and output layers by name.
                                             Example: -iop "input:FP16, output:FP16".
                                             Notice that quotes are required.
                                             Overwrites precision from ip and op options for specified layers.
    -il                          <value>     Optional. Specifies layout for all input layers of the network.
    -ol                          <value>     Optional. Specifies layout for all output layers of the network.
    -iol                        "<value>"    Optional. Specifies layout for input and output layers by name.
                                             Example: -iol "input:NCHW, output:NHWC".
                                             Notice that quotes are required.
                                             Overwrites layout from il and ol options for specified layers.
    -iml                         <value>     Optional. Specifies model layout for all input layers of the network.
    -oml                         <value>     Optional. Specifies model layout for all output layers of the network.
    -ioml                       "<value>"    Optional. Specifies model layout for input and output tensors by name.
                                             Example: -ionl "input:NCHW, output:NHWC".
                                             Notice that quotes are required.
                                             Overwrites layout from il and ol options for specified layers.
    -ov_api_1_0                              Optional. Compile model to legacy format for usage in Inference Engine API,
                                             by default compiles to OV 2.0 API

 MYRIAD-specific options:
    -VPU_NUMBER_OF_SHAVES        <value>     Optional. Specifies number of shaves.
                                             Should be set with "VPU_NUMBER_OF_CMX_SLICES".
                                             Overwrites value from config.

    -VPU_NUMBER_OF_CMX_SLICES    <value>     Optional. Specifies number of CMX slices.
                                             Should be set with "VPU_NUMBER_OF_SHAVES".
                                             Overwrites value from config.
    -VPU_TILING_CMX_LIMIT_KB     <value>     Optional. Specifies CMX limit for data tiling.
                                             Value should be equal or greater than -1.
                                             Overwrites value from config.
```

Running the application with the empty list of options yields an error message.

For example, to compile a blob for inference on an Intel® Neural Compute Stick 2 from a trained network, run the command below:

```sh
./compile_tool -m <path_to_model>/model_name.xml -d MYRIAD
```

### Import a Compiled Blob File to Your Application

To import a blob with the network from a generated file into your application, use the
`ov::Core::import_model` method:

```cpp
ov::Core ie;
std::ifstream file{"model_name.blob"};
ov::CompiledModel compiled_model = ie.import_model(file, "MYRIAD", {});
```
