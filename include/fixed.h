//
// Created by elwingh on 21/01/19.
//

#ifndef FIXED_FIXED_H
#define FIXED_FIXED_H

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#define M_PI           3.14159265358979323846

namespace fp {
	/**
	 * usual for fixed point constructor
	 */
	 template<int>
	 struct underlying_type_def {
	 };
	 
	 template<>
	 struct underlying_type_def<8> {
	 	typedef int8_t type;
	 };
	 
	 template<>
	 struct underlying_type_def<16> {
	 	typedef int16_t type;
	 };
	 
	 template<>
	 struct underlying_type_def<32> {
	 	typedef int32_t type;
	 };
	 
	 template<>
	 struct underlying_type_def<64> {
	 	typedef int64_t type;
	 };
	 
	 constexpr int define_type(int nb_bits) {
	 	int val = nb_bits;
	 	if (val <= 8) {
	 		val = 8;
	 	} else if (val > 8 && val <= 16) {
	 		val = 16;
	 	} else if (val > 16 && val <= 32) {
	 		val = 32;
	 	} else {
	 		val = 64;
	 	}
	 	
	 	return val;
	 } 
    /**
     * fixed point type
     */

    template<std::size_t Int, std::size_t Frac>
    class fixed {
    
    
    public:
    	
    	struct fixed_type;
    
        using underlying_type = typename underlying_type_def<define_type(static_cast<int>(Int + Frac))>::type;

        underlying_type value;

        static constexpr std::size_t integer_part = Int;
        static constexpr std::size_t fractionnal_part = Frac;

        /**
         * constructors
         */

        fixed() = default;

        constexpr explicit fixed(float x) : value(
                (x / std::exp2(Int) < 1 ? static_cast<underlying_type>(floor(x * std::exp2(Frac)))
                                          : throw std::overflow_error("Overflow in the fixed number creation"))) {

        }

