#include <none_sim_engine.h>
#include <backends/common/module.h>
#include <uipc/common/log.h>
#include <none_sim_system.h>

namespace uipc::backend::none
{
NoneSimEngine::NoneSimEngine(EngineCreateInfo* info)
    : SimEngine(info)
{
    spdlog::info("[NoneEngine] Constructor called.");
    spdlog::info(R"(Hello, this is the NoneEngine from libuipc backends.
This engine does nothing, but helps to do the checking of the engine interface.
And it is a good place to print out some debug information during the life cycle of the engine.
)");
}

void NoneSimEngine::do_init(backend::WorldVisitor v)
{
    spdlog::info("[NoneEngine] do_init() called.");

    build_systems();

    m_system = &require<NoneSimSystem>();

    dump_system_info();
}

void NoneSimEngine::do_advance()
{
    frame++;
    spdlog::info("[NoneEngine] do_advance() called.");
}

void NoneSimEngine::do_sync()
{
    spdlog::info("[NoneEngine] do_sync() called.");
}

void NoneSimEngine::do_retrieve()
{
    spdlog::info("[NoneEngine] do_receive() called.");
}

NoneSimEngine::~NoneSimEngine()
{
    spdlog::info("[NoneEngine] Destructor called.");
}


SizeT NoneSimEngine::get_frame() const
{
    return frame;
}
}  // namespace uipc::backend::none


UIPC_BACKEND_API EngineInterface* uipc_create_engine(EngineCreateInfo* info)
{
    return new uipc::backend::none::NoneSimEngine(info);
}

UIPC_BACKEND_API void uipc_destroy_engine(EngineInterface* engine)
{
    delete engine;
}