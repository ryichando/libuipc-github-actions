#include <finite_element/finite_element_vertex_reporter.h>
#include <global_geometry/global_vertex_manager.h>
namespace uipc::backend::cuda
{
REGISTER_SIM_SYSTEM(FiniteElementVertexReporter);

void FiniteElementVertexReporter::do_build()
{
    m_impl.finite_element_method = &require<FiniteElementMethod>();
    auto& global_vertex_manager  = require<GlobalVertexManager>();
    global_vertex_manager.add_reporter(this);
}

void FiniteElementVertexReporter::Impl::report_count(GlobalVertexManager::VertexCountInfo& info)
{
    info.count(fem().xs.size());
}

void FiniteElementVertexReporter::Impl::report_attributes(GlobalVertexManager::VertexAttributeInfo& info)
{
    using namespace muda;
    // fill the coindices for later use
    auto N = info.coindices().size();
    ParallelFor()
        .kernel_name(__FUNCTION__)
        .apply(N,
               [coindices = info.coindices().viewer().name("coindices"),
                src_pos   = fem().xs.cviewer().name("src_pos"),
                dst_pos = info.positions().viewer().name("dst_pos")] __device__(int i) mutable
               {
                   coindices(i) = i;
                   dst_pos(i)   = src_pos(i);
               });

    auto async_copy = []<typename T>(span<T> src, muda::BufferView<T> dst)
    { muda::BufferLaunch().copy<T>(dst, src.data()); };

    async_copy(span{fem().h_vertex_contact_element_ids}, info.contact_element_ids());

    // record the global vertex info
    reporter_vertex_offset = info.coindices().offset();
    reporter_vertex_count  = info.coindices().size();
}

void FiniteElementVertexReporter::Impl::report_displacements(GlobalVertexManager::VertexDisplacementInfo& info)
{
    using namespace muda;

    info.displacements().copy_from(fem().dxs);
}

void FiniteElementVertexReporter::do_report_count(GlobalVertexManager::VertexCountInfo& info)
{
    m_impl.report_count(info);
}
void FiniteElementVertexReporter::do_report_attributes(GlobalVertexManager::VertexAttributeInfo& info)
{
    m_impl.report_attributes(info);
}

void FiniteElementVertexReporter::do_report_displacements(GlobalVertexManager::VertexDisplacementInfo& info)
{
    m_impl.report_displacements(info);
}
}  // namespace uipc::backend::cuda
