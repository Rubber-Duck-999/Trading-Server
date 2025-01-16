#include <string>
#include "boost/log/trivial.hpp"
#include "boost/log/utility/setup.hpp"
#include <boost/log/utility/setup/common_attributes.hpp>

#ifndef LOGGING_H
#define LOGGING_H

class Logger {
public:
    Logger() {
        boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");

        boost::log::add_file_log(
            boost::log::keywords::file_name = "sample_%3N.log",
            boost::log::keywords::rotation_size = 1 * 1024 * 1024,
            boost::log::keywords::max_size = 20 * 1024 * 1024,
            boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
            boost::log::keywords::auto_flush = true
        );

        boost::log::add_common_attributes();

#ifndef _DEBUG
        boost::log::core::get()->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::info
        );
#endif
    }
};

static Logger globalLogger; 
// Automatically initializes at program startup (-Wall)

#endif // LOGGING_H