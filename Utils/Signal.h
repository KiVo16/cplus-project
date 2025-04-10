#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <vector>

// Generic Signal class template that supports any argument signature.
template <typename... Args>
class Signal {
public:
    // A slot is any callable that takes arguments of types Args...
    using SlotType = std::function<void(Args...)>;

    // Connect a new slot (callback) to this signal.
    void connect(const SlotType &slot) {
        m_slots.push_back(slot);
    }

    // Disconnect all connected slots.
    void disconnectAll() {
        m_slots.clear();
    }

    // Emit the signal by calling all connected slots with the given arguments.
    void emitSignal(Args... args) const {
        for (const auto &slot : m_slots) {
            if (slot)
                slot(args...);
        }
    }

    // Overload the function call operator for natural syntax.
    void operator()(Args... args) const {
        emitSignal(args...);
    }

private:
    std::vector<SlotType> m_slots;  // Renamed from 'slots' to 'm_slots'
};

#endif // SIGNAL_H
