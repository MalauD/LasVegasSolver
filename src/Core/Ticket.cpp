#include "Ticket.hpp"

Ticket::Ticket(TicketValues Value) noexcept : m_Value{Value}
{
}

TicketValues Ticket::GetValue() const noexcept
{
    return m_Value;
}

int Ticket::GetValueInt() const noexcept
{
    return static_cast<int>(m_Value);
}