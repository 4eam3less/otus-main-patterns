#pragma once

#include "../rotate/angle.hpp"
#include "../move/vec2.hpp"
#include <variant>
#include <map>

class Property {
public:
    using PropertyType = std::variant<int, Angle, std::string, Vec2>;

    Property() = default;

    template<typename T>
    Property(T value) : value_(value) {}

    template<typename T>
    Property& operator=(T value) {
        value_ = value;
        return *this;
    }

    template<typename T>
    T get() const {
        if (auto val = std::get_if<T>(&value_)) {
            return *val;
        }
        throw std::bad_variant_access();
    }

private:
    PropertyType value_;
};

class UObject {
public:
    void set_property(const std::string& key, const Property& value) {
        properties_[key] = value;
    }

    Property& operator[](const std::string& key) {
        return properties_[key];
    }

    const Property& operator[](const std::string& key) const {
        auto it = properties_.find(key);
        if (it != properties_.end()) {
            return it->second;
        }
        throw std::out_of_range("Property not found");
    }

private:
    std::map<std::string, Property> properties_;
};
