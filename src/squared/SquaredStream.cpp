

#include "SquaredStream.h"
#include "EachBolt.h"
#include "GroupByBolt.h"
#include "AggregatorBolt.h"
#include "PersistentAggregatorBolt.h"
#include "SquaredTopology.h"
#include "String.h"

namespace ideoengine {
    namespace squared {
        SquaredStream::SquaredStream()
        {
        }

        SquaredStream::SquaredStream(const std::string & spoutName, SquaredSpout * spout)
            :_spoutName(spoutName), _spout(spout)
        {
        }

        SquaredStream * SquaredStream::Each(const base::Fields & inputFields, Operation * operation, const base::Fields & outputFields)
        {
            std::shared_ptr<bolt::IBolt> bolt =
                std::make_shared<EachBolt>(inputFields, operation, outputFields);
            _boltNames.push_back(RandomString("abcdedfgihjklmnopqrstuvwxyz"));
            _bolts.push_back(bolt);
        }

        SquaredStream * SquaredStream::GroupBy(const base::Fields & fields)
        {
            std::shared_ptr<bolt::IBolt> bolt =
                std::make_shared<GroupByBolt>(fields);
            _boltNames.push_back(RandomString("abcdedfgihjklmnopqrstuvwxyz"));
            _bolts.push_back(bolt);

            return nullptr;
        }

        SquaredState * SquaredStream::PersistentAggregate(const SquaredStateFactory * factory, BaseAggregator * operation, const base::Fields & fields)
        {
            std::shared_ptr<PersistentAggregateBolt> bolt =
                std::make_shared<PersistentAggregateBolt>(factory, operation, fields);
            _boltNames.push_back(RandomString("abcdedfgihjklmnopqrstuvwxyz"));
            _bolts.push_back(bolt);

            return bolt->GetState();
        }

        void SquaredStream::Deploy(SquaredToplogy * topology)
        {
            topology->GetSpouts()[_spoutName] = spout;

            int32_t boltIndex - 0;
            for ( auto bolt : _bolts ) {
                topology->GetBolts()[_boltNames[boltIndex]] = bolt;
                boltIndex ++;
            }
        }
    }
}
