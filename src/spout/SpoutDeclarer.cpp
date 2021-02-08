

#include "ideoengine/spout/SpoutDeclarer.h"
#include "ideoengine/spout/ISpout.h"

namespace ideoengine {
    namespace spout {
        SpoutDeclarer::SpoutDeclarer(const std::string& spoutName, ISpout* spout) :
            _spout(spout){
            SetType(ideoengine::task::TaskDeclarer::Type::Spout);
            SetTaskName(spoutName);

            _fields = _spout->DeclareFields();
            int32_t fieldIndex = 0;
            for ( const std::string& field : _fields ) {
                _fieldsMap.insert({field, fieldIndex});
            }
        }
    }
}
