

#pragma once

#include "ideoengine/base/Fields.h"
#include "ideoengine/base/Values.h"

#include <cstdint>
#include <map>

namespace ideoengine {
    namespace squared {
        class SquaredTuple {
        public:
            SquaredTuple(const base::Fields& fields, const base::Values& values) :
                    _fields(fields), _values(values){
                int32_t fieldIndex = 0;
                for ( const std::string& field : fields ) {
                    _fieldMaps[field] = fieldIndex;

                    ++ fieldIndex;
                }
            }

            int32_t GetInteger(int32_t index) {
                return _values[index].ToInt32();
            }

            int32_t GetInteger(const std::string& fieldName) {
                int32_t index = _fieldMaps[fieldName];

                return GetInteger(index);
            }

            std::string GetString(int32_t index) {
                return _values[index].ToString();
            }

            std::string GetString(const std::string& fieldName) {
                int32_t index = _fieldMaps[fieldName];

                return GetString(index);
            }

            const base::Values& GetValues() {
                return _values;
            }

            void SetBatchId(int32_t batchId) {
                _batchId = batchId;
            }

            int32_t GetBatchId() const {
                return _batchId;
            }

        private:
            base::Fields _fields;
            std::map<std::string, int32_t> _fieldMaps;
            base::Values _values;
            int32_t _batchId;
        };
    }
}
