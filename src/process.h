#pragma once

#include <string>
#include <stdio.h>

namespace ABB::OptiMold::Utils {

    // Execute system command and return its output as a string
    // @TODO: rewrite with boost::process
    inline std::string execute(const char* cmd) {
        char buffer[128];
        std::string result = "";
        FILE* pipe = popen(cmd, "r");
        if (!pipe) return "";
        try {
            while (!feof(pipe)) {
                if (fgets(buffer, 128, pipe) != NULL)
                    result += buffer;
            }
        } catch (...) {
            pclose(pipe);
        }
        pclose(pipe);
        return result;
    }

}
