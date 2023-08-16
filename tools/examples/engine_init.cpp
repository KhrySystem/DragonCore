#include <cstdlib>
#include <cstdio>
#include <dragon/core.hpp>

DgEngine engine;

void initEngine() {
    DgEngineCreateInfo createInfo{};
    createInfo.vulkanDebugEnabled = DG_TRUE;
    createInfo.appName = "Engine Init Test";

    DgResult r = dgInitEngine(engine, createInfo);
    printf("dgInitEngine returned code 0x%x\n", r);
    if(r == DG_SUCCESS) return;
    abort();
}

void destroy() {
    dgDestroyEngine(engine);
}

int main(void) {
    initEngine();
    destroy();
}