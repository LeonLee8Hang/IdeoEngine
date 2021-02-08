#pragma once

#include "ideoengine/message/Message.h"
#include "ideoengine/base/Values.h"

namespace ideoengine {

    namespace bolt {

        class BoltMessage : public message::Message{
        public:
            struct MessageType {
                enum {
                    Data = 0x1000
                };
            };

            BoltMessage(const base::Values& values) : 
                message::Message(MessageType::Data), _values(values) {
            }

            const base::Values& GetValues() const {
                return _values;
            }

            void SetValues(const base::Values& values) {
                _values = values;
            }

        private:
            base::Values _values;
        };
    }

}