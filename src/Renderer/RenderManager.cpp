#include "Renderer/RenderManager.h"

RenderManager::RenderManager()
{
    setType("RenderManager");
}

RenderManager& RenderManager::getInstance()
{
    static RenderManager renderManager;
    return renderManager;
}

RenderManager::~RenderManager()
{
    shutDown();
}

int RenderManager::startUp()
{
    return 0;
}

void RenderManager::shutDown()
{
}
