#pragma once

// Project includes
#include "../../ILogger.h"
#include "../../VM/OpcodeHandler.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode801C final : public OpcodeHandler
            {
                public:
                    Opcode801C(std::shared_ptr<ILogger> logger);

                private:
                    std::shared_ptr<ILogger> _logger;
                    void _run(VM::Script& script) override;
            };
        }
    }
}
