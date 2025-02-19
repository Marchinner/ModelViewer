#include "Utils/utility.h"
#include <ctime>
#include <cassert>
#include <stdio.h>

char* getTimeString()
{
    int res = 0;

    // String to return, made 'static' so persists.
    static char time_str[30];

    // System call to get time.
    time_t now;
    time_t time_res = time(&now);
    assert(time_res != -1);

    struct tm* p_time = localtime(&now);
    assert(p_time);

    // '02' gives two digits, '%d' for integers.
    res = snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d",
        p_time->tm_hour,
        p_time->tm_min,
        p_time->tm_sec);
    assert(res > 0);

    return time_str;
}
