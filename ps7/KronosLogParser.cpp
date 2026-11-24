// File: KronosLogParser.cpp
// Project: ps7
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/28/2022

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>

class Service {
 public:
    Service():
        title(""), time("0"), filename(""), startLine(0), endLine(0) {}
    Service(std::string name, std::size_t startLine, std::string file):
        title(name), time("0"), filename(file),
        startLine(startLine), endLine(0) {}
    void setName(std::string n) { title = n; }
    void setTime(std::string ms) { time = ms; }
    void setFile(std::string f) { filename = f; }
    void setStartLine(size_t l) { startLine = l; }
    void setEndLine(size_t l) { endLine = l; }
    std::string name() const { return title; }
    std::string toString(std::string filename) const {
        std::string end;
        if (endLine != 0)
            end = "\t\t Completed: " + std::to_string(endLine)
                + "(" + filename + ")\n"
                + "\t\t Elapsed Time: " + time + "\n";
        else
            end = "\t\t Completed: Not completed"
                  "(" + filename + ")\n"
                  "\t\t Elapsed Time: \n";
        return "\t" + title + "\n"
            + "\t\t Start: " + std::to_string(startLine)
            + "(" + filename + ")\n"
            + end;
    }

 private:
    std::string title, time, filename;
    std::size_t startLine, endLine;
};

std::string notStartedServices(std::string filename);

int main(int argc, char **argv) {
    // open the given log file
    std::string logFilename = argv[1];
    std::ifstream logFile(logFilename);
    if (!logFile)
        throw std::invalid_argument("Given file not found.");

    // parse the log file for boot data
    std::regex bootMsg{"\\(log\\.c\\.166\\) server started"},
               endBootMsg{"oejs\\.AbstractConnector:Started "
                          "SelectChannelConnector@0\\.0\\.0\\.0:9080"},
               serviceMsg{"Starting Service\\.  .*"},
               endServiceMsg{"Service started successfully\\.  .*"},
               timeParse{"(\\d{4}-\\d{2}-\\d{2} (\\d{2}:){2}\\d{2}).*"},
               serviceParse{"Starting Service\\.  (\\w*).*"},
               endServiceParse{"Service started successfully\\.  "
                               "(\\w*).*"},
               endServiceTimeParse{"Service started successfully\\.  "
                               "\\w* [\\d\\.]{3,5} \\((.*)\\)"};
    std::string format("$1"),
                report;
    std::size_t bootStarts = 0,
                bootEnds = 0;
    enum bootStates { Booting, NotBooting };
    bootStates bootState = NotBooting;
    std::vector<Service> services;
    size_t i = 0;
    boost::posix_time::ptime startTime;
    while (logFile) {
        i++;
        std::string line;
        std::getline(logFile, line);
        switch (bootState) {
            case Booting:
            // check for service
            if (std::regex_match(line, serviceMsg)) {
                services.push_back(Service(
                    std::regex_replace(line, serviceParse, format),
                    i, logFilename));
            }
            // check for service end
            if (std::regex_match(line, endServiceMsg)) {
                std::string name(
                    std::regex_replace(line, endServiceParse, format));
                for (auto& serv : services) {
                    if (serv.name() == name) {
                        serv.setTime(std::regex_replace(
                            line, endServiceTimeParse, format));
                        serv.setEndLine(i);
                        break;
                    }
                }
            }
            // check for boot end
            if (std::regex_search(line, endBootMsg)) {
                boost::posix_time::ptime endTime = boost::posix_time::ptime(
                    boost::posix_time::time_from_string(
                        std::regex_replace(line, timeParse, format)));
                boost::posix_time::time_duration duration = endTime - startTime;
                report += std::to_string(i) + "(" + logFilename + "): "
                       + std::regex_replace(line, timeParse, format)
                       + " Boot Completed\n"
                       + "\tBoot Time: "
                       + std::to_string(duration.total_milliseconds()) + "ms "
                       + "\n\nServices\n";
                for (const auto& ser : services)
                    report += ser.toString(logFilename);
                report += "\n";
                bootEnds++;
                bootState = NotBooting;
                break;
            }
            case NotBooting:
            // check for boot start
            if (std::regex_search(line, bootMsg)) {
                // if previous boot's end hasn't been found,
                // then the boot was incomplete
                if (bootState == Booting) {
                    report += "**** Incomplete boot **** \n\n"
                           + notStartedServices(logFilename);
                }
                report += "=== Device boot ===\n"
                       + std::to_string(i) + "(" + logFilename + "): "
                       + std::regex_replace(line, timeParse, format)
                       + " Boot Start\n";
                startTime = boost::posix_time::ptime(
                    boost::posix_time::time_from_string(
                        std::regex_replace(line, timeParse, format)));
                services.clear();
                bootStarts++;
                bootState = Booting;
                break;
            }
            default:
            break;
        }
    }
    if (bootState == Booting) {
        report += "**** Incomplete boot **** \n\n"
               + notStartedServices(logFilename);
    }
    report.pop_back();  // remove the final char, \n
    logFile.close();

    // assemble header
    report = "Device Boot Report\n\n"
             "InTouch log file: " + logFilename + "\n"
             "Lines Scanned: " + std::to_string(i-1) + "\n\n"
             "Device boot count: initiated = " + std::to_string(bootStarts) +
             ", completed: " + std::to_string(bootEnds) + "\n\n\n"
             + report;

    // write data to the output file
    std::string reportFilename = logFilename + ".rpt";
    std::ofstream reportFile(reportFilename);
    reportFile << report;
    reportFile.close();

    return 0;
}

// notStartedServices() returns a string representing
// a formated list of services that were not successfully
// started as a result of an unsuccessful boot.
// The string argument is the name of the log file.
std::string notStartedServices(std::string filename) {
    std::vector<std::string> services = {
        "Logging",
        "DatabaseInitialize",
        "MessagingService",
        "HealthMonitorService",
        "Persistence",
        "ConfigurationService",
        "LandingPadService",
        "PortConfigurationService",
        "CacheService",
        "ThemingService",
        "StagingService",
        "DeviceIOService",
        "BellService",
        "GateService",
        "ReaderDataService",
        "BiometricService",
        "StateManager",
        "OfflineSmartviewService",
        "AVFeedbackService",
        "DatabaseThreads",
        "SoftLoadService",
        "WATCHDOG",
        "ProtocolService",
        "DiagnosticsService"
    };
    std::string result("Services\n");
    for (const auto& str : services) {
        result += "\t" + str + "\n"
               + "\t\t Start: Not started(" + filename + ")\n"
               + "\t\t Completed: Not completed(" + filename + ")\n"
               + "\t\t Elapsed Time: \n";
    }
    result += "\n\t*** Services not successfully started:";
    for (const auto& str : services) result += " " + str + ",";
    result.pop_back();
    result += "\n\n";
    return result;
}
