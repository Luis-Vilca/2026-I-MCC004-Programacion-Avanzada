#ifndef __X_H__
#define __X_H__

#include <iostream>
#include <string>

using namespace std;
using TX = double;

class X {
    public:
        TX m_a = 0, m_b = 0;
    public:
        X() { }
        X(TX a, TX b) : m_a(a), m_b(b) { }

        TX GetA() const { return m_a; }
        void setA(TX a) { m_a = a; }

        TX GetB() const { return m_b; }
        void setB(TX b) { m_b = b; }
        
        TX Suma()     const { return m_a + m_b; }
        TX Producto() const { return m_a * m_b; }
        TX Resta()    const { return m_a - m_b; }
        TX Division() const { return m_b != 0 ? m_a / m_b : 0; }

        string ToString() const {
            return "X(" + to_string(m_a) + ", " + to_string(m_b) + ")";
        }
        ostream &operator<<(ostream &os) const {
            os << ToString();
            return os;
        }
};
#endif // __X_H__