#include "Core/Manager.h"

Manager::Manager()
    : m_type{ "Manager" }
    , m_is_started{ false }
{
}

Manager::~Manager()
{
}

int Manager::startUp()
{
    m_is_started = true;
    return 0;
}

void Manager::shutDown()
{
    m_is_started = false;
}

std::string Manager::getType() const
{
    return m_type;
}

bool Manager::isStarted() const
{
    return m_is_started;
}

void Manager::setType(std::string type)
{
    m_type = type;
}