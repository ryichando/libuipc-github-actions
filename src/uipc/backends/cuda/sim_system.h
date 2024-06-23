#pragma once
#include <type_define.h>

#include <i_sim_system.h>
#include <sim_action.h>
#include <string_view>
#include <sim_engine_state.h>
#include <sim_system_auto_register.h>
#include <uipc/backend/visitors/world_visitor.h>

namespace uipc::backend::cuda
{
class SimEngine;
class SimSystemCollection;

class SimSystem : public ISimSystem
{
    friend class SimEngine;

  public:
    SimSystem(SimEngine& sim_engine) noexcept;

  protected:
    template <std::derived_from<SimSystem> T>
    T* find();

    virtual void do_build() override{};

    /**
     * @brief register an action to be executed when the scene is initialized
     * 
     * This function can only be called in do_build() function
     */
    void on_init_scene(std::function<void()>&& action) noexcept;

    /**
     * @brief register an action to be executed when the scene is rebuilt
     * 
     * This function can only be called in do_build() function
     */
    void on_rebuild_scene(std::function<void()>&& action) noexcept;

    /**
     * @brief register an action to be executed when the scene is written
     * 
     * This function can only be called in do_build() function
     */
    void on_write_scene(std::function<void()>&& action) noexcept;

    WorldVisitor& world() noexcept;

    void check_state(SimEngineState state, std::string_view function_name) noexcept;

  private:
    SimEngine&           m_sim_engine;
    SimSystemCollection& collection() noexcept;
};
}  // namespace uipc::backend::cuda

#include "details/sim_system.inl"