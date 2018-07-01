#include "atb_settings_loader.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <sstream>

// -----------------------------------------------------------------------------
// util
// -----------------------------------------------------------------------------
#include "atb.common/logger.h"

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

bool atb::core::atb_settings_loader::load(char const* const data,
                                          const int length,
                                          atb_settings& settings) noexcept {

    boost::property_tree::ptree config_root;
    //std::stringstream config_text(data, length);
    //try {
    //    boost::property_tree::read_json(config_text, config_root);
    //}
    //catch (boost::property_tree::json_parser_error& exception) {
    //    // atb::logger::error("");
    //}

    // -------------------------------------------------------------------------
    // for now provide single / default configuration
    // -------------------------------------------------------------------------
    settings.z_timeout = 30000; // 30s
    settings.z_message_count = 3;
    return true;
}
