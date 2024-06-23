#pragma once
#include <sim_system.h>
#include <affine_body/affine_body_dynamics.h>

namespace uipc::backend::cuda
{
class ABDOrthoPotential : public SimSystem
{
  public:
    static constexpr U64 ConstitutionUID = 1ull;

    using SimSystem::SimSystem;

    virtual void do_build() override;

  public:
    class Impl
    {
      public:
        void on_filter(const AffineBodyDynamics::FilteredInfo& info, WorldVisitor& world);
        void on_compute_energy(const AffineBodyDynamics::ComputeEnergyInfo& info);
        void on_compute_gradient_hessian(const AffineBodyDynamics::ComputeGradientHessianInfo& info);

        void _build_on_device();

        AffineBodyDynamics* affine_body_geometry;

        vector<AffineBodyDynamics::BodyInfo> h_body_infos;
        vector<Float>                        h_kappas;

        muda::DeviceBuffer<Float> kappas;
        muda::DeviceBuffer<Float> body_energies;
    };

  private:
    Impl m_impl;
};
}  // namespace uipc::backend::cuda