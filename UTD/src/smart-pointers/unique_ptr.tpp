template <typename _Data>
constexpr utd::unique_ptr<_Data>::unique_ptr(_Data* ptr) noexcept {
    raw = ptr;
}

template <typename _Data>
utd::unique_ptr<_Data>::unique_ptr(_Data&& rhs) noexcept {
    this->raw = rhs.raw;
    rhs.raw = nullptr;
}

template <typename _Data>
_Data& utd::unique_ptr<_Data>::operator=(_Data&& rhs) noexcept {
    this->safeDelete();
    this->raw = rhs.raw;
    rhs.raw = nullptr;
}

template <typename _Data>
utd::unique_ptr<_Data>::~unique_ptr() {
    safeDelete();
}

template <typename _Data>
_Data& utd::unique_ptr<_Data>::operator*() const {
    return *raw;
}

template <typename _Data>
_Data* utd::unique_ptr<_Data>::operator->() const {
    return raw;
}

template <typename _Data>
_Data* utd::unique_ptr<_Data>::get() const noexcept {
    return raw;
}

template <typename _Data>
void utd::unique_ptr<_Data>::safeDelete() noexcept {
    if (raw) delete raw;
}

template <typename _Data, typename ...Args>
utd::unique_ptr<_Data> utd::make_unique(Args&&... args) {
    return unique_ptr(new _Data(std::forward<Args>(args)...));
}