#pragma once

#include <ctime>
#include <chrono>


namespace ABB::OptiMold::Utils {

std::tm timetotm(time_t secondsUTC);

time_t time_now();

class runtime_measurement
{
public:
    void start();
    double end();

private:
    std::chrono::steady_clock::time_point start_point;
};

}
