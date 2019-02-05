//
// Created by elwingh on 21/01/19.
//

#ifndef FIXED_FIXED_H
#define FIXED_FIXED_H

#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <cmath>

namespace fp {

    /**
     * fixed point type
     */

    template<std::size_t Int, std::size_t Frac>
    class fixed {
    public:
    	
    	struct fixed_type 
    
        using underlying_type = long long;

        underlying_type value;

        static constexpr std::size_t integer_part = Int;
        static constexpr std::size_t fractionnal_part = Frac;

        /**
         * constructors
         */

        fixed() = default;

        constexpr explicit fixed(float x) : value(
                (x / std::pow(2, Int) < 1 ? static_cast<underlying_type>(floor(x * std::pow(2, Frac)))
                                          : throw std::overflow_error("Overflow in the fixed number creation"))) {

        }

        constexpr explicit fixed(double x) : value(
                (x / std::pow(2, Int) < 1 ? static_cast<underlying_type>(floor(x * std::pow(2, Frac)))
                                          : throw std::overflow_error("Overflow in the fixed number creation"))) {

        }

        /**
         * copy constructors
         */

        fixed(const fixed &other) {
            value = other.value;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed(const fixed<OtherInt, OtherFrac> &other) {
            auto tmp = other.value / (std::pow(2, OtherFrac));
            if (tmp / std::pow(2, integer_part) < 1) {
                value = static_cast<underlying_type>(floor(tmp * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while copy of a fixed number into a smaller one");
            }
        };

        /**
         * copy assigment
         */

        fixed &operator=(const fixed &other) {
            this->value = other.value;
            return *this;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator=(const fixed<OtherInt, OtherFrac> &other) {
            auto tmp = other.value / (std::pow(2, OtherFrac));
            if (tmp / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor(tmp * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while copy assigment of a fixed number into a smaller one");
            }

            return *this;
        }

        /**
         * conversions
         */

        explicit operator float() const {
            return static_cast<float>(value / (std::pow(2, fractionnal_part)));
        }

        explicit operator double() const {
            return (value / (std::pow(2, fractionnal_part)));
        }

        /**
         * compound assigment operators
         */

        fixed &operator+=(const fixed &other) {
            auto tmpOther = other.value / (std::pow(2, other.fractionnal_part));
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpOther + tmpThis) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpOther + tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while incrementing");
            }

            return *this;
        }

        fixed &operator+=(float other) {
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((other + tmpThis) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((other + tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while incrementing");
            }

            return *this;
        }

        fixed &operator+=(double other) {
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((other + tmpThis) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((other + tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while incrementing");
            }

            return *this;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator+=(const fixed<OtherInt, OtherFrac> &other) {
            auto tmpOther = other.value / (std::pow(2, OtherFrac));
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpOther + tmpThis) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpOther + tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while incrementing");
            }

            return *this;
        }

        fixed &operator-=(const fixed &other) {
            auto tmpOther = other.value / (std::pow(2, other.fractionnal_part));
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpThis - tmpOther) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor(
                        -(tmpOther - tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while decrementing");
            }

            return *this;
        }

        fixed &operator-=(float other) {
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpThis - other) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor(-(other - tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while decrementing");
            }

            return *this;
        }

        fixed &operator-=(double other) {
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpThis - other) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor(-(other - tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while decrementing");
            }

            return *this;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator-=(const fixed<OtherInt, OtherFrac> &other) {
            auto tmpOther = other.value / (std::pow(2, OtherFrac));
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpThis - tmpOther) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor(
                        -(tmpOther - tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while decrementing");
            }

            return *this;
        }

        fixed &operator*=(const fixed &other) {
            auto tmpOther = other.value / (std::pow(2, other.fractionnal_part));
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpOther * tmpThis) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpOther * tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while multiplying");
            }

            return *this;
        }

        fixed &operator*=(float other) {
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((other * tmpThis) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((other * tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while multiplying");
            }

            return *this;
        }

        fixed &operator*=(double other) {
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((other * tmpThis) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((other * tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while multiplying");
            }

            return *this;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator*=(const fixed<OtherInt, OtherFrac> &other) {
            auto tmpOther = other.value / (std::pow(2, OtherFrac));
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpOther * tmpThis) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpOther * tmpThis) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while multiplying");
            }

            return *this;
        }

        fixed &operator/=(const fixed &other) {
            auto tmpOther = other.value / (std::pow(2, other.fractionnal_part));
            if (tmpOther == 0) {
                throw std::overflow_error("Division by 0");
            }
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpThis / tmpOther) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpThis / tmpOther) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while dividing");
            }

            return *this;
        }

        fixed &operator/=(float other) {
            if (other == 0) {
                throw std::overflow_error("Division by 0");
            }
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpThis / other) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpThis / other) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while dividing");
            }

            return *this;
        }

        fixed &operator/=(double other) {
            if (other == 0) {
                throw std::overflow_error("Division by 0");
            }
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpThis / other) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpThis / other) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while dividing");
            }

