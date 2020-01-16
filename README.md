# monodepth2-cpp
deploy cpp with [monodepth](https://github.com/nianticlabs/monodepth2),

## depend
opencv
libtorch(test in 1.3.0,you can try other version)

## you can reference my qt config to develop in other ide
```
QMAKE_CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0
INCLUDEPATH += $$PWD/../../../lib/libtorch/include
DEPENDPATH += $$PWD/../../../lib/libtorch/include
INCLUDEPATH += $$PWD/../../../lib/libtorch/include/torch/csrc/api/include
DEPENDPATH += $$PWD/../../../lib/libtorch/include/torch/csrc/api/include
unix:!macx: LIBS += -L$$PWD/../../../lib/libtorch/lib/ -lgloo -lgloo_cuda -lasmjit -lgmock -lbenchmark -lgmock_main -lbenchmark_main \
                                                        -lgomp-7c85b1e2 -lc10_cuda -lgtest -lc10d -lgtest_main -lc10d_cuda_test -lmkldnn -lc10 -lnnpack \
                                                        -lcaffe2_detectron_ops_gpu -lnnpack_reference_layers -lcaffe2_module_test_dynamic -lnvrtc-a0b34244 \
                                                        -lcaffe2_nvrtc -lnvrtc-builtins -lCaffe2_perfkernels_avx2 -lnvToolsExt-3965bdd0 -lCaffe2_perfkernels_avx512 \
                                                        -lonnx -lCaffe2_perfkernels_avx -lonnx_proto -lcaffe2_protos -lprotobuf -lclog -lprotobuf-lite \
                                                        -lcpuinfo -lprotoc -lcpuinfo_internals -lpthreadpool -lcudart-1581fefa -lpytorch_qnnpack -lfbgemm \
                                                        -lqnnpack -lfoxi_loader -ltorch
```
有些lib我不知道有没有，所以基本就是全添加进去了，不用的编译器会自动忽略

## model
>链接: https://pan.baidu.com/s/1MDQAGdJFpEpph7wJxv0mzQ  密码: 7odd
 
there is a [other libtorch project](https://github.com/ZHEQIUSHUI/RFBnet-cpp-libtorch) model about [RFBNet](https://github.com/ruinmessi/RFBNet) in this link,if you have interesting in it,you can follow it

# demo
![](https://github.com/nianticlabs/monodepth2/raw/master/assets/teaser.gif)
