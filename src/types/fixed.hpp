#ifndef FIXED_TYPES_HPP
#define FIXED_TYPES_HPP

#include <math.h>
#include <iostream>

struct fixed{
    int8_t val;
    fixed(int x=0) 
            : val(x) { }
    fixed& operator=(const fixed& a){
        val = a.val;
        return *this;
    }
    fixed operator+(const fixed& a) const{
        return fixed(val+a.val);
    }
    fixed operator-(const fixed& a) const{
        return fixed(val-a.val);
    }
    fixed operator*(const fixed& a) const{
        return fixed(val*a.val);
    }
    fixed operator/(const fixed& a) const{
        return fixed(val/a.val);
    }
    bool operator==(const fixed& a) const {
        return (val == a.val);
    }
};

struct fixed6{
    int8_t val;
    fixed6(int x=0) 
            : val(x) { }
    fixed6& operator=(const fixed6& a){
        val = a.val;
        return *this;
    }
    fixed6 operator+(const fixed6& a) const{
        return fixed6(val+a.val);
    }
    fixed6 operator-(const fixed6& a) const{
        return fixed6(val-a.val);
    }
    fixed6 operator*(const fixed6& a) const{
        return fixed6(val*a.val);
    }
    fixed6 operator/(const fixed6& a) const{
        return fixed6(val/a.val);
    }
    bool operator<(const fixed6& a) const {
        return (val < a.val);
    }
    bool operator>(const fixed6& a) const {
        return (val > a.val);
    }
    bool operator<=(const fixed6& a) const {
        return (val <= a.val);
    }
    bool operator>=(const fixed6& a) const {
        return (val >= a.val);
    }
    bool operator==(const fixed6& a) const {
        return (val == a.val);
    }
    fixed6& operator=(const float& a){
        val = (int8_t) round(a * (1 << 7));
        return *this;
    }
    fixed6 operator+(const float& a) const{
        return fixed6(val+(int8_t) round(a * (1 << 7)));
    }
    fixed6 operator-(const float& a) const{
        return fixed6(val-(int8_t) round(a * (1 << 7)));
    }
    fixed6 operator*(const float& a) const{
        return fixed6((val*(int8_t) round(a *(1 << 7))) >> 7);//(int8_t) round(a * (1 << 6)));
    }
    fixed6 operator/(const float& a) const{
        return fixed6(val/(int8_t) round(a * (1 << 7)));
    }
};

fixed6 operator+(const float& a, const fixed6& b) { return b + a; }
fixed6 operator-(const float& a, const fixed6& b) { return b - a; }
fixed6 operator*(const float& a, const fixed6& b) { return b * a; }
fixed6 operator/(const float& a, const fixed6& b) { return b / a; }

std::ostream& operator<<(std::ostream& os, fixed6 p) {
    os << (float) p.val / (float) (1 << 7);
    return os; 
}

#endif
