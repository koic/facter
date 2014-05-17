#ifndef FACTER_FACTS_MAP_VALUE_HPP_
#define FACTER_FACTS_MAP_VALUE_HPP_

#include "value.hpp"
#include <map>
#include <string>
#include <memory>

namespace facter { namespace facts {

    /**
     * Represents a fact value that maps fact names to values.
     */
    struct map_value : value
    {
        /**
         * Constructs a map value.
         */
        map_value()
        {
        }

        /**
         * Constructs a map value.
         * @param elements The elements to store in the map value.
         */
        explicit map_value(std::map<std::string, std::unique_ptr<value>>&& elements) :
            _elements(std::move(elements))
        {
        }

        // Force non-copyable
        map_value(map_value const&) = delete;
        map_value& operator=(map_value const&) = delete;

        // Allow movable
        map_value(map_value&&) = default;
        map_value& operator=(map_value&&) = default;

        /**
         * Converts the value to a JSON value.
         * @param allocator The allocator to use for creating the JSON value.
         * @param value The returned JSON value.
         */
        virtual void to_json(rapidjson::Allocator& allocator, rapidjson::Value& value) const;

        /**
         * Gets the map of elements in the value.
         * @return Returns the vector of elements in the array.
         */
        std::map<std::string, std::unique_ptr<value>> const& elements() const { return _elements; }

        /**
         * Gets the value in the map of the given name.
         * @param name The name of the value in the map to get.
         * @return Returns the value in the map or nullptr if the value is not in the map.
         */
        value const* operator[](std::string const& name) const;

     protected:
        /**
          * Writes the value to the given stream.
          * @param os The stream to write to.
          * @returns Returns the stream being written to.
          */
        virtual std::ostream& write(std::ostream& os) const;

        /**
          * Writes the value to the given YAML emitter.
          * @param emitter The YAML emitter to write to.
          * @returns Returns the given YAML emitter.
          */
        virtual YAML::Emitter& write(YAML::Emitter& emitter) const;

     private:
        std::map<std::string, std::unique_ptr<value>> _elements;
    };

}}  // namespace facter::facts

#endif  // FACTER_FACTS_MAP_VALUE_HPP_

