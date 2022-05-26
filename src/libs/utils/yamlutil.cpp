#include "yamlutil.h"

#include <fstream>

#include <log/logger.h>

#include "runtimeerror.h"

using namespace Utils;

YAMLNode::~YAMLNode() {}

namespace Utils {
template <>
YAMLNode &YAMLNode::operator=<YAMLNode>(const YAMLNode &value)
{
    m_yaml_node = value.m_yaml_node;
    return *this;
}
} // namespace Utils

void YAMLNode::load_string(const std::string &str)
{
    try {
        m_yaml_node = YAML::Load(str);
    } catch (...) {
        LOG_ERROR("load config string failed.");
        throw Utils::RuntimeError("load config string failed");
    }
}

void YAMLNode::load_file(const std::string &file)
{
    try {
        m_yaml_node = YAML::LoadFile(file);
    } catch (...) {
        LOG_ERROR("load config file failed.");
        throw Utils::RuntimeError("load config file failed");
    }
}

// Recursive helper function that outputs ordered maps
void writeNode(YAML::Emitter &emitter, const YAML::Node &node)
{
    switch (node.Type()) {
    case YAML::NodeType::Sequence: {
        emitter << YAML::BeginSeq;
        for (size_t i = 0; i < node.size(); i++) {
            writeNode(emitter, node[i]);
        }
        emitter << YAML::EndSeq;
        break;
    }
    case YAML::NodeType::Map: {
        emitter << YAML::BeginMap;
        // First collect all the keys
        std::vector<std::string> keys(node.size());
        int key_it = 0;
        for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
            keys[key_it] = it->first.as<std::string>();
            ++key_it;
        }
        // Then sort them
        std::sort(keys.begin(), keys.end());
        // Then emit all the entries in sorted order.
        for (size_t i = 0; i < keys.size(); i++) {
            emitter << YAML::Key;
            emitter << keys[i];
            emitter << YAML::Value;
            writeNode(emitter, node[keys[i]]);
        }
        emitter << YAML::EndMap;
        break;
    }
    default:
        emitter << node;
        break;
    }
}

std::string YAMLNode::to_string() const
{
    YAML::Emitter emitter;
    if (m_double_precision > 0) {
        emitter.SetDoublePrecision(m_double_precision);
    }
    if (m_float_precision > 0) {
        emitter.SetFloatPrecision(m_float_precision);
    }
    writeNode(emitter, get_yaml());
    return emitter.c_str();
}

void YAMLNode::to_file(const std::string &filename) const
{
    std::ofstream ofs(filename);
    ofs << to_string();
}

YAMLNode YAMLNode::clone() const
{
    return YAMLNode(YAML::Clone(get_yaml()));
}

YAMLNode &YAMLNode::combine(const YAMLNode &from)
{
    if (from.is_map()) {
        std::set<std::string> keys = from.get_keys();
        for (auto it = keys.begin(); it != keys.end(); ++it) {
            const std::string &key = *it;
            if (has_key(key)) {
                continue;
            }
            m_yaml_node[key] = YAML::Clone(from[key].get_yaml());
        }
    }
    return *this;
}

static void combine_yaml_recursive(YAML::Node &to, const YAML::Node &from)
{
    if (from.IsMap()) {
        for (YAML::const_iterator yit = from.begin(); yit != from.end(); ++yit) {
            const std::string &key = yit->first.as<std::string>();
            if (to[key]) {
                if (to[key].IsMap()) {
                    YAML::Node sub_to = YAML::Clone(to[key]);
                    combine_yaml_recursive(sub_to, yit->second);
                    to[key] = sub_to;
                }
            } else {
                to[key] = YAML::Clone(yit->second);
            }
        }
    }
}

YAMLNode &YAMLNode::combine_recursive(const YAMLNode &from)
{
    combine_yaml_recursive(m_yaml_node, from.get_yaml());
    return *this;
}