            return *this;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator/=(const fixed<OtherInt, OtherFrac> &other) {
            auto tmpOther = other.value / (std::pow(2, OtherFrac));
            if (tmpOther == 0) {
                throw std::overflow_error("Division by 0");
            }
            auto tmpThis = value / (std::pow(2, fractionnal_part));

            if ((tmpThis / tmpOther) / std::pow(2, integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpThis / tmpOther) * std::pow(2, fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while dividing");
            }

            return *this;
        }

    };



    /**
     * arithmetic operators
     */
/*

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    implementationDefined operator+(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
    
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    implementationDefined operator-(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    implementationDefined operator*(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    implementationDefined operator/(fixed<I1, F1> lhs, fixed<I2, F2> rhs);
*/

    /**
     * comparison operators
     */

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator==(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        auto tmpLhs = lhs.value / (std::pow(2, F1));
        auto tmpRhs = rhs.value / (std::pow(2, F2));

        return tmpLhs == tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator!=(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        auto tmpLhs = lhs.value / (std::pow(2, F1));
        auto tmpRhs = rhs.value / (std::pow(2, F2));

        return tmpLhs != tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        auto tmpLhs = lhs.value / (std::pow(2, F1));
        auto tmpRhs = rhs.value / (std::pow(2, F2));

        return tmpLhs < tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        auto tmpLhs = lhs.value / (std::pow(2, F1));
        auto tmpRhs = rhs.value / (std::pow(2, F2));

        return tmpLhs > tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<=(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        auto tmpLhs = lhs.value / (std::pow(2, F1));
        auto tmpRhs = rhs.value / (std::pow(2, F2));

        return tmpLhs <= tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>=(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        auto tmpLhs = lhs.value / (std::pow(2, F1));
        auto tmpRhs = rhs.value / (std::pow(2, F2));

        return tmpLhs >= tmpRhs;
    }

    /**
     * types
     */

    using Q_8_8     = fixed<8, 8>;
    using Q_16_16   = fixed<16, 16>;
    using Q_0_32    = fixed<0, 32>;

    /**
     * traits
     */

    template<typename Fixed>
    struct fixed_traits {
        static constexpr Fixed lowest();

        static constexpr Fixed min();

        static constexpr Fixed max();

        static constexpr Fixed zero();

        static constexpr Fixed one();

        static constexpr Fixed pi();

    };

    /**
     * functions
     */

    template<typename Fixed>
    Fixed sqrt(Fixed f) {
        if (f.value < 0) {
            throw std::overflow_error("Negative numbers can't be sqrted");
        }
        auto tmp = f.value / (std::pow(2, f.fractionnal_part));
        fp::fixed<Fixed::integer_part, Fixed::fractionnal_part> ret(std::pow(tmp, 0.5));
        return ret;
    }


    template<typename Fixed>
    std::string to_string(Fixed f) {
        std::string ret;
        ret += "Fixed<" + std::to_string(f.integer_part) + "," + std::to_string(f.fractionnal_part) + "> Value = " +
               std::to_string(f.value);
        return ret;
    }

    template<typename Fixed>
    std::ostream &operator<<(std::ostream &o, Fixed f) {
        o << fp::to_string(f);

        return o;
    }

}


#endif //FIXED_FIXED_H
