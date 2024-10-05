#pragma once
#include <uipc/core/scene.h>

namespace uipc::backend
{
class WorldVisitor;
}

namespace uipc::core
{
class Engine;
}

namespace uipc::core
{
class UIPC_CORE_API World final
{
    friend class backend::WorldVisitor;

  public:
    World(Engine& e) noexcept;
    void init(Scene& s);

    void advance();
    void sync();
    void retrieve();
    bool dump();
    bool recover();

    SizeT frame() const;

  private:
    Scene*        m_scene  = nullptr;
    core::Engine* m_engine = nullptr;
    bool          m_valid  = true;
    void          sanity_check(Scene& s);
};
}  // namespace uipc::core
