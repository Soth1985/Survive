#pragma once

//see Modern C++ Design: Generic Programming and Design Patterns Applied for details

namespace Survive
{

class NullType{};

template <class T, class U>
struct Typelist
{
   typedef T Head;
   typedef U Tail;
};

template <class TList, unsigned int index> struct TypeAt;

template <class Head, class Tail, unsigned int i>
struct TypeAt<Typelist<Head, Tail>, i>
{
   typedef typename TypeAt<Tail, i - 1>::Result Result;
};

template <class Head, class Tail>
struct TypeAt< Typelist<Head, Tail>, 0 >
{
   typedef Head Result;
};


#define SURVIVE_TYPELIST_0() Survive::Typelist<Survive::NullType, Survive::NullType>

#define SURVIVE_TYPELIST_1(T1) Survive::Typelist<T1, Survive::NullType>

#define SURVIVE_TYPELIST_2(T1, T2) Survive::Typelist<T1, SURVIVE_TYPELIST_1(T2) >

#define SURVIVE_TYPELIST_3(T1, T2, T3) Survive::Typelist<T1, SURVIVE_TYPELIST_2(T2, T3) >

#define SURVIVE_TYPELIST_4(T1, T2, T3, T4) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_3(T2, T3, T4) >

#define SURVIVE_TYPELIST_5(T1, T2, T3, T4, T5) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_4(T2, T3, T4, T5) >

#define SURVIVE_TYPELIST_6(T1, T2, T3, T4, T5, T6) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_5(T2, T3, T4, T5, T6) >

#define SURVIVE_TYPELIST_7(T1, T2, T3, T4, T5, T6, T7) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_6(T2, T3, T4, T5, T6, T7) >

#define SURVIVE_TYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_7(T2, T3, T4, T5, T6, T7, T8) >

#define SURVIVE_TYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9) >

#define SURVIVE_TYPELIST_10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_9(T2, T3, T4, T5, T6, T7, T8, T9, T10) >

#define SURVIVE_TYPELIST_11(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_10(T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) >

#define SURVIVE_TYPELIST_12(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_11(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12) >

#define SURVIVE_TYPELIST_13(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_12(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13) >

#define SURVIVE_TYPELIST_14(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_13(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14) >

#define SURVIVE_TYPELIST_15(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_14(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15) >

#define SURVIVE_TYPELIST_16(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_15(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16) >

#define SURVIVE_TYPELIST_17(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_16(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17) >

#define SURVIVE_TYPELIST_18(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_17(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18) >

#define SURVIVE_TYPELIST_19(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_18(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19) >

#define SURVIVE_TYPELIST_20(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_19(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) >

#define SURVIVE_TYPELIST_21(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_20(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) >

#define SURVIVE_TYPELIST_22(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_21(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) >

#define SURVIVE_TYPELIST_23(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_22(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) >

#define SURVIVE_TYPELIST_24(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_23(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) >

#define SURVIVE_TYPELIST_25(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_24(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25) >

#define SURVIVE_TYPELIST_26(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_25(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26) >

#define SURVIVE_TYPELIST_27(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_26(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27) >

#define SURVIVE_TYPELIST_28(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_27(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28) >

#define SURVIVE_TYPELIST_29(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_28(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29) >

#define SURVIVE_TYPELIST_30(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_29(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) >

#define SURVIVE_TYPELIST_31(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_30(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) >

#define SURVIVE_TYPELIST_32(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_31(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) >

#define SURVIVE_TYPELIST_33(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_32(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) >

#define SURVIVE_TYPELIST_34(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_33(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) >

#define SURVIVE_TYPELIST_35(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_34(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35) >

#define SURVIVE_TYPELIST_36(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_35(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36) >

#define SURVIVE_TYPELIST_37(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_36(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37) >

#define SURVIVE_TYPELIST_38(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_37(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38) >

#define SURVIVE_TYPELIST_39(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_38(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39) >

#define SURVIVE_TYPELIST_40(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_39(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) >

#define SURVIVE_TYPELIST_41(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_40(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) >

#define SURVIVE_TYPELIST_42(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_41(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) >

#define SURVIVE_TYPELIST_43(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_42(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) >

#define SURVIVE_TYPELIST_44(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_43(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) >

#define SURVIVE_TYPELIST_45(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_44(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45) >

#define SURVIVE_TYPELIST_46(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_45(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46) >

#define SURVIVE_TYPELIST_47(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_46(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47) >

#define SURVIVE_TYPELIST_48(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_47(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48) >

#define SURVIVE_TYPELIST_49(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48, T49) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_48(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48, T49) >

#define SURVIVE_TYPELIST_50(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50) \
    Survive::Typelist<T1, SURVIVE_TYPELIST_49(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50) >

}//Survive