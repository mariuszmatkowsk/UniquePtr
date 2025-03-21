#pragma once

namespace foo {

struct default_delete{};

template <typename T, typename Deleter = default_delete>
class UniquePtr {

public:

};

}  // namespace foo