void YAMLNode::_check_array(const char *file, const char *function, int line) const
{
    if (!is_array()) {
        std::string err;
        err.append(file)
            .append(":")
            .append(function)
            .append(":")
            .append(std::to_string(line))
            .append(" node is not an array:\n");
        LOG_ERROR(err);
        throw Utils::RuntimeError("node is not an array");
    }
}

void YAMLNode::_check_index(const char *file, const char *function, int line, size_t index) const
{
    if (!has_index(index)) {
        std::string err;
        err.append(file)
            .append(":")
            .append(function)
            .append(":")
            .append(std::to_string(line))
            .append(" node does not have index (")
            .append(std::to_string(index))
            .append("):\n");
        LOG_ERROR(err);

        throw Utils::RuntimeError("node does not have the index");
    }
}

void YAMLNode::_check_map(const char *file, const char *function, int line) const
{
    if (!is_map()) {
        std::string err;
        err.append(file)
            .append(":")
            .append(function)
            .append(":")
            .append(std::to_string(line))
            .append(" node is not a map:\n");
        LOG_ERROR(err);

        throw Utils::RuntimeError("node is not a map");
    }
}

void YAMLNode::_check_key(const char *file, const char *function, int line, const std::string &key) const
{
    if (!has_key(key)) {
        std::string err;
        err.append(file)
            .append(":")
            .append(function)
            .append(":")
            .append(std::to_string(line))
            .append(" node does not have key (")
            .append(key)
            .append("):\n");
        LOG_ERROR(err);
        throw Utils::RuntimeError("node does not have the key");
    }
}

#define check_array()                                                                                                  \
    do {                                                                                                               \
        _check_array(__FILE__, __FUNCTION__, __LINE__);                                                                \
    } while (0)
#define check_index(index)                                                                                             \
    do {                                                                                                               \
        _check_index(__FILE__, __FUNCTION__, __LINE__, (index));                                                       \
    } while (0)
#define check_map()                                                                                                    \
    do {                                                                                                               \
        _check_map(__FILE__, __FUNCTION__, __LINE__);                                                                  \
    } while (0)
#define check_key(key)                                                                                                 \
    do {                                                                                                               \
        _check_key(__FILE__, __FUNCTION__, __LINE__, (key));                                                           \
    } while (0)

const YAMLNode YAMLNode::get_node(const std::string &key) const
{
    if (is_map() && has_key(key)) {
        return YAMLNode(get_yaml()[key]);
    } else {
        return YAMLNode(YAML::Node(YAML::NodeType::Undefined));
    }
}

const YAMLNode YAMLNode::get_node(size_t index) const
{
    if (is_array() && has_index(index)) {
        return YAMLNode(get_yaml()[index]);
    } else {
        return YAMLNode(YAML::Node(YAML::NodeType::Undefined));
    }
}

const YAMLNode YAMLNode::get_node_force(const std::string &key) const
{
    check_map();
    check_key(key);
    return get_node(key);
}

const YAMLNode YAMLNode::get_node_force(size_t index) const
{
    check_array();
    check_index(index);
    return get_node(index);
}

const YAMLNode YAMLNode::operator[](const std::string &key) const
{
    return get_node(key);
}

const YAMLNode YAMLNode::operator[](size_t index) const
{
    return get_node_force(index);
}

YAMLNode YAMLNode::operator[](const std::string &key)
{
    return Utils::YAMLNode(m_yaml_node[key]);
}

YAMLNode YAMLNode::operator[](size_t index)
{
    return Utils::YAMLNode(m_yaml_node[index]);
}

std::set<std::string> YAMLNode::get_keys() const
{
    std::set<std::string> result;
    if (is_null()) {
        return result;
    }

    check_map();

    for (YAML::Node::const_iterator it = get_yaml().begin(); it != get_yaml().end(); ++it) {
        result.insert(it->first.as<std::string>());
    }
    return result;
}

