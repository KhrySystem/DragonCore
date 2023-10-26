#include <dragon/core.hpp>
#include "engine_init.hpp"

bool Dragon::Engine::addSubmodule(Dragon::Submodule* submodule) {
    this->submodules.push_back(submodule);
    submodule->onAddition(this);
    return true;
}

void Dragon::Engine::update() {
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->update(this);
    }
}

void Dragon::Engine::close() {
    vmaDestroyAllocator(this->allocator);
    vkb::destroy_device(this->device);
    vkb::destroy_instance(this->instance);
}

Dragon::Engine::~Engine() {
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->beforeClose(this);
    }
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->close(this);
    }
    this->close();
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->afterClose(this);
    }
}