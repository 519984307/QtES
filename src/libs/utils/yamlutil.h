#ifndef __YAMLUTIL_H__
#define __YAMLUTIL_H__

#include "runtimeerror.h"
#include "utils_global.h"

#include <yaml-cpp/yaml.h>

namespace Utils {
class UTILSSHARED_EXPORT YAMLNode
{
public:
    YAMLNode() : m_double_precision(-1), m_float_precision(-1) {}
    explicit YAMLNode(const YAML::Node &node) : m_double_precision(-1), m_float_precision(-1), m_yaml_node(node) {}
    ~YAMLNode();

    void load_string(const std::string &str);
    void load_file(const std::string &file);

    std::string get_string(const std::string &key) const { return get_value<std::string>(key); }
    std::string get_string(const std::string &key, const std::string &default_value) const
    {
        return get_value<std::string>(key, default_value);
    }
    std::string get_string(size_t index) const { return get_value<std::string>(index); }
    std::string get_string(size_t index, const std::string &default_value) const
    {
        return get_value<std::string>(index, default_value);
    }
    std::vector<std::string> get_string_array(const std::string &key) const
    {
        return get_value_array<std::string>(key);
    }
    std::vector<std::string> get_string_array(size_t index) const { return get_value_array<std::string>(index); }
    std::map<std::string, std::string> get_string_map(const std::string &key) const
    {
        return get_value_map<std::string>(key);
    }
    std::map<std::string, std::string> get_string_map(size_t index) const { return get_value_map<std::string>(index); }

    int get_int(const std::string &key) const { return get_value<int>(key); }
    int get_int(const std::string &key, int default_value) const { return get_value<int>(key, default_value); }
    int get_int(size_t index) const { return get_value<int>(index); }
    int get_int(size_t index, int default_value) const { return get_value<int>(index, default_value); }
    std::vector<int> get_int_array(const std::string &key) const { return get_value_array<int>(key); }
    std::vector<int> get_int_array(size_t index) const { return get_value_array<int>(index); }
    std::map<std::string, int> get_int_map(const std::string &key) const { return get_value_map<int>(key); }
    std::map<std::string, int> get_int_map(size_t index) const { return get_value_map<int>(index); }

    int64_t get_int64(const std::string &key) const { return get_value<int64_t>(key); }
    int64_t get_int64(const std::string &key, int64_t default_value) const
    {
        return get_value<int64_t>(key, default_value);
    }
    int64_t get_int64(size_t index) const { return get_value<int64_t>(index); }
    int64_t get_int64(size_t index, int64_t default_value) const { return get_value<int64_t>(index, default_value); }
    std::vector<int64_t> get_int64_array(const std::string &key) const { return get_value_array<int64_t>(key); }
    std::vector<int64_t> get_int64_array(size_t index) const { return get_value_array<int64_t>(index); }
    std::map<std::string, int64_t> get_int64_map(const std::string &key) const { return get_value_map<int64_t>(key); }
    std::map<std::string, int64_t> get_int64_map(size_t index) const { return get_value_map<int64_t>(index); }

    double get_double(const std::string &key) const { return get_value<double>(key); }
    double get_double(const std::string &key, double default_value) const
    {
        return get_value<double>(key, default_value);
    }
    double get_double(size_t index) const { return get_value<double>(index); }
    double get_double(size_t index, double default_value) const { return get_value<double>(index, default_value); }
    std::vector<double> get_double_array(const std::string &key) const { return get_value_array<double>(key); }
    std::vector<double> get_double_array(size_t index) const { return get_value_array<double>(index); }
    std::map<std::string, double> get_double_map(const std::string &key) const { return get_value_map<double>(key); }
    std::map<std::string, double> get_double_map(size_t index) const { return get_value_map<double>(index); }

