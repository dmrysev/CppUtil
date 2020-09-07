#include "util/time.h"

using namespace std::chrono;


namespace ABB::OptiMold::Utils {

tm timetotm(time_t secondsUTC) {
    struct tm* ptm = gmtime(&secondsUTC);

    struct tm stm = *ptm;
    stm.tm_year += 1900;
    ++stm.tm_mon;

    return stm;
}

time_t time_now() {
    auto timePoint = system_clock::now();
    time_t time = system_clock::to_time_t(timePoint);

    return time;
}

void runtime_measurement::start() {
    start_point = steady_clock::now();
}

double runtime_measurement::end() {
    auto endPoint = steady_clock::now();
    auto totalDuration = duration_cast<microseconds>(endPoint - start_point).count();
    auto totalDuration_ms = static_cast<double>(totalDuration / 1000);

    return totalDuration_ms;
}

//std::string msg = name.empty() ? "Finished in " : name + " finished in ";
//LOG(DEBUG) << msg << totalDuration_ms << " milliseconds" << std::endl;


}
