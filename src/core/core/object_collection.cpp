#include <uipc/core/object_collection.h>
#include <uipc/common/log.h>
namespace uipc::core
{
template <typename T>
T& remove_const(const T& t)
{
    return const_cast<T&>(t);
}

S<Object> ObjectCollection::emplace(Object&& object)
{
    IndexT id  = m_next_id++;
    auto   ptr = uipc::make_shared<Object>(std::move(object));
    m_objects.emplace(id, ptr);
    return ptr;
}

S<Object> ObjectCollection::find(IndexT id) noexcept
{
    if(auto it = m_objects.find(id); it != m_objects.end())
        return it->second;

    return {};
}

S<const Object> ObjectCollection::find(IndexT id) const noexcept
{
    return remove_const(*this).find(id);
}

void ObjectCollection::destroy(IndexT id) noexcept
{
    auto it = m_objects.find(id);
    if(it != m_objects.end())
        m_objects.erase(it);
    else
        UIPC_WARN_WITH_LOCATION("Try to destroy object({}) that does not exist, ignored.", id);
}

void ObjectCollection::reserve(SizeT size) noexcept
{
    m_objects.reserve(size);
}

SizeT ObjectCollection::size() const noexcept
{
    return m_objects.size();
}
IndexT ObjectCollection::next_id() const noexcept
{
    return m_next_id;
}
}  // namespace uipc::core