bool YAMLNode::has_chain_keys(int i, ...) const
{
    va_list va;

    va_start(va, i);

    YAMLNode config;

    for (int j = 0; j < i; ++j) {
        const char *ckey = va_arg(va, const char *);
        const std::string key = std::string(ckey);

        if (j == 0) {
            if (!has_key(key))
                return false;

            config = get_node(key).clone();
        } else {
            if (!config.has_key(key))
                return false;

            config = config.get_node(key).clone();
        }
    }

    va_end(va);

    return true;
}

bool YAMLNode::has_key(const std::string &key) const
{
    if (!is_map()) {
        return false;
    }

    for (YAML::Node::const_iterator it = get_yaml().begin(); it != get_yaml().end(); ++it) {
        if (key == it->first.as<std::string>()) {
            return true;
        }
    }
    return false;
}

bool YAMLNode::has_index(size_t index) const
{
    if (!is_array()) {
        return false;
    }

    return index >= 0 && index < size();
}

bool YAMLNode::is_null() const
{
    return get_yaml().IsNull() || !get_yaml().IsDefined();
}

bool YAMLNode::is_scale() const
{
    return !is_null() && !is_array() && !is_map();
}

bool YAMLNode::is_array() const
{
    return get_yaml().IsSequence();
}

bool YAMLNode::is_map() const
{
    return get_yaml().IsMap();
}

size_t YAMLNode::size() const
{
    return get_yaml().size();
}

template <typename T>
T YAMLNode::get_value(const std::string &key) const
{
    check_map();
    check_key(key);
    return get_yaml()[key].as<T>();
}
template std::string YAMLNode::get_value<std::string>(const std::string &key) const;
template int YAMLNode::get_value<int>(const std::string &key) const;
template int64_t YAMLNode::get_value<int64_t>(const std::string &key) const;
template double YAMLNode::get_value<double>(const std::string &key) const;
template float YAMLNode::get_value<float>(const std::string &key) const;

template <typename T>
T YAMLNode::get_value(size_t index) const
{
    check_array();
    check_index(index);
    return get_yaml()[index].as<T>();
}
template std::string YAMLNode::get_value<std::string>(size_t index) const;
template int YAMLNode::get_value<int>(size_t index) const;
template int64_t YAMLNode::get_value<int64_t>(size_t index) const;
template double YAMLNode::get_value<double>(size_t index) const;
template float YAMLNode::get_value<float>(size_t index) const;

template <typename T>
T YAMLNode::get_value(const std::string &key, const T &default_value) const
{
    try {
        if (!has_key(key)) {
            return default_value;
        }
        return get_value<T>(key);
    } catch (...) {
        return default_value;
    }
}
template std::string YAMLNode::get_value<std::string>(const std::string &key, const std::string &default_value) const;
template int YAMLNode::get_value<int>(const std::string &key, const int &default_value) const;
template int64_t YAMLNode::get_value<int64_t>(const std::string &key, const int64_t &default_value) const;
template double YAMLNode::get_value<double>(const std::string &key, const double &default_value) const;
template float YAMLNode::get_value<float>(const std::string &key, const float &default_value) const;

template <typename T>
T YAMLNode::get_value(size_t index, const T &default_value) const
{
    try {
        if (!has_index(index)) {
            return default_value;
        }
        return get_value<T>(index);
    } catch (...) {
        return default_value;
    }
}
template std::string YAMLNode::get_value<std::string>(size_t index, const std::string &default_value) const;
template int YAMLNode::get_value<int>(size_t index, const int &default_value) const;
template int64_t YAMLNode::get_value<int64_t>(size_t index, const int64_t &default_value) const;
template double YAMLNode::get_value<double>(size_t index, const double &default_value) const;
template float YAMLNode::get_value<float>(size_t index, const float &default_value) const;