        constexpr explicit fixed(double x) : value(
                (x / std::exp2(Int) < 1 ? static_cast<underlying_type>(floor(x * std::exp2(Frac)))
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
            auto tmp = other.value / (std::exp2(OtherFrac));
            if (tmp / std::exp2(integer_part) < 1) {
                value = static_cast<underlying_type>(floor(tmp * std::exp2(fractionnal_part)));
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
            auto tmp = other.value / (std::exp2(OtherFrac));
            if (tmp / std::exp2(integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor(tmp * std::exp2(fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while copy assigment of a fixed number into a smaller one");
            }

            return *this;
        }

        /**
         * conversions
         */

        explicit operator float() const {
            return static_cast<float>(value / (std::exp2(fractionnal_part)));
        }

        explicit operator double() const {
            return (value / (std::exp2(fractionnal_part)));
        }

        /**
         * compound assigment operators
         */

        fixed &operator+=(const fixed &other) {
            auto tmp = (this->value + other.value)/std::exp2(this->fractionnal_part);
            if ((tmp/std::exp2(this->integer_part))<1) {
                this->value += other.value;
            } else {
                throw std::overflow_error("Overflow while incrementing");
            }

            return *this;
        }

        fixed &operator+=(float other) {
            auto tmp = (this->value + other*std::exp2(this->fractionnal_part))/std::exp2(this->fractionnal_part);
            if ((tmp/std::exp2(this->integer_part))<1) {
                this->value += other*std::exp2(this->fractionnal_part);
            } else {
                throw std::overflow_error("Overflow while incrementing");
            }

            return *this;
        }

        fixed &operator+=(double other) {
            auto tmp = (this->value + other*std::exp2(this->fractionnal_part))/std::exp2(this->fractionnal_part);
            if ((tmp/std::exp2(this->integer_part))<1) {
                this->value += other*std::exp2(this->fractionnal_part);
            } else {
                throw std::overflow_error("Overflow while incrementing");
            }

            return *this;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator+=(const fixed<OtherInt, OtherFrac> &other) {
            auto tmp = (this->value + other.value*std::exp2(this->fractionnal_part-OtherFrac))/std::exp2(this->fractionnal_part);
            if ((tmp/std::exp2(this->integer_part))<1) {
                this->value += other.value*std::exp2(this->fractionnal_part-OtherFrac);
            } else {
                throw std::overflow_error("Overflow while incrementing");
            }

            return *this;
        }

        fixed &operator-=(const fixed &other) {
            auto tmp = (this->value - other.value)/std::exp2(this->fractionnal_part);
            if ((std::abs(tmp)/std::exp2(this->integer_part))<1) {
                this->value -= other.value;
            } else {
                throw std::overflow_error("Overflow while decrementing");
            }

            return *this;
        }

        fixed &operator-=(float other) {
            auto tmp = (this->value - other*exp2(this->fractionnal_part))/std::exp2(this->fractionnal_part);
            if ((std::abs(tmp)/std::exp2(this->integer_part))<1) {
                this->value -= other*exp2(this->fractionnal_part);
            } else {
                throw std::overflow_error("Overflow while decrementing");
            }

            return *this;
        }

        fixed &operator-=(double other) {
            auto tmp = (this->value - other*exp2(this->fractionnal_part))/std::exp2(this->fractionnal_part);
            if ((std::abs(tmp)/std::exp2(this->integer_part))<1) {
                this->value -= other*exp2(this->fractionnal_part);
            } else {
                throw std::overflow_error("Overflow while decrementing");
            }

            return *this;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator-=(const fixed<OtherInt, OtherFrac> &other) {
            auto tmp = (this->value - other.value*std::exp2(this->fractionnal_part-OtherFrac))/std::exp2(this->fractionnal_part);
            if ((std::abs(tmp)/std::exp2(this->integer_part))<1) {
                this->value -= other.value*std::exp2(this->fractionnal_part-OtherFrac);
            } else {
                throw std::overflow_error("Overflow while decrementing");
            }

            return *this;
        }

        fixed &operator*=(const fixed &other) {
            auto tmpOther = other.value / (std::exp2(other.fractionnal_part));
            auto tmpThis = value / (std::exp2(fractionnal_part));

            if ((tmpOther * tmpThis) / std::exp2(integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpOther * tmpThis) * std::exp2(fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while multiplying");
            }

            return *this;
        }

        fixed &operator*=(float other) {
            auto tmpThis = value / (std::exp2(fractionnal_part));

            if ((other * tmpThis) / std::exp2(integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((other * tmpThis) * std::exp2(fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while multiplying");
            }

            return *this;
        }

        fixed &operator*=(double other) {
            auto tmpThis = value / (std::exp2(fractionnal_part));

            if ((other * tmpThis) / std::exp2(integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((other * tmpThis) * std::exp2(fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while multiplying");
            }

            return *this;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator*=(const fixed<OtherInt, OtherFrac> &other) {
            auto tmpOther = other.value / (std::exp2(OtherFrac));
            auto tmpThis = value / (std::exp2(fractionnal_part));

            if ((tmpOther * tmpThis) / std::exp2(integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpOther * tmpThis) * std::exp2(fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while multiplying");
            }

            return *this;
        }

        fixed &operator/=(const fixed &other) {
            auto tmpOther = other.value / (std::exp2(other.fractionnal_part));
            if (tmpOther == 0) {
                throw std::overflow_error("Division by 0");
            }
            auto tmpThis = value / (std::exp2(fractionnal_part));

            if ((tmpThis / tmpOther) / std::exp2(integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpThis / tmpOther) * std::exp2(fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while dividing");
            }

            return *this;
        }

        fixed &operator/=(float other) {
            if (other == 0) {
                throw std::overflow_error("Division by 0");
            }
            auto tmpThis = value / (std::exp2(fractionnal_part));

            if ((tmpThis / other) / std::exp2(integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpThis / other) * std::exp2(fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while dividing");
            }

            return *this;
        }

        fixed &operator/=(double other) {
            if (other == 0) {
                throw std::overflow_error("Division by 0");
            }
            auto tmpThis = value / (std::exp2(fractionnal_part));

            if ((tmpThis / other) / std::exp2(integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpThis / other) * std::exp2(fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while dividing");
            }

            return *this;
        }

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator/=(const fixed<OtherInt, OtherFrac> &other) {
            auto tmpOther = other.value / (std::exp2(OtherFrac));
            if (tmpOther == 0) {
                throw std::overflow_error("Division by 0");
            }
            auto tmpThis = value / (std::exp2(fractionnal_part));

            if ((tmpThis / tmpOther) / std::exp2(integer_part) < 1) {
                this->value = static_cast<underlying_type>(floor((tmpThis / tmpOther) * std::exp2(fractionnal_part)));
            } else {
                throw std::overflow_error("Overflow while dividing");
            }

            return *this;
        }

    };



    /**
     * arithmetic operators
     */


    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<std::max(I1,I2)+1,std::max(F1,F2)> operator+(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        fixed<std::max(I1,I2)+1,std::max(F1,F2)> ret;
        ret.value = lhs.value*std::exp2(ret.fractionnal_part - F1) + rhs.value*std::exp2(ret.fractionnal_part - F2);

        return ret;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<std::max(I1,I2)+1,std::max(F1,F2)> operator-(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        fixed<std::max(I1,I2)+1,std::max(F1,F2)> ret;
        ret.value = lhs.value*std::exp2(ret.fractionnal_part - F1) - rhs.value*std::exp2(ret.fractionnal_part - F2);

        return ret;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<I1+I2+1,F1+F2+1> operator*(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {

    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<I1+I2+1,F1+F2+1> operator/(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    /**
     * comparison operators
     */

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator==(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
    	auto tmpRhs = (F1 < F2) ? rhs.value >> (F2 - F1) : rhs.value << (F1 - F2);
        return lhs.value == tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator!=(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        auto tmpRhs = (F1 < F2) ? rhs.value >> (F2 - F1) : rhs.value << (F1 - F2);
        
        return lhs.value != tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
		auto tmpRhs = (F1 < F2) ? rhs.value >> (F2 - F1) : rhs.value << (F1 - F2);
        
        return lhs.value < tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
		auto tmpRhs = (F1 < F2) ? rhs.value >> (F2 - F1) : rhs.value << (F1 - F2);
        
        return lhs.value > tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<=(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        auto tmpRhs = (F1 < F2) ? rhs.value >> (F2 - F1) : rhs.value << (F1 - F2);
        
        return lhs.value <= tmpRhs;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>=(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        auto tmpRhs = (F1 < F2) ? rhs.value >> (F2 - F1) : rhs.value << (F1 - F2);
        
        return lhs.value >= tmpRhs;
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
        static constexpr Fixed lowest() {
            return Fixed{-exp2(Fixed::integer_part - 1)};
        }

        static constexpr Fixed min() {
            return Fixed{1/exp2(Fixed::fractionnal_part)};
        }

        static constexpr Fixed max() {
            return Fixed{exp2(Fixed::integer_part - 1) - 1/exp2(Fixed::fractionnal_part) - 1};
        }

        static constexpr Fixed zero() {
            return Fixed{double(0)};
        }

        static constexpr Fixed one() {
            return Fixed{double(1)};
        }

        static constexpr Fixed pi() {
            return Fixed{M_PI};
        }

    };

    /**
     * functions
     */

    template<typename Fixed>
    Fixed sqrt(Fixed f) {
        if (f.value < 0) {
            throw std::overflow_error("Negative numbers can't be sqrted");
        }
        auto tmp = f.value / (std::exp2(f.fractionnal_part));
        fp::fixed<Fixed::integer_part, Fixed::fractionnal_part> ret(std::pow(tmp, 0.5));
        return ret;
    }


    template<size_t Int, size_t Frac>
    std::string to_string(fixed<Int, Frac> f) {
        std::string ret;
        ret += "Fixed<" + std::to_string(f.integer_part) + "," + std::to_string(f.fractionnal_part) + "> Value = " +
               std::to_string(f.value);
        return ret;
    }

    template<size_t Int, size_t Frac>
    std::ostream &operator<<(std::ostream &o, fixed<Int, Frac> f) {
        o << fp::to_string(f);

        return o;
    }

}


#endif //FIXED_FIXED_H