    float get_float(const std::string &key) const { return get_value<float>(key); }
    float get_float(const std::string &key, float default_value) const { return get_value<float>(key, default_value); }
    float get_float(size_t index) const { return get_value<float>(index); }
    float get_float(size_t index, float default_value) const { return get_value<float>(index, default_value); }
    std::vector<float> get_float_array(const std::string &key) const { return get_value_array<float>(key); }
    std::vector<float> get_float_array(size_t index) const { return get_value_array<float>(index); }
    std::map<std::string, float> get_float_map(const std::string &key) const { return get_value_map<float>(key); }
    std::map<std::string, float> get_float_map(size_t index) const { return get_value_map<float>(index); }

    std::string as_string() const { return as_value<std::string>(); }
    int as_int() const { return as_value<int>(); }
    double as_double() const { return as_value<double>(); }
    float as_float() const { return as_value<float>(); }
    std::vector<std::string> as_string_array() const { return as_array<std::string>(); }
    std::vector<int> as_int_array() const { return as_array<int>(); }
    std::vector<double> as_double_array() const { return as_array<double>(); }
    std::vector<float> as_float_array() const { return as_array<float>(); }
    std::map<std::string, std::string> as_string_map() const { return as_map<std::string>(); }
    std::map<std::string, int> as_int_map() const { return as_map<int>(); }
    std::map<std::string, double> as_double_map() const { return as_map<double>(); }
    std::map<std::string, float> as_float_map() const { return as_map<float>(); }

    const YAMLNode get_node(const std::string &key) const;
    const YAMLNode get_node(size_t index) const;
    const YAMLNode get_node_force(const std::string &key) const;
    const YAMLNode get_node_force(size_t index) const;

    const YAMLNode operator[](size_t index) const;
    const YAMLNode operator[](const std::string &key) const;
    YAMLNode operator[](size_t index);
    YAMLNode operator[](const std::string &key);

    template <typename T>
    YAMLNode &operator=(const T &value)
    {
        m_yaml_node = value;
        return *this;
    }

    template <typename T>
    void push_back(const T &value)
    {
        m_yaml_node.push_back(value);
    }
    void push_back(const YAMLNode &value) { m_yaml_node.push_back(value.get_yaml()); }

    template <typename KEYTYPE, typename VALUETYPE>
    void insert(const KEYTYPE &key, const VALUETYPE &value)
    {
        m_yaml_node.force_insert(key, value);
    }

    std::set<std::string> get_keys() const;
    bool has_key(const std::string &key) const;
    bool has_index(size_t index) const;
    bool is_null() const;
    bool is_scale() const;
    bool is_array() const;
    bool is_map() const;
    size_t size() const;

    bool has_chain_keys(int i, ...) const;

    explicit operator bool() const { return !is_null(); }

    std::string to_string() const;
    bool to_file(const std::string &filename) const;
    void set_double_precision(int p) { m_double_precision = p; }
    void set_float_precision(int p) { m_float_precision = p; }

    YAMLNode clone() const;
    YAMLNode &combine(const YAMLNode &from);
    YAMLNode &combine_recursive(const YAMLNode &from);

    //open for refactor, will be private
    const YAML::Node &get_yaml() const { return m_yaml_node; }

private:
    void _check_array(const char *file, const char *function, int line) const;
    void _check_index(const char *file, const char *function, int line, size_t index) const;
    void _check_map(const char *file, const char *function, int line) const;
    void _check_key(const char *file, const char *function, int line, const std::string &key) const;

    template <typename T>
    T get_value(const std::string &key) const;
    template <typename T>
    T get_value(size_t index) const;
    template <typename T>
    T get_value(const std::string &key, const T &default_value) const;
    template <typename T>
    T get_value(size_t index, const T &default_value) const;
    template <typename T>
    std::vector<T> get_value_array(const std::string &key) const;
    template <typename T>
    std::vector<T> get_value_array(size_t index) const;
    template <typename T>
    std::map<std::string, T> get_value_map(const std::string &key) const;
    template <typename T>
    std::map<std::string, T> get_value_map(size_t index) const;

    template <typename T>
    T as_value() const;
    template <typename T>
    std::vector<T> as_array() const;
    template <typename T>
    std::map<std::string, T> as_map() const;

private:
    int m_double_precision;
    int m_float_precision;
    YAML::Node m_yaml_node;
};
} // namespace Utils

#endif // __YAMLUTIL_H__