template <typename T>
std::vector<T> YAMLNode::get_value_array(const std::string &key) const
{
    check_map();
    check_key(key);
    const YAMLNode &node = get_node(key);
    return node.as_array<T>();
}
template std::vector<std::string> YAMLNode::get_value_array<std::string>(const std::string &key) const;
template std::vector<int> YAMLNode::get_value_array<int>(const std::string &key) const;
template std::vector<double> YAMLNode::get_value_array<double>(const std::string &key) const;
template std::vector<float> YAMLNode::get_value_array<float>(const std::string &key) const;

template <typename T>
std::vector<T> YAMLNode::get_value_array(size_t index) const
{
    check_array();
    check_index(index);
    const YAMLNode &node = get_node(index);
    return node.as_array<T>();
}
template std::vector<std::string> YAMLNode::get_value_array<std::string>(size_t index) const;
template std::vector<int> YAMLNode::get_value_array<int>(size_t index) const;
template std::vector<int64_t> YAMLNode::get_value_array<int64_t>(size_t index) const;
template std::vector<double> YAMLNode::get_value_array<double>(size_t index) const;
template std::vector<float> YAMLNode::get_value_array<float>(size_t index) const;

template <typename T>
std::map<std::string, T> YAMLNode::get_value_map(const std::string &key) const
{
    check_map();
    check_key(key);
    const YAMLNode &node = get_node(key);
    return node.as_map<T>();
}
template std::map<std::string, std::string> YAMLNode::get_value_map<std::string>(const std::string &key) const;
template std::map<std::string, int> YAMLNode::get_value_map<int>(const std::string &key) const;
template std::map<std::string, int64_t> YAMLNode::get_value_map<int64_t>(const std::string &key) const;
template std::map<std::string, double> YAMLNode::get_value_map<double>(const std::string &key) const;
template std::map<std::string, float> YAMLNode::get_value_map<float>(const std::string &key) const;

template <typename T>
std::map<std::string, T> YAMLNode::get_value_map(size_t index) const
{
    check_array();
    check_index(index);
    const YAMLNode &node = get_node(index);
    return node.as_map<T>();
}
template std::map<std::string, std::string> YAMLNode::get_value_map<std::string>(size_t index) const;
template std::map<std::string, int> YAMLNode::get_value_map<int>(size_t index) const;
template std::map<std::string, int64_t> YAMLNode::get_value_map<int64_t>(size_t index) const;
template std::map<std::string, double> YAMLNode::get_value_map<double>(size_t index) const;
template std::map<std::string, float> YAMLNode::get_value_map<float>(size_t index) const;

template <typename T>
T YAMLNode::as_value() const
{
    return get_yaml().as<T>();
}
template std::string YAMLNode::as_value<std::string>() const;
template int YAMLNode::as_value<int>() const;
template double YAMLNode::as_value<double>() const;
template float YAMLNode::as_value<float>() const;

template <typename T>
std::vector<T> YAMLNode::as_array() const
{
    std::vector<T> result;
    if (is_scale()) {
        result.push_back(this->as_value<T>());
        return result;
    }
    check_array();
    for (size_t i = 0; i < this->size(); ++i) {
        result.push_back(this->get_value<T>(i));
    }
    return result;
}
template std::vector<std::string> YAMLNode::as_array<std::string>() const;
template std::vector<int> YAMLNode::as_array<int>() const;
template std::vector<int64_t> YAMLNode::as_array<int64_t>() const;
template std::vector<double> YAMLNode::as_array<double>() const;
template std::vector<float> YAMLNode::as_array<float>() const;

template <typename T>
std::map<std::string, T> YAMLNode::as_map() const
{
    check_map();
    std::map<std::string, T> result;
    std::set<std::string> keys = this->get_keys();
    for (auto it = keys.begin(); it != keys.end(); ++it) {
        result[*it] = this->get_value<T>(*it);
    }
    return result;
}
template std::map<std::string, std::string> YAMLNode::as_map<std::string>() const;
template std::map<std::string, int> YAMLNode::as_map<int>() const;
template std::map<std::string, double> YAMLNode::as_map<double>() const;
template std::map<std::string, float> YAMLNode::as_map<float>() const;
