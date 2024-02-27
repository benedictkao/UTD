#include <utility>

namespace utd {
    template <typename _Data>
    class unique_ptr {

    public:
        // Ctor
        explicit constexpr unique_ptr(_Data*) noexcept;
        constexpr unique_ptr() noexcept = default;

        // Copy
        unique_ptr(const _Data&) = delete;
        _Data& operator=(const _Data&) = delete;

        // Move
        unique_ptr(_Data&&) noexcept;
        _Data& operator=(_Data&&) noexcept;

        // Dtor
        ~unique_ptr();

        // Pointer operations
        _Data& operator*() const;
        _Data* operator->() const;

        // Get raw ptr
        _Data* get() const noexcept;

    private:
        void safeDelete() noexcept;

    private:
        _Data* raw{nullptr};
    };

    template<typename _Data, typename... Args>
    unique_ptr<_Data> make_unique(Args&&... args);
}

#include "unique_ptr.tpp"