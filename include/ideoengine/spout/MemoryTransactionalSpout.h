

#pragma once

#include "TransactionalSpout.h"

namespace ideoengine {
    namespace spout {
        class MemoryCoordinator : public Coordinator {
        public:
            MemoryCoordinator() {}

            virtual void Open(base::OutputCollector& outputCollector) {
                Coordinator::Open(outputCollector);
            }

            virtual void Close() {

            }

            virtual void Execute() {

            }

            virtual ISpout* Clone() const override {
                return new MemoryCoordinator(*this);
            }

            virtual base::Fields DeclareFields() const override {
                return {};
            }
        };

        class MemoryEmitter : public bolt::Emitter {
        public:
            MemoryEmitter() {}

            virtual void Prepare(base::OutputCollector& outputCollector) {
                bolt::Emitter::Prepare(outputCollector);

            }

            virtual void Cleanup() {

            }

            virtual void Execute(const base::Values& values) {

            }

            virtual IBolt* Clone() const {
                return new MemoryEmitter(*this);
            }

            virtual base::Fields DeclareFields() const {
                return {};
            }
        };

        class MemoryTransactionalSpout : public TransactionalSpout {
        public:
            MemoryTransactionalSpout() :
                _coordinator(new MemoryCoordinator), _emitter(new MemoryEmitter) {

            }

            virtual ideoengine::spout::Coordinator* GetCoordinator() {
                return _coordinator;
            }

            virtual ideoengine::bolt::Emitter* GetEmitter() {
                return _emitter;
            }

        private:
            MemoryCoordinator* _coordinator;
            MemoryEmitter* _emitter;
        };
    }
}