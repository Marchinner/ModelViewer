#pragma once

#include "Core/Manager.h"

#define RM RenderManager::getInstance()

class RenderManager : public Manager
{
public:
    // Get the one and only instance of RenderManager.
    static RenderManager& getInstance();

    ~RenderManager();

    // Start rendering engine and opens graphics window.
    // Return 0 if ok, else -1.
    int startUp();

    // Close graphics window.
    void shutDown();

private:
    RenderManager();                                            // Singleton
    RenderManager(const RenderManager&) = delete;               // Disable copy
    RenderManager& operator=(const RenderManager&) = delete;    // Disable assignment
};