// Run all days:     forge_tests
// Run one day:      forge_tests day7
#include "check.h"
#include "Common.h"
#include <csignal>
#include <cstdlib>
#include <map>
#include <vector>

int g_checks = 0;
int g_failures = 0;
static int g_day = 0;

void registerDays(std::map<int, std::function<void()>>& days);

static void onCrash(int) {
    std::cout << "day" << g_day << "  CRASHED. Look for a bad pointer or a double delete.\n";
    std::_Exit(3);
}

int main(int argc, char* argv[]) {
    std::signal(SIGSEGV, onCrash);
    std::signal(SIGABRT, onCrash);
#ifdef SIGBUS
    std::signal(SIGBUS, onCrash);   // macOS can report a bad pointer this way
#endif
    std::map<int, std::function<void()>> days;
    registerDays(days);
    int only = 0;
    if (argc == 2) {
        std::string a = argv[1];
        only = std::atoi(a.rfind("day", 0) == 0 ? a.c_str() + 3 : a.c_str());
        if (!days.count(only)) {
            std::cout << "No tests for " << a << ". Reviews and exam days have no code tests.\n";
            return 1;
        }
    }
    int done = 0, total = 0;
    for (auto& entry : days) {
        if (only && entry.first != only) continue;
        ++total;
        g_day = entry.first;
        g_checks = g_failures = 0;
        std::string status;
        try {
            entry.second();
            status = g_failures ? "FAIL" : "PASS";
        } catch (const NotImplemented&) {
            status = "TODO";
        } catch (const std::exception& e) {
            std::cout << "    unexpected exception: " << e.what() << '\n';
            status = "FAIL";
        }
        if (status == "PASS") ++done;
        std::cout << "day" << entry.first << "  " << status << "  (" << g_checks - g_failures
                  << " of " << g_checks << " checks passed)\n";
    }
    std::cout << done << " of " << total << " days complete\n";
    return done == total ? 0 : 1;
}
