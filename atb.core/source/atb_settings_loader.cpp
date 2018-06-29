#include "atb_settings_loader.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <sstream>

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

atb::core::atb_settings* atb::core::atb_settings_loader::load(
    atb::logger::logger* const logger,
    char const * const data, const int length) noexcept {

    boost::property_tree::ptree config_root;
    std::stringstream config_text(data, length);
    try {
        boost::property_tree::read_json(config_text, config_root);
    } catch (boost::property_tree::json_parser_error& exception) {
        mess
        logger->error();
    }
    return nullptr;
}
