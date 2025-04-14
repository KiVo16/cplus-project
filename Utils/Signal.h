#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <vector>

/// class for signals supporting any number of arguments
template <typename... Args>
class Signal {
public:
    /// callable that takes parameters of types Args
    using SlotType = std::function<void(Args...)>;

    /// adds consumer callback function
    void connect(const SlotType &slot) {
        m_slots.push_back(slot);
    }

    /// clears all consumers
    void disconnectAll() {
        m_slots.clear();
    }

    /// sends signal to all consumers with provided arguments
    void emitSignal(Args... args) const {
        for (const auto &slot : m_slots) {
            if (slot)
                slot(args...);
        }
    }

    /// () operator overload
    void operator()(Args... args) const {
        emitSignal(args...);
    }

private:
    /// vector storing all consumers
    std::vector<SlotType> m_slots;
};

#endif // SIGNAL_H
