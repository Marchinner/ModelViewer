#pragma once

#include <string>

// Base Manager Class
class Manager
{
public:
    Manager();
    virtual ~Manager();

    // Start up Manager.
    // Return 0 if success, else negative number.
    virtual int startUp();

    // Shut down Manager.
    virtual void shutDown();

    // Get the type identifier of Manager.
    std::string getType() const;

    // Return true when startUp() was executed ok, else false.
    bool isStarted() const;

protected:
    // Set type identifier of Manager.
    void setType(std::string type);


private:
    std::string m_type; // Manager type identifier.
    bool m_is_started;  // True when started successfully.
};