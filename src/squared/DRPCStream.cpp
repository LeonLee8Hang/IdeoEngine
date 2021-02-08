

#include "DRPCStream.h"
#include "EachBolt.h"
#include "GroupByBolt.h"
#include "AggregatorBolt.h"
#include "PersistentAggregatorBolt.h"
#include "SquaredTopology.h"
#include "String.h"
#include "MapGet.h"

namespace ideoengine {
    namespace squared {
        DRPCStream::DRPCStream()
        {
        }

        DRPCStream * DRPCStream::Each(const base::Fields & inputFields, Operation * operation, const base::Fields & outputFields)
        {
            std::shared_ptr<bolt::IBolt> bolt =
                std::make_shared<EachBolt>(inputFields, operation, outputFields);
            _boltNames.push_back(RandomString("abcdedfgihjklmnopqrstuvwxyz"));
            _bolts.push_back(bolt);

            return this;
        }

        DRPCStream * DRPCStream::GroupBy(const base::Fields & fields)
        {
            std::shared_ptr<bolt::IBolt> bolt =
                std::make_shared<GroupByBolt>(fields);
            _boltNames.push_back(RandomString("abcdedfgihjklmnopqrstuvwxyz"));
            _bolts.push_back(bolt);

            return this;
        }

        DRPCStream* DRPCStream::StateQuery(SquaredState* state, base::Fields& inputFields,
            MapGet* mapGetter, base::Fields& outputFields) {
            mapGetter->SetState(state);
            std::shared_ptr<bolt::IBolt> bolt =
                std::shared_ptr<MapGet>();

            _boltNames.push_back(RandomString("abcdedfgihjklmnopqrstuvwxyz"));
            _bolts.push_back(bolt);

            return this;
        }

        DRPCStream* DRPCStream::Aggregate(base::Fields& inputFields, BaseAggregator* aggregator,
            base::Fields* outputFields) {
            std::shared_ptr<AggregatorBolt> bolt =
                std::make_shared<AggregatorBolt>(aggregator, fields);
            _boltNames.push_back(RandomString("abcdedfgihjklmnopqrstuvwxyz"));
            _bolts.push_back(bolt);

            return this;
        }

        std::string DRPCStream::WaitFormResult(const std::string & args)
        {
            return std::string();
        }

        std::string DRPCStream::WaitFormResult()
        {
            return std::string();
        }

        SquaredState * SquaredStream::PersistentAggregate(const SquaredStateFactory * factory, BaseAggregator * operation, const base::Fields & fields)
        {
            std::shared_ptr<PersistentAggregateBolt> bolt =
                std::make_shared<PersistentAggregateBolt>(factory, operation, fields);
            _boltNames.push_back(RandomString("abcdedfgihjklmnopqrstuvwxyz"));
            _bolts.push_back(bolt);

            return bolt->GetState();
        }

        void DRPCStream::Deploy(SquaredToplogy * topology)
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
