#include <iostream>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/attr.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;

void initLogging(int verbooseLevel = 0);

BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)

using namespace logging::trivial;

void initLogging(int verbooseLevel)
{
    auto logLineOutput = (
            expr::stream
                << "#" << expr::attr< unsigned int >("LineID") << " ["
                << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                << "] Thread " 
                << expr::attr< boost::log::attributes::current_thread_id::value_type >("ThreadID")
                << " - "
                << /*std::setw(7) << */logging::trivial::severity
                << ": " << expr::smessage
        );
    
    logging::add_file_log
    (
        keywords::file_name = "MyLog.txt",
        keywords::format = logLineOutput
    );
    
    logging::add_console_log
    (
        std::cout,
        keywords::format = logLineOutput
    );
    logging::add_common_attributes();
    
    switch (verbooseLevel)
    {
        default:
        case 0:
            logging::core::get()->set_filter ( severity >= info);
        break;
        case 1:
            logging::core::get()->set_filter ( severity >= debug );
        break;
        case 2:
            logging::core::get()->set_filter ( severity >= trace );
        break;
    }
}

int main()
{
    initLogging(2);
    src::severity_logger_mt< severity_level > logger;
    BOOST_LOG_SEV(logger, info) << "Hello, Masha, info for you!";
    BOOST_LOG_SEV(logger, debug) << "Hello, Masha, debug for you!";
    BOOST_LOG_SEV(logger, trace) << "Hello, Masha, trace for you!";
    return 0;
}
