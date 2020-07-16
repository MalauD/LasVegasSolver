#pragma once
enum class TicketValues{
    t90k = 90,
    t80k = 80,
    t70k = 70,
    t60k = 60,
    t50k = 50,
    t30k = 30,
    t20k = 20,
    t10k = 10,
};

class Ticket {
    private:
        TicketValues m_Value;
    public:
        Ticket(TicketValues Value) noexcept;
        TicketValues GetValue() const noexcept;
        int GetValueInt() const noexcept;
};

inline bool operator==(const Ticket& a, const Ticket& b) noexcept {
    return a.GetValue() == b.GetValue();
};

inline bool operator>(const Ticket& a, const Ticket& b) noexcept {
    return a.GetValue() > b.GetValue();
};

inline bool operator>=(const Ticket& a, const Ticket& b) noexcept {
    return a.GetValue() >= b.GetValue();
};

inline bool operator<(const Ticket& a, const Ticket& b) noexcept {
    return a.GetValue() < b.GetValue();
};

inline bool operator<=(const Ticket& a, const Ticket& b) noexcept {
    return a.GetValue() <= b.GetValue();
};

inline bool operator!=(const Ticket& a, const Ticket& b) noexcept {
    return a.GetValue() != b.GetValue();
